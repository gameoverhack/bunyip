/*
 *  MouseController.cpp
 *  Bunyip
 *
 *  Created by gameover on 25/08/11.
 *  Copyright 2011 trace media. All rights reserved.
 *
 */

#include "MouseController.h"

MouseController::MouseController() {
	
	LOG_NOTICE("Constructing MouseController");
	
	//registerStates();
	
	ofAddListener(ofEvents.mouseDragged, this, &MouseController::mouseMoved);
	ofAddListener(ofEvents.mouseDragged, this, &MouseController::mouseDragged);
	ofAddListener(ofEvents.mousePressed, this, &MouseController::mousePressed);
	ofAddListener(ofEvents.mouseReleased, this, &MouseController::mouseReleased);
	
}

MouseController::~MouseController() {
	
	LOG_NOTICE("Destroying MouseController");
	
	ofRemoveListener(ofEvents.mouseDragged, this, &MouseController::mouseMoved);
	ofRemoveListener(ofEvents.mouseDragged, this, &MouseController::mouseDragged);
	ofRemoveListener(ofEvents.mousePressed, this, &MouseController::mousePressed);
	ofRemoveListener(ofEvents.mouseReleased, this, &MouseController::mouseReleased);
	
}

/*void DisplayController::registerStates() {
	
	LOG_VERBOSE("Registering States");
	
	registerState(kDISPLAYCONTROLLER_INIT, "kDISPLAYCONTROLLER_INIT");
	registerState(kDISPLAYCONTROLLER_EDIT, "kDISPLAYCONTROLLER_EDIT");
	registerState(kDISPLAYCONTROLLER_READY, "kDISPLAYCONTROLLER_READY");
	registerState(kDISPLAYCONTROLLER_ERROR, "kDISPLAYCONTROLLER_ERROR");
	
	_appModel->registerStatefulClass(typeid(*this).name());
 
	setState(kDISPLAYCONTROLLER_INIT);
	
}*/

//--------------------------------------------------------------
void MouseController::mouseMoved(ofMouseEventArgs &e) {
	
}

//--------------------------------------------------------------
void MouseController::mouseDragged(ofMouseEventArgs &e) {
	
	if (_currentViewPortIndex != -1) {
		
		Scene* currentScene				= _appModel->getCurrentScene();
		ViewPort * currentViewPort		= currentScene->getKinectLayer(_currentViewPortIndex)->getViewPort();
		
		if (currentScene == NULL) return;
		
		if(_currentViewPortCorner != -1){
			float scaleX = ((float)e.x - currentViewPort->getEditX() - (currentViewPort->getX()) * currentViewPort->getEditScaleX())/(currentViewPort->getWidth() * currentViewPort->getEditScaleX());
			float scaleY = ((float)e.y - currentViewPort->getEditY() - (currentViewPort->getY()) * currentViewPort->getEditScaleY())/(currentViewPort->getHeight() * currentViewPort->getEditScaleY());
			currentViewPort->getCorners()[_currentViewPortCorner].x = scaleX;
			currentViewPort->getCorners()[_currentViewPortCorner].y = scaleY;
			//saveViewport(whichViewport);
		}
		
		if (_currentViewPortCorner == -1) {
			currentViewPort->setX(currentViewPort->getX() + (e.x - _mouseOriginX)/currentViewPort->getEditScaleX());
			currentViewPort->setY(currentViewPort->getY() + (e.y - _mouseOriginY)/currentViewPort->getEditScaleY());
			_mouseOriginX = e.x;
			_mouseOriginY = e.y;
			//saveViewport(whichViewport);
		}
	}

}

//--------------------------------------------------------------
void MouseController::mousePressed(ofMouseEventArgs &e) {
	
	float smallestDist = 0.2;
	_currentViewPortIndex = -1;
	_currentViewPortCorner = -1;
	
	Scene* currentScene	= _appModel->getCurrentScene();
	ViewPort * currentViewPort;
	
	if (currentScene == NULL) return;
	
	for (int i = 0; i < currentScene->getNumberOfKinectLayers(); i++) {
		
		for(int corner = 0; corner < 4; corner++){
			
			currentViewPort = currentScene->getKinectLayer(i)->getViewPort();
			
			float distx = (currentViewPort->getCorners()[corner].x - ((float)e.x - currentViewPort->getEditX() - (currentViewPort->getX()) * currentViewPort->getEditScaleX())/(currentViewPort->getWidth() * currentViewPort->getEditScaleX()));
			float disty = (currentViewPort->getCorners()[corner].y - ((float)e.y - currentViewPort->getEditY() - (currentViewPort->getY()) * currentViewPort->getEditScaleY())/(currentViewPort->getHeight() * currentViewPort->getEditScaleY()));

			float dist  = sqrt( distx * distx + disty * disty);
			
			if(dist < smallestDist && dist < 0.1){
				_currentViewPortCorner = corner;
				_currentViewPortIndex = i;
				currentScene->setCurrentKinectLayer(_currentViewPortIndex); // for threshold stuff
				smallestDist = dist;
				return;
			}
		}
	}
	
	if (_currentViewPortCorner == -1) {
		for (int i = 0; i < currentScene->getNumberOfKinectLayers(); i++) {
			
			currentViewPort = currentScene->getKinectLayer(i)->getViewPort();
			
			if ((float)e.x > currentViewPort->getEditX() + (currentViewPort->getX()) * currentViewPort->getEditScaleX() &&
				(float)e.x < currentViewPort->getEditX() + (currentViewPort->getX() + currentViewPort->getWidth()) * currentViewPort->getEditScaleX() &&
				(float)e.y > currentViewPort->getEditY() + (currentViewPort->getY()) * currentViewPort->getEditScaleY() &&
				(float)e.y < currentViewPort->getEditY() + (currentViewPort->getY() + currentViewPort->getHeight()) * currentViewPort->getEditScaleY()) {
				
				_currentViewPortIndex = i;
				currentScene->setCurrentKinectLayer(_currentViewPortIndex); // for threshold stuff
				_mouseOriginX = e.x;
				_mouseOriginY = e.y;
				return;
			}
		}
	}
	
	
}

//--------------------------------------------------------------
void MouseController::mouseReleased(ofMouseEventArgs &e) {
	_currentViewPortIndex = -1;
	_currentViewPortCorner = -1;
}