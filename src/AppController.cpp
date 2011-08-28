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
//	_appModel->setProperty("farThreshold1", 10000);
	
	_mouseController = new MouseController();
	_keyboardController = new KeyboardController();
	_midiController = new MidiController();
	_kinectController = new KinectController();
	
	_appView = new AppView(1024.0f, 768.0f);
	
	//_appModel->setScene(new Scene("test_scene", 2, 0, 1024.0f, 768.0f));
	//_appModel->setScene(new Scene("test2_scene", 2, 0, 1024.0f, 768.0f));
	
	_appModel->setCurrentScene("test_scene");

	_appModel->_keyboardModel->registerFunction("KinectController::adjustNearThreshold", 
												MakeDelegate(_kinectController, &KinectController::adjustNearThreshold));

	_appModel->_keyboardModel->registerFunction("KinectController::adjustFarThreshold", 
												MakeDelegate(_kinectController, &KinectController::adjustFarThreshold));
	
	_appModel->_keyboardModel->registerFunction("AppModel::toggleBooleanProperty", 
												MakeDelegate(_appModel, &AppModel::toggleBooleanProperty));
	
	_appModel->_keyboardModel->registerFunction("AppController::toggleFullscreen", 
												MakeDelegate(this, &AppController::toggleFullscreen));
	
	_appModel->_keyboardModel->registerFunction("KinectController::toggleRegisterKinectViewport", 
												MakeDelegate(_kinectController, &KinectController::toggleRegisterKinectViewport));

	
	ofSetFullscreen(boost::any_cast<bool>(_appModel->getProperty("showFullscreen")));
	
	KeyMessage km1('p', kKEY_DOWN, 0);
	InputParams1<KeyMessage, string> ki1(km1, "showProps");
	
	KeyMessage km2('d', kKEY_DOWN, 0);
	InputParams1<KeyMessage, string> ki2(km2, "showDebug");
	
	KeyMessage km3('f', kKEY_DOWN, 0);
	InputParams0<KeyMessage> ki3(km3);
	
	KeyMessage km4('s', kKEY_DOWN, 0);
	InputParams1<KeyMessage, string> ki4(km4, "showKinectFull");

	KeyMessage km5('g', kKEY_DOWN, 0);
	InputParams1<KeyMessage, string> ki5(km5, "showDualScreen");
	
	KeyMessage km6('r', kKEY_DOWN, 0);
	InputParams0<KeyMessage> ki6(km6);
	
	KeyMessage km7('y', kKEY_DOWN, 0);
	InputParams2<KeyMessage, int, int> ki7(km7, 0, 10);
	
	KeyMessage km8('h', kKEY_DOWN, 0);
	InputParams2<KeyMessage, int, int> ki8(km8, 0, -10);
	
	KeyMessage km9('u', kKEY_DOWN, 0);
	InputParams2<KeyMessage, int, int> ki9(km9, 0, 10);
	
	KeyMessage km10('j', kKEY_DOWN, 0);
	InputParams2<KeyMessage, int, int> ki10(km10, 0, -10);
	
	KeyMessage km11('i', kKEY_DOWN, 0);
	InputParams2<KeyMessage, int, int> ki11(km11, 1, 10);
	
	KeyMessage km12('k', kKEY_DOWN, 0);
	InputParams2<KeyMessage, int, int> ki12(km12, 1, -10);
	
	KeyMessage km13('o', kKEY_DOWN, 0);
	InputParams2<KeyMessage, int, int> ki13(km13, 1, 10);
	
	KeyMessage km14('l', kKEY_DOWN, 0);
	InputParams2<KeyMessage, int, int> ki14(km14, 1, -10);
	
	_appModel->_keyboardModel->registerInputToFunction("AppModel::toggleBooleanProperty", ki1, "show all properties in debug view");
	_appModel->_keyboardModel->registerInputToFunction("AppModel::toggleBooleanProperty", ki2, "show debug view");
	_appModel->_keyboardModel->registerInputToFunction("AppController::toggleFullscreen", ki3, "toggle full screen");
	_appModel->_keyboardModel->registerInputToFunction("AppModel::toggleBooleanProperty", ki4, "toggle depth mask full screen");
	_appModel->_keyboardModel->registerInputToFunction("AppModel::toggleBooleanProperty", ki5, "toggle dual/mirror screen");
	_appModel->_keyboardModel->registerInputToFunction("KinectController::toggleRegisterKinectViewport", ki6, "toggle kinect register viewport");
	_appModel->_keyboardModel->registerInputToFunction("KinectController::adjustNearThreshold", ki7, "increment nearThreshold0");
	_appModel->_keyboardModel->registerInputToFunction("KinectController::adjustNearThreshold", ki8, "decrement nearThreshold0");
	_appModel->_keyboardModel->registerInputToFunction("KinectController::adjustFarThreshold", ki9, "increment farThreshold0");
	_appModel->_keyboardModel->registerInputToFunction("KinectController::adjustFarThreshold", ki10, "decrement farThreshold0");
	_appModel->_keyboardModel->registerInputToFunction("KinectController::adjustNearThreshold", ki11, "increment nearThreshold1");
	_appModel->_keyboardModel->registerInputToFunction("KinectController::adjustNearThreshold", ki12, "decrement nearThreshold1");
	_appModel->_keyboardModel->registerInputToFunction("KinectController::adjustFarThreshold", ki13, "increment farThreshold1");
	_appModel->_keyboardModel->registerInputToFunction("KinectController::adjustFarThreshold", ki14, "decrement farThreshold1");
	
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