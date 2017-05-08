#pragma once
#include "IGuitarEffect.h"

/*Nonlinear function for fuzz/distortion found in some pdf:
f(x) = sign(x)*(1-exp(abs(x)));
*/

class Distortion :
	public IGuitarEffect
{
public:
	Distortion(double gain, double mix) : m_gain(gain), m_mix() {};
	~Distortion();

	int applyEffect(double* iData, double* oData, unsigned int bufferSize);

private:
	double m_gain;
	double m_mix;
};

