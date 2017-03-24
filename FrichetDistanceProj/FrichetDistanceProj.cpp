// FrichetDistanceProj.cpp : Defines the entry point for the console application.
//
//Includes
#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <list>
using namespace std;

//Structs
struct trajectory {
	double xAxis, yAxis, zAxis;
	int kAxis, tid;

	trajectory(double x, double y, double z, int k, int t) { //ctor
		xAxis = x; yAxis = y; zAxis = z;
		kAxis = k; tid = t;

	}
};

//helper methods
void loadStream(string s) {

}


//main method
int main(){

	//create input file stream
	ifstream ifile("files/dataset.txt");

	//make sure file stream opens
	if (!ifile)
	{
		cout << endl << "Error Opening File" << endl;
		exit(0);
	}
	
	//create a list of filenames in dataset for opening file streams
	list<string> dataset;
	string line;
	while (!ifile.eof()) {
		getline(ifile, line);
		dataset.push_back(line);	
	}
	ifile.close();

	//debugging the dataset
	/*for (string x : dataset) {
		cout << x << endl;
	}*/

	//open files from dataset one at a time and create trajectories and store them in a 
	string filename;
	int j = dataset.size() - 1;
	for (int i = 0; i < j; i++) {
		//select ith filename from dataset
		filename = "files/" + dataset.front();
		dataset.pop_front();

		ifstream ifile(filename);

		//debugging the dataset
		//cout << filename << end;
	}

	return 0;
}

