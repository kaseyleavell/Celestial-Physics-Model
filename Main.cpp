#include <iostream>
#include "planet.h"
#include "Star.h"
#include "Mass.h"
#include "Screen.h"
#include <math.h>
void Initialize();
Screen scrn;
int main(int argc, char** argv) {

	//Initialize the code
	
	Initialize();
	/* Initialize the celestial bodies being simulated*/
	//Must have at least 2
	//future iterations will impliment a more user friendly approach to initializing the bodies
	//utilize an Excel File reader of some sort
	Mass* head = new Mass(300,275,1,0.05,0,30,0,'y');
	Mass* e = new Mass(300, 300, 30,0, 0, 0, 0,'x');   
	//Mass* a = new Mass(150, 10, 1, 0.05, 0.1, 0, 0, '0');
	
	head->nextNode = e;
	//head->nextNode->nextNode = a;
	//simul loop
	//********************************************************
	//Testing
	//scrn.PrintPlanets(head);
	//*******************************************************
	/*For now just using mass class so that linked list can be used for calc loops*/
	//Future implimentations could use the Planet.h class for specific planets
	Mass* runner = NULL;
	//***************

	for (;;) {
		/*
		STRUCTURE OF THIS LOOP IS AS FOLLOWS

		|-->Calc places---->(x,y)-------->Calc Forces->-|
		|------(F)<------Display on Screen<-------------|
		
		*/
		//set runner to the front
		runner = head;
		//move masses
		//This loop calculates location of all masses
		/*Could impliment all of these calculation loops using recurrsion*/
		while (runner != NULL) {
			//split force into Fx and Fy
			//F = ma->a = F/m
			runner->CalcLocation();
			/*
			std::cout << "Y: " << runner->GetY() << std::endl;
			std::cout << "X: " << runner->GetX() << std::endl;
			*/
			//step to the next mass in the linked list
			runner = runner->nextNode;
		}
		//set runner to the front
		runner = head;
		//recalc forces given new location calculations
		while (runner != NULL) {
			//try using recursion here
			runner->CalcNetForce(head);
			//step to the next mass
			runner = runner->nextNode;
		}
		runner = head;
		//print all of the celestial bodies
		scrn.screenUpdate(runner);
	}
};
void Initialize() {
	//initialize space, screen, etc.
	//Initialize the screen
	scrn.Initialize();
	//initialize the head node
};
void PopulateSpace() {
	//instantiate masses for orbits, etc.

};
