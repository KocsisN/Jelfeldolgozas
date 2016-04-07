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
	int zeroCrossing = 0;
	for (int i = 1; i < signal.size(); ++i){
		(signbit(signal[i]) != signbit(signal[i - 1])) ? ++zeroCrossing : zeroCrossing;
	}
	/*int zeroCrossing = count_if(signal.begin(), signal.end(), [](double el)
	{
		return (el < EPSFORZERO && el > -EPSFORZERO);
	});
*/
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
	
	cout << "return isIMF:\n\t zeroCrossing: " << zeroCrossing << "\n\tnumOfExtrema: " << numberOfExtremas
		<< "\n\tnonZeroPoints: " << nonzeroPoints << "\n\t\tPress\n";
	//cin.get();

	return (abs(zeroCrossing - numberOfExtremas) < 2 && nonzeroPoints == 0);
	
}

void EMD::compute(vector<double> &signal)
{
	int nrofimf = 0;
	int ss = signal.size();
	vector<double> minima(ss), maxima(ss), minimaIndex(ss), maximaIndex(ss);
	vector<double> residue(ss), mean(ss), signalNew(ss);
	spline::spline3 s_minima, s_maxima;
	bool DONE = false;
	ofstream q("atlag.txt"); q << "";
	q.close();
	//ofstream q2("m.txt"); q2 << ""; q2.close();
	//while signal has more tha 2 extremas


	cout << "Jel kiirva" << endl;
	while(!DONE){
		minima.clear(); maxima.clear();
		minimaIndex.clear(); maximaIndex.clear();
		//residue.clear();
		mean.clear(); signalNew.clear();

		//find the first imf
		ofstream o("NewSignalo.txt");
		for (auto &i : signal){
			o << i << endl;
		}
		o.close();

		signalNew = signal;
		while (true){
			//lebontjuk az elso tenyezot
			mean.clear();

			/***************************EXTREMAK*****************************/
			extrema.getExtremas(signalNew, minima, minimaIndex, maxima, maximaIndex);


			if (minima.size() < 2 || maxima.size() < 2){
				DONE = true;
				cout << "Itt van";
				break;
			}

			/**************************INTERPOLACIO****************************/
			try{
				s_minima.set_points(minimaIndex, minima);
				s_maxima.set_points(maximaIndex, maxima);
			}
			catch (...){
				DONE = true;
				cout << "\nmin:" << minima.size() << "\tmax: " << maxima.size() << endl;
				break;
			}

			//ofstream omi("min.txt"), oma("max.txt");

			/************************KIVONAS**********************************/
			for (int i = 0; i < signalNew.size(); ++i){
				mean.push_back((s_minima(i*step) + s_maxima(i*step)) / 2);
				//omi << s_minima(i*step) << endl;
				//oma << s_maxima(i*step) << endl;
				//az atlag izet kivonom a jelbol
				residue[i] = (signalNew[i] - mean[i]);
			}
			//omi.close(); oma.close();
			cout << "Minima and maxima out, press\n"; //cin.get();

			/*ofstream o("residue.txt");
			for (auto &i : residue){
				o << i << endl;
			}
			o.close();*/
			//az uj izere ellenorziiuk, hogy imf-e
			extrema.getExtremas(residue, minima, minimaIndex, maxima, maximaIndex);

			try{
				s_minima.set_points(minimaIndex, minima);
				s_maxima.set_points(maximaIndex, maxima);
			}
			catch (...){
				DONE = true;
				cout << "\nmin:" << minima.size() << "\tmax: " << maxima.size() << endl;
				break;
			}
			//mean.clear();
			//ofstream momi("meanmin.txt"), moma("meanmax.txt");
			for (int i = 0; i < signalNew.size(); ++i){
				mean[i] = ((s_minima(i*step) + s_maxima(i*step)) / 2);
				//momi << s_minima(i*step) << endl;
				//moma << s_maxima(i*step) << endl;
			}
			//momi.close(); moma.close();
			cout << "Mean Minima and Mean Maxima out, press\n"; //cin.get();

			//ha imf, kiepunk, maskepp kivonjuk a nagy jelbol
			if (isIMF(residue, minima.size() + maxima.size(), mean)){
				
				ofstream o("atlag.txt");
				o << endl;
				for (int i = 0; i < residue.size(); ++i){
					o << residue[i] << endl;
					signal[i] -= residue[i];
					//o << signal[i] << " ";
					//kivonjuk az imf-et az eredeti jelbol
				}
				o << endl;
				cout << "\t\t\tIMF found" << endl;
				/*for (auto &v : residue){
					o << v << " ";
				}
				o << endl;
				o.close();*/
				break;
			}
			else
			{
				for (int i = 0; i < residue.size(); ++i){
					signalNew[i] = residue[i];
				}
				//ofstream o("NewSignal.txt");  o << endl;
				//for (auto &i : residue){
				//	o << i << endl;
				//}
				//o << endl;
				//o.close();

				//cout << "Not an IMF" << endl;// cin.get();
			}
			cout << "Round done, press\n"; //cin.get();
		}
		cout << "\t\tThe " << ++nrofimf << ". imf found.\n\n"; cin.get();
	}
	cout << "Job's done: " << nrofimf << endl;
}