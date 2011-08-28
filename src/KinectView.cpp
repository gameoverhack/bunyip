/*
 *  KinectView.cpp
 *  Bunyip
 *
 *  Created by gameover on 23/08/11.
 *  Copyright 2011 trace media. All rights reserved.
 *
 */

#include "KinectView.h"

//--------------------------------------------------------------
KinectView::KinectView(float width, float height, ViewPort * viewPort) : BaseView(width, height) {
	
	LOG_NOTICE("Constructing KinectView");
	
	if (viewPort == NULL) {
		
		LOG_VERBOSE("Creating KinectView with default ViewPort");
		
		_viewPort = new ViewPort(width, height);
		
	} else {
		
		LOG_VERBOSE("Creating KinectView with defined ViewPort");
		
		_viewPort = viewPort;
		
	}
	
	_depthPixels	= new unsigned char[640 * 480];
	_depthImage		= new ofxCvGrayscaleImage();
	_depthContour	= new ofxCvContourFinder();
	//_depthSmooth	= new vector<ofPoint>;
	//spline2D.setInterpolation(MSA::kInterpolationCubic);
	
	_depthImage->allocate(640, 480);
	
}

//--------------------------------------------------------------
KinectView::~KinectView() {
	
	LOG_NOTICE("Destroying KinectView");
	
	_depthImage->clear();
	
	//delete _viewPort;
	delete _depthImage;
	delete _depthContour;
	//delete _depthSmooth;
	delete [] _depthPixels;
	
}

//--------------------------------------------------------------
void KinectView::update() {
	
	_viewFBO.begin();
	glPushMatrix();
	
	glClearColor(0.0, 0.0, 0.0, 0.0); // transparent clear colour
    glClear(GL_COLOR_BUFFER_BIT);
	
	//_depthImage->draw(0, 0, _viewWidth, _viewHeight);
	_depthContour->draw(0, 0, _viewWidth, _viewHeight);
	
	glPopMatrix();
	_viewFBO.end();
	
}