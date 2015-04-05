#include "Darwin.h"	// header file

using namespace std;

// ----------------------
// Creature class methods
// ----------------------
Creature::Creature(const Creature& c):
	_direc(c._direc),
	_pc(c._pc),
	_sp(c._sp){}

Creature::Creature(int direc, const Species& sp):
	_direc(direc),
	_sp(sp){}

Creature& Creature::operator=(const Creature& rhs){
	_sp = rhs._sp;
	_direc = rhs._direc;
	_pc = rhs._pc;
	finish = rhs.finish;
	return *this;
}

void Creature::turn_left(){
	++_direc;
	if(_direc > 3)
		_direc = 0;
}
void Creature::turn_right(){
	--_direc;
	if(_direc < 0)
		_direc = 3;
}
// this Creature will infect Creature c using its species
void Creature::infect(Creature& c) const{
	// copy assignment for Species?
	c._sp = _sp;
}

const char Creature::getspecie() const{
	return _sp.getname();
}

bool Creature::isenemy(const Creature* target, bool wall){
	return target != NULL && (*target).getspecie() !='.' && !wall && !(_sp == (*target)._sp);
}

bool Creature::isempty(const Creature* target, bool wall){
	// cout<<"name: "<<(target.getspecie())<<"\nis this a wall: "<<wall<<endl;
	return target != NULL && (*target).getspecie() =='.' && !wall;
}

int Creature::my_turn(const bool* iswall, Creature* neighbor[]){
	while(1){
		int inst = _sp.getstep(_pc);
		// cout<<"inst"<<inst<<endl;
		if(inst%10>=5){// if instruction is a control
			if(inst%10==5 && isempty(neighbor[_direc], iswall[_direc]))
				go(inst/10);
			else if(inst%10==6 && iswall[_direc])
				go(inst/10);
			else if(inst%10==7 && rand()%2==1)
				go(inst/10);
			else if(inst%10==8 && isenemy(neighbor[_direc], iswall[_direc]))
				go(inst/10);
			else if(inst%10==9)
				go(inst/10);
			else
				go(-1);
			continue;
		}
		else if(inst%10<=4){// if instruction is an action
			if(inst%10==1 && isempty(neighbor[_direc], iswall[_direc])){
				go(-1);
				return _direc;
			}
			else if(inst%10==2){
				turn_left();
				go(-1);
				return -1;
			}
			else if(inst%10==3){
				turn_right();
				go(-1);
				return -1;
			}
			else if(inst%10==4 && isenemy(neighbor[_direc], iswall[_direc])){
				infect(*neighbor[_direc]);
				go(-1);
				return -1;
			}
			return -1;
		}
	}
}

void Creature::go(int i){
	if(i==-1){
		++_pc;
		if(_pc>=_sp.getprogsize())
			_pc = 0;
	}
	else
	{
		assert(i>=0 && i<_sp.getprogsize());
		_pc=i;
	}
	
}

// ---------------------
// Species class methods
// ---------------------

Species::Species():
	_name('.'){}
Species::Species(char name, const vector<int>& steps):
	_name(name), 
	_steps(steps){}
Species::Species(const Species& rhs):
	_name(rhs._name),
	_steps(rhs._steps){}

Species& Species::operator=(const Species& s){
	_name = s._name;
	_steps = s._steps;
	return *this;
}

bool Species::operator==(const Species& s){
	return _name == s._name;
}

// Decode the program step into a integer
// Ones digit being the type of instruction: 1=hop, 2=left, etc.
// Digits beyond ones will be the step it pointed to: "go 10" = 109, 
void Species::addstep(string l){
	istringstream line(l);
	int i = 0;
	string step;
	line>>step;
	if(step=="hop"){i=1;}
	else if(step=="left"){i=2;}
	else if(step=="right"){i=3;}
	else if(step=="infect"){i=4;}
	else if(step=="if_empty"){
		line>>i;
		i=i*10+5;
	}
	else if(step=="if_wall"){
		line>>i;
		i=i*10+6;
	}
	else if(step=="if_random"){
		line>>i;
		i=i*10+7;
	}
	else if(step=="if_enemy"){
		line>>i;
		i=i*10+8;
	}
	else if(step=="go"){
		line>>i;
		i=i*10+9;
	}
	_steps.push_back(i);
}

const int& Species::getstep(int i) const{
	return _steps[i];
}

const char Species::getname() const{
	return _name;
}

int Species::getprogsize() const{
	return _steps.size();
}

// -------------------
// World class methods
// -------------------

// -----
// World
// -----
/* Constructor of World.
 * takes r and c that represent the size of the world
 * there's no default constructor since a world can't be empty (black hole?)
 */
World::World(int r, int c){
	this->r = r; 
	this->c = c;
	darwin = new Creature*[r];
	for(int i=0;i<r;++i)
		darwin[i] = new Creature[c];
}

// ----------
// destructor
// ----------
/* We set up the world as a 2D heap array so the size can be later specified in the constructor.
 * therefore we need a destructor to free the array afterward.
 */
World::~World(){
	for(int i=0;i<r;++i)
		delete [] darwin[i];
	delete [] darwin;
}

// ---------
// give_turn
// ---------
/* give the Creature on (x,y) a turn.
 * receive a int fron my_turn() that indicate the direction of movement; if -1, don't move.
 */
void World::give_turn(int x, int y){
	assert(x >= 0);
	assert(y >= 0);
	assert(x < r);
	assert(y < c);

	bool iswall[4] = {false};
	if(x-1 < 0) {iswall[0]=true;}
	if(y+1 >= c) {iswall[1]=true;}
	if(x+1 >= r) {iswall[2]=true;}
	if(y-1 < 0) {iswall[3]=true;}

	Creature& current = darwin[x][y];

	Creature* neighbor[4];
	
	neighbor[0] = !iswall[0] ? &darwin[x-1][y] : NULL;
	neighbor[1] = !iswall[1] ? &darwin[x][y+1] : NULL;
	neighbor[2] = !iswall[2] ? &darwin[x+1][y] : NULL;
	neighbor[3] = !iswall[3] ? &darwin[x][y-1] : NULL;

	// A Creature act more than twice a turn because its new position is at "next-to-act"
	// Proposal 1: create a 2D bool array that save the acted-or-not value; value moved with the Creature
	// Proposal 2: put additinal bool variable in Creature class. Use vector to save all acted Creatures and reset theor acted value at the end.


	int code = current.my_turn(iswall, neighbor);
	// then use code to execute appropriate action
	current.finish = true;
	if(code >= 0){
		// cout<<"code"<<code<<endl;
		assert(code<=4);
		if(code == 0){
			assert(x-1 >= 0);
			darwin[x-1][y] = current;
			current = Creature();
		} else if(code == 1){
			assert(y+1 < c);
			darwin[x][y+1] = current;
			current = Creature();
		} else if(code == 2){
			assert(x+1 < r);
			darwin[x+1][y] = current;
			current = Creature();
		} else if(code == 3){
			assert(y-1 >= 0);
			darwin[x][y-1] = current;
			current = Creature();
		}
	}
	// current.finish = true;
}

// -----------
// addCreature
// -----------
/* add a creature onto the specified coordinate (x,y)
 */
void World::addCreature(Creature c, int x, int y){
	darwin[x][y] = c;
}

// ---
// run
// ---
/* run the world for m rounds.
 * print the grid in its initial state and a grid after each round.
 */
void World::run(int m){
	int t = 0;
	// initial state
	print_grid(t, cout);
	while(t<=m){
		// give a turn for each creature on the maps
		vector<Creature*> creatures; 
		for(int i=0;i<r;++i){
			for(int j=0;j<c;++j){
				if(darwin[i][j].getspecie()!='.' && !darwin[i][j].finish){
					// cout<<"we are at?"<<i<<","<<j<<endl;
					creatures.push_back(&darwin[i][j]);
					give_turn(i,j);
				}
			}
		}
		for(Creature* temp: creatures)
			(*temp).finish = false;
		++t;
		print_grid(t, cout);
	}
}

// ----------
// print_grid
// ----------
/* iterate through each space in the grid and print out it out as a 2D array. 
 */
void World::print_grid(int turn, ostream& out){
	out<<"Turn = "<<turn<<endl;
	for(int i=-1;i<r;++i){
		if(i==-1)
			out<<"  ";
		else
			out<<i%10<<" ";

		for(int j=0;j<c;++j){
			if(i == -1){
				out<<j%10;
				continue;
			}
			else
				out<<darwin[i][j].getspecie();
		}
		out<<endl;
	}
}