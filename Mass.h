#pragma once
#define PI 3.14159265
#include <iostream>
#include <math.h>
/*
FUNCTION MACROS
*/
//#define DELTA_T 86400	//This is an earth day in seconds
#define DELTA_T 1	//used for ease of debugging
class Mass
{
	//This class will be the parent class for all stars, planets and asteroids.
	//gravity constant for all objects
	float G = 6.673*(10^(-11));		/*N*m^2/kg^2*/
	//x and y coordinates, as of right now, only implimenting a 2d field of observation.
	float X, Y;			/*m*/
	float M;	//stores mass in kilograms
	float F;	//stores force in Newtons
	float Fang;	//stores force angle in radians
	float v;	//stores velocity in meters/second
	float vang;	//velocity angle in radians
	char ASC;	//this is the bodies ascii character that will be printed onto the scree

public:
	Mass* nextNode = NULL;
	//Add some sort of force vector

	/// //////////////////////////////////////////////////////////////////////////////
public:
	Mass(int x, int y, int mass, float force, float fang, int velocity,int van, char ascii) {
		X = x;
		Y = y;
		M = mass;
		F = force;
		Fang = fang;
		v = velocity;
		vang = van;
		ASC = ascii;
	}
	int GetX() {
		return X;
	}
	float GetY() {
		return Y;
	}
	float GetMass() {
		return M;
	}
	float GetForce() {
		return F;
	}
	float GetFang() {
		return Fang;
	}
	int GetVelocity() {
		return v;
	}
	int GetVang() {
		return vang;
	}
	void SetX(int x) {
		X = x;
		return;
	}
	void SetY(int y) {
		Y = y;
		return;
	}
	void SetMass(float mass) {
		M = mass;
		return;
	}
	void SetForce(float force) {
		F = force;
		return;
	}
	void SetFang(float fang) {
		Fang = fang;
		return;
	}
	void SetVelocity(float vel) {
		v = vel;
		return;
	}
	void SetVang(float van) {
		vang = van;
		return;
	}
	char GetAsc() {
		return ASC;
	}
	void SetAsc(char ascii) {
		ASC = ascii;
		return;
	}
	Mass* Fracture() {
		//This function could be implimented later to be used for collisions and creating more than one of an asteroid that collided with a planet.
	}
	//Add in a function that calculates the force vector 
	void CalcLocation() {
		//Instantiate variables
		float Fx;
		float Fy;
		//-------------
		float ax;
		float ay;
		//-------------
		float vx;
		float vy;
		//-------------
		float xDelta = 0;
		float yDelta = 0;
		//--------------
		float vMagNew;
		float vAngNew;
		//--------------
		int temp;
		//////////////////////////////////////////////////////////////////////////////////////
		//might be changing calcs here depending on whatquadrant we are in
		//WORKS FOR ALL QUADRANTS
		Fx = F * cos(Fang);
		Fy = F * sin(Fang);

		/////////////////////////////////////////////////////////////////////////////////////
		//calcing vx and vy from v and vang
		vx = v* cos(vang);
		vy = v * sin(vang);

		///////////////////////////////////////////////////////////////////
		//acceleration in x and y direction given the specified force components
		ax = Fx / M;
		ay = Fy / M;
		///////////////////////////////////////////////////////////////////
		//calculate distance traveled in time delta
		//using d = v*t + 1/2*a*t^2
		xDelta = vx * DELTA_T + (1 / 2) * ax * pow(DELTA_T, 2);
		yDelta = vy * DELTA_T + (1 / 2) * ay * pow(DELTA_T, 2);
		//set the new x and y
		X = X + xDelta;
		Y = Y + yDelta;

		/////////////////////////////////////////////////////////////////////////////
		//final velocity
		vMagNew = sqrt(pow((ax * DELTA_T),2) + pow((ay * DELTA_T),2));
		
		//vang
		vAngNew = atan2((ay * DELTA_T), (ax * DELTA_T));
		AddVect(&v, &vang, vMagNew, vAngNew);
		return;
	}
	void CalcNetForce(Mass*hd) {
		//std::cout << "#####################################################################################" << std::endl;
		//std::cout << "#####################################################################################" << std::endl;
		//test variables
		int i = 0;
		//initialize function variables
		Mass* head = hd;
		float FGravMag;
		float FGravTheta;
		float distance;
		//reset the forces
		F = 0;
		Fang = 0;
		//iterate through all masses, calculate force, add it to the force on this object with AddVect
		while (head != NULL) {
			//std::cout << "#################################" << std::endl;
			//std::cout << i++ << std::endl;
			//add forces, skipping this object
			if (head != this) {
				/////////////////////////////////////////////////////////////////////////
				//calc the FG = G*(m1*m2)/d
				distance = sqrt(pow((this->GetX() - head->GetX()), 2) + pow((this->GetY() - head->GetY()), 2));
				FGravMag = G*(this->GetMass() * head->GetMass()) / distance;									//units here could be an issue
				//std::cout << "Fmag " << FGravMag << std::endl;
				FGravTheta = atan2((this->GetY() - head->GetY()), this->GetX() - head->GetX());
				////////////////////////////////////////////////////////////////////////
				//add to the forc vector of this object
				AddVect(&F, &Fang, FGravMag, FGravTheta);
				//std::cout << "From function F:" << F << " Fang: " << Fang << std::endl;
			}
			//iterate to next node
			head = head->nextNode;
		}
	}

	//function adds a vector to a referenced location in. This can be used for force and velocity
	void AddVect(float* mag, float* ang, float magAdd, float angAdd) {
		//////////////////////////////////////////////////////////////////////////
		//reference vector
		float vect1X = (*mag) * cos(*ang);
		float vect1Y = (*mag) * sin(*ang);
		//////////////////////////////////////////////////////////////////////////
		//vector to be added
		float vect2X = magAdd * cos(angAdd);
		//std::cout << "Fx2 " << magAdd * cos(angAdd) << std::endl;
		float vect2Y = magAdd * sin(angAdd);
		//std::cout << "FY2 " << magAdd * sin(angAdd) << std::endl;
		//////////////////////////////////////////////////////////////////////////
		//change the mag to abs() of x and ys added
		*mag = sqrt(pow((vect1X + vect2X),2) + pow((vect1Y + vect2Y), 2));
		//std::cout << "Fmag " << *mag << std::endl;
		//////////////////////////////////////////////////////////////////////////
		//change the ang to the atan of the two
		*ang = atan2((vect1Y + vect2Y), (vect1X + vect2X));
		//std::cout << "Fang " << *ang << std::endl;
	}
};

