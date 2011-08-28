/*
 *  DataController.cpp
 *  Bunyip
 *
 *  Created by gameover on 24/08/11.
 *  Copyright 2011 trace media. All rights reserved.
 *
 */

#include "DataController.h"

//--------------------------------------------------------------
DataController::DataController() {
	
	LOG_NOTICE("Constructing DataController");
	
    registerStates();
	
}

//--------------------------------------------------------------
DataController::~DataController() {
	
	LOG_NOTICE("Destroying DataController");
	
}

//--------------------------------------------------------------
void DataController::registerStates() {
	
	LOG_VERBOSE("Registering States");
	
	registerState(kDATACONTROLLER_READY, "kDATACONTROLLER_READY");
	registerState(kDATACONTROLLER_PROPERTY_PARSING, "kDATACONTROLLER_PROPERTY_PARSING");
	registerState(kDATACONTROLLER_PROPERTY_BUILDING, "kDATACONTROLLER_PROPERTY_BUILDING");
	registerState(kDATACONTROLLER_SCENE_PARSING, "kDATACONTROLLER_SCENE_PARSING");
	registerState(kDATACONTROLLER_SCENE_BUILDING, "kDATACONTROLLER_SCENE_BUILDING");
	registerState(kDATACONTROLLER_FINISHED, "kDATACONTROLLER_FINISHED");
	
	_appModel->registerStatefulClass(typeid(*this).name());
	
	setState(kDATACONTROLLER_READY);
	
}

//--------------------------------------------------------------
void DataController::loadProperties(string configFilePath) {
	
	setState(kDATACONTROLLER_PROPERTY_PARSING);
	
	string loadPath = _configFilePath = configFilePath;
	
	LOG_NOTICE("Loading properties from XML: " + loadPath);
	
	try {
		PropertyXMLParser propertyXMLParser(loadPath);
	}
	catch (GenericXMLParseException) {
		LOG_WARNING("Loading properties from XML: " + loadPath + " failed...perhaps this is the first time you are running? Make sure to save properties on exit...");
	}
	
	setState(kDATACONTROLLER_READY);
	
}

//--------------------------------------------------------------
void DataController::saveProperties(string configFilePath) {
	
	setState(kDATACONTROLLER_PROPERTY_BUILDING);
	
	string savePath = string(configFilePath != "" ? configFilePath : _configFilePath);
	
	LOG_NOTICE("Saving properties to XML: " + savePath);
	
	PropertyXMLBuilder propertyXMLBuilder(savePath);
	
	setState(kDATACONTROLLER_READY);
	
}

//--------------------------------------------------------------
void DataController::loadScenes(string scenesFilePath) {
	
	setState(kDATACONTROLLER_SCENE_PARSING);
	
	string loadPath = _scenesFilePath = scenesFilePath;
	
	LOG_NOTICE("Loading scenes from XML: " + loadPath);
	
	try {
		SceneXMLParser scenesXMLParser(loadPath);
	}
	catch (GenericXMLParseException) {
		LOG_WARNING("Loading properties from XML: " + loadPath + " failed...perhaps this is the first time you are running? Make sure to save properties on exit...");
	}
	
	setState(kDATACONTROLLER_READY);
	
}

//--------------------------------------------------------------
void DataController::saveScenes(string scenesFilePath) {
	
	setState(kDATACONTROLLER_SCENE_BUILDING);
	
	string savePath = string(scenesFilePath != "" ? scenesFilePath : _scenesFilePath);
	
	LOG_NOTICE("Saving scenes to XML: " + savePath);
	
	SceneXMLBuilder scenesXMLBuilder(savePath);
	
	setState(kDATACONTROLLER_READY);
	
}