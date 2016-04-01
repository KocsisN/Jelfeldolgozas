#include "EMD.h"

EMD::EMD(double step) : step(step), extrema(step)
{

}

EMD::EMD(string inputFile, string outputFile, double step) : inputFile(inputFile), outputFile(outputFile), extrema(step)
{
}


EMD::~EMD()
{
}

//number of zero crossing and number of maxima equals +- 1
//the mean value of upper and lover is zero everywhere
bool EMD::isIMF(vector<double> &potentialIMF, int numberOfExtremas, vector<double> &signalNew)
{
	//how many zero crossings are
	int zeroCrossing = extrema.numberOfZeroCross(potentialIMF);
	int nonzeroPoints = count_if(signalNew.begin(), signalNew.end(), [](double val){
		return val < -0.0001 || val > 0.0001;
		// epszilon = 0.0001
	});
		//zero crossing hasonlitani maximak szamaval

	//if (nonzeroPoints){
	//	ofstream o("atlag.txt");
	//	for (int i = 0; i < signalNew.size(); ++i){
	//		o << signalNew[i] << " ";
	//	}
	//	o.close();
	//	cout << "Sok nemzero van\n";
	//}
	

	return (zeroCrossing == numberOfExtremas && nonzeroPoints == 0);
	
}

void EMD::compute(vector<double> &signal)
{
	vector<double> minima, maxima, minimaIndex, maximaIndex;
	vector<double> interpolationMinima, interpolationMaxima, mean, signalNew;

	//while signal has more tha 2 extremas
	minima.clear(); maxima.clear();
	minimaIndex.clear(); maximaIndex.clear();
	interpolationMaxima.clear(); interpolationMinima.clear();
	mean.clear(); signalNew.clear();

	//find the first imf
	signalNew = signal;
	while (true){
		extrema.getExtremas(signalNew, minima, minimaIndex, maxima, maximaIndex);
		spline::spline3 s_minima, s_maxima;

		s_minima.set_points(minimaIndex, minima);
		s_maxima.set_points(maximaIndex, maxima);

		for (int i = 0; i < signal.size(); ++i){
			mean.push_back((s_minima(i*step) + s_maxima(i*step)) / 2);
			//signalNew.push_back(signal[i] - mean[i]);
		}
		//kell egy kivonas signalNew
		if (isIMF(signal, minima.size() + maxima.size(), mean)){
			cout << "Erre mukodik" << endl;
		}
	}
}