/*
 *  AppModel.cpp
 *  emptyExample
 *
 *  Created by gameover on 22/08/11.
 *  Copyright 2011 trace media. All rights reserved.
 *
 */

#include "AppModel.h"

//--------------------------------------------------------------
AppModel::AppModel() {
	
    LOG_NOTICE("Constructing AppModel");
	
    //registerStates();
	_currentScene = NULL;
}

//--------------------------------------------------------------
AppModel::~AppModel() {
	
    LOG_NOTICE("Destroying AppModel");
	
}

// state registration
//--------------------------------------------------------------
//void AppModel::registerStates() {
//	
//	LOG_VERBOSE("Registering States");
//	
//	registerState(kAPP_INITING, "kAPP_INITING");
//	registerState(kAPP_LOADING, "kAPP_LOADING");
//	registerState(kAPP_RUNNING, "kAPP_RUNNING");
//	registerState(kAPP_EXITING, "kAPP_EXITING");
//	
//}

/********************************************************
 *      Getters and setters for Scenes               	*
 ********************************************************/
//--------------------------------------------------------------
void AppModel::setScene(Scene * scene) {
	_scenes.insert(pair<string, Scene *>(scene->getName(), scene));
}

Scene *AppModel::getScene(int sceneIndex) {
	
	assert(sceneIndex < _scenes.size());
	int index = 0;
	
	map<string, Scene *>::iterator iter;
	for (iter = _scenes.begin(); iter != _scenes.end(); iter++) {
		if (index == sceneIndex) {
			break;
		}
		index++;
	}
	
	return iter->second;
	
}

Scene *AppModel::getScene(string sceneName) {
	
	map<string, Scene *>::iterator iter;
	iter = _scenes.find(sceneName);
	if(iter == _scenes.end()){
		LOG_ERROR("Attempted to get invalid scene name " + sceneName);
		abort();
	}
	return iter->second;
	
}

bool AppModel::setCurrentScene(string sceneName) {
	
	map<string, Scene *>::iterator sceneIter;
	sceneIter = _scenes.find(sceneName);
	if(sceneIter != _scenes.end()) {
		
		_currentScene = sceneIter->second; // TODO: DO we have to dereference this? TEST IT.
		
		LOG_NOTICE("Set current scene to " + sceneName);
		return true;
		
	} else {
		LOG_ERROR("Unable to set current scene to '" + sceneName + "' because its not in the map");
	}
	
	return false;
}

bool AppModel::nextScene() {
	
	if (_currentScene == NULL) {
		setCurrentScene(_scenes.begin()->first);
		return true;
	}
	
	string nextname;
	// find current scene in map
	map<string, Scene *>::iterator iter;
	for(iter = _scenes.begin(); iter != _scenes.end(); iter++) {
		if(iter->first == _currentScene->getName()){
			iter++; // found current, increment to next
			// is iter end? set name to first, else use iter name
			nextname = (iter == _scenes.end() ? _scenes.begin()->first : iter->first);
			setCurrentScene(nextname);
			LOG_VERBOSE("Next scene: " + nextname);
			return true;
		}
	}
	return false; // should never get here, can probably just be void return
}

bool AppModel::previousScene() {
	
	if (_currentScene == NULL) {
		setCurrentScene(_scenes.rbegin()->first);
		return true;
	}
	
	string previousname;
	// find current scene in map
	map<string, Scene *>::iterator iter;
	for(iter = _scenes.begin(); iter != _scenes.end(); iter++){
		if(iter->first == _currentScene->getName()){
			iter--; // found current, decrement to previous
			// is iter end? set name to reverse first (ie last), else use iter name
			previousname = (iter == _scenes.end() ? _scenes.rbegin()->first : iter->first);
			setCurrentScene(previousname);
			LOG_VERBOSE("Previous scene: " + previousname);
			return true;
		}
	}
	return false; // should never get here, can probably just be void return
}

Scene * AppModel::getCurrentScene(){
	//assert(_currentScene != NULL);
	return _currentScene;
}

map<string, Scene*> AppModel::getScenes() {
	return _scenes;
}

void AppModel::registerStatefulClass(string className) {

	LOG_NOTICE("Registering Stateful Class: " + className);
	
	map<string, string>::iterator it;
	it = _allStates.find(className);
	assert(it == _allStates.end()); // make sure we don't got it already
	
	_allStates.insert(pair<string, string>(className, "NONE"));
	
}

void AppModel::setRemoteState(string className, string state) {

	if (className.find("BaseState") != string::npos) return;
	
	map<string, string>::iterator it;
	it = _allStates.find(className);
	assert(it != _allStates.end()); // make sure we got it
	
	it->second = state;
	
}

string AppModel::getRemoteState(string className) {
	
	map<string, string>::iterator it;
	it = _allStates.find(className);
	assert(it != _allStates.end()); // make sure we got it
	
	return it->second;
	
}

string AppModel::getAllStatesAsList() {
	
	ostringstream out;
	
	map<string, string>::iterator it;
	for (it = _allStates.begin(); it != _allStates.end(); it++) {
		out << it->first << " [" << it->second << "]" << endl;
	}
	
	return out.str();
	
}

/********************************************************
 * Getters and setters for simple int, float, string	*
 * properties using boost::any and std::map. These		*
 * should NOT be used where efficiency really really	*
 * matters but still seem pretty quick!					*
 ********************************************************/

// set any property in a map to propVal
//--------------------------------------------------------------
void AppModel::setProperty(string propName, boost::any propVal) {
	
	if (_anyProps.count(propName) != 0 && !_anyProps[propName].empty()) {
		assert (_anyProps[propName].type() == propVal.type());	// don't let properties change types once init'd
	}
	
	_anyProps[propName] = propVal;
	
}

//--------------------------------------------------------------
void AppModel::adjustIntProperty(string propName, int amount) {
	
	setProperty(propName, boost::any_cast<int>(_anyProps[propName]) + amount);
	
}

//--------------------------------------------------------------
void AppModel::adjustFloatProperty(string propName, float amount) {
	
	setProperty(propName, boost::any_cast<float>(_anyProps[propName]) + amount);
	
}

// get any int property in a map (no cast necessary)
//--------------------------------------------------------------
void AppModel::getProperty(string propName, int & propVal) {
	
	assert(_anyProps.count(propName) != 0);	// if it ain't there abort
	assert(is_int(_anyProps[propName]));		// if it propVal ref is not same type abort
	propVal = boost::any_cast<int>(_anyProps[propName]);
	
}

// get any float property in a map (no cast necessary)
//--------------------------------------------------------------
void AppModel::getProperty(string propName, float & propVal) {
	
	assert(_anyProps.count(propName) != 0);	// if it ain't there abort
	assert(is_float(_anyProps[propName]));	// if it propVal ref is not same type abort
	propVal = boost::any_cast<float>(_anyProps[propName]);
	
}

// get any string property in a map (no cast necessary)
//--------------------------------------------------------------
void AppModel::getProperty(string propName, string & propVal) {
	
	assert(_anyProps.count(propName) != 0);	// if it ain't there abort
	assert(is_string(_anyProps[propName]));	// if it propVal ref is not same type abort
	propVal = boost::any_cast<string>(_anyProps[propName]);
	
}

// get any ANY property in a map (cast necessary -> use boost::any_cast<TYPE>(property))
//--------------------------------------------------------------
boost::any AppModel::getProperty(string propName) {
	
	assert(_anyProps.count(propName) != 0); // if it ain't there abort
	return _anyProps[propName];
	
}

// has any ANY property in a map?
//--------------------------------------------------------------
bool AppModel::hasProperty(string propName) {
	
	return (_anyProps.count(propName) == 0 ? false : true);
	
}

void AppModel::toggleBooleanProperty(string propName) {
	bool prop = boost::any_cast<bool>(getProperty(propName));
	setProperty(propName, !prop);
}

// return a list of ALL properties -> useful for debug
//--------------------------------------------------------------
string AppModel::getAllPropsAsList() {
	
	string propsList;
	
	map<string, boost::any>::iterator anyIT;
	for (anyIT = _anyProps.begin(); anyIT != _anyProps.end(); anyIT++) {
		
		string valAsString;
		string propAsString = anyIT->first;
		if (is_int(anyIT->second) == true) {
			valAsString = ofToString(boost::any_cast<int>(anyIT->second));
		}
		if (is_float(anyIT->second) == true) {
			valAsString = ofToString(boost::any_cast<float>(anyIT->second));
		}
		if (is_string(anyIT->second) == true) {
			valAsString = boost::any_cast<string>(anyIT->second);
		}
		if(is_bool(anyIT->second) == true){
			valAsString = ((boost::any_cast<bool>)(anyIT->second) ? "true" : "false");
		}
		
		propsList += pad(propAsString) + " = " + pad(valAsString) + " type: " + anyIT->second.type().name() + "\n";
	}
	
	return propsList;
	
}

//--------------------------------------------------------------
map<string, string> AppModel::getAllPropsNameTypeAsMap() {
	/*
	 returning as name,type instead of name,boost::any
	 beacuse we'd have to expose the is_int/etc to check the any types.
	 */
	map<string, string> retmap;
	
	map<string, boost::any>::iterator iter;
	for (iter = _anyProps.begin(); iter != _anyProps.end(); iter++) {
		/* add the name and type to the map */
		if (is_int(iter->second)){
			retmap.insert(pair<string,string>(iter->first, "int"));
		}
		if (is_float(iter->second)){
			retmap.insert(pair<string,string>(iter->first, "float"));
		}
		if (is_string(iter->second)){
			retmap.insert(pair<string,string>(iter->first, "string"));
		}
		if(is_bool(iter->second)){
			retmap.insert(pair<string,string>(iter->first, "bool"));
		}
	}
	return retmap;
}

//--------------------------------------------------------------
inline string AppModel::pad(string & t_string) {
	
	// possibly a more elegant sprintf solution for this but can't work out how to
	// dynamically set sprintf(objWithWhiteSpace, "%" + ofToString(_padLength) + "s", objectName) ???
	
	string paddedString = t_string;
	int padLength = 0;
	
	// check length and adjust overall pad if the objectName is longer than the current padLength
	if (t_string.size() > _padLength) _padLength = t_string.size();
	
	padLength = _padLength - t_string.size();
	
	for (int i = 0; i < padLength; i++) paddedString += " ";
	
	return paddedString;
	
}

// check type int
//--------------------------------------------------------------
inline bool AppModel::is_int(const boost::any & operand) {
    return operand.type() == typeid(int);
}

// check type float
//--------------------------------------------------------------
inline bool AppModel::is_float(const boost::any & operand) {
    return operand.type() == typeid(float);
}

// check type string
//--------------------------------------------------------------
inline bool AppModel::is_string(const boost::any & operand) {
    return operand.type() == typeid(string);
}

// check type bool
//--------------------------------------------------------------
inline bool AppModel::is_bool(const boost::any & operand) {
	return operand.type() == typeid(bool);
}

// check type char *
//--------------------------------------------------------------
inline bool AppModel::is_char_ptr(const boost::any & operand) {
    try {
		boost::any_cast<const char *>(operand);
        return true;
    } catch(const boost::bad_any_cast &) {
        return false;
    }
}