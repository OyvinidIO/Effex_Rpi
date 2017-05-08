#include "CombFilter.h"

int CombFilter::applyEffect(double* iData, double * oData, unsigned int bufferSize)
{
	// We know we only have 1 sample per frame here.
	for (unsigned int i = 0; i < bufferSize; i++) {
		oData[i] = iData[i] + 0.98 * delay_.lastOut(); // feedback comb
														//    odata[i] = idata[i] + delay.tick( idata[i] ); // feedforward comb
		oData[i] *= 0.45;
		delay_.tick(oData[i]);  // feedback comb
	}
	return 0;
}

CombFilter::~CombFilter()
{
}

