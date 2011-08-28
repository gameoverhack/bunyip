/*
 *  SceneView.cpp
 *  Bunyip
 *
 *  Created by gameover on 26/08/11.
 *  Copyright 2011 trace media. All rights reserved.
 *
 */

#include "SceneView.h"
//--------------------------------------------------------------
SceneView::SceneView(float width, float height) : BaseView(width ,height) {
	
	LOG_NOTICE("Constructing SceneView");
	
}

/*--------------------------------------------------------------
 SceneView::~SceneView() {
 
 LOG_NOTICE("Destroying SceneView");
 
 }*/

//--------------------------------------------------------------
void SceneView::update() {
	
	Scene* currentScene = _appModel->getCurrentScene();
	
	_viewFBO.begin();
	glPushMatrix();
	
	glClearColor(0.0, 0.0, 0.0, 0.0); // transparent clear colour
    glClear(GL_COLOR_BUFFER_BIT);
	
	//ofEnableAlphaBlending();
	
	for (int layer = 0; layer < currentScene->getNumberOfKinectLayers(); layer++) {
		
		glPushMatrix();

		KinectView* kinectLayer = currentScene->getKinectLayer(layer);
		ViewPort* viewPort		 = kinectLayer->getViewPort();
		
		float x = viewPort->getX();
		float y = viewPort->getY();
		float width = viewPort->getWidth();
		float height = viewPort->getHeight();
		
		kinectLayer->draw(x, y, width, height);
		
		glPopMatrix();
	}
	//ofDisableAlphaBlending();
//		
//		KinectView* kinectLayer = currentScene->getKinectLayer(layer);
//		ViewPort* viewPort		 = kinectLayer->getViewPort();
//		
//		float x = viewPort->getX();
//		float y = viewPort->getY();
//		float width = viewPort->getWidth();
//		float height = viewPort->getHeight();
//		
//		warp(viewPort->getWidth(), viewPort->getHeight(), viewPort->getCorners());
//		kinectLayer->getDepthImage()->draw(x, y, width, height);
//		kinectLayer->getDepthContour()->draw(x, y, width, height);
		
//		vector<ofPoint>* depthSmooth = kinectLayer->_depthSmooth;
//		
//		ofSetColor(255, 0, 0);
//		glPushMatrix();
//		glScaled(1024.0/640.0f, 768.0/480.0f, 1.0f);
//		ofNoFill();
//		ofBeginShape();
//		for (int i = 0; i < depthSmooth->size(); i++) {
//			ofVertex(depthSmooth->at(i).x, depthSmooth->at(i).y);
//		}
//		ofEndShape(true);
//		glPopMatrix();
//		ofSetColor(255, 255, 255);
		
		//drawInterpolatorSmooth(kinectLayer->spline2D, 10000);
		
//	}

	//ofDisableAlphaBlending();
	
	glPopMatrix();
	_viewFBO.end();
	
}

