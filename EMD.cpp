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
bool EMD::isIMF(vector<double> &signal, int numberOfExtremas, vector<double> &mean)
{
	//how many zero crossings are
	int zeroCrossing = count_if(signal.begin(), signal.end(), [](double el)
	{
		return (el < EPSFORZERO && el > -EPSFORZERO);
	});

	//az 2 uj nterploacio atlaga kell 0 legyen
	int nonzeroPoints = count_if(mean.begin(), mean.end(), [](double val){
		return (val < -EPSFORNONZERO || val > EPSFORNONZERO);
	});
		//zero crossing hasonlitani maximak szamaval


	//ofstream o("atlag.txt");
	//for (int i = 0; i < signal.size(); ++i){
	//	o << signal[i] - signal[i] << " ";
	//	//kivonjuk az imf-et az eredeti jelbol
	//	signal[i] -= signal[i];
	//}
	//o.close();

	return (abs(zeroCrossing - numberOfExtremas) < 2 && nonzeroPoints == 0);
	
}

void EMD::compute(vector<double> &signal)
{
	vector<double> minima, maxima, minimaIndex, maximaIndex;
	vector<double> residue, mean, signalNew;
	ofstream q("atlag.txt"); q << "";
	q.close();
	//while signal has more tha 2 extremas

	do{
		minima.clear(); maxima.clear();
		minimaIndex.clear(); maximaIndex.clear();
		residue.clear();
		mean.clear(); signalNew.clear();

		//find the first imf
		signalNew = signal;
		while (true){
			//lebontjuk az elso tenyezot
			extrema.getExtremas(signalNew, minima, minimaIndex, maxima, maximaIndex);
			spline::spline3 s_minima, s_maxima;

			s_minima.set_points(minimaIndex, minima);
			s_maxima.set_points(maximaIndex, maxima);

			for (int i = 0; i < signalNew.size(); ++i){
				mean.push_back((s_minima(i*step) + s_maxima(i*step)) / 2);
				//az atlag izet kivonom a jelbol
				residue.push_back(signalNew[i] - mean[i]);
			}

			//az uj izere ellenorziiuk, hogy imf-e
			extrema.getExtremas(residue, minima, minimaIndex, maxima, maximaIndex);

			s_minima.set_points(minimaIndex, minima);
			s_maxima.set_points(maximaIndex, maxima);
			//mean.clear();
			for (int i = 0; i < signalNew.size(); ++i){
				mean[i] = ((s_minima(i*step) + s_maxima(i*step)) / 2);
			}

			//ha imf, kiepunk, maskepp kivonjuk a nagy jelbol
			if (isIMF(residue, minima.size() + maxima.size(), mean)){
				ofstream o("atlag.txt", ios_base::app);
				o << endl;
				for (int i = 0; i < residue.size(); ++i){
					signal[i] -= residue[i];
					o << signal[i] << " ";
					//kivonjuk az imf-et az eredeti jelbol
				}
				o << endl;
				for (auto &v : residue){
					o << v << " ";
				}
				o << endl;
				o.close();
				break;
			}
			else
			{
				for (int i = signal.size(); i--;){
					signalNew[i] = signal[i] - residue[i];
				}
			}
		}
	} while (minima.size() + maxima.size() > 2);
}