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
	
	_kinectModel = new KinectModel();
	
	ofxOpenNIContext*	oniContext = _kinectModel->getONIContext();
	ofxDepthGenerator*	oniDepthGen = _kinectModel->getONIDepthGen();
	ofxImageGenerator*	oniImageGen = _kinectModel->getONIImageGen();
    ofxIRGenerator*     oniIRGen = _kinectModel->getONIIRGen();
	ofxUserGenerator*	oniUserGen = _kinectModel->getONIUserGen();
	ofxHandGenerator*	oniHandGen = _kinectModel->getONIHandGen();
	
	bool ok;
	
	ok = oniContext->setup();
	ok = oniDepthGen->setup(oniContext);
	//ok = oniImageGen->setup(oniContext);
    ok = oniIRGen->setup(oniContext);
	ok = oniUserGen->setup(oniContext);
	ok = oniHandGen->setup(oniContext, 1);
	
	cout << "muther " << oniDepthGen->getWidth() << endl;
	
	if (ok) {
		oniDepthGen->setMaxNumDepthThresholds(2);
		oniDepthGen->setDepthThreshold(0, 30, 3000);
		oniDepthGen->setDepthThreshold(1, 4000, 10000);
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
void KinectController::adjustNearThreshold(int forDepthThreshold, int amount) {
	if (checkState(kKINECTCONTROLLER_READY)) {
		int near = boost::any_cast<int>(_appModel->getProperty("nearThreshold"+ofToString(forDepthThreshold)));
		int far = boost::any_cast<int>(_appModel->getProperty("farThreshold"+ofToString(forDepthThreshold)));
		near = near + amount;
		ofxDepthGenerator*	oniDepthGen = _kinectModel->getONIDepthGen();
		oniDepthGen->setDepthThreshold(forDepthThreshold, near, far);
		_appModel->setProperty("nearThreshold"+ofToString(forDepthThreshold), near);
	}
}

//--------------------------------------------------------------
void KinectController::adjustFarThreshold(int forDepthThreshold, int amount) {
	if (checkState(kKINECTCONTROLLER_READY)) {
		int near = boost::any_cast<int>(_appModel->getProperty("nearThreshold"+ofToString(forDepthThreshold)));
		int far = boost::any_cast<int>(_appModel->getProperty("farThreshold"+ofToString(forDepthThreshold)));
		far = far + amount;
		ofxDepthGenerator*	oniDepthGen = _kinectModel->getONIDepthGen();
		oniDepthGen->setDepthThreshold(forDepthThreshold, near, far);
		_appModel->setProperty("farThreshold"+ofToString(forDepthThreshold), far);
	}
}

//--------------------------------------------------------------
void KinectController::update() {
	
	if (checkState(kKINECTCONTROLLER_READY)) {
		
		Scene * currentScene = _appModel->getCurrentScene();
		
		ofxOpenNIContext*	oniContext = _kinectModel->getONIContext();
		ofxDepthGenerator*	oniDepthGen = _kinectModel->getONIDepthGen();
        //ofxImageGenerator*	oniImageGen = _kinectModel->getONIImageGen();
        ofxIRGenerator*     oniIRGen = _kinectModel->getONIIRGen();
		ofxUserGenerator*	oniUserGen = _kinectModel->getONIUserGen();
		ofxHandGenerator*	oniHandGen = _kinectModel->getONIHandGen();
		
		oniContext->update();
		oniDepthGen->update();
		//oniImageGen->update();
        oniIRGen->update();
		oniUserGen->update();
		
		for (int layer = 0; layer < currentScene->getNumberOfKinectLayers(); layer++) {
			
			KinectView* kinectLayer				= currentScene->getKinectLayer(layer);
			unsigned char* depthPixels			= kinectLayer->getDepthPixels();
			ofxCvGrayscaleImage* depthImage		= kinectLayer->getDepthImage();
			ofxCvContourFinder* depthContour	= kinectLayer->getDepthContour();
			//vector<ofPoint>* depthSmooth		= kinectLayer->_depthSmooth;
			
			depthPixels	= oniDepthGen->getDepthPixels(layer);
			
			depthImage->setFromPixels(depthPixels, (int)oniDepthGen->getWidth(), (int)oniDepthGen->getHeight());
			
			int nBlobs = depthContour->findContours(*depthImage, 1000, 200000, 20, true, false, 0.1);
			
			kinectLayer->update();
			
//			vector<ofPoint> pts;
//			
//			for (int i = 0; i < nBlobs; i++) {
//				for (int j = 0; j < depthContour->blobs[i].pts.size(); j++) {
//					pts.push_back(ofPoint(depthContour->blobs[i].pts[j].x, depthContour->blobs[i].pts[j].y));
//				}
//			}
//			
//			smoothPoints(pts, depthSmooth, 0.1);
			
			
//			kinectLayer->spline2D.clear();
//			
//			for (int i = 0; i < nBlobs; i++) {
//				for (int j = 0; j < depthContour->blobs[i].pts.size(); j++) {
//					if (j%20 == 0) {
//						MSA::Vec2f pt = MSA::Vec2f(depthContour->blobs[i].pts[j].x, depthContour->blobs[i].pts[j].y);
//						kinectLayer->spline2D.push_back(pt);
//					}
//					
//				}
//			}

		}
		
	}
	
}