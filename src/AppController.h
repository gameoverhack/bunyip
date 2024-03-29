/*
 *  AppController.h
 *  emptyExample
 *
 *  Created by gameover on 22/08/11.
 *  Copyright 2011 trace media. All rights reserved.
 *
 */

#ifndef _H_APPCONTROLLER
#define _H_APPCONTROLLER

#include "ofMain.h"

#include "AppModel.h"
#include "KeyboardModel.h"
#include "BaseState.h"
#include "DataController.h"
#include "KeyboardController.h"
#include "MouseController.h"
#include "MidiController.h"
#include "VideoController.h"
#include "KinectController.h"
#include "GuiController.h"

#include "AppView.h"

enum {
	kAPPCONTROLLER_INITING,
	kAPPCONTROLLER_LOADING,
	kAPPCONTROLLER_RUNNING,
	kAPPCONTROLLER_EXITING
};

class AppController : public ofBaseApp, public BaseState {
	
public:
	
	AppController();
	~AppController();

	void registerStates();
	
	void update();
	void draw();
	
private:

	void nextScene();
	void previousScene();
	void gotoScene(int sceneIndex);
	void gotoScene(string sceneName);
	
	void toggleFullscreen();
	
	void windowResized(int w, int h);
	
	DataController*			_dataController;
	KeyboardController*		_keyboardController;
	MouseController*		_mouseController;
	MidiController*			_midiController;
	VideoController*		_videoController;
	KinectController*		_kinectController;
	GuiController*			_guiController;
	
	AppView*				_appView;

};

#endif
