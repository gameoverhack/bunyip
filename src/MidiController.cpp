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
	
	_midiIn.openPort();
    //_midiIn.setVerbose(true);
	
    ofAddListener(_midiIn.newMessageEvent, this, &MidiController::midiMessage);
	
}

//--------------------------------------------------------------
MidiController::~MidiController() {
	LOG_NOTICE("Destructing MidiController");
}

//--------------------------------------------------------------
void MidiController::midiMessage(ofxMidiEventArgs &args) {
	
	MidiMessage midiMessage(args.port, args.channel, args.status, args.byteOne, args.byteTwo, args.timestamp);
	_midiModel->executeFunction(midiMessage);
	
}