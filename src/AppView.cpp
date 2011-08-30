/*
 *  AppView.cpp
 *  emptyExample
 *
 *  Created by gameover on 22/08/11.
 *  Copyright 2011 trace media. All rights reserved.
 *
 */

#include "AppView.h"

AppView::AppView(float width, float height) : BaseView(width ,height) {
	
	LOG_NOTICE("Constructing AppView");
	
    LOG_NOTICE("Setting up all (sub) views");
	_debugView      = new DebugView(width, height);
	_sceneView		= new SceneView(width, height);
}

AppView::~AppView() {
	
	LOG_NOTICE("Destroying AppView");
	
    LOG_NOTICE("Destroying all other (sub) views");
	
    _viewFBO.detach();
    _viewFBOTexture.clear();
	
	delete _sceneView;
    delete _debugView;
	
}

void AppView::update() {
	
	ofBackground(255, 255, 255);
	
	if(false) { //_appModel->checkState(kAPP_LOADING)){
		//_loadingView->update();
	} else {
		
		_sceneView->update();
		
		if(boost::any_cast<bool>(_appModel->getProperty("showDebug"))) {
			_debugView->update();
		}
	}
}

void AppView::draw() {
	
    float displayOffsetX = 0;
	
	if (true) {//boost::any_cast<bool>(_appModel->getProperty("showDualScreen"))) {
		displayOffsetX = ofGetWidth() - 1024.0f;
        
	}

    float width = CLAMP((float)ofGetWidth(), 0.0f , 1024.0f);
    float height = CLAMP((float)ofGetHeight(), 0.0f , 768.0f);
	
	if(false) { //_appModel->checkState(kAPP_LOADING)){
		//_loadingView->draw(0, height, width, -height);
	} else {
		
		// composite all views
		
		// TODO: this dual screen draw is tearing on Windows...and presumably on Mac OSX in GLUT...
		// options for solving include: use OSX and ofxCocoa or look into multiple openGL contexts and
		// shared textures and/or switched context drawing...
		// ...see http://forum.openframeworks.cc/index.php/topic,4872.0.html
		_sceneView->draw(0, 0, width, height);
		_sceneView->draw(displayOffsetX, 0, width, height);
			
		
		if(boost::any_cast<bool>(_appModel->getProperty("showDebug"))){
			_debugView->draw(0, height, width, -height);
		}
	}
	
}