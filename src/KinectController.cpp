/*
 *  KinectController.cpp
 *  Bunyip
 *
 *  Created by gameover on 23/08/11.
 *  Copyright 2011 trace media. All rights reserved.
 *
 */

#include "KinectController.h"

//--------------------------------------------------------------
KinectController::KinectController() {
	
	LOG_NOTICE("Constructing DataController");
	
    registerStates();

	_useApproximation = true;
	
	if (_kinectModel->setup()) {
		setState(kKINECTCONTROLLER_READY);
	} else setState(kKINECTCONTROLLER_ERROR);
	
}

//--------------------------------------------------------------
KinectController::~KinectController() {
	
	LOG_NOTICE("Destroying DataController");
	
	delete _kinectModel;
	
}

//--------------------------------------------------------------
void KinectController::registerStates() {

	LOG_VERBOSE("Registering States");
	
	registerState(kKINECTCONTROLLER_INIT, "kKINECTCONTROLLER_INIT");
	registerState(kKINECTCONTROLLER_READY, "kKINECTCONTROLLER_READY");
	registerState(kKINECTCONTROLLER_ERROR, "kKINECTCONTROLLER_ERROR");
	
	_appModel->registerStatefulClass(typeid(*this).name());
	
	setState(kKINECTCONTROLLER_INIT);
	
}

//--------------------------------------------------------------
void KinectController::toggleRegisterKinectViewport() {
	if (checkState(kKINECTCONTROLLER_READY)) {
		ofxOpenNIContext*	oniContext = _kinectModel->getONIContext();
		oniContext->toggleRegisterViewport();
	}
}

//--------------------------------------------------------------
void KinectController::toggleMirrorKinectViewport() {
	if (checkState(kKINECTCONTROLLER_READY)) {
		ofxOpenNIContext*	oniContext = _kinectModel->getONIContext();
		oniContext->toggleMirror();
	}
}

//--------------------------------------------------------------
void KinectController::setNearThreshold(int amount, bool relative) {
	
	if (checkState(kKINECTCONTROLLER_READY)) {
		
		ofxDepthGenerator*	oniDepthGen = _kinectModel->getONIDepthGen();
		Scene * currentScene			= _appModel->getCurrentScene();
		KinectView * kinectLayer		= currentScene->getCurrentKinectLayer();
		int	kinectLayerIndex			= currentScene->getCurrentKinectLayerIndex();
		
		if (kinectLayer != NULL) {
			kinectLayer->setNearThreshold(amount, relative);
		}
		
		oniDepthGen->setDepthThreshold(kinectLayerIndex, *kinectLayer->getNearThreshold(), *kinectLayer->getFarThreshold());
	}
	
}

//--------------------------------------------------------------
void KinectController::setFarThreshold(int amount, bool relative) {

	if (checkState(kKINECTCONTROLLER_READY)) {
		
		ofxDepthGenerator*	oniDepthGen = _kinectModel->getONIDepthGen();
		Scene * currentScene			= _appModel->getCurrentScene();
		KinectView * kinectLayer		= currentScene->getCurrentKinectLayer();
		int	kinectLayerIndex			= currentScene->getCurrentKinectLayerIndex();
		
		if (kinectLayer != NULL) {
			kinectLayer->setFarThreshold(amount, relative);
		}
		
		oniDepthGen->setDepthThreshold(kinectLayerIndex, *kinectLayer->getNearThreshold(), *kinectLayer->getFarThreshold());		
	}
	
}

//--------------------------------------------------------------
void KinectController::setupKinectLayers() {

	if (checkState(kKINECTCONTROLLER_READY)) {
		
		Scene * currentScene			= _appModel->getCurrentScene();
		ofxDepthGenerator*	oniDepthGen = _kinectModel->getONIDepthGen();
		int	numberOfKinectLayers		= currentScene->getNumberOfKinectLayers();
		
		oniDepthGen->setMaxNumDepthThresholds(numberOfKinectLayers);
		
		for (int layer = 0; layer < numberOfKinectLayers; layer++) {
			
			KinectView * kinectLayer	= currentScene->getKinectLayer(layer);
			oniDepthGen->setDepthThreshold(layer, *kinectLayer->getNearThreshold(), *kinectLayer->getFarThreshold());
		}
	
	}
	
}

//--------------------------------------------------------------
void KinectController::update() {
	
	if (checkState(kKINECTCONTROLLER_READY)) {
		
		Scene * currentScene = _appModel->getCurrentScene();
		
		ofxOpenNIContext*	oniContext = _kinectModel->getONIContext();
		ofxDepthGenerator*	oniDepthGen = _kinectModel->getONIDepthGen();
        ofxImageGenerator*	oniImageGen = _kinectModel->getONIImageGen();
        //ofxIRGenerator*     oniIRGen = _kinectModel->getONIIRGen();
		//ofxUserGenerator*	oniUserGen = _kinectModel->getONIUserGen();
		//ofxHandGenerator*	oniHandGen = _kinectModel->getONIHandGen();
		
		oniContext->update();
		oniDepthGen->update();
		oniImageGen->update();
        //oniIRGen->update();
		//oniUserGen->update();
		
		if (currentScene == NULL) return;
		
		for (int layer = 0; layer < currentScene->getNumberOfKinectLayers(); layer++) {
			
			ofxDepthGenerator* oniDepthGen		= _kinectModel->getONIDepthGen();
			KinectView* kinectLayer			= currentScene->getKinectLayer(layer);
			unsigned char* depthPixels			= kinectLayer->getDepthPixels();
			ofxCvGrayscaleImage* depthImage		= kinectLayer->getDepthImage();
			ofxCvContourFinder* depthContour	= kinectLayer->getDepthContour();
			float smoothContourThreshold		= *kinectLayer->getSmoothContourThreshold();
			int minSizeBlobs					= *kinectLayer->getMinSizeContourBlobs();
			int maxSizeBlobs					= *kinectLayer->getMaxSizeContourBlobs();
			
			oniDepthGen->setDepthThreshold(layer, *kinectLayer->getNearThreshold(), *kinectLayer->getFarThreshold());
			
			depthPixels	= oniDepthGen->getDepthPixels(layer);	
			depthImage->setFromPixels(depthPixels, (int)oniDepthGen->getWidth(), (int)oniDepthGen->getHeight());
			int nBlobs = depthContour->findContours(*depthImage, minSizeBlobs, maxSizeBlobs, 4, true, _useApproximation, smoothContourThreshold);
			kinectLayer->update();
			
		}
		
	}
	
}
