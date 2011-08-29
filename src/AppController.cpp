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
	

	_keyModel->registerFunction("AppModel::adjustIntProperty", 
												MakeDelegate(_appModel, &AppModel::adjustIntProperty));
	
	_keyModel->registerFunction("KinectController::setNearThreshold", 
												MakeDelegate(_kinectController, &KinectController::setNearThreshold));

	_keyModel->registerFunction("KinectController::setFarThreshold", 
												MakeDelegate(_kinectController, &KinectController::setFarThreshold));
	
	_keyModel->registerFunction("AppModel::toggleBooleanProperty", 
												MakeDelegate(_appModel, &AppModel::toggleBooleanProperty));
	
	_keyModel->registerFunction("AppController::toggleFullscreen", 
												MakeDelegate(this, &AppController::toggleFullscreen));
	
	_keyModel->registerFunction("KinectController::toggleRegisterKinectViewport", 
												MakeDelegate(_kinectController, &KinectController::toggleRegisterKinectViewport));

	
	ofSetFullscreen(boost::any_cast<bool>(_appModel->getProperty("showFullscreen")));
	
	_keyModel->registerKey('f', kKEY_DOWN, "toggle fullscreen/window", "AppController::toggleFullscreen");
	_keyModel->registerKey('r', kKEY_DOWN, "toggle kinect register viewport", "KinectController::toggleRegisterKinectViewport");
	_keyModel->registerKey('p', kKEY_DOWN, "show all properties in debug view", "AppModel::toggleBooleanProperty", (string)"showProps");
	_keyModel->registerKey('d', kKEY_DOWN, "show/hide debug view", "AppModel::toggleBooleanProperty", (string)"showDebug");
	_keyModel->registerKey('s', kKEY_DOWN, "toggle dual screen draw", "AppModel::toggleBooleanProperty", (string)"showDualScreen");
	_keyModel->registerKey('y', kKEY_DOWN, "increment blurIterations", "AppModel::adjustIntProperty", (string)"blurIterations", 1);
	_keyModel->registerKey('h', kKEY_DOWN, "decrement blurIterations", "AppModel::adjustIntProperty", (string)"blurIterations", -1);
	_keyModel->registerKey('i', kKEY_DOWN, "increment current kinectLayer nearThreshold", "KinectController::setNearThreshold", 10, true);
	_keyModel->registerKey('k', kKEY_DOWN, "decrement current kinectLayer nearThreshold", "KinectController::setNearThreshold", -10, true);
	_keyModel->registerKey('o', kKEY_DOWN, "increment current kinectLayer farThreshold", "KinectController::setFarThreshold", 10, true);
	_keyModel->registerKey('l', kKEY_DOWN, "decrement current kinectLayer farThreshold", "KinectController::setFarThreshold", -10, true);
	
	_appModel->setCurrentScene("test_scene");
	_kinectController->setupKinectLayers();
	_videoController->setupVideoLayers();
	
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