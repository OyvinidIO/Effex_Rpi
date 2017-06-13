#pragma once
#include "IGuitarEffect.h"
class DelayEffect :
	public IGuitarEffect
{
public:
	DelayEffect(unsigned int bufferSize, double delayGain, int delayTime);
	~DelayEffect();
	int applyEffect(double * iData, double * oData, unsigned int bufferSize);
	int changeEffectParameters(void * userdata);

	void set_gain_(double gain);
	void set_dlyTime_(double dlyTime);
	int get_gain_();
	int get_dlyTime_();

private:	
	int dlyBufferSize_;
	double* dlyBuffer_; // Buffer with samples for delay processing
	int sample_cntr_;
	double dlyGain_; // Delay gain
	double dlyTime_; // MS between each repeat
	int dlySamples_; // delay time in samples
	double sampleRate_;
};

