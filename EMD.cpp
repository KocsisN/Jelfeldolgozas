#include "EMD.h"

EMD::EMD(double step) : step(step)
{

}

EMD::EMD(string inputFile, string outputFile) : inputFile(inputFile), outputFile(outputFile)
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
	double *x = &signal[0];
	int zeroCrossing = 0;
	for (int i = 1; i < signal.size(); ++i){
		(signbit(x[i]) != signbit(x[i - 1])) ? ++zeroCrossing : zeroCrossing;
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


	//cout << "return isIMF:\n\t zeroCrossing: " << zeroCrossing << "\n\tnumOfExtrema: " << numberOfExtremas
	//	<< "\n\tnonZeroPoints: " << nonzeroPoints << endl;
	//cin.get();

	return (abs(zeroCrossing - numberOfExtremas) < 2 && nonzeroPoints == 0);

}

void EMD::compute(vector<double> &signal)
{

	const size_t NROFELEMENTS = signal.size();

	int nrofimf = 1;
	int ss = signal.size();
	vector<double> minima(ss), maxima(ss), minimaIndex(ss), maximaIndex(ss);
	vector<double> residue(ss), mean(ss), signalNew(ss);
	spline::spline3 s_minima, s_maxima;
	bool DONE = false;

	double *pMean = &mean[0];
	double *pSignalNew = &signalNew[0];
	double *pResidue = &residue[0];
	double *pSignal = &signal[0];

	ofstream o("output.dat");

	//cout << "Jel kiirva" << endl;
	while (!DONE){
		//minima.clear(); maxima.clear();
		minimaIndex.clear(); maximaIndex.clear();
		//residue.clear();
		//mean.clear(); signalNew.clear();

		signalNew = signal;
		chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

		while (true){
			//lebontjuk az elso tenyezot
			//mean.clear();

			/***************************EXTREMAK*****************************/
			extrema.getExtremas(signalNew, minima, minimaIndex, maxima, maximaIndex);


			if (minima.size() < 2 || maxima.size() < 2){
				DONE = true;
				break;
			}

			/**************************INTERPOLACIO****************************/
			try{
				s_minima.set_points(minimaIndex, minima);
				s_maxima.set_points(maximaIndex, maxima);
			}
			catch (...){
				DONE = true;
				//cout << "\nmin:" << minima.size() << "\tmax: " << maxima.size() << endl;
				break;
			}

			//ofstream omi("min.txt"), oma("max.txt");

			/************************KIVONAS**********************************/
			for (int i = 0; i < NROFELEMENTS; ++i){
				//mean.push_back((s_minima(i*step) + s_maxima(i*step)) / 2);
				pMean[i] = (s_minima(i*step) + s_maxima(i*step)) / 2;

				//omi << s_minima(i*step) << endl;
				//oma << s_maxima(i*step) << endl;
				//az atlag izet kivonom a jelbol
				pResidue[i] = (pSignalNew[i] - pMean[i]);
			}
			//omi.close(); oma.close();
			//cout << "Minima and maxima out, press\n"; //cin.get();

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
				//cout << "\nmin:" << minima.size() << "\tmax: " << maxima.size() << endl;
				break;
			}
			//mean.clear();
			//ofstream momi("meanmin.txt"), moma("meanmax.txt");
			for (int i = 0; i < NROFELEMENTS; ++i){
				//mean[i] = ((s_minima(i*step) + s_maxima(i*step)) / 2);

				pMean[i] = ((s_minima(i*step) + s_maxima(i*step)) / 2);

				//momi << s_minima(i*step) << endl;
				//moma << s_maxima(i*step) << endl;
			}
			//momi.close(); moma.close();
			//cout << "Mean Minima and Mean Maxima out, press\n"; //cin.get();

			//ha imf, kiepunk, maskepp kivonjuk a nagy jelbol
			if (isIMF(residue, minima.size() + maxima.size(), mean)){

				o << endl;
				for (int i = 0; i < residue.size(); ++i){
					/*o << residue[i] << " ";
					signal[i] -= residue[i];*/

					o << pResidue[i] << " ";
					pSignal[i] -= pResidue[i];

					//o << signal[i] << " ";
					//kivonjuk az imf-et az eredeti jelbol
				}
				o << endl;
				//cout << "\t\t\tIMF found" << endl;
				//o.close();
				break;
			}
			else
			{
				for (int i = 0; i < residue.size(); ++i){
					//signalNew[i] = residue[i];
					pSignalNew[i] = pResidue[i];
				}
			}
			//cout << "Round done, press\n"; //cin.get();
		}
		cout << "\t\tThe " << nrofimf++ << ". imf found.\n";// cin.get();
		chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
		cout << "Elapsed seconds: " << chrono::duration_cast<std::chrono::seconds>(end - begin).count() << endl;
	}
	o.close();
	//cout << "Job's done: " << endl;
}