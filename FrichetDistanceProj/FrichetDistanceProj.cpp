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
	list<pointInTraj> traj;
	list<list<pointInTraj>> trajList;
	string line, filename;
	double x, y;
	int k, t;

	while (!ifile.eof()) {
		getline(ifile, line);
		dataset.push_back(line);	
	}
	ifile.close();


	//iterator for dataset
	int j = dataset.size() - 1;
	/*open files from dataset one at a time and create points and store them 
	in an array of points*/
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
			traj.clear();
			getline(ifile, line);
			ifile >> x >> y >> k >> t;
			pointInTraj p = pointInTraj(x, y, k, t);
			traj.push_back(p);k++;

		}
		trajList.push_back(traj);
		cout << "just pushed the " << i << "st/th" << " trajectory into trajectory list" << endl;
	}
	//all trajectories are now in trajList<list<pointInTraj>>
	//load trajectories from queries.txt

	//compare each vector from queries.txt to all vectors in trajList

		//for each trajectory that falls within the frechet distance bounds from queries.txt get written
		//into an output file


}

