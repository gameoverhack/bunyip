/*
 *  MidiController.cpp
 *  Bunyip
 *
 *  Created by gameover on 23/08/11.
 *  Copyright 2011 trace media. All rights reserved.
 *
 */

#include "MidiController.h"

//--------------------------------------------------------------
MidiController::MidiController() {
	
	LOG_NOTICE("Constructing MidiController");
	
	/*InputParams1<string> ki;
	
	ki.setKey('a');
	ki.setParam1("moviename.mov");
	
	_appModel->registerInputToFunction("AppController::test", ki);
	*/
	_midiIn.openPort();
    _midiIn.setVerbose(true);
	
    ofAddListener(_midiIn.newMessageEvent, this, &MidiController::midiMessage);
	
}

//--------------------------------------------------------------
MidiController::~MidiController() {
	LOG_NOTICE("Destructing MidiController");
}

//--------------------------------------------------------------
void MidiController::midiMessage(ofxMidiEventArgs &args) {
	
	MidiMessage mm(args.port, args.channel, args.status, args.byteOne, args.byteTwo, args.timestamp);
	mm.print(true);
	
}

//--------------------------------------------------------------
void MidiController::executeFunction(int key) {

}