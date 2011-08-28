/*
 *  BaseView.cpp
 *  Jungle
 *
 *  Created by gameover on 29/06/11.
 *  Copyright 2011 trace media. All rights reserved.
 *
 */

#include "BaseView.h"

BaseView::BaseView(float width, float height) {
	
	LOG_NOTICE("Constructing BaseView");
	
	// save parameters
	_viewWidth = width;
	_viewHeight = height;

	// Create black pixels for inital texture, TODO: Potentially not required
	unsigned char * black = (unsigned char *)calloc(_viewWidth * _viewHeight * 4, sizeof(unsigned char));

	// allocate the fbo texture
	_viewFBOTexture.allocate(_viewWidth, _viewHeight, GL_RGBA);
	_viewFBOTexture.loadData(black, _viewWidth, _viewHeight, GL_RGBA);

	// set up fbo and attach texture
	_viewFBO.setup(_viewWidth, _viewHeight);
	_viewFBO.attach(_viewFBOTexture);

	// Free black pixels
	free(black);
	
	_viewPort = NULL;
	
}

BaseView::~BaseView() {
	
	LOG_NOTICE("Destroying BaseView");
	
	_viewFBO.detach(0);
	_viewFBOTexture.clear();
	delete _viewPort;
	
}

// Returns the views fbo
ofxFbo * BaseView::getViewFBO(){
	return &_viewFBO;
}

ofTexture * BaseView::getViewFBOTexture(){
	return &_viewFBOTexture;
}

float BaseView::getWidth() {
    return _viewWidth;
}
float BaseView::getHeight() {
    return _viewHeight;
}

void BaseView::warp(int width, int height, ofPoint * corners) {
	
	GLfloat myMatrix[16];
	
	for(int i = 0; i < 16; i++){
		if(i % 5 != 0) myMatrix[i] = 0.0;
		else myMatrix[i] = 1.0;
	}
	
	CvPoint2D32f cvsrc[4];
	CvPoint2D32f cvdst[4];	
	
	cvsrc[0].x = 0;
	cvsrc[0].y = 0;
	cvsrc[1].x = width;
	cvsrc[1].y = 0;
	cvsrc[2].x = width;;
	cvsrc[2].y = height;
	cvsrc[3].x = 0;
	cvsrc[3].y = height;			
	
	for(int i = 0; i < 4; i++){
		cvdst[i].x = corners[i].x * (float)width;
		cvdst[i].y = corners[i].y * (float)height;
	}
	
	CvMat * translate = cvCreateMat(3,3,CV_32FC1);
	
	CvMat* src_mat = cvCreateMat( 4, 2, CV_32FC1 );
	CvMat* dst_mat = cvCreateMat( 4, 2, CV_32FC1 );
	
	cvSetData( src_mat, cvsrc, sizeof(CvPoint2D32f));
	cvSetData( dst_mat, cvdst, sizeof(CvPoint2D32f));
	
	cvFindHomography(src_mat, dst_mat, translate);
	
	float *matrix = translate->data.fl;     
	
	myMatrix[0]		= matrix[0];
	myMatrix[4]		= matrix[1];
	myMatrix[12]	= matrix[2];
	
	myMatrix[1]		= matrix[3];
	myMatrix[5]		= matrix[4];
	myMatrix[13]	= matrix[5];	
	
	myMatrix[3]		= matrix[6];
	myMatrix[7]		= matrix[7];
	myMatrix[15]	= matrix[8];	
	
	glMultMatrixf(myMatrix);
	
	cvReleaseMat(&translate);
	cvReleaseMat(&src_mat);
	cvReleaseMat(&dst_mat);	
	
}

void BaseView::draw() {
	glPushMatrix();
	if (_viewPort != NULL) warp(_viewPort->getWidth(), _viewPort->getHeight(), _viewPort->getCorners());
	_viewFBO.draw(0, 0);
	glPopMatrix();
}

void BaseView::draw(float x, float y) {
	glPushMatrix();
	glTranslatef(x, y, 0.0f);
	draw();
	glPopMatrix();
}

void BaseView::draw(float x, float y, float width, float height) {
	glPushMatrix();
	glTranslatef(x, y, 0.0f);
	glScalef(width/_viewWidth, height/_viewHeight, 0.0f);
	draw();
	glPopMatrix();
}
