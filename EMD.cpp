#include "EMD.h"


EMD::EMD(string inputFile, string outputFile) : inputFile(inputFile), outputFile(outputFile)
{
}


EMD::~EMD()
{
}

bool EMD::isIMF(vector<double> &potentialIMF)
{
	int zeroCrossing = extrema.numberOfZeroCross();

}

void EMD::compute(vector<double> signal)
{
	vector<double> minima, maxima, minimaIndex, maximaIndex;
	vector<double> interpolationMinima, interpolationMaxima, interpolationMean;


}