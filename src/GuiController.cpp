/*
 *  GuiController.cpp
 *  Bunyip
 *
 *  Created by gameover on 30/08/11.
 *  Copyright 2011 trace media. All rights reserved.
 *
 */

#include "GuiController.h"

//--------------------------------------------------------------
GuiController::GuiController() {
	LOG_NOTICE("Constructing GuiController");
}

//--------------------------------------------------------------
GuiController::~GuiController() {
	LOG_NOTICE("Destructing GuiController");
}

//--------------------------------------------------------------
void GuiController::setup() {
	
	bool b = true;
	
	LOG_NOTICE("Setting Up GuiController");
	
	_appModel->gui.addPage("Bunyip");
	_appModel->gui.addTitle("Control");
	_appModel->gui.addToggle("Calibrate", _appModel->guiProp_Calibrate);
	_appModel->gui.addButton("(Re)load Scenes", _appModel->guiProp_ReloadScenes);
	_appModel->gui.addButton("Reset Current Viewport", _appModel->guiProp_ResetViewport);
	_appModel->gui.addButton("Reset Current Depth", _appModel->guiProp_ResetDepth);
	_appModel->gui.addButton("Fullscreen", b, "AppController::toggleFullscreen");
	_appModel->gui.addToggle("Use Contour Approximation", _appModel->guiProp_UseApproximation);
	
	_appModel->gui.addButton("First Scene", _appModel->guiProp_FirstScene);
	_appModel->gui.addButton("Prev Scene", _appModel->guiProp_PrevScene);
	_appModel->gui.addButton("Next Scene", _appModel->guiProp_NextScene);
	_appModel->gui.addButton("Last Scene", _appModel->guiProp_LastScene);
	
	_appModel->gui.addButton("Add Scene", _appModel->guiProp_AddScene);
	_appModel->gui.addButton("Del Scene", _appModel->guiProp_DelScene);
	
	_appModel->gui.loadFromXML();
	
    _appModel->gui.show();
	
}


//--------------------------------------------------------------
void GuiController::addSceneGui(Scene* scene) {

	bool b = true;
	
	if (scene == NULL) {
		scene = new Scene("scene" + ofToString(_appModel->getNumberOfScenes()), 0, 0, 1024.0, 768.0);
		_appModel->setScene(scene);
	}
	
	LOG_NOTICE("Adding Scene Gui: " + scene->getName()); 
	
	_appModel->gui.addPage(scene->getName());
	
	for (int layer = 0; layer < scene->getNumberOfKinectLayers(); layer++) {
		
		KinectView* kinectLayer = scene->getKinectLayer(layer);
		
		_appModel->gui.addTitle("Kinect Layer " + ofToString(layer));
		_appModel->gui.addSlider("nearThreshold", *kinectLayer->getNearThreshold(), 0, 10000);
		_appModel->gui.addSlider("farThreshold", *kinectLayer->getFarThreshold(), 0, 10000);
		_appModel->gui.addSlider("minBlobSize", *kinectLayer->getMinSizeContourBlobs(), 0, 200000);
		_appModel->gui.addSlider("maxBlobSize", *kinectLayer->getMaxSizeContourBlobs(), 0, 200000);
		_appModel->gui.addSlider("smoothThreshold", *kinectLayer->getSmoothContourThreshold(), 0.0f, 1.0f);
		_appModel->gui.addButton("delete layer", b, scene->getName()+"::Scene::deleteKinectLayer", *kinectLayer->getLayerIndex());
	}
	
	
	_appModel->gui.addButton("Add Video Layer", _appModel->guiProp_AddVideo);
	
	for (int layer = 0; layer < scene->getNumberOfVideoLayers(); layer++) {
		
		VideoView* videoLayer = scene->getVideoLayer(layer);
		
		_appModel->gui.addTitle("Video Layer " + ofToString(layer));
		//_appModel->gui.addSlider("nearThreshold", *kinectLayer->getNearThreshold(), 0, 10000);
		
	}
	
}