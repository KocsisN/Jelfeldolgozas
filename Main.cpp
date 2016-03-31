#include<iostream>
#include "spline3.h"
#include<vector>
#include<fstream>
#include"Extrema.h"

using namespace std;

int main()
{
	std::vector<double> signal, time;
	ifstream in("p.txt");
	

	double dt0, DT, dt = 0, val;
	in >> dt0 >> DT;

	while (in >> val){
		signal.push_back(val);
		time.push_back(dt);
		dt += DT;
	}
	in.close();

	vector<double> minima, maxima, minimaIndexes, maximaIndexes;

	Extrema e;
	e.getExtremas(signal, minima, minimaIndexes, maxima, maximaIndexes, DT);
	
	spline::spline3 s_minima;
	s_minima.set_points(minimaIndexes, minima);


	spline::spline3 s_maxima;
	s_maxima.set_points(maximaIndexes, maxima);

	vector<double> interp1, interp2;
	for (double &t : time){
		interp1.push_back(s_minima(t));
		interp2.push_back(s_maxima(t));
	}

	e.printToFile("ki.txt", interp1, time, interp2, time);

	//std::vector<double> X(5), Y(5);
	//X[0] = 0.1; X[1] = 0.4; X[2] = 1.2; X[3] = 1.8; X[4] = 2.0;
	//Y[0] = 0.1; Y[1] = 0.7; Y[2] = 0.6; Y[3] = 1.1; Y[4] = 0.9;

	//spline::spline3 s;
	//s.set_points(X, Y);    // currently it is required that X is already sorted

	//cout << "Spline3 at 1.5: " << s(1.5) << endl;

	system("pause");
	return 0;
}