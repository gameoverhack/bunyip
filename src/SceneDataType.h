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

#define MAX_KINECT_LAYERS 4
#define MAX_VIDEO_LAYERS 4

#include "KinectView.h"
#include "VideoView.h"

class Scene {
	
public:
	
	Scene(string name, int numberKienctLayers, int numberVideoLayers, int width, int height, KinectView * kinectLayers[MAX_KINECT_LAYERS] = NULL, VideoView * videoLayers[MAX_VIDEO_LAYERS] = NULL)
	: _name(name), _numberKinectLayers(numberKienctLayers), _numberVideoLayers(numberVideoLayers), _width(width), _height(height) {
		
		if (kinectLayers == NULL) {
			
			LOG_VERBOSE("Constructing new scene with defualt KinectLayer and ViewPorts");
			
			for (int layer = 0; layer < _numberKinectLayers; layer++) {
				_kinectLayers[layer] = new KinectView(width, height, layer);
			}
			
		} else {
			
			LOG_VERBOSE("Constructing new scene with defined KinectLayer and ViewPorts");
			
			for (int layer = 0; layer < _numberKinectLayers; layer++) {
				_kinectLayers[layer] = kinectLayers[layer];
			}
						
		}
		
		if (videoLayers == NULL) {
			
			LOG_VERBOSE("Constructing new scene with defualt VideoLayer");
			
			for (int layer = 0; layer < _numberVideoLayers; layer++) {
				_videoLayers[layer] = new VideoView(width, height, layer);
			}
			
		} else {
			
			LOG_VERBOSE("Constructing new scene with defined VideoLayer");
			
			for (int layer = 0; layer < _numberVideoLayers; layer++) {
				_videoLayers[layer] = videoLayers[layer];
			}
			
		}
		
		_currentVideoLayer	= -1;
		_currentKinectLayer = -1;
		
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
	
	KinectView*	getCurrentKinectLayer() {
		if(_currentKinectLayer >= 0) {
			return _kinectLayers[_currentKinectLayer];
		} else return NULL;
	};
	
	int			getCurrentKinectLayerIndex() {return _currentKinectLayer;};
	void		setCurrentKinectLayer(int layer) {assert(layer < _numberKinectLayers); _currentKinectLayer = layer;};
	
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
			_kinectLayers[layer] = new KinectView(_width, _height, layer);
		} else {
			_kinectLayers[layer] = kinectLayer;
		}

		_numberKinectLayers++;
		
		return true;
		
	};
	
	KinectView*			getKinectLayer(int layer) {assert(layer < _numberKinectLayers); return _kinectLayers[layer];};
	
	VideoView*	getCurrentVideoLayer() {
		if(_currentVideoLayer >= 0) {
			return _videoLayers[_currentVideoLayer];
		} else return NULL;
	};
	
	int			getCurrentVideoLayerIndex() {return _currentVideoLayer;};
	void		setCurrentVideoLayer(int layer) {assert(layer < _numberVideoLayers); _currentVideoLayer = layer;};
	
	bool	deleteVideoLayer(int layer) {
		
		LOG_VERBOSE("Deleting VideoLayer: " + ofToString(layer) + " from " + getName());
		
		if (layer > _numberVideoLayers) {
			LOG_ERROR("Requested VideoLayer to delete is outside of range");
			return false;
		}
		
		delete _videoLayers[layer];
		
		for (int i = layer; i < _numberVideoLayers; i++) {
			swap(_videoLayers[i], _videoLayers[i+1]);
		}
		
		_numberVideoLayers--;
		
		return true;
		
	};
	
	bool	addVideoLayer(int layer = -1, VideoView * videoLayer = NULL) {
		
		LOG_VERBOSE("Adding VideoLayer to: " + getName());
		
		if (_numberVideoLayers + 1 > MAX_VIDEO_LAYERS) {
			LOG_ERROR("Requested VideoLayer to add is greater than MAX_VIDEO_LAYERS");
			return false;
		}
		
		if (layer >= 0) {
			for (int i = _numberVideoLayers; i > layer ; i--) {
				swap(_videoLayers[i], _videoLayers[i-1]);
			}
		} else {
			layer = _numberVideoLayers;
		}
		
		if (layer > _numberVideoLayers) {
			LOG_ERROR("Requested VideoLayer to add is greater than _numberVideoLayers + 1");
			return false;
		}
		
		if (videoLayer == NULL) {
			_videoLayers[layer] = new VideoView(_width, _height, layer);
		} else {
			_videoLayers[layer] = videoLayer;
		}
		
		_numberVideoLayers++;
		
		return true;
		
	};
	
	VideoView*	getVideoLayer(int layer) {assert(layer < _numberVideoLayers); return _videoLayers[layer];};
	
private:
	
	string		_name;
	
	int			_numberKinectLayers;
	int			_numberVideoLayers;
	int			_currentKinectLayer;
	int			_currentVideoLayer;
	
	float		_width;
	float		_height;
	
	VideoView*	_videoLayers[MAX_VIDEO_LAYERS];
	KinectView*	_kinectLayers[MAX_KINECT_LAYERS];
	
};

#endif;