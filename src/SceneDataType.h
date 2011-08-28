/*
 *  SceneDataType.h
 *  Bunyip
 *
 *  Created by gameover on 26/08/11.
 *  Copyright 2011 trace media. All rights reserved.
 *
 */

#ifndef _H_SCENEDATATYPE
#define _H_SCENEDATATYPE

#include "KinectView.h"

//class KinectLayer : public BaseView {
//	
//public:
//	
//	KinectLayer(float width, float height, ViewPort * viewPort = NULL) : BaseView(width, height) {
//		
//		if (viewPort == NULL) {
//			
//			LOG_VERBOSE("Creating KinectLayer with default ViewPort");
//			
//			_viewPort = new ViewPort(width, height);
//			
//		} else {
//			
//			LOG_VERBOSE("Creating KinectLayer with defined ViewPort");
//			
//			_viewPort = viewPort;
//			
//		}
//
//		_depthPixels	= new unsigned char[640 * 480];
//		_depthImage		= new ofxCvGrayscaleImage();
//		_depthContour	= new ofxCvContourFinder();
//		//_depthSmooth	= new vector<ofPoint>;
//		//spline2D.setInterpolation(MSA::kInterpolationCubic);
//		
//		_depthImage->allocate(640, 480);
//		
//	};
//	
//	~KinectLayer() {
//		
//		LOG_NOTICE("Destroying KinectLayer");
//		
//		_depthImage->clear();
//		
//		delete _viewPort;
//		delete _depthImage;
//		delete _depthContour;
//		//delete _depthSmooth;
//		delete [] _depthPixels;
//		
//	}
//	void update() {};
//	//ViewPort*				getViewPort() {return _viewPort;};
//	ofxCvGrayscaleImage*	getDepthImage() {return _depthImage;};
//	ofxCvContourFinder*		getDepthContour() {return _depthContour;};
//	unsigned char*			getDepthPixels() {return _depthPixels;};
//	
//	//float					getWidth() {return _width;};
//	//float					getHeight() {return _height;};
//	
//	//MSA::Interpolator2D				spline2D;
//	
//	//vector <ofPoint>* _depthSmooth;
//	
//private:
//	
//	//float					_width;
//	//float					_height;
//		
//	ofxCvGrayscaleImage*	_depthImage;
//	ofxCvContourFinder*		_depthContour;
//	unsigned char*			_depthPixels;
//	//ViewPort*				_viewPort;
//	
//};


class Scene {
	
public:
	
	Scene(string name, int numberKienctLayers, int numberVideoLayers, int width, int height, KinectView * kinectLayers[MAX_KINECT_LAYERS] = NULL)
	: _name(name), _numberKinectLayers(numberKienctLayers), _numberVideoLayers(numberVideoLayers), _width(width), _height(height) {
		
		if (kinectLayers == NULL) {
			
			LOG_VERBOSE("Constructing new scene with defualt KinectLayer and ViewPorts");
			
			for (int layer = 0; layer < _numberKinectLayers; layer++) {
				_kinectLayers[layer] = new KinectView(width, height);
			}
			
		} else {
			
			LOG_VERBOSE("Constructing new scene with defined KinectLayer and ViewPorts");
			
			for (int layer = 0; layer < _numberKinectLayers; layer++) {
				_kinectLayers[layer] = kinectLayers[layer];
			}
						
		}

	};
	
	~Scene() {
		
		for (int layer = 0; layer < _numberKinectLayers; layer++) {
			delete _kinectLayers[layer];
		}
		
	};
	
	string	getName() {return _name;};
	
	float	getWidth() {return _width;};
	float	getHeight() {return _height;};	
	
	int		getNumberOfKinectLayers() {return _numberKinectLayers;};
	int		getNumberOfVideoLayers() {return _numberVideoLayers;};
	
	bool	deleteKinectLayer(int layer) {
		
		LOG_VERBOSE("Deleting KinectLayer: " + ofToString(layer) + " from " + getName());
		
		if (layer > _numberKinectLayers) {
			LOG_ERROR("Requested KinectLayer to delete is outside of range");
			return false;
		}
		
		delete _kinectLayers[layer];
		
		for (int i = layer; i < _numberKinectLayers; i++) {
			swap(_kinectLayers[i], _kinectLayers[i+1]);
		}
			
		_numberKinectLayers--;
		
		return true;
		
	};
	
	bool	addKinectLayer(int layer = -1, KinectView * kinectLayer = NULL) {
		
		LOG_VERBOSE("Adding KinectLayer to: " + getName());
		
		if (_numberKinectLayers + 1 > MAX_KINECT_LAYERS) {
			LOG_ERROR("Requested KinectLayer to add is greater than MAX_KINECT_LAYERS");
			return false;
		}

		if (layer >= 0) {
			for (int i = _numberKinectLayers; i > layer ; i--) {
				swap(_kinectLayers[i], _kinectLayers[i-1]);
			}
		} else {
			layer = _numberKinectLayers;
		}
		
		if (layer > _numberKinectLayers) {
			LOG_ERROR("Requested KinectLayer to add is greater than _numberKinectLayers + 1");
			return false;
		}
		
		if (kinectLayer == NULL) {
			_kinectLayers[layer] = new KinectView(_width, _height);
		} else {
			_kinectLayers[layer] = kinectLayer;
		}

		_numberKinectLayers++;
		
		return true;
		
	};
	
	KinectView*	getKinectLayer(int layer) {assert(layer < _numberKinectLayers); return _kinectLayers[layer];};
	
private:
	
	string		_name;
	
	int			_numberKinectLayers;
	int			_numberVideoLayers;
	float		_width;
	float		_height;
	
	KinectView* _kinectLayers[MAX_KINECT_LAYERS];
	
};

#endif;