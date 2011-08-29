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
	
	for (int layer = 0; layer < currentScene->getNumberOfVideoLayers(); layer++) {
		
		VideoView* videoLayer			= currentScene->getVideoLayer(layer);
		
		videoLayer->getVideo()->update();
		videoLayer->update();
		
	}
	
}

//--------------------------------------------------------------
void VideoController::setupVideoLayers() {
	
	Scene* currentScene = _appModel->getCurrentScene();
	
	for (int layer = 0; layer < currentScene->getNumberOfVideoLayers(); layer++) {
		
		VideoView* videoLayer			= currentScene->getVideoLayer(layer);
		
		if (videoLayer->getVideoPath() != "") videoLayer->loadMovie();
		
	}
}