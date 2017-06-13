#pragma once
#include "IGuitarEffect.h"
class CleanEffect :public IGuitarEffect{
public:

	int applyEffect(double* iData, double* oData, unsigned int bufferSize);
	int changeEffectParameters(void* userdata);
	CleanEffect(double gain);
	~CleanEffect();

private:
	double gain_ ;
};

