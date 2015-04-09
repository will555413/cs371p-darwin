#include <iostream> // cout, endl
#include <sstream>  // istringtstream, ostringstream
#include <string>   // string
#include <utility>  // pair
#include <random>

#include "gtest/gtest.h"
#include "Darwin.h"

using namespace std;

TEST(Darwin, Creature_Constructor_1) {
    Creature c;
    ASSERT_EQ(c.getspecie(), '.');
    ASSERT_EQ(c._direc, 0);
}

TEST(Darwin, Creature_Constructor_2) {
    Species food('f');
    Creature c(0, food);
    ASSERT_EQ(c.getspecie(), 'f');
    ASSERT_EQ(c._direc, 0);
}

TEST(Darwin, Creature_Constructor_3) {
    Species hopper('h');
    Creature c(1, hopper);
    ASSERT_EQ(c.getspecie(), 'h');
    ASSERT_EQ(c._direc, 1);
}

TEST(Darwin, Creature_Constructor_4) {
    Creature c1;
    Creature c2(c1);
    ASSERT_TRUE(c1.getspecie()==c2.getspecie());
    ASSERT_TRUE(c1._direc==c2._direc);
}

TEST(Darwin, Creature_Constructor_5) {
    Species hopper('h');
    Creature c1(1, hopper);
    Creature c2(c1);
    ASSERT_TRUE(c1.getspecie()==c2.getspecie());
    ASSERT_TRUE(c1._direc==c2._direc);
}

TEST(Darwin, Creature_Constructor_6) {
    Species hopper('h');
    Creature c1(1, hopper);
    Creature c2(static_cast<const Creature>(c1));
    c1.turn_left();
    ASSERT_TRUE(c1.getspecie()==c2.getspecie());
    ASSERT_TRUE(c1._direc!=c2._direc);
}

TEST(Darwin, Creature_getspecie) {
    Species food('f');
    Creature c(0, food);
    ASSERT_EQ(c.getspecie(), 'f');
}

TEST(Darwin, Creature_Equal_1) {
    Species hopper('h');
    Creature c1(1, hopper);
    Creature c2;
    ASSERT_TRUE(c1.getspecie()!=c2.getspecie());
    ASSERT_TRUE(c1._direc!=c2._direc);
    c2 = c1;
    ASSERT_TRUE(c1.getspecie()==c2.getspecie());
    ASSERT_TRUE(c1._direc==c2._direc);
}

TEST(Darwin, Creature_Equal_2) {
    Species food('f');
    Species hopper('h');
    Creature c1(1, hopper);
    Creature c2(2, food);
    ASSERT_TRUE(c1.getspecie()!=c2.getspecie());
    ASSERT_TRUE(c1._direc!=c2._direc);
    c2 = c1;
    ASSERT_TRUE(c1.getspecie()==c2.getspecie());
    ASSERT_TRUE(c1._direc==c2._direc);
}

TEST(Darwin, Creature_Turn_Left_1) {
    Creature c(0);
    c.turn_left();
    ASSERT_EQ(c._direc, 3);
}

TEST(Darwin, Creature_Turn_Left_2) {
    Creature c(1);
    c.turn_left();
    ASSERT_EQ(c._direc, 0);
}

TEST(Darwin, Creature_Turn_Left_3) {
    Creature c(2);
    c.turn_left();
    ASSERT_EQ(c._direc, 1);
}

TEST(Darwin, Creature_Turn_Right_1) {
    Creature c(0);
    c.turn_right();
    ASSERT_EQ(c._direc, 1);
}

TEST(Darwin, Creature_Turn_Right_2) {
    Creature c(1);
    c.turn_right();
    ASSERT_EQ(c._direc, 2);
}

TEST(Darwin, Creature_Turn_Right_3) {
    Creature c(3);
    c.turn_right();
    ASSERT_EQ(c._direc, 0);
}

TEST(Darwin, Creature_Infect_1) {
    Species food('f');
    Species rover('r');

    Creature c1(0, food);
    Creature c2(0, rover);

    c2.infect(c1);
    ASSERT_EQ(c1.getspecie(), c2.getspecie());
}

TEST(Darwin, Creature_Infect_2) {
    Species hopper('h');
    Species rover('r');

    Creature c1(0, hopper);
    Creature c2(0, rover);

    c2.infect(c1);
    ASSERT_EQ(c1.getspecie(), c2.getspecie());
}

TEST(Darwin, Creature_Infect_3) {
    Species food('f');
    Species hopper('h');

    Creature c1(0, food);
    Creature c2(0, hopper);

    c2.infect(c1);
    ASSERT_EQ(c1.getspecie(), c2.getspecie());
}

TEST(Darwin, Creature_Isenemy_1) {
    Species food('f');
    Species rover('r');

    Creature c1(0, food);
    Creature c2(0, rover);

    ASSERT_TRUE(c2.isenemy(&c1, false));
}

TEST(Darwin, Creature_Isenemy_2) {
    Species rover('r');

    Creature c1;
    Creature c2(0, rover);

    ASSERT_FALSE(c2.isenemy(&c1, false));
}

TEST(Darwin, Creature_Isenemy_3) {
    Species rover('r');
    Creature c2(0, rover);

    ASSERT_FALSE(c2.isenemy(NULL, true));
}

TEST(Darwin, Creature_Isempty_1) {
    Creature c1;
    ASSERT_TRUE(c1.isempty(&c1, false));
}

TEST(Darwin, Creature_Isempty_2) {
    Species rover('r');
    Creature c2(0, rover);

    ASSERT_FALSE(c2.isempty(&c2, false));
}

TEST(Darwin, Creature_Isempty_3) {
    Species rover('r');
    Creature c2(0, rover);
    ASSERT_FALSE(c2.isempty(NULL, true));
}

TEST(Darwin, Creature_go_1) {
    Species food('f');
    food.addstep("left");
    food.addstep("go 0");
    Creature c2(0, food);
    c2.go(-1);
    ASSERT_EQ(c2._pc, 1);
}

TEST(Darwin, Creature_go_2) {
    Species food('f');
    food.addstep("left");
    food.addstep("go 0");
    Creature c2(0, food);
    c2.go(-1);
    ASSERT_EQ(c2._pc, 1);
    c2.go(-1);
    ASSERT_EQ(c2._pc, 0);
}

TEST(Darwin, Creature_go_3) {
    Species food('f');
    food.addstep("left");
    food.addstep("go 0");
    food.addstep("right");
    food.addstep("go 0");
    Creature c2(0, food);
    c2.go(3);
    ASSERT_EQ(c2._pc, 3);
}

TEST(Darwin, Creature_my_turn_1) {
    Species food('f');
    food.addstep("left");
    food.addstep("go 0");
    Creature c2(0, food);
    bool barr[4] = {false,false,false,false};
    Creature* carr[4] = {NULL,NULL,NULL,NULL};
    ASSERT_EQ(c2.my_turn(barr, carr), -1);
}

TEST(Darwin, Creature_my_turn_2) {
    Species hopper('h');
    hopper.addstep("hop");
    hopper.addstep("go 0");
    Creature c2(0, hopper);
    Creature empty;
    bool barr[4] = {false,false,false,false};
    Creature* carr[4] = {&empty,&empty,&empty,&empty};
    ASSERT_EQ(c2.my_turn(barr, carr), 0);
}

TEST(Darwin, Species_constructor_1) {
    Species empty;
    ASSERT_EQ(empty.getname(), '.');
}

TEST(Darwin, Species_constructor_2) {
    Species food('f');
    ASSERT_EQ(food.getname(), 'f');
}

TEST(Darwin, Species_copy_1) {
    Species food('f');
    food.addstep("left");
    food.addstep("go 0");
    Species food2;
    food2 = food;
    ASSERT_EQ(food.getname(), food2.getname());
    ASSERT_EQ(food.getprogsize(), food2.getprogsize());
}

TEST(Darwin, Species_copy_2) {
    Species food('f');
    food.addstep("left");
    food.addstep("go 0");
    Species food2;
    food2 = food;
    food.addstep("go 1");
    ASSERT_EQ(food.getname(), food2.getname());
    ASSERT_FALSE(food.getprogsize()==food2.getprogsize());
}

TEST(Darwin, Species_copy_3) {
    Species food('f');
    food.addstep("left");
    food.addstep("go 0");
    Species hopper('h');
    hopper.addstep("hop");
    hopper.addstep("go 0");
    ASSERT_FALSE(food.getname()==hopper.getname());
    ASSERT_FALSE(food.getstep(0)==hopper.getstep(0));

    hopper = food;
    ASSERT_TRUE(food.getname()==hopper.getname());
    ASSERT_TRUE(food.getstep(0)==hopper.getstep(0));
}

TEST(Darwin, Species_equal_1) {
    Species food('f');
    food.addstep("left");
    food.addstep("go 0");
    Species hopper('h');
    hopper.addstep("hop");
    hopper.addstep("go 0");
    ASSERT_FALSE(food==hopper);
}

TEST(Darwin, Species_equal_2) {
    Species food('f');
    food.addstep("left");
    food.addstep("go 0");
    ASSERT_TRUE(food==food);
}

TEST(Darwin, Species_equal_3) {
    Species food('f');
    food.addstep("left");
    food.addstep("go 0");
    Species fakefood('f');
    food.addstep("right");
    food.addstep("go 0");
    ASSERT_FALSE(food==fakefood);
}

TEST(Darwin, Species_equal_4) {
    Species food('f');
    food.addstep("left");
    food.addstep("go 0");
    Species food2('F');
    food.addstep("left");
    food.addstep("go 0");
    ASSERT_FALSE(food==food2);
}

TEST(Darwin, Species_addstep_1) {
    Species food('f');
    food.addstep("left");
    food.addstep("go 0");
    ASSERT_EQ(food.getstep(0), 2);
}

TEST(Darwin, Species_getprogsize_1) {
    Species food('f');
    food.addstep("left");
    food.addstep("go 0");
    ASSERT_EQ(food.getprogsize(), 2);
}

TEST(Darwin, Species_getprogsize_2) {
    Species food('f');
    food.addstep("left");
    food.addstep("go 0");
    ASSERT_EQ(food.getprogsize(), 2);
    Species fakefood('F');
    food = fakefood;
    ASSERT_EQ(food.getprogsize(), 0);
}

TEST(Darwin, Species_getprogsize_3) {
    Species food('f');
    ASSERT_EQ(food.getprogsize(), 0);
}

TEST(Darwin, World_constructor_1) {
    World darwin(2,2);
    stringstream output;
    darwin.print_grid(-1,output);
    string expected = "Turn = -1\n  01\n0 ..\n1 ..\n";
    ASSERT_EQ(output.str(), expected);
}

TEST(Darwin, World_constructor_2) {
    World darwin(5,5);
    stringstream output;
    darwin.print_grid(-1,output);
    string expected = "Turn = -1\n  01234\n0 .....\n1 .....\n2 .....\n3 .....\n4 .....\n";
    ASSERT_EQ(output.str(), expected);
}

TEST(Darwin, World_constructor_3) {
    World darwin(0,0);
    stringstream output;
    darwin.print_grid(-1,output);
    string expected = "Turn = -1\n  \n";
    ASSERT_EQ(output.str(), expected);
}

TEST(Darwin, World_addCreature_1) {
    World darwin(2,2);
    Species food('f');
    darwin.addCreature(Creature(0,food),0,0);
    darwin.addCreature(Creature(0,food),1,1);
    stringstream output;
    darwin.print_grid(-1,output);
    string expected = "Turn = -1\n  01\n0 f.\n1 .f\n";
    ASSERT_EQ(output.str(), expected);
}

TEST(Darwin, World_addCreature_2) {
    World darwin(2,2);
    Species food('f');
    Species hopper('h');
    darwin.addCreature(Creature(0,food),0,0);
    darwin.addCreature(Creature(0,hopper),1,1);
    stringstream output;
    darwin.print_grid(-1,output);
    string expected = "Turn = -1\n  01\n0 f.\n1 .h\n";
    ASSERT_EQ(output.str(), expected);
}

TEST(Darwin, World_addCreature_3) {
    World darwin(2,2);
    Species food('f');
    Species hopper('h');
    darwin.addCreature(Creature(0,food),0,0);
    darwin.addCreature(Creature(0,food),0,1);
    darwin.addCreature(Creature(0,hopper),1,0);
    darwin.addCreature(Creature(0,hopper),1,1);
    stringstream output;
    darwin.print_grid(-1,output);
    string expected = "Turn = -1\n  01\n0 ff\n1 hh\n";
    ASSERT_EQ(output.str(), expected);
}

TEST(Darwin, World_give_turn_1) {
    World darwin(2,2);
    Species hopper('h');
    hopper.addstep("hop");
    hopper.addstep("go 0");
    darwin.addCreature(Creature(0,hopper),1,0);
    darwin.addCreature(Creature(0,hopper),1,1);
    stringstream output;
    darwin.print_grid(-1,output);
    ASSERT_EQ(output.str(), "Turn = -1\n  01\n0 ..\n1 hh\n");
    darwin.give_turn(1,0);
    output.str("");
    darwin.print_grid(-1,output);
    ASSERT_EQ(output.str(), "Turn = -1\n  01\n0 h.\n1 .h\n");
}

TEST(Darwin, World_give_turn_2) {
    World darwin(2,2);
    Species virus('v');
    virus.addstep("infect");
    virus.addstep("go 0");
    Species food('f');
    food.addstep("left");
    food.addstep("go 0");
    darwin.addCreature(Creature(0,virus),1,0);
    darwin.addCreature(Creature(0,food),0,0);
    stringstream output;
    darwin.print_grid(-1,output);
    ASSERT_EQ(output.str(), "Turn = -1\n  01\n0 f.\n1 v.\n");
    darwin.give_turn(1,0);
    output.str("");
    darwin.print_grid(-1,output);
    ASSERT_EQ(output.str(), "Turn = -1\n  01\n0 v.\n1 v.\n");
}

TEST(Darwin, World_give_turn_3) {
    World darwin(2,2);
    Species rover('r');
    rover.addstep("if_empty 3");
    rover.addstep("right");
    rover.addstep("go 0");
    rover.addstep("hop");
    rover.addstep("go 0");
    darwin.addCreature(Creature(1,rover),0,0);
    stringstream output;
    darwin.print_grid(0,output);
    ASSERT_EQ(output.str(), "Turn = 0\n  01\n0 r.\n1 ..\n");
    darwin.give_turn(0,0);
    output.str("");
    darwin.print_grid(1,output);
    ASSERT_EQ(output.str(), "Turn = 1\n  01\n0 .r\n1 ..\n");
    darwin.give_turn(0,1);
    output.str("");
    darwin.print_grid(2,output);
    ASSERT_EQ(output.str(), "Turn = 2\n  01\n0 .r\n1 ..\n");
    darwin.give_turn(0,1);
    output.str("");
    darwin.print_grid(3,output);
    ASSERT_EQ(output.str(), "Turn = 3\n  01\n0 ..\n1 .r\n");
}

TEST(Darwin, World_run_1) {
    World darwin(2,2);
    Species virus('v');
    virus.addstep("infect");
    virus.addstep("go 0");
    Species food('f');
    food.addstep("left");
    food.addstep("go 0");
    darwin.addCreature(Creature(0,virus),1,0);
    darwin.addCreature(Creature(0,food),0,0);
    stringstream output;
    darwin.run(1,output);
    ASSERT_EQ(output.str(), "Turn = 0\n  01\n0 f.\n1 v.\nTurn = 1\n  01\n0 v.\n1 v.\n");
}

TEST(Darwin, World_run_2) {
    World darwin(2,2);
    Species rover('r');
    rover.addstep("if_enemy 6");
    rover.addstep("if_empty 4");
    rover.addstep("left");
    rover.addstep("go 0");
    rover.addstep("hop");
    rover.addstep("go 0");
    rover.addstep("infect");
    rover.addstep("go 0");
    Species food('f');
    food.addstep("left");
    food.addstep("go 0");
    darwin.addCreature(Creature(0,rover),1,1);
    darwin.addCreature(Creature(0,food),0,0);
    stringstream output;
    darwin.run(3,output);
    ASSERT_EQ(output.str(), "Turn = 0\n  01\n0 f.\n1 .r\nTurn = 1\n  01\n0 fr\n1 ..\nTurn = 2\n  01\n0 fr\n1 ..\nTurn = 3\n  01\n0 rr\n1 ..\n");
}

TEST(Darwin, World_run_3) {
    World darwin(2,2);
    Species rover('r');
    rover.addstep("if_empty 3");
    rover.addstep("left");
    rover.addstep("go 0");
    rover.addstep("hop");
    rover.addstep("go 0");
    darwin.addCreature(Creature(0,rover),1,1);
    stringstream output;
    darwin.run(3,output);
    ASSERT_EQ(output.str(), "Turn = 0\n  01\n0 ..\n1 .r\nTurn = 1\n  01\n0 .r\n1 ..\nTurn = 2\n  01\n0 .r\n1 ..\nTurn = 3\n  01\n0 r.\n1 ..\n");
}