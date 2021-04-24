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
	
	Mass* head = new Mass(300,275,1,0.05,0,30,0,'y');	//add this into initialize??
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
	Mass* runner = NULL;
	//***************

	//Trap

	//while (1);

	for (;;) {
		/*
		STRUCTURE OF THIS LOOP IS AS FOLLOWS

		|-->Calc places---->(x,y)-------->Calc Forces->-|
		|------(F)<------Display on Screen<-------------|
		
		*/
		//set runner to the front
		runner = head;
		//move masses
		std::cout << "start" << std::endl;
		while (runner != NULL) {
			std::cout << "#######################" << std::endl;

			//try using recursion here instead of the loop

			//split force into Fx and Fy
			  
			//F = ma->a = F/m
			runner->CalcLocation();
			std::cout << "Y: " << runner->GetY() << std::endl;
			std::cout << "X: " << runner->GetX() << std::endl;
			//step to the next mass in the linked list
			runner = runner->nextNode;
		}
		//set runner to the front
		runner = head;
		//recalc forces given new calculations
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
	/*currently done in main because I suck*/
};
void PopulateSpace() {
	//instantiate masses for orbits, etc.

};