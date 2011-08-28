/*
 *  BaseView.h
 *  Jungle
 *
 *  Created by gameover on 29/06/11.
 *  Copyright 2011 trace media. All rights reserved.
 *
 */

#ifndef _H_BASEVIEW
#define _H_BASEVIEW

#include "ViewPort.h"
#include "Logger.h"

#include "ofxOpenCv.h"
#include "ofxFbo.h"


class BaseView {

public:

	BaseView(float width, float height);	//ctor
	virtual ~BaseView();						//dtor

	virtual void update() = 0; // update view fbo to draw image

	virtual void draw(); // draw out the view fbo
	virtual void draw(float x, float y);
	virtual void draw(float x, float y, float width, float height);

	// Returns the views fbo
	ofxFbo		* getViewFBO();
	ofTexture	* getViewFBOTexture();

    float         getWidth();
    float         getHeight();

	ViewPort*	  getViewPort() {return _viewPort;};
	
protected:

	void		  warp(int width, int height, ofPoint * corners);

	ViewPort*	_viewPort;
	
	float		_viewWidth, _viewHeight;

	ofxFbo		_viewFBO; // final output FBO

	ofTexture	_viewFBOTexture; // Texture for final output FBO

};

#endif
