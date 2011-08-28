/*
 *  KinectModel.h
 *  Bunyip
 *
 *  Created by gameover on 24/08/11.
 *  Copyright 2011 trace media. All rights reserved.
 *
 */

#ifndef _H_KINECTMODEL
#define _H_KINECTMODEL

#include "Singleton.h"
#include "Logger.h"

#include "ofxOpenNI.h"

class KinectModel {
	
public:
	
	KinectModel() {
		
		LOG_NOTICE("Constructing KinectModel");
		
		_oniContext = new ofxOpenNIContext();
		_oniDepthGen = new ofxDepthGenerator();
		_oniImageGen = new ofxImageGenerator();
        _oniIRGen = new ofxIRGenerator();
		_oniUserGen = new ofxUserGenerator();
		_oniHandGen = new ofxHandGenerator();

	};
	
	~KinectModel() {
		
		LOG_NOTICE("Destructing KinectModel");
		
		delete _oniDepthGen;
		delete _oniImageGen;
        delete _oniIRGen;
		delete _oniUserGen;
		delete _oniHandGen;
		delete _oniContext;
		
	};	
	
	ofxOpenNIContext*	getONIContext() {return _oniContext;};
	ofxDepthGenerator*	getONIDepthGen() {return _oniDepthGen;};
	ofxImageGenerator*	getONIImageGen() {return _oniImageGen;};
    ofxIRGenerator*     getONIIRGen() {return _oniIRGen;};
	ofxUserGenerator*	getONIUserGen() {return _oniUserGen;};
	ofxHandGenerator*	getONIHandGen() {return _oniHandGen;};
	
private:
	
	ofxOpenNIContext*	_oniContext;
	ofxDepthGenerator*	_oniDepthGen;
	ofxImageGenerator*	_oniImageGen;
    ofxIRGenerator*     _oniIRGen;
	ofxUserGenerator*	_oniUserGen;
	ofxHandGenerator*	_oniHandGen;
	
};

typedef Singleton<KinectModel> KinectModelSingleton;					// Global declaration

static KinectModel * _kinectModel	= KinectModelSingleton::Instance();	// this is my idea of a compromise:
// no defines, keeps introspection
// but allows data sharing between classes


#endif