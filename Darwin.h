#include <cassert>	// assert
#include <string>	// string
#include <vector>	// program
#include <iostream> // endl, istream, ostream
#include <sstream>  // istringstream
#include <cstdlib>	// rand


using namespace std;

class Species{
private:
	// -----
	// _name
	// -----
	/**
	 * name of the species as a char. 
	 * Usually the initial of the specie's name
	 */
	char _name;

	// ------
	// _steps
	// ------
	/**
	 * decoded program of a specie
	 */
	vector<int> _steps;
public:
	// ----------------------------
	// Species' default constructor
	// ----------------------------
	/**
	 * If no name is given, set that species name to '.', which means it's an empty space.
	 */
	Species();
	// -------------------------
	// Species' char constructor
	// -------------------------
	/**
	 * Set that species name to name, which is just a character.
	 */
	Species(char name);

	// ------------------------
	// Species' copy assignment
	// ------------------------
	/**
	 * Set this species to be equivalent to Species s.
	 */
	Species& operator=(const Species& s);
	// -----------------
	// Comparison method
	// -----------------
	/**
	 * Check whether the two species are equivalent
	 */
	bool operator==(const Species& s);
	// --------------------
	// addstep(string line)
	// --------------------
	/**
	 * Add a single step, represented in string, to the species' program.
	 */
	void addstep(string line);
	// --------------
	// getstep(int i)
	// --------------
	/**
	 * Get the step at index i in the program of this species.
	 */
	const int& getstep(int i) const;
	// ---------
	// getname()
	// ---------
	/**
	 * Get the name of this species.
	 */
	const char getname() const;
	// -------------
	// getprogsize()
	// -------------
	/**
	 * Get the size of this species' program.
	 */
	int getprogsize() const;
};

class Creature{
private:
	/**
	 * Contains the species of a creature
	 */
	Species _sp;
public:
	/**
	 * Saves the direction of a creature
	 * 0 = West, 1 = North, 2 = East, 3 = South.
	 * Reset if value < 0 or value > 3
	 */
	int _direc = 0;
	/**
	 * Program counter of a creature
	 * Reset to 0 if value > number of steps available in the specie
	 */
	int _pc = 0;
	/**
	 * Tells whether the creature has been acted in the run
	 */
	bool finish = false;

	/**
	 * Construct a Creature of Species sp facing direc.
	 * The default direction is 0(West) and the default species is '.'(empty ground). 
	 */
	Creature(int direc = 0, const Species& sp = Species());
	/**
	 * Construct a Creature that's equivalent in value to Creature c.
	 */
	Creature(const Creature& c);
	/**
	 * Set this Creature to be equivalent to Creature rhs.
	 */
	Creature& operator=(const Creature& rhs);
	/**
	 * Change the direction of creature to left.
	 */
	void turn_left();
	/**
	 * Change the direction of creature to right.
	 */
	void turn_right();
	/**
	 * If the neighbor is not empty nor a wall, change its species.
	 */
	void infect(Creature& c) const;
	/**
	 * Get the species of this creature.
	 */
	const char getspecie() const;
	/**
	 * Check whether the neighbor belongs to another species.
	 */
	bool isenemy(const Creature* target, bool wall);
	/**
	 * Check whether the neighbor is empty, which is represented as a '.'
	 */
	bool isempty(const Creature* target, bool wall);
	/**
	 * Do the action/control step on the creature.
	 */
	int my_turn(const bool* iswall, Creature* neighbor[]);
	/**
	 * Update/reset the pc after the action is finished.
	 */
	void go(int i);

};

class World{
private:
	/**
	 * Save the size of the world
	 */
	int r, c;
	/**
	 * Actual 2D array that represent the world
	 */
	Creature** darwin;
public:
	/**
	 * Construct a world of size r by c
	 */
	World(int r, int c);
	/**
	 * Since we are using heap array to store the 2D array that represent our world, we would like to free the memory afterward.
	 */
	~World();
	/**
	 * Gives the Creature on space (x,y) a turn to act.
	 */
	void give_turn(int x, int y);
	/**
	 * Add Creature c onto space (x,y).
	 * Replaces the existing Creature if there's one.
	 */
	void addCreature(Creature c, int x, int y);
	/**
	 * Run the world for m round and print the output to out.
	 */
	void run(int m, ostream& out);
	/**
	 * Print the formatted grid to out.
	 * Turn indicate the current round.
	 */
	void print_grid(int turn, ostream& out);
};