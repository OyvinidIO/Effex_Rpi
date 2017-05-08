////WINDOWS Info:
///*
//Windows95/98/2000/XP/7:
//Realtime support is available using either DirectSound, ASIO or WASAPI audio drivers.
//- For DirectSound support, use the __WINDOWS_DS__ preprocessor definition and link with the dsound.lib, winmm.lib, and Wsock32.lib libraries.
//- For ASIO support, use the __WINDOWS_ASIO__ preprocessor definition, include all the files in the src/asio/ directory
//(i.e. asio.h,cpp, asiodrivers.h,cpp, ...), and link with the winmm.lib, and Wsock32.lib libraries.
//- For WASAPI support, use the __WINDOWS_WASAPI__ preprocessor definition.
//
//In addition, the __LITTLE_ENDIAN__ and __WINDOWS_MM__ preprocessor definitions are necessary for all Windows systems
//(RtMidi uses the Windows MultiMedia MIDI API). Fairly old Visual C++ project files are provided in each project directory,
//though they may not work on newer versions of MSVS. As well, the MinGW compiler is supported (see below). It is important
//to link with the non-debug libraries when compiling "release" program versions and debug libraries when compiling "debug"
//program versions.
//*/
////Linux Info:
///*
//Linux: Realtime audio support is enabled with either the __LINUX_ALSA__, __UNIX_JACK__, and/or __LINUX_OSS__ preprocessor definitions,
//which are used to select the underlying audio system API(s). Because the ALSA library is now integrated into the standard Linux kernel, 
//it is the default audio/MIDI API with STK versions 4.2 and higher. The __LINUX_ALSASEQ__ preprocessor definition must be included for 
//MIDI support. Note that native OSS MIDI support no longer exists in RtMidi. If the __LINUX_OSS__ preprocessor definition is specified, 
//only OSS (version 4.0) audio support will be compiled and RtMidi will still be compiled using the ALSA API (assuming the __LINUX_ALSASEQ__ 
//definition is defined). For this reason, STK now requires the asound library for realtime support. Realtime programs must also link with 
//the pthread library. In addition, the __LITTLE_ENDIAN__ preprocessor definition is necessary if compiling on a little-endian system. See 
//the README-Linux file for further system configuration information.
//*/


#include "deps/STK/src/stk/RtAudio.h"
#include "deps/STK/src/stk/Stk.h"
#include <iostream>
#include "CleanEffect.h"
#include "EffectManager.h"
#include "DelayEffect.h"
using namespace stk; 
using namespace std;

// Using a global object to hold the effects for simplicity.
EffectManager effectManager;

int cbFunc(void *outputBuffer, void *inputBuffer, unsigned int nBufferFrames, double, RtAudioStreamStatus, void *) {
	effectManager.applyEffect((double*)inputBuffer, (double*)outputBuffer, nBufferFrames);
	return 0;
}

int main()
{
	// Declare parameters
	unsigned int nBufferFrames = 256;
	unsigned int sampleRate = 44100;
	unsigned int nIChannels = 1;
	unsigned int nOChannels = 2;
	RtAudio* adac = new RtAudio();
	RtAudio::StreamOptions StreamOptions;
	StreamOptions.flags = RTAUDIO_NONINTERLEAVED;


	// Effex parameters
	double maingain = 0.3;// Clean paramters
	double delaygain = 0.65*0.3; // Delay parameters
	int delayfactor = 400; // MS

	// Apply effects
	effectManager.setEffect(new CleanEffect(maingain));
	effectManager.setEffect(new DelayEffect(nBufferFrames, delaygain, delayfactor));
	
	// Open the default realtime output device.
	RtAudio::StreamParameters oParameters, iParameters;
	oParameters.deviceId = adac->getDefaultOutputDevice();
	iParameters.deviceId = adac->getDefaultInputDevice();
	oParameters.nChannels = nOChannels;
	iParameters.nChannels = nIChannels;
	
	try { 
		adac->openStream(&oParameters, &iParameters, RTAUDIO_FLOAT64, sampleRate, &nBufferFrames, cbFunc,NULL, &StreamOptions);
	}
	catch (RtAudioError &error) {
		//cout << "Now I'm here" << endl;
		error.printMessage();
		exit(EXIT_FAILURE);
	}
	try {
		adac->startStream();
		
	}
	catch (RtAudioError &error) {
		
		error.printMessage();
		exit(EXIT_FAILURE);
	}
	
	cout << "Play ... " << endl;	
	char input;
	cin.get(input); // block until user hits return

	try {
		adac->stopStream();
	}
	catch (RtAudioError &error) {
		error.printMessage();
	}
	delete adac;
	effectManager.deallocateEffects();
	return 0;
}