/*
 *  ViewPort.h
 *  Bunyip
 *
 *  Created by gameover on 28/08/11.
 *  Copyright 2011 trace media. All rights reserved.
 *
 */

#ifndef _H_VIEWPORT
#define _H_VIEWPORT

#include "ofMain.h"

class ViewPort {
	
public:
	
	ViewPort(float width, float height) : _width(width), _height(height) {_corners = new ofPoint[4];reset(width, height);};
	
	ViewPort(float x, float y, float width, float height, ofPoint * corners)
	: _x(x), _y(y), _width(width), _height(height), _corners(corners) {};
	
	~ViewPort() {delete [] _corners;};
	
	void reset(float width, float height) {
		
		_x				= 0.0f;
		_y				= 0.0f;
		_width			= width;
		_height			= height;
		_corners[0].x	= 0.0f;
		_corners[0].y	= 0.0f;
		_corners[1].x	= 1.0f;
		_corners[1].y	= 0.0f;
		_corners[2].x	= 1.0f;
		_corners[2].y	= 1.0f;
		_corners[3].x	= 0.0f;
		_corners[3].y	= 1.0f;
		
	};
	
	void drawViewport() {
		glPushMatrix();
		
		ofNoFill();
		ofSetColor(0, 255, 0);
		ofRect(0, 0, _width, _height);
		ofSetColor(255, 255, 255, 255);
		
		ofNoFill();
		ofSetColor(255, 0, 0);
		ofBeginShape();
		for(int corner = 0; corner < 4; corner++){
			ofVertex(_x + _corners[corner].x * _width, 
					 _y + _corners[corner].y * _height);
		}
		ofEndShape(true);
		ofSetColor(255, 255, 255, 255);
		glPopMatrix();
	}
	
	void drawViewport(float x, float y) {
		
		_editX		= x;
		_editY		= y;
		_editScaleX = 1.0f;
		_editScaleY	= 1.0f;
		
		glPushMatrix();
		glTranslatef(_editX, _editY, 0.0f);
		drawViewport();
		glPopMatrix();
	}
	
	void drawViewport(float x, float y, float width, float height) {
		
		_editX		= x;
		_editY		= y;
		_editScaleX = width/_width;
		_editScaleY	= height/_height;
		
		glPushMatrix();
		glTranslatef(_editX, _editY, 0.0f);
		glScalef(_editScaleX, _editScaleY, 0.0f);
		drawViewport();
		glPopMatrix();
	}
	
	void		setX(float x) {_x = x;};
	void		setY(float y) {_y = y;};
	void		setWidth(float width) {_width = width;};
	void		setHeight(float height) {_height = height;};
	
	float		getX() {return _x;};
	float		getY() {return _y;};
	float		getWidth() {return _width;};
	float		getHeight() {return _height;};
	ofPoint*	getCorners() {return _corners;};
	
	float		getEditX() {return _editX;};
	float		getEditY() {return _editY;};
	float		getEditScaleX() {return _editScaleX;};
	float		getEditScaleY() {return _editScaleY;};		
	
private:
	
	float		_x;
	float		_y;
	float		_width;
	float		_height;
	ofPoint*	_corners;
	
	float		_editX;
	float		_editY;
	float		_editScaleX;
	float		_editScaleY;
	
};

#endif