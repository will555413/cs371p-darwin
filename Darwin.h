#include <cassert>	// assert
#include <string>	// string
#include <vector>	// program
#include <iostream> // endl, istream, ostream
#include <sstream>  // istringstream
#include <cstdlib>	// rand


using namespace std;

class Species{
// variables
private:
	char _name;
	vector<int> _steps;
public:
	Species();
	Species(char name, const vector<int>& steps = vector<int>());
	Species(const Species& rhs);

	Species& operator=(const Species& s);
	bool operator==(const Species& s);
	void addstep(string line);
	const int& getstep(int i) const;
	const char& getname() const;
	int getprogsize() const;
};

class Creature{
// variables
private:
	/* save the direction of a creature
	 * 0 = North, 1 = East, 2 = South, 3 = West.
	 * reset if value < 0 or value > 3
	 */
	int _direc = 0;
	/* program counter of a creature
	 * reset to 0 if value > number of steps available in the specie
	 */
	int _pc = 0;
	/* Contains the species of a creature
	 */
	Species _sp;
public:
	Creature(int direc = 0, const Species& sp = Species());
	Creature(const Creature& c);
	// Creature(const Species& sp);
	Creature& operator=(const Creature& rhs);
	void turn_left();
	void turn_right();
	// replace current specie with new specie s
	void infect(Creature& c) const;
	// add 1 to _pc; reset when _pc > _sp.steps.size()
	const char& getspecie() const;
	bool isenemy(const Creature& target, bool wall);
	bool isempty(const Creature& target, bool wall);
	int my_turn(const bool* iswall, Creature** neighbor);
	void go(int i);
	//void hop();
	// void infect();
};

class World{
// variables
private:
	int r, c;
	Creature** darwin;
public:
	World(int r, int c);
	~World();

	void interpret(int x, int y);
	// implement hop/infect in interpret
	// implement all controls
	void addCreature(Creature c, int x, int y);
	// run the world for m steps and print each grid
	void run(int m);
	void print_grid(int turn, ostream& out);
};