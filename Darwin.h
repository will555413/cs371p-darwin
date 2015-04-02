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
	vector<string> _steps;
public:
	Species();
	Species(char name, vector<string> steps);
	Species(const Species& rhs);

	Species& operator=(const Species& s);
	bool operator==(const Species& s);
	void addstep(string line);
	const string& getstep(int i) const;
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
	Creature();
	Creature(const Creature& c);
	// Creature(const Species& sp);
	Creature& operator=(const Creature& rhs);
	void turn_left();
	void turn_right();
	// replace current specie with new specie s
	void get_infected(const Creature& c);
	// add 1 to _pc; reset when _pc > _sp.steps.size()
	const string& getstep() const;
	const char& getname() const;
	const int& getdir() const;
	bool isenemy(const Creature& target);
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

	void interpret(int x, int y, string step);
	// implement hop/infect in interpret
	// implement all controls
	bool isempty(Creature x);
	void addCreature(Creature c, int x, int y);
	// run the world for m steps and print each grid
	void run(int m);
	void print_grid(int turn, ostream& out);
};