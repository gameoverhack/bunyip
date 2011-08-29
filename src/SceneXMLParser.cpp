/*
 *  SceneXMLParser.cpp
 *  Bunyip
 *
 *  Created by gameover on 26/08/11.
 *  Copyright 2011 trace media. All rights reserved.
 *
 */

#include "SceneXMLParser.h"

SceneXMLParser::SceneXMLParser(string xmlFile) : IXMLParser(xmlFile){
	load();
	parseXML();
}

void SceneXMLParser::parseXML(){
	
	if(!_xml.pushTag("scenes", 0)){
		LOG_ERROR("No scene nodes in config");
		abort();
	} else {
		LOG_VERBOSE("Parsing scenes");
	}

	for(int node = 0; node < _xml.getNumTags("scene"); node++) {
		
		string sceneName	= _xml.getAttribute("scene", "name", "error", node);
		int numKinectLayers = _xml.getAttribute("scene", "numKinectLayers", -1, node);
		int numVideoLayers	= _xml.getAttribute("scene", "numVideoLayers", -1, node);
		float sceneWidth	= _xml.getAttribute("scene", "width", -1.0f, node);
		float sceneHeight	= _xml.getAttribute("scene", "height", -1.0f, node);
		
		if (sceneName == "error" || numKinectLayers == -1 || numVideoLayers == -1 || sceneWidth == -1.0f || sceneHeight == -1.0f) {
			LOG_ERROR("Scene attributes are missing or broken!");
			abort();
		}
		
		KinectView* kinectLayers[MAX_KINECT_LAYERS];
		bool hasKinectLayers = false;
		
		_xml.pushTag("scene", node);
		
		for (int layer = 0; layer < _xml.getNumTags("kinectLayer"); layer++) {
			
			hasKinectLayers = true;
			
			float layerWidth		= _xml.getAttribute("kinectLayer", "width", -1.0f, layer);
			float layerHeight		= _xml.getAttribute("kinectLayer", "height", -1.0f, layer);
			int layerNearThresh		= _xml.getAttribute("kinectLayer", "nearThreshold", 0, layer);
			int layerFarThresh		= _xml.getAttribute("kinectLayer", "farThreshold", 10000, layer);
			
			
			if (layerWidth == -1.0f || layerHeight == -1.0f) {
				LOG_ERROR("KinectLayer attributes are missing or broken!");
				abort();
			}
			
			_xml.pushTag("kinectLayer", layer);
			
			float viewportX			= _xml.getAttribute("viewPort", "x", -1.0f, 0);
			float viewportY			= _xml.getAttribute("viewPort", "y", -1.0f, 0);
			float viewportWidth		= _xml.getAttribute("viewPort", "width", -1.0f, 0);
			float viewportHeight	= _xml.getAttribute("viewPort", "height", -1.0f, 0);
			
			ofPoint* viewportCorners = new ofPoint[4];
			
			_xml.pushTag("viewPort", 0);
			
			for (int corner = 0; corner < 4; corner++) {
				viewportCorners[corner].x = _xml.getAttribute("corner", "x", 0.0f, corner);
				viewportCorners[corner].y = _xml.getAttribute("corner", "y", 0.0f, corner);
			}
			
			if (viewportX == -1.0f || viewportY == -1.0f || viewportWidth == -1.0f || viewportHeight == -1.0f) {
				LOG_ERROR("ViewPort attributes are missing or broken!");
				abort();
			}

			ViewPort * viewPort = new ViewPort(viewportX, viewportY, viewportWidth, viewportHeight, viewportCorners);
			kinectLayers[layer] = new KinectView(layerWidth, layerHeight, layer, viewPort, layerNearThresh, layerFarThresh);
			
			_xml.popTag();
			_xml.popTag();
			
		}
		
		VideoView* videoLayers[MAX_VIDEO_LAYERS];
		bool hasVideoLayers = false;
		
		for (int layer = 0; layer < _xml.getNumTags("videoLayer"); layer++) {
			
			hasVideoLayers = true;
			
			string videoPath	=_xml.getAttribute("videoLayer", "videoPath", "error", layer);
			float videoWidth	= _xml.getAttribute("videoLayer", "width", -1.0f, 0);
			float videoHeight	= _xml.getAttribute("videoLayer", "height", -1.0f, 0);
			
			videoLayers[layer]	= new VideoView(videoWidth, videoHeight, layer, videoPath);
			
		}
		
		Scene* scene = new Scene(sceneName, 
								 numKinectLayers, 
								 numVideoLayers, 
								 sceneWidth, 
								 sceneHeight, 
								 (hasKinectLayers ? kinectLayers : NULL), 
								 (hasVideoLayers ? videoLayers : NULL));
		
		_appModel->setScene(scene);
		
		_xml.popTag();
		
	}
		
}
