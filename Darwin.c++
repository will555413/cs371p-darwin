#include "Darwin.h"	// header file

using namespace std;

// ----------------------
// Creature class methods
// ----------------------

Creature::Creature():
	_sp(){}

Creature::Creature(const Creature& c):
	_direc(c._direc),
	_pc(c._pc),
	_sp(c._sp){}

Creature& Creature::operator=(const Creature& rhs){
	_sp = rhs._sp;
	_direc = rhs._direc;
	_pc = rhs._pc;
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
// replace current specie with new specie s
void Creature::get_infected(const Creature& c){
	// copy assignment for Species?
	_sp = c._sp;
}
// add 1 to _pc; reset when _pc > _sp.steps.size()
const string& Creature::getstep() const{
	int old_pc = _pc;
	
	return _sp.getstep(old_pc);
}

const char& Creature::getname() const{
	return _sp.getname();
}

const int& Creature::getdir() const{
	return _direc;
}

bool Creature::isenemy(const Creature& target)
{
	return !(_sp == target._sp);
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
Species::Species(char name, vector<string> steps):
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

void Species::addstep(string line){
	_steps.push_back(line);
}

const string& Species::getstep(int i) const{
	return _steps[i];
}

const char& Species::getname() const{
	return _name;
}

int Species::getprogsize() const{
	return _steps.size();
}

// -------------------
// World class methods
// -------------------

World::World(int r, int c){
	this->r = r; 
	this->c = c;
	darwin = new Creature[r][c];
}
World::~World(){
	delete [] darwin;
}

// implement hop/infect in interpret
// implement all controls
void World::interpret(int x, int y, string step){
	Creature* north, *east, *south, *west;
	if(x-1 >= 0)
		north = &darwin[x-1][y];
	if(y+1 <= c)
		east = &darwin[x][y+1];
	if(x+1 <= r)
		south = &darwin[x+1][y];
	if(y-1>=0)
		west = &darwin[x][y-1];
	Creature& current = darwin[x][y];

	while(true){
		if(step.find("hop")!=string::npos)
		{
			Creature temp;
			temp = current;
			if(current.getdir()==0 && x-1 >= 0 && isempty(*north)){
				current = *north;
				*north = temp;
				// current = Creature();
			}
			else if(current.getdir()==1 && y+1 <= c && isempty(*east)){
				current = *east;
				*east = temp;
				// current = Creature();
			}
			else if(current.getdir()==2 && x+1 <= r && isempty(*south)){
				current = *south;
				*south = temp;
				// current = Creature();
			}
			else if(current.getdir()==3 && y-1>=0 && isempty(*west)){
				current = *west;
				*west = temp;
				// current = Creature();
			}
			current.go(-1);
			break;
		}
		else if(step.find("left")!=string::npos)
		{
			current.turn_left();
			current.go(-1);
			break;
		}
		else if(step.find("right")!=string::npos)
		{
			current.turn_right();
			current.go(-1);
			break;
		}
		else if(step.find("infect")!=string::npos)
		{
			if(current.getdir()==0 && x-1 >= 0 && !isempty(*north) && current.isenemy(*north)){
				(*north).get_infected(current);
				// current = Creature();
			}
			else if(current.getdir()==1 && y+1 <= c && !isempty(*east) && current.isenemy(*east)){
				(*east).get_infected(current);
				// current = Creature();
			}
			else if(current.getdir()==2 && x+1 <= r && !isempty(*south) && current.isenemy(*south)){
				(*south).get_infected(current);
				// current = Creature();
			}
			else if(current.getdir()==3 && y-1>=0 && !isempty(*west) && current.isenemy(*west)){
				(*west).get_infected(current);
				// current = Creature();
			}
			current.go(-1);
			break;
		}
		
		istringstream line(step);
		int i = 0;
		line>>step>>i;
		if(step.find("if_empty")!=string::npos)
		{
			if(current.getdir()==0 && x-1 >= 0 && isempty(*north)){
				current.go(i);
			}
			else if(current.getdir()==1 && y+1 <= c && isempty(*east)){
				current.go(i);
			}
			else if(current.getdir()==2 && x+1 <= r && isempty(*south)){
				current.go(i);
			}
			else if(current.getdir()==3 && y-1>=0 && isempty(*west)){
				current.go(i);
			}
			else
				current.go(-1);
		}
		else if(step.find("if_wall")!=string::npos)
		{
			if(current.getdir()==0 && x-1 < 0){
				current.go(i);
			}
			else if(current.getdir()==1 && y+1 > c){
				current.go(i);
			}
			else if(current.getdir()==2 && x+1 > r){
				current.go(i);
			}
			else if(current.getdir()==3 && y-1 < 0){
				current.go(i);
			}
			else
				current.go(-1);
		}
		else if(step.find("if_random")!=string::npos)
		{
			if(rand()%2==1)
				current.go(i);
			else
				current.go(-1);
		}
		else if(step.find("if_enemy")!=string::npos)
		{
			if(current.getdir()==0 && x-1 >= 0 && !isempty(*north) && current.isenemy(*north)){
				current.go(i);
			}
			else if(current.getdir()==1 && y+1 <= c && !isempty(*east) && current.isenemy(*east)){
				current.go(i);
			}
			else if(current.getdir()==2 && x+1 <= r && !isempty(*south) && current.isenemy(*south)){
				current.go(i);
			}
			else if(current.getdir()==3 && y-1>=0 && !isempty(*west) && current.isenemy(*west)){
				current.go(i);
			}
			else
				current.go(-1);
		}
		else if(step.find("go")!=string::npos)
		{
			current.go(i);
		}
	}

}

bool World::isempty(Creature x){
	if(x.getname() =='.')
		return true;
	return false;
}

// add a creature onto the specified coordinate
void World::addCreature(Creature c, int x, int y){
	darwin[x][y] = c;
}
// run the world for m rounds and print each grid
void World::run(int m){
	while(m>0){
		// give a turn for each creature on the maps
		for(int i=0;i<r;++i){
			for(int j=0;j<c;++j){
				if(darwin[i][j].getname()=='.')
					continue;
				else
					interpret(i,j,darwin[i][j].getstep());
			}
		}
		print_grid(m, cout);
		--m;
	}
}
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
				out<<darwin[i][j].getname();
		}
		out<<endl;
	}
}