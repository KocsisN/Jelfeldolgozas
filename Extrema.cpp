#include "Extrema.h"


Extrema::Extrema()
{
}


Extrema::~Extrema()
{
}

//indexes: ha maximum pozitiv, ha minimum negativ
void Extrema::getExtremas(vector<double> signal, vector<double> &maxima, vector<double> &maximaIndexes,
												vector<double> &minima, vector<double> &minimaIndexes, double step)
{
	maxima.clear(); maximaIndexes.clear();
	minima.clear(); minimaIndexes.clear();

	int n = signal.size() - 1;
	for (int i = 1; i < n - 1; ++i){
		/*cout << signal[i - 1] << " -> " << signal[i] << " -> " << signal[i + 1] << endl;
		cin.get();*/
		//ha az elozo es a kovetkezo is kissebb => maximum pont
		if (signal[i + 1] < signal[i] && signal[i - 1] < signal[i]){
			maxima.push_back(signal[i]);
			maximaIndexes.push_back(i*step);
		}
		//elozo es kovetkezo is nagyobb => minimum pont
		if (signal[i + 1] > signal[i] && signal[i - 1] > signal[i]){
			minima.push_back(signal[i]);
			minimaIndexes.push_back(i*step);
		}
	}
}

void Extrema::printToFile(string filename, vector<double> &minima, vector<double> &minimaIndexes,
	vector<double> &maxima, vector<double> &maximaIndexes)
{
	ofstream out(filename);

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
	}

	out.close();
}