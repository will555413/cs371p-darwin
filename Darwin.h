#include <cassert>	// assert
#include <string>	// string
#include <vector>	// program
#include <iostream> // endl, istream, ostream
#include <sstream>  // istringstream
#include <cstdlib>	// rand


using namespace std;

class Species{
private:
	/* name of the species as a char. 
	 * Usually the initial of the specie's name
	 */
	char _name;
	/* decoded program of a specie
	 */
	vector<int> _steps;
public:
	Species();
	Species(char name);

	Species& operator=(const Species& s);
	bool operator==(const Species& s);
	void addstep(string line);
	const int& getstep(int i) const;
	const char getname() const;
	int getprogsize() const;
};

class Creature{
private:
	/* Contains the species of a creature
	 */
	Species _sp;
public:
	/* save the direction of a creature
	 * 0 = North, 1 = East, 2 = South, 3 = West.
	 * reset if value < 0 or value > 3
	 */
	int _direc = 0;
	/* program counter of a creature
	 * reset to 0 if value > number of steps available in the specie
	 */
	int _pc = 0;

	Creature(int direc = 0, const Species& sp = Species());
	Creature(const Creature& c);
	Creature& operator=(const Creature& rhs);
	void turn_left();
	void turn_right();
	void infect(Creature& c) const;
	const char getspecie() const;
	bool isenemy(const Creature* target, bool wall);
	bool isempty(const Creature* target, bool wall);
	int my_turn(const bool* iswall, Creature* neighbor[]);
	void go(int i);
	bool finish = false;
};

class World{
private:
	/* save the size of the world
	 */
	int r, c;
	/* actual 2D array that represent the world
	 */
	Creature** darwin;
public:
	World(int r, int c);
	~World();
	void give_turn(int x, int y);
	void addCreature(Creature c, int x, int y);
	void run(int m, ostream& out);
	void print_grid(int turn, ostream& out);
};