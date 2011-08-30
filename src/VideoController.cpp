/*
 *  VideoController.cpp
 *  Bunyip
 *
 *  Created by gameover on 24/08/11.
 *  Copyright 2011 trace media. All rights reserved.
 *
 */

#include "VideoController.h"

//--------------------------------------------------------------
VideoController::VideoController() {
	LOG_NOTICE("Constructing VideoController");
}

//--------------------------------------------------------------
VideoController::~VideoController() {
	LOG_NOTICE("Destroying VideoController");
}

//--------------------------------------------------------------
void VideoController::update() {
	
	Scene* currentScene = _appModel->getCurrentScene();
	
	if (currentScene == NULL) return;
	
	for (int layer = 0; layer < currentScene->getNumberOfVideoLayers(); layer++) {
		
		VideoView* videoLayer			= currentScene->getVideoLayer(layer);
		
		videoLayer->getVideo()->update();
		videoLayer->update();
		
	}
	
}

//--------------------------------------------------------------
void VideoController::setupVideoLayers() {
	
	Scene* currentScene = _appModel->getCurrentScene();
	
	if (currentScene == NULL) return;
	 
	for (int layer = 0; layer < currentScene->getNumberOfVideoLayers(); layer++) {
		
		VideoView* videoLayer			= currentScene->getVideoLayer(layer);
		goThreadedVideo* video			= videoLayer->getVideo();
		
		video->setPaused(false);
		//video->setFrame(0);
		
	}
}

//--------------------------------------------------------------
void VideoController::stopVideoLayers() {
	
	Scene* currentScene = _appModel->getCurrentScene();
	
	if (currentScene== NULL) return;
		
	for (int layer = 0; layer < currentScene->getNumberOfVideoLayers(); layer++) {
		
		VideoView* videoLayer			= currentScene->getVideoLayer(layer);
		
		videoLayer->getVideo()->setPaused(true);
		videoLayer->getVideo()->setFrame(0);
	}
}

//--------------------------------------------------------------
//void VideoController::errored(int & e) {
//	// nothing
//	cout << "*******************************ERROR" << endl;
//}
//
//
//--------------------------------------------------------------
//void VideoController::loaded(string & e) {
//	// nothing
//	cout << "*******************************LOADED" << endl;
//}