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

	KinectView(float width, float height, int layerIndex, float smoothContourThreshold = 0.2, int minSizeBlobs = 1000, int maxSizeBlobs = 200000, ViewPort * viewPort = NULL, int nearThreshold = 0, int farThreshold = 10000);
	~KinectView();
	
	void update();
	
	ofxCvGrayscaleImage*	getDepthImage() {return _depthImage;};
	ofxCvContourFinder*		getDepthContour() {return _depthContour;};
	unsigned char*			getDepthPixels() {return _depthPixels;};
	
	int*					getNearThreshold() {return &_nearThreshold;};
	int*					getFarThreshold() {return &_farThreshold;};
	int*					getMinSizeContourBlobs() {return &_minSizeBlobs;};
	int*					getMaxSizeContourBlobs() {return &_maxSizeBlobs;};
	float*					getSmoothContourThreshold() {return &_smoothContourThreshold;};
	int*					getLayerIndex() {return &_layerIndex;};
	
	void					setNearThreshold(int amount, bool relative = false);
	void					setFarThreshold(int amount, bool relative = false);
	void					setMinSizeContourBlobs(int amount, bool relative = false);
	void					setMaxSizeContourBlobs(int amount, bool relative = false);
	void					setSmoothContourThreshold(float amount, bool relative = false);
	
private:
	
	ofxCvGrayscaleImage*	_depthImage;
	ofxCvContourFinder*		_depthContour;
	unsigned char*			_depthPixels;
	
	int						_nearThreshold;
	int						_farThreshold;
	int						_minSizeBlobs;
	int						_maxSizeBlobs;
	
	float					_smoothContourThreshold;
	
	int						_layerIndex;
	
};

#endif