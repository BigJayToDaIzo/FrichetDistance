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
struct pointInTraj {
	double xAxis, yAxis;
	int kAxis, tid;

	pointInTraj(double x, double y, int k, int t) { //ctor
		xAxis = x; yAxis = y;
		kAxis = k; tid = t;

	}
};

//main method
void main(){

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
	//create arraylist of points
	list<pointInTraj> points;
	string line, filename;
	double x, y;
	int k, t;

	while (!ifile.eof()) {
		getline(ifile, line);
		dataset.push_back(line);	
	}
	ifile.close();

	//debugging the dataset
	/*for (string x : dataset) {
		cout << x << endl;
	}*/

	//iterator for dataset
	int j = dataset.size() - 1;
	//open files from dataset one at a time and create points and store them in an array of points
	for (int i = 0; i < j; i++) {
		//select ith filename from dataset
		filename = "files/" + dataset.front();
		dataset.pop_front();

		//create stream to new file name modeled on the input filename
		ifstream ifile(filename);
		//discard first line of datafile which holds 'column headers'
		getline(ifile, line); 
		//while file has next, create trajectories and pack them into an array
		while (!ifile.eof()) {
			//grab data for a point
			getline(ifile, line);
			ifile >> x >> y >> k >> t;
			pointInTraj p = pointInTraj(x, y, k, t);
			points.push_back(p);

		}

		//debugging the dataset list
		//cout << filename << endl;
		//debugging the points list
		/*for (pointInTraj p : points) {
			cout << "x: " << p.xAxis << " y: " << p.yAxis << " k: " << p.kAxis << " tid: " << p.tid << endl;
		}*/

	}

}

