#include "CleanEffect.h"
#include <cstring>

using namespace std;

int CleanEffect::applyEffect(double* iData, double* oData, unsigned int bufferSize) {
		
	// We know we only have 1 sample per frame here.
	for (unsigned int i = 0; i < bufferSize; i++) {
		oData[i] = gain_*iData[i];
		oData[i + bufferSize] = gain_*iData[i];
	}
	
	return 0;
}
CleanEffect::CleanEffect(double gain) {
	gain_ = gain;
	
}

CleanEffect::~CleanEffect(){

}
