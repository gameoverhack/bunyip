/*
 *  VideoController.h
 *  Bunyip
 *
 *  Created by gameover on 24/08/11.
 *  Copyright 2011 trace media. All rights reserved.
 *
 */

#ifndef _H_VIDEOCONTROLLER
#define _H_VIDEOCONTROLLER

#include "AppModel.h"
#include "Logger.h"
#include "goThreadedVideo.h"

class VideoController {

public:
	
	VideoController();
	~VideoController();
	
	void update();
	
	void setupVideoLayers();
	void stopVideoLayers();
	
//	void errored(int & e);
//	void loaded(string & e);
	
private:
	
};

#endif