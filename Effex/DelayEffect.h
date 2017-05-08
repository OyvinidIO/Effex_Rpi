#pragma once
#include "IGuitarEffect.h"
class DelayEffect :
	public IGuitarEffect
{
public:
	DelayEffect(unsigned int bufferSize, double delayGain, int delayTime);
	~DelayEffect();
	int applyEffect(double * iData, double * oData, unsigned int bufferSize);

	void set_gain_(double gain);
	void set_dlyTime_(double dlyTime);
	int get_gain_();
	int get_dlyTime_();

private:
	int MAX_DLY_TIME_;
	double* samples_; // Buffer with samples for delay processing
	int sample_cntr_;
	double gain_; // Delay gain
	double dlyTime_; // MS between each repeat
	double sampleRate_;
};

