#include "Extrema.h"

Extrema::Extrema()
{
}

Extrema::Extrema(double step) :step(step)
{
}

Extrema::~Extrema()
{
}

void Extrema::getExtremas(vector<double> signal, vector<double> &maxima, vector<double> &maximaIndexes,
												vector<double> &minima, vector<double> &minimaIndexes)
{
	maxima.clear(); maximaIndexes.clear();
	minima.clear(); minimaIndexes.clear();

	int n = signal.size() - 1;
	for (int i = 1; i < n - 1; ++i){
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
