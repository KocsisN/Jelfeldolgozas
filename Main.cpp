#include<iostream>
#include "spline3.h"
#include<vector>

using namespace std;

int main()
{
	std::vector<double> X(5), Y(5);
	X[0] = 0.1; X[1] = 0.4; X[2] = 1.2; X[3] = 1.8; X[4] = 2.0;
	Y[0] = 0.1; Y[1] = 0.7; Y[2] = 0.6; Y[3] = 1.1; Y[4] = 0.9;

	spline::spline3 s;
	s.set_points(X, Y);    // currently it is required that X is already sorted

	cout << "Spline3 at 1.5: " << s(1.5) << endl;

	system("pause");
	return 0;
}