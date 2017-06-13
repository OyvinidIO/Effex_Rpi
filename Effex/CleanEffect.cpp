#include "CleanEffect.h"
#include "MsgStruct.h"
#include <cstring>

using namespace std;

int CleanEffect::changeEffectParameters(void * userdata) {

	effectParamsChanged_ = false;
	
	MsgFromUser* msg = (MsgFromUser*)userdata;
	if (!(msg->header_.EffectName == "clean")) {
		effectParamsChanged_ = false;
		return 0;
	}

	// # Header #
	enableEffect_ = msg->header_.enable;

	// # PARAM 1 # Master volume
	gain_ = msg->body_.params[0];

	// Report effect changed
	effectParamsChanged_ = true;
	
	return 0;
}


int CleanEffect::applyEffect(double* iData, double* oData, unsigned int bufferSize) {
		
	// We know we only have 1 sample per frame here.
	double sample;
	for (unsigned int i = 0; i < bufferSize; i++) {
		sample = gain_*iData[i];
		oData[i] = sample;
		oData[i + bufferSize] = sample;
	}
	
	return 0;
}
CleanEffect::CleanEffect(double gain) {
	gain_ = gain;
	
}

CleanEffect::~CleanEffect(){

}

