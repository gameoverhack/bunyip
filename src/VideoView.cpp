/*
 *  VideoView.cpp
 *  Bunyip
 *
 *  Created by gameover on 29/08/11.
 *  Copyright 2011 trace media. All rights reserved.
 *
 */

#include "VideoView.h"

//--------------------------------------------------------------
VideoView::VideoView(float width, float height, int layerIndex, string videoPath, ViewPort * viewPort) 
: BaseView(width, height), _layerIndex(layerIndex), _videoPath(videoPath) {
	
	LOG_NOTICE("Constructing VideoView");
	
	if (viewPort == NULL) {
		
		LOG_VERBOSE("Creating VideoView with no ViewPort");
		
		//_viewPort = new ViewPort(width, height);
		
	} else {
		
		LOG_VERBOSE("Creating VideoView with defined ViewPort");
		
		_viewPort = viewPort;
		
	}
	
	_video = new goThreadedVideo();
	
	//if (videoPath != "") loadMovie();
	
}

//--------------------------------------------------------------
VideoView::~VideoView() {
	
	LOG_NOTICE("Destroying VideoView");
	
	delete _video;
	
}

//--------------------------------------------------------------
void VideoView::update() {
	
	_viewFBO.begin();
	glPushMatrix();
	
	//glClearColor(0.0, 0.0, 0.0, 0.0); // transparent clear colour
    //glClear(GL_COLOR_BUFFER_BIT);
	
	ofSetColor(255, 255, 255, 255);
	_video->draw(0, 0, _viewWidth, _viewHeight);
	
	glPopMatrix();
	_viewFBO.end();
	
}

//--------------------------------------------------------------
void VideoView::loadMovie(string videoPath) {
	
	if (videoPath != "") _videoPath = videoPath;
	
	_video->loadMovie(ofToDataPath(_videoPath));
}


