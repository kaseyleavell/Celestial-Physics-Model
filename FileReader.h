#pragma once
#include<iostream>
#include<fstream>
struct CelBody {
	bool readError;
	int x;
	int y;
	int mass;
	float force;
	float fang;
	int velocity;
	int van;
	char ascii;
};
//Not yet funcitoning in full capacity Still quite buggy
class FileReader
{
public:
	//At this point the program will only accept 30 body inputs in the file
	CelBody returnArray[30];
	char fileName[15] = "input.csv";
	
	std::ifstream ifs;
public:
	CelBody* ReadCelFile() {
		//read all of the available bodies information into the returnArray
		//while feedback != EOF read into array
		CelBody* array = new CelBody[10];
		int j = 0;
		ifs.open(fileName, std::ifstream::in);
		array[j] = ReadBody();
		while (array[j].readError != 1) {
			j++;
			array[j] = ReadBody();
		}
		ifs.close();
		return array;
	}
	CelBody ReadBody() {
		//reads the next full line from the file into the temp struct and returns that
		CelBody temp;
		//code for reading from csv file
		//obviously a hardcoded solution
		int i = 0;
		char buf[20];
		buf[i] = ifs.get();
		//read x
		while (ifs.good()) {
			if (buf[i] == ',') {
				buf[i] = '\n';
				break;
			}
			i++;
			buf[i] = ifs.get();
		}
		temp.x = atoi(buf);
		i = 0;
		//read y
		buf[i] = ifs.get();
		while (ifs.good()) {
			if (buf[i] == ',') {
				buf[i] = '\n';
				break;
			}
			i++;
			buf[i] = ifs.get();
		}
		temp.y = atoi(buf);
		i = 0;
		//read mass
		buf[i] = ifs.get();
		while (ifs.good()) {
			if (buf[i] == ',') {
				buf[i] = '\n';
				break;
			}
			i++;
			buf[i] = ifs.get();
		}
		temp.mass = atoi(buf);
		i = 0;
		//red force
		buf[i] = ifs.get();
		while (ifs.good()) {
			if (buf[i] == ',') {
				buf[i] = '\n';
				break;
			}
			i++;
			buf[i] = ifs.get();
		}
		temp.force = atoi(buf);
		i = 0;
		//read fang
		buf[i] = ifs.get();
		while (ifs.good()) {
			if (buf[i] == ',') {
				buf[i] = '\n';
				break;
			}
			i++;
			buf[i] = ifs.get();
		}
		temp.fang = atoi(buf);
		i = 0;
		//read velocity
		buf[i] = ifs.get();
		while (ifs.good()) {
			if (buf[i] == ',') {
				buf[i] = '\n';
				break;
			}
			i++;
			buf[i] = ifs.get();
		}
		temp.velocity = atoi(buf);
		i = 0;
		//read van
		buf[i] = ifs.get();
		while (ifs.good()) {
			if (buf[i] == ',') {
				buf[i] = '\n';
				break;
			}
			i++;
			buf[i] = ifs.get();
		}
		temp.van = atoi(buf);
		i = 0;
		//read ascii
		buf[i] = ifs.get();
		while (ifs.good()) {
			if (buf[i] == ','||buf[i] == EOF) {
				if (buf[i] == EOF) {
					temp.readError = 1;
				}
				buf[i] = '\n';
				break;
			}
			i++;
			buf[i] = ifs.get();
		}
		temp.ascii = atoi(buf);
		i = 0;
		//what to do for an EOF read???
		return temp;
	}
};

