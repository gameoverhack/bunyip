/*
 *  KinectController.h
 *  Bunyip
 *
 *  Created by gameover on 23/08/11.
 *  Copyright 2011 trace media. All rights reserved.
 *
 */

#ifndef _H_KINECTCONTROLLER
#define _H_KINECTCONTROLLER

#include "AppModel.h"
#include "KinectModel.h"
#include "BaseState.h"
#include "contourSimplify.h"

#include "ofxOpenCv.h"

enum {
	kKINECTCONTROLLER_INIT,
	kKINECTCONTROLLER_READY,
	kKINECTCONTROLLER_ERROR
};

class KinectController : public BaseState {
	
public:
	
	KinectController();
	~KinectController();
	
	void	registerStates();
	
	void	toggleRegisterKinectViewport();
	void	toggleMirrorKinectViewport();
	void	adjustNearThreshold(int forDepthThreshold, int amount);
	void	adjustFarThreshold(int forDepthThreshold, int amount);
	
	void	update();
	
private:
	
	
	
};

#endif