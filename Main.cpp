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
	if (!in){
		cout << "Baj" << endl;
		return 0;
	}
	double dt0, dt1, dt = 0, val;
	in >> dt0 >> dt1;

	while (in >> val){
		signal.push_back(val);
		time.push_back(dt);
		dt += dt1;
	}
	in.close();
	cout << signal.size() << endl;
	ofstream out("ki.txt");
	/*vector<double> minima, maxima;
	vector<int> minimaIndexes, maximaIndexes;

	Extrema e;
	e.getExtremas(signal, maxima, maximaIndexes, minima, minimaIndexes);
	
	for (int i = 0; i < minimaIndexes.size(); ++i){
		out << " " << minimaIndexes[i];
	}
	out << endl;

	for (int i = 0; i < minimaIndexes.size(); ++i){
		out << " " << minima[i];
	}
	out << endl;
	for (int i = 0; i < maximaIndexes.size(); ++i){
		out << " " << maximaIndexes[i];
	}
	out << endl;
	for (int i = 0; i < maximaIndexes.size(); ++i){
		out << " " << maxima[i];
	}*/
	for (double &i : signal){
		out << i << " ";
	}
	out.close();

	//std::vector<double> X(5), Y(5);
	//X[0] = 0.1; X[1] = 0.4; X[2] = 1.2; X[3] = 1.8; X[4] = 2.0;
	//Y[0] = 0.1; Y[1] = 0.7; Y[2] = 0.6; Y[3] = 1.1; Y[4] = 0.9;

	//spline::spline3 s;
	//s.set_points(X, Y);    // currently it is required that X is already sorted

	//cout << "Spline3 at 1.5: " << s(1.5) << endl;

	system("pause");
	return 0;
}