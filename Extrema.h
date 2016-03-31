#ifndef EXTREMA_H
#define EXTREMA_H

#include<vector>
#include<iostream>

using namespace std;

class Extrema
{
public:
	Extrema();
	~Extrema();

	void getExtremas(vector<double> signal, vector<double> &maxima, vector<int> &maximaIndexes,
											vector<double> &minima, vector<int> &minimaIndexes);
};

#endif