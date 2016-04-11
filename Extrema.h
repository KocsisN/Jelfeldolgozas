#ifndef EXTREMA_H
#define EXTREMA_H

#include<vector>
#include<iostream>
#include<fstream>
#include<algorithm>

using namespace std;

class Extrema
{
private:
	double step;
	
public:
	Extrema();
	Extrema(double step);
	~Extrema();

	void getExtremas(vector<double> signal, vector<double> &minima, vector<double> &minimaIndexes,
		vector<double> &maxima, vector<double> &maximaIndexes);

	/*
	void printToFile(string filename, vector<double> &minima, vector<double> &minimaIndexes,
		vector<double> &maxima, vector<double> &maximaIndexes);*/
};

#endif