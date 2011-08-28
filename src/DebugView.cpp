/*
 *  DebugView.cpp
 *  Bunyip
 *
 *  Created by gameover on 23/08/11.
 *  Copyright 2011 trace media. All rights reserved.
 *
 */

#include "DebugView.h"

//--------------------------------------------------------------
DebugView::DebugView(float width, float height) : BaseView(width, height) {
	
	LOG_NOTICE("Constructing DebugView");
	
}

//--------------------------------------------------------------
void DebugView::update() {
	
	Scene* currentScene = _appModel->getCurrentScene();
	
	float displayOffsetX = 0;
	
	if (boost::any_cast<bool>(_appModel->getProperty("showDualScreen"))) {
		displayOffsetX = ofGetWidth() - 1024.0f;
	}
	
	string msg = "FPS: " + ofToString(ofGetFrameRate()) + "\n\n";
	
	if (boost::any_cast<bool>(_appModel->getProperty("showProps"))) {
		msg += _appModel->getAllPropsAsList() + "\n";
		msg += _appModel->_keyboardModel->getAllKeyboardUsageAsList(false) + "\n";
		msg += _appModel->getAllStatesAsList() + "\n";
	}
	
	_viewFBO.begin();
	
	glPushMatrix();
	
	glClearColor(0.0, 0.0, 0.0, 0.0); // transparent clear colour
    glClear(GL_COLOR_BUFFER_BIT);
	
	for (int layer = 0; layer < currentScene->getNumberOfKinectLayers(); layer++) {
		glPushMatrix();
		KinectView* kinectLayer		= currentScene->getKinectLayer(layer);
		ViewPort* viewPort			= kinectLayer->getViewPort();
		
		float x = 10+(layer * ( 14 + kinectLayer->getWidth()/4.0f ));
		float y = 10;
		float width = kinectLayer->getWidth()/4.0f;
		float height = kinectLayer->getHeight()/4.0f;
		
		glTranslatef(0.0f, _viewHeight, 0.0f);
		glScaled(1.0f, -1.0f, 0.0f);
		viewPort->drawViewport(x, y, width, height); // upside down mr squiggle
		glPopMatrix();
	}
	
	ofSetColor(0, 255, 255);
	ofDrawBitmapString(msg, 20, 20);
	ofSetColor(255, 255, 255);
	
	glPopMatrix();
	
	_viewFBO.end();

}