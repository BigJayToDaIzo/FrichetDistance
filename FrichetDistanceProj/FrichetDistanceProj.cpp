// FrichetDistanceProj.cpp : Defines the entry point for the console application.
//
//Includes
#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <vector>
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

	void toString() {
		cout << "xAxis: " << xAxis << " yAxis: " << yAxis << " kAxis: " << kAxis << " tid: " << tid << endl;
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

	void toString() {
		cout << "queryNum: " << queryNum << " queryTraj: " << queryTraj << " leashLength: " << leashLength << endl;
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

//discreteFrechetDistance and supporting methods
double computeDFD(int i, int j) {
	return 1.0;
}
double discreteFrechetDistance(list<pointInTraj> P, list<pointInTraj> Q) {
	//create and resize vector
	vector<vector<double>> mem;
	mem.resize(P.size());
	for (int i = 0; i < P.size(); i++) {
		mem[i].resize(Q.size());
	}
	//populate vector with -1.0
	for (int i = 0; i < mem.size(); i++) {
		for (int j = 0; j < mem[i].size(); j++) {
			mem[i][j] = -1.0;
		}
	}
	//computeDFD
	return computeDFD(P.size() - 1, Q.size() - 1);

}


//main method
void main(){

	//create input file stream
	ifstream ifile("files/dataset.txt");
	//create a list of filenames in dataset for opening file streams
	list<string> dataset, dataset2;  //confirmed populating correctly
	list<query> queryList, queryList2; //confirmed populating correctly
	list<pointInTraj> traj; //confirmed populating correctly
	list<list<pointInTraj>> datasetTrajList; //confirmed populating correctly
	list<list<pointInTraj>> queryTrajList; //confirmed populating correctly
										   
	string line, filename, queryname;
	
	double maxLeash;
	double x, y;

	int k, t, DIM;


	//make sure file stream opens
	if (!ifile)
	{
		cout << endl << "Error Opening files/dataset.txt" << endl;
		exit(0);
	}
	cout << "scanning dataset.txt" << endl;
	while (!ifile.eof()) {
		getline(ifile, line);
		if (line != "") {
			dataset.push_back(line);
			dataset2.push_back(line);
		}
			
	}
	ifile.close();
	/*debug dataset
	for (string l : dataset) {
		cout << "string from dataset: " << l << endl;
	}*/

	//load trajectories from queries.txt
	//create input file stream
	ifstream ifile2("queries.txt");
	//check to see if stream opened
	if (!ifile2)
	{
		cout << endl << "Error Opening queries.txt" << endl;
		exit(0);
	}

	cout << "scanning queries.txt" << endl;
	//added queryNum to struct for queries to use for output into result-XXXX.txt
	int queryNum = 0;
	while (!ifile2.eof()) {
		ifile2 >> queryname >> maxLeash;
		query q = query(queryNum, queryname, maxLeash);
		queryList.push_back(q);
		queryList2.push_back(q);
		queryNum++;

	}
	ifile2.close();
	/*debug queryList
	for (query q : queryList) {
		q.toString();
	}*/

	//iterator for dataset
	int j = dataset.size() - 1;
	cout << "generating dataset trajectories..." << endl;
	/*open files from dataset one at a time and create points and store them 
	in an array of points*/
	for (int i = 0; i <= j; i++) {
		//select ith filename from dataset
		filename = "files/" + dataset.front();
		dataset.pop_front();

		//create stream to new file name modeled on the input filename
		//cout << "generating dataset trajectory " << filename << endl;
		ifstream ifile(filename);
		//discard first line of datafile which holds 'column headers'
		//while file has next, create trajectories and pack them into an array
		while (!ifile.eof()) {
			//grab data for a point
			getline(ifile, line);
			while (ifile >> x >> y >> k >> t) {
				pointInTraj p = pointInTraj(x, y, k, t);
				traj.push_back(p);
			}

		}
		datasetTrajList.push_back(traj);
		/*debug traj
		for (pointInTraj p : traj) {
			p.toString();
		}*/
		traj.clear();
		ifile.close();
	}
	/*debug datasetTrajList
	for (list<pointInTraj> l : datasetTrajList) {
		for (pointInTraj p : l) {
			p.toString();
		}
	}*/

	//for each query, pull in trajectories into another list
	//iterator for queryset
	j = queryList.size() - 1;
	cout << "generating query trajectories..." << endl;
	/*open files from dataset one at a time and create points and store them
	in an array of points*/
	for (int i = 0; i <= j; i++) {
		//select ith filename from dataset
		filename = queryList.front().queryTraj;
		cout << "filename: " << filename << endl;
		queryList.pop_front();

		//create stream to new file name modeled on the input filename
		ifstream ifile3(filename);
		//check to see if stream opened
		if (!ifile3)
		{
			cout << endl << "Error Opening stream to query file." << endl;
			exit(0);
		}

		//while file has next, create trajectories and pack them into an array
		while (getline(ifile3, line)) {
			//grab data for a point
			while (ifile3 >> x >> y >> k >> t) {
				pointInTraj p = pointInTraj(x, y, k, t);
				traj.push_back(p);
			}
			
		}
		queryTrajList.push_back(traj);
		traj.clear();
		ifile3.close();
			
	}
	/*debug queryTrajList
	for (list<pointInTraj> l : queryTrajList) {
		for (pointInTraj p : l) {
			p.toString();
		}
	}*/

	//all data structured created and confirmed correctly populated
	//for loop that compares each trajectory in queryTrajList to each trajectory in datasetTrajList
	for (list<pointInTraj> qt : queryTrajList) {
		for (list<pointInTraj> dt : datasetTrajList) {
			double temp = discreteFrechetDistance(qt, dt);
			
		}
	}


}



