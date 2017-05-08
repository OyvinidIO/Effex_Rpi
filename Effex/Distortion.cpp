#include "Distortion.h"
#include <math.h>
#include <cmath>


Distortion::~Distortion()
{
}

int Distortion::applyEffect(double* iData, double* oData, unsigned int bufferSize) {
	//double max = 0.0, maxAbsZ, sampleAbs, q, y;
	//double* z = new double[bufferSize];

	////do preparatory calculations: calculate max sample value and function values
	//for (int i = 0; i < bufferSize; i++) {
	//	sampleAbs = abs(iData[i]);
	//	if (sampleAbs > max) {
	//		max = sampleAbs;
	//	}
	//}

	//maxAbsZ = max * m_gain;
	//TODO

	/*for (unsigned int i = 0; i < bufferSize; i++) {
		q = iData[i]* m_gain / max;
		z = sgn(-q)*(1 - exp(sgn(-q)*q));
		y = m_mix * z * max / max(abs(z)) + (1 - mix)*x;
		y = y*max(abs(x)) / max(abs(y));
	}*/
	return 0;
}
