// FrichetDistanceProj.cpp : Defines the entry point for the console application.
//
//Includes
#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <math.h>
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

struct query {
	int queryNum;
	string queryTraj;
	double leashLength;

	query(int qn, string qt, double l){ //ctor
		queryNum = qn;
		queryTraj = qt;
		leashLength = l;
	}
};
//Frichet and supporting methods
//min
double min(double a, double b) {
	if (a <= b)
		return a;
	else
		return b;
}
//max
double max(double a, double b) {
	if (a >= b)
		return a;
	else
		return b;
}

//euclidianDist
double euclideanDistance(pointInTraj a, pointInTraj b) {
	double distance = 0;
	distance += sqrt(pow((a.xAxis - b.xAxis), 2) + pow((a.yAxis - b.yAxis), 2));

	return distance;
}

//frechetDistance

//main method
void main(){

	//create input file stream
	ifstream ifile("files/dataset.txt");

	//make sure file stream opens
	if (!ifile)
	{
		cout << endl << "Error Opening files/dataset.txt" << endl;
		exit(0);
	}
	
	//create a list of filenames in dataset for opening file streams
	list<string> dataset;
	//create arraylist of points
	list<pointInTraj> traj;
	list<list<pointInTraj>> trajList;
	list<list<pointInTraj>> queryList;
	string line, filename;
	double x, y;
	int k, t;

	while (!ifile.eof()) {
		getline(ifile, line);
		if(line != "")
			dataset.push_back(line);	
	}
	ifile.close();

	for (string line : dataset) {
		cout << "line contents: " << line << endl;
	}
	//debug dataset COMPLETE


	//iterator for dataset
	int j = dataset.size() - 1;
	cout << "dataset.size() = " << j << endl;
	cout << "generating trajectories..." << endl;
	/*open files from dataset one at a time and create points and store them 
	in an array of points*/
	for (int i = 0; i <= j; i++) {
		//select ith filename from dataset
		filename = "files/" + dataset.front();
		dataset.pop_front();

		//create stream to new file name modeled on the input filename
		cout << "generating dataset trajectory " << filename << endl;
		ifstream ifile(filename);
		//discard first line of datafile which holds 'column headers'
		getline(ifile, line); 
		//while file has next, create trajectories and pack them into an array
		while (!ifile.eof()) {
			//grab data for a point
			getline(ifile, line);
			ifile >> x >> y >> k >> t;
			pointInTraj p = pointInTraj(x, y, k, t);
			traj.push_back(p);

		}
		trajList.push_back(traj);
		traj.clear();
		//debug trajList
		

	}

	//debug trajList COMPLETE

	////load trajectories from queries.txt
	////create input file stream
	//ifstream ifile2("queries.txt");
	////check to see if stream opened
	//if (!ifile2)
	//{
	//	cout << endl << "Error Opening queries.txt" << endl;
	//	exit(0);
	//}
	//list<query> queries;
	//string queryname;
	//double maxLeash;

	//cout << "scanning queries.txt" << endl;
	////added queryNum to struct for queries to use for output into result-XXXX.txt
	//int queryNum = 0;
	//while (!ifile2.eof()) {
	//	ifile2 >> queryname >> maxLeash;
	//	query q = query(queryNum, queryname, maxLeash);
	//	queries.push_back(q);
	//	queryNum++;

	//}
	//ifile2.close();

	////for each query, pull in trajectories into another list
	////iterator for queryset
	//j = queries.size() - 1;
	//cout << "generating query trajectories..." << endl;
	///*open files from dataset one at a time and create points and store them
	//in an array of points*/
	//for (int i = 0; i <= j; i++) {
	//	//select ith filename from dataset
	//	filename = queries.front().queryTraj;
	//	queries.pop_front();

	//	//create stream to new file name modeled on the input filename
	//	ifstream ifile3(filename);
	//	//discard first line of datafile which holds 'column headers'
	//	getline(ifile3, line);
	//	//while file has next, create trajectories and pack them into an array
	//	while (!ifile3.eof()) {
	//		//grab data for a point
	//		traj.clear();
	//		getline(ifile3, line);
	//		ifile3 >> x >> y >> k >> t;
	//		pointInTraj p = pointInTraj(x, y, k, t);
	//		traj.push_back(p);

	//	}
	//	queryList.push_back(traj);
	//	//debug queryList
	//	

	//	}

	}