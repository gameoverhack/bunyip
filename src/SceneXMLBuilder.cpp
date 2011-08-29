/*
 *  SceneXMLBuilder.cpp
 *  Bunyip
 *
 *  Created by gameover on 26/08/11.
 *  Copyright 2011 trace media. All rights reserved.
 *
 */

#include "SceneXMLBuilder.h"

SceneXMLBuilder::SceneXMLBuilder(string xmlFile) : IXMLBuilder(xmlFile){
	buildXML();
	save();
}

void SceneXMLBuilder::buildXML(){
	
	// get list of all properties
	map<string, Scene*> scenes = _appModel->getScenes();
	
	// set xml and root
	_xml.addTag("scenes");
	_xml.pushTag("scenes");
	
	// create nodes for each property
	map<string, Scene*>::iterator iter = scenes.begin();
	while(iter != scenes.end()) {
		
		Scene* scene = iter->second;
		
		int node = _xml.addTag("scene");
		_xml.addAttribute("scene", "name", scene->getName(), node);
		_xml.addAttribute("scene", "numKinectLayers", scene->getNumberOfKinectLayers(), node);
		_xml.addAttribute("scene", "numVideoLayers", scene->getNumberOfVideoLayers(), node);
		_xml.addAttribute("scene", "width", scene->getWidth(), node);
		_xml.addAttribute("scene", "height", scene->getHeight(), node);
		
		_xml.pushTag("scene", node);
		
		for (int layer = 0; layer < scene->getNumberOfKinectLayers(); layer++) {
			
			KinectView* kinectLayer		= scene->getKinectLayer(layer);
			ViewPort* viewPort			= kinectLayer->getViewPort();

			_xml.addTag("kinectLayer");
			
			_xml.addAttribute("kinectLayer", "width", kinectLayer->getWidth(), layer);
			_xml.addAttribute("kinectLayer", "height", kinectLayer->getHeight(), layer);
			_xml.addAttribute("kinectLayer", "nearThreshold", kinectLayer->getNearThreshold(), layer);
			_xml.addAttribute("kinectLayer", "farThreshold", kinectLayer->getFarThreshold(), layer);
			
			_xml.pushTag("kinectLayer", layer);
			
			_xml.addTag("viewPort");
			
			_xml.addAttribute("viewPort", "x", viewPort->getX(), 0);
			_xml.addAttribute("viewPort", "y", viewPort->getY(), 0);
			_xml.addAttribute("viewPort", "width", viewPort->getWidth(), 0);
			_xml.addAttribute("viewPort", "height", viewPort->getHeight(), 0);
			
			_xml.pushTag("viewPort", 0);
			
			for (int corner = 0; corner < 4; corner++) {
				
				_xml.addTag("corner");
				
				(float)_xml.addAttribute("corner", "x", viewPort->getCorners()[corner].x, corner);
				(float)_xml.addAttribute("corner", "y", viewPort->getCorners()[corner].y, corner);
				
			}
			
			_xml.popTag();
			_xml.popTag();
			
		}
		
		for (int layer = 0; layer < scene->getNumberOfVideoLayers(); layer++) {
			
			VideoView* videoLayer		= scene->getVideoLayer(layer);
			//ViewPort* viewPort			= kinectLayer->getViewPort();
			
			_xml.addTag("videoLayer");
			
			_xml.addAttribute("videoLayer", "videoPath", videoLayer->getVideoPath(), layer);
			_xml.addAttribute("videoLayer", "width", videoLayer->getWidth(), layer);
			_xml.addAttribute("videoLayer", "height", videoLayer->getHeight(), layer);
			
		}

		_xml.popTag();
		
		iter++;
		
	}
	
	_xml.popTag();
}
