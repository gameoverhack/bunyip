/*
 *  DisplayController.cpp
 *  Bunyip
 *
 *  Created by gameover on 25/08/11.
 *  Copyright 2011 trace media. All rights reserved.
 *
 */

#include "DisplayController.h"

DisplayController::DisplayController() {
	
	LOG_NOTICE("Constructing DisplayController");
	
	registerStates();
	
}

DisplayController::~DisplayController() {
	LOG_NOTICE("Destroying DisplayController");
}

void DisplayController::registerStates() {
	
	LOG_VERBOSE("Registering States");
	
	registerState(kDISPLAYCONTROLLER_INIT, "kDISPLAYCONTROLLER_INIT");
	registerState(kDISPLAYCONTROLLER_EDIT, "kDISPLAYCONTROLLER_EDIT");
	registerState(kDISPLAYCONTROLLER_READY, "kDISPLAYCONTROLLER_READY");
	registerState(kDISPLAYCONTROLLER_ERROR, "kDISPLAYCONTROLLER_ERROR");
	
	_appModel->registerStatefulClass(typeid(*this).name());
	
	setState(kDISPLAYCONTROLLER_INIT);
	
}

bool DisplayController::addDisplay(int x, int y, int width, int height, string name) {
	
}

bool DisplayController::addViewport(int x, int y, int width, int height, string name) {
	
}

void DisplayController::setFullscreen(bool b) {
	
}

void DisplayController::toggleFullscreen() {

}