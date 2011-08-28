/*
 *  KinectView.h
 *  Bunyip
 *
 *  Created by gameover on 23/08/11.
 *  Copyright 2011 trace media. All rights reserved.
 *
 */

#ifndef _H_KINECTVIEW
#define _H_KINECTVIEW

#include "KinectModel.h"
#include "BaseView.h"
#include "ofxOpenNI.h"
#include "ofxOpenCv.h"
//#include "MSAInterpolator.h"

class KinectView : public BaseView {

public:

	KinectView(float width, float height, ViewPort * viewPort = NULL);
	~KinectView();
	
	void update();
	
	ofxCvGrayscaleImage*	getDepthImage() {return _depthImage;};
	ofxCvContourFinder*		getDepthContour() {return _depthContour;};
	unsigned char*			getDepthPixels() {return _depthPixels;};
	
private:
	
	ofxCvGrayscaleImage*	_depthImage;
	ofxCvContourFinder*		_depthContour;
	unsigned char*			_depthPixels;
	
};

#endif