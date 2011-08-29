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
KinectView::KinectView(float width, float height, int layerIndex, ViewPort * viewPort, int nearThreshold, int farThreshold) 
						: BaseView(width, height), _layerIndex(layerIndex), _nearThreshold(nearThreshold), _farThreshold(farThreshold) {
	
	LOG_NOTICE("Constructing KinectView: " + ofToString(_nearThreshold) + " : " + ofToString(_farThreshold));
	
	if (viewPort == NULL) {
		
		LOG_VERBOSE("Creating KinectView with default ViewPort");
		
		_viewPort = new ViewPort(width, height);
		
	} else {
		
		LOG_VERBOSE("Creating KinectView with defined ViewPort");
		
		_viewPort = viewPort;
		
	}
	
	_depthPixels	= new unsigned char[(int)width * (int)height];
	_depthImage		= new ofxCvGrayscaleImage();
	_depthContour	= new ofxCvContourFinder();
	//_depthSmooth	= new vector<ofPoint>;
	//spline2D.setInterpolation(MSA::kInterpolationCubic);
	
	_depthImage->allocate(width, height);
	
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
	//_depthContour->draw(0, 0, _viewWidth, _viewHeight);
	ofSetColor(255, 255, 0, 255);
	for( int i=0; i<(int)_depthContour->blobs.size(); i++ ) {
		ofFill();
		ofBeginShape();
		for( int j=0; j<_depthContour->blobs[i].nPts; j++ ) {
			ofVertex( _depthContour->blobs[i].pts[j].x, _depthContour->blobs[i].pts[j].y );
		}
		ofEndShape(true);
		
	}
	ofSetColor(255, 255, 255);
	
	glPopMatrix();
	_viewFBO.end();
	
}

//--------------------------------------------------------------
void KinectView::setNearThreshold(int amount, bool relative) {
	if (relative) {
		_nearThreshold += amount;
	} else _nearThreshold = amount;
}

//--------------------------------------------------------------
void KinectView::setFarThreshold(int amount, bool relative) {
	if (relative) {
		_farThreshold += amount;
	} else _farThreshold = amount;
}