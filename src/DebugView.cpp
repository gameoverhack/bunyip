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
	
	if (currentScene== NULL) return;
	
	string msg = "FPS: " + ofToString(ofGetFrameRate()) + "\n\n";
	
	if (boost::any_cast<bool>(_appModel->getProperty("showProps"))) {
		msg += _appModel->getAllPropsAsList() + "\n";
		msg += _keyModel->getAllKeyboardUsageAsList(false) + "\n";
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
		
		float x			= 10+(layer * ( 14 + kinectLayer->getWidth()/4.0f ));
		float y			= 10;
		float width		= kinectLayer->getWidth()/4.0f;
		float height	= kinectLayer->getHeight()/4.0f;
		string info		= "kLayer " + ofToString(layer) + " near: " + ofToString(*kinectLayer->getNearThreshold()) + " far: " + ofToString(*kinectLayer->getFarThreshold());

		glTranslatef(0.0f, _viewHeight, 0.0f);
		glScaled(1.0f, -1.0f, 0.0f);
		if (layer == currentScene->getCurrentKinectLayerIndex()) {
			ofSetColor(0, 0, 255);
		} else ofSetColor(255, 255, 255);
		ofDrawBitmapString(info, x+4, y+12);
		ofSetColor(255, 255, 255);
		viewPort->drawViewport(x, y, width, height); // upside down mr squiggle
		kinectLayer->getDepthImage()->draw(x, y+height, width, height);
		glPopMatrix();
		
	}
	
	glPushMatrix();
	
	ofxDepthGenerator*	oniDepthGen = _kinectModel->getONIDepthGen();
	ofxImageGenerator*	oniImageGen = _kinectModel->getONIImageGen();
	//ofxIRGenerator*     oniIRGen = _kinectModel->getONIIRGen();
	//ofxUserGenerator*	oniUserGen = _kinectModel->getONIUserGen();
	//ofxHandGenerator*	oniHandGen = _kinectModel->getONIHandGen();
	
	glTranslatef(0.0f, 0.0f, 0.0f);
	glScalef(0.5f, -0.5f, 1.0f);
	glTranslatef(_viewWidth-oniDepthGen->getWidth()/2, -oniDepthGen->getHeight(), 0.0f);
	oniDepthGen->draw();
	//oniUserGen->draw();
	//oniHandGen->draw();
	glTranslatef(oniDepthGen->getWidth(), 0.0f, 0.0f);
	//oniIRGen->draw();
	oniImageGen->draw();
	glPopMatrix();
	
	ofSetColor(0, 255, 255);
	ofDrawBitmapString(msg, 20, 20);
	ofSetColor(255, 255, 255);
	
	glPopMatrix();
	
	_viewFBO.end();

}