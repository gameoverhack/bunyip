/*
 *  MidiController.h
 *  Bunyip
 *
 *  Created by gameover on 23/08/11.
 *  Copyright 2011 trace media. All rights reserved.
 *
 */

#ifndef _H_MIDICONTROLLER
#define _H_MIDICONTROLLER

#include "ofMain.h"

#include "AppModel.h"
#include "MidiModel.h"

#include "ofxMidi.h"

class MidiController : public ofBaseApp {
	
public:
	
	MidiController();
	~MidiController();
	
private:
	
	ofxMidiIn			_midiIn;
	
	void				midiMessage(ofxMidiEventArgs& eventArgs);
	
};

#endif
