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

	
	glPopMatrix();
	_viewFBO.end();
	
}

