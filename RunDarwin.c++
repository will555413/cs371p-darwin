// -----------------------------
// projects/darwin/RunDarwin.c++
// Copyright (C) 2015
// Glenn P. Downing
// -----------------------------

// --------
// includes
// --------

#include <cassert>   // assert
#include <cstdlib>   // rand, srand
#include <iostream>  // cout, endl
#include <stdexcept> // invalid_argument, out_of_range
#include "Darwin.h" // header file

// ----
// main
// ----

int main () {
    using namespace std;

    // ----
    // food
    // ----

    /*
     0: left
     1: go 0
    */
    
    Species food('f');
    // vector<string> prog = {"left", "go 0"};
    food.addstep("left");
    food.addstep("go 0");

    // ------
    // hopper
    // ------

    /*
     0: hop
     1: go 0
    */

    // prog = {"hop", "go 0"};
    Species hopper('h');
    hopper.addstep("hop");
    hopper.addstep("go 0");

    // -----
    // rover
    // -----

    /*
     0: if_enemy 9
     1: if_empty 7
     2: if_random 5
     3: left
     4: go 0
     5: right
     6: go 0
     7: hop
     8: go 0
     9: infect
    10: go 0
    */

    // prog = {"if_enemy 9", "if_empty 7", "if_random 5", "left", "go 0"
            // "right","go 0","hop","go 0","infect", "go 0"};
    Species rover('r');
    rover.addstep("if_enemy 9");
    rover.addstep("if_empty 7");
    rover.addstep("if_random 5");
    rover.addstep("left");
    rover.addstep("go 0");
    rover.addstep("right");
    rover.addstep("go 0");
    rover.addstep("hop");
    rover.addstep("go 0");
    rover.addstep("infect");
    rover.addstep("go 0");

    // ----
    // trap
    // ----

    /*
     0: if_enemy 3
     1: left
     2: go 0
     3: infect
     4: go 0
    */

    // prog = {"if_enemy 3", "left", "go 0", "infect", "go 0"};
    Species trap('t');
    trap.addstep("if_enemy 3");
    trap.addstep("left");
    trap.addstep("go 0");
    trap.addstep("infect");
    trap.addstep("go 0");

    // ----------
    // darwin 8x8
    // ----------

    cout << "*** Darwin 8x8 ***" << endl;
    /*
    8x8 Darwin
    Food,   facing east,  at (0, 0)
    Hopper, facing north, at (3, 3)
    Hopper, facing east,  at (3, 4)
    Hopper, facing south, at (4, 4)
    Hopper, facing west,  at (4, 3)
    Food,   facing north, at (7, 7)
    Simulate 5 moves.
    Print every grid.
    */
    World d1(8,8);
    d1.addCreature(Creature(1,food),0,0);
    d1.addCreature(Creature(0,hopper),3,3);
    d1.addCreature(Creature(1,hopper),3,4);
    d1.addCreature(Creature(2,hopper),4,4);
    d1.addCreature(Creature(3,hopper),4,3);
    d1.addCreature(Creature(0,food),7,7);
    d1.run(5);


    // ----------
    // darwin 7x9
    // ----------

    cout << "*** Darwin 7x9 ***" << endl;
    srand(0);
    /*
    7x9 Darwin
    Trap,   facing south, at (0, 0)
    Hopper, facing east,  at (3, 2)
    Rover,  facing north, at (5, 4)
    Trap,   facing west,  at (6, 8)
    Simulate 5 moves.
    Print every grid.
    */
    World d2(7,9);
    d2.addCreature(Creature(2,trap),0,0);
    d2.addCreature(Creature(1,hopper),3,2);
    d2.addCreature(Creature(0,rover),5,4);
    d2.addCreature(Creature(3,trap),6,8);
    d2.run(5);

    // ------------
    // darwin 72x72
    // without best
    // ------------

    cout << "*** Darwin 72x72 without Best ***" << endl;
    srand(0);
    /*
    Randomly place the following creatures facing randomly.
    Call rand(), mod it with 5184 (72x72), and use that for the position
    in a row-major order grid.
    Call rand() again, mod it with 4 and use that for it's direction with
    the ordering: west, north, east, south.
    Do that for each kind of creature.
    10 Food
    10 Hopper
    10 Rover
    10 Trap
    Simulate 1000 moves.
    Print the first 10 grids          (i.e. 0, 1, 2...9).
    Print every 100th grid after that (i.e. 100, 200, 300...1000).
    */

    // ------------
    // darwin 72x72
    // with best
    // ------------

    cout << "*** Darwin 72x72 with Best ***" << endl;
    srand(0);
    /*
    Randomly place the following creatures facing randomly.
    Call rand(), mod it with 5184 (72x72), and use that for the position
    in a row-major order grid.
    Call rand() again, mod it with 4 and use that for it's direction with
    the ordering: 0:west, 1:north, 2:east, 3:south.
    Do that for each kind of creature.
    10 Food
    10 Hopper
    10 Rover
    10 Trap
    10 Best
    Simulate 1000 moves.
    Best MUST outnumber ALL other species for the bonus pts.
    Print the first 10 grids          (i.e. 0, 1, 2...9).
    Print every 100th grid after that (i.e. 100, 200, 300...1000).
    */

    return 0;}
