/*
 *  AppController.cpp
 *  emptyExample
 *
 *  Created by gameover on 22/08/11.
 *  Copyright 2011 trace media. All rights reserved.
 *
 */

#include "AppController.h"

//--------------------------------------------------------------
AppController::AppController() {
	
	LOG_NOTICE("Constructing AppController");
	
	registerStates();
	
	_dataController = new DataController();
	_dataController->loadProperties("config.xml");
	_dataController->loadScenes("scenes.xml");
	
	//_appModel->setProperty("showProps", false);
	//_appModel->setProperty("showDebug", false);
	//_appModel->setProperty("showFullscreen", false);
	//_appModel->setProperty("showKinectFull", true);
	//_appModel->setProperty("showDualScreen", true);
//	_appModel->setProperty("nearThreshold0", 300);
//	_appModel->setProperty("farThreshold0", 4000);
//	_appModel->setProperty("nearThreshold1", 0);
	//_appModel->setProperty("blurIterations", 1);
	
	_mouseController = new MouseController();
	_keyboardController = new KeyboardController();
	_midiController = new MidiController();
	_videoController = new VideoController();
	_kinectController = new KinectController();
	
	_appView = new AppView(1024.0f, 768.0f);
	
	//_appModel->setScene(new Scene("test_scene", 2, 0, 1024.0f, 768.0f));
	//_appModel->setScene(new Scene("test2_scene", 2, 0, 1024.0f, 768.0f));
	
	_appModel->registerFunction("AppModel::adjustIntProperty", 
												MakeDelegate(_appModel, &AppModel::adjustIntProperty));
	
	_appModel->registerFunction("KinectController::setNearThreshold", 
												MakeDelegate(_kinectController, &KinectController::setNearThreshold));

	_appModel->registerFunction("KinectController::setFarThreshold", 
												MakeDelegate(_kinectController, &KinectController::setFarThreshold));
	
	_appModel->registerFunction("AppModel::toggleBooleanProperty", 
												MakeDelegate(_appModel, &AppModel::toggleBooleanProperty));
	
	_appModel->registerFunction("AppController::toggleFullscreen", 
												MakeDelegate(this, &AppController::toggleFullscreen));
	
	_appModel->registerFunction("KinectController::toggleRegisterKinectViewport", 
												MakeDelegate(_kinectController, &KinectController::toggleRegisterKinectViewport));

	_appModel->registerFunction("AppController::nextScene", 
								MakeDelegate(this, &AppController::nextScene));
	
	_appModel->registerFunction("AppController::previousScene", 
								MakeDelegate(this, &AppController::previousScene));
	
	ofSetFullscreen(boost::any_cast<bool>(_appModel->getProperty("showFullscreen")));
	
	_keyModel->registerEvent('f', kKEY_DOWN, "toggle fullscreen/window", "AppController::toggleFullscreen");
	_keyModel->registerEvent('r', kKEY_DOWN, "toggle kinect register viewport", "KinectController::toggleRegisterKinectViewport");
	_keyModel->registerEvent('p', kKEY_DOWN, "show all properties in debug view", "AppModel::toggleBooleanProperty", (string)"showProps");
	_keyModel->registerEvent('d', kKEY_DOWN, "show/hide debug view", "AppModel::toggleBooleanProperty", (string)"showDebug");
	_keyModel->registerEvent('s', kKEY_DOWN, "toggle dual screen draw", "AppModel::toggleBooleanProperty", (string)"showDualScreen");
	_keyModel->registerEvent('y', kKEY_DOWN, "increment blurIterations", "AppModel::adjustIntProperty", (string)"blurIterations", 1);
	_keyModel->registerEvent('h', kKEY_DOWN, "decrement blurIterations", "AppModel::adjustIntProperty", (string)"blurIterations", -1);
	_keyModel->registerEvent('i', kKEY_DOWN, "increment current kinectLayer nearThreshold", "KinectController::setNearThreshold", 10, true);
	_keyModel->registerEvent('k', kKEY_DOWN, "decrement current kinectLayer nearThreshold", "KinectController::setNearThreshold", -10, true);
	_keyModel->registerEvent('o', kKEY_DOWN, "increment current kinectLayer farThreshold", "KinectController::setFarThreshold", 10, true);
	_keyModel->registerEvent('l', kKEY_DOWN, "decrement current kinectLayer farThreshold", "KinectController::setFarThreshold", -10, true);
	
	_keyModel->registerEvent('.', kKEY_DOWN, "next scene", "AppController::nextScene");
	_keyModel->registerEvent(',', kKEY_DOWN, "previous scene", "AppController::nextScene");
	
	_midiModel->registerEvent(1, 144, 36, 0, kMIDI_ANY, "toggle fullscreen/window", "AppController::toggleFullscreen");
//	_midiModel->registerEvent(1, 144, 37, 0, kMIDI_PASS_BYTE_ONE, "test1", "AppController::test1");
//	_midiModel->registerEvent(1, 144, 38, 0, kMIDI_PASS_BYTE_TWO, "test2", "AppController::test2", (string)"byteTwo");
//	_midiModel->registerEvent(1, 208, 0, 0, kMIDI_PASS_BYTE_BOTH, "test3", "AppController::test3");


	
	//_appModel->getCurrentScene()->addVideoLayer();
	//->getCurrentScene()->getVideoLayer(0)->loadMovie("/Users/gameover/Desktop/FolioBig/VimeoReady/MoralesVacircaGingoldEDIT.mp4");
	
	setState(kAPPCONTROLLER_RUNNING);
	
}

//--------------------------------------------------------------
AppController::~AppController() {
	
	LOG_NOTICE("Destroying AppController");
	
	_dataController->saveProperties("config.xml");
	_dataController->saveScenes("scenes.xml");
	
	delete _appView;
	delete _dataController;
	delete _keyboardController;
	delete _midiController;
	delete _videoController;
	delete _kinectController;
	delete _appModel;
}

// state registration
//--------------------------------------------------------------
void AppController::registerStates() {
	
	LOG_VERBOSE("Registering States");
	
	registerState(kAPPCONTROLLER_INITING, "kAPPCONTROLLER_INITING");
	registerState(kAPPCONTROLLER_LOADING, "kAPPCONTROLLER_LOADING");
	registerState(kAPPCONTROLLER_RUNNING, "kAPPCONTROLLER_RUNNING");
	registerState(kAPPCONTROLLER_EXITING, "kAPPCONTROLLER_EXITING");
	
	_appModel->registerStatefulClass(typeid(*this).name());
	
	setState(kAPPCONTROLLER_INITING);
	
}

//--------------------------------------------------------------
void AppController::nextScene() {
	_videoController->stopVideoLayers();
	_appModel->nextScene();
	_kinectController->setupKinectLayers();
	_videoController->setupVideoLayers();
}

//--------------------------------------------------------------
void AppController::previousScene() {
	_videoController->stopVideoLayers();
	_appModel->previousScene();
	_kinectController->setupKinectLayers();
	_videoController->setupVideoLayers();
}

//--------------------------------------------------------------
void AppController::gotoScene(int sceneIndex) {
	
}

//--------------------------------------------------------------
void AppController::gotoScene(string sceneName) {
	
}

//--------------------------------------------------------------
void AppController::update() {
	_videoController->update();
	_kinectController->update();
	_appView->update();
}

//--------------------------------------------------------------
void AppController::draw() {
	_appView->draw();
}

//--------------------------------------------------------------
void AppController::windowResized(int w, int h) {
	
}

//--------------------------------------------------------------
void AppController::toggleFullscreen() {
	ofToggleFullscreen();
	_appModel->toggleBooleanProperty("showFullscreen");
}