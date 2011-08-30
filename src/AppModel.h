/*
 *  AppModel.h
 *  emptyExample
 *
 *  Created by gameover on 22/08/11.
 *  Copyright 2011 trace media. All rights reserved.
 *
 */

#ifndef _H_APPMODEL
#define	_H_APPMODEL

#include "Singleton.h"
#include "AppDataTypes.h"
#include "SceneDataType.h"

#include <boost/any.hpp>

#include <map>
#include <vector>
#include <assert.h>
#include <string>

//#define EXTENDED_DISPLAY

//#define SANS_KINECT


using std::map;
using std::vector;
using std::string;

//enum {
//	kAPP_INITING,
//	kAPP_LOADING,
//	kAPP_RUNNING,
//	kAPP_EXITING
//};

class AppModel {
	
public:
	
	AppModel();
	~AppModel();
	
	//void					registerStates();
	
	// scene and sequence getter/setters
	void					setScene(Scene * scene);
	bool					setCurrentScene(string sceneName);
	
	Scene*					getCurrentScene();
	
	Scene*					getScene(string sceneName);
	map<string, Scene*>		getScenes();
	
    bool					nextScene();
	bool					previousScene();
	
    // generic property getter/setters
	bool					hasProperty(string propName);
	void					setProperty(string propName, boost::any propVal);
	
	// grrr
	void					adjustIntProperty(string propName, int amount);
	void					adjustFloatProperty(string propName, float amount);
	
	void					getProperty(string propName, int & propVal);
	void					getProperty(string propName, float & propVal);
	void					getProperty(string propName, string & propVal);
	
	boost::any				getProperty(string propName);
	
	void					toggleBooleanProperty(string propName);
	
	string					getAllPropsAsList();
	map<string, string>		getAllPropsNameTypeAsMap();
	
	void					registerStatefulClass(string className);
	void					setRemoteState(string className, string state);
	string					getRemoteState(string className);
	
	string					getAllStatesAsList();
	
	// function registration for dynamic/virtualization
	template <class DelegateType>
	void registerFunction(string uniqueFunctionID, DelegateType delegate) {
		_registeredFunctions.insert(pair<string, DelegateMemento>(uniqueFunctionID, delegate.GetMemento()));
	};

	map<string, DelegateMemento>	_registeredFunctions; // dangerous but copies and pointers don't seem to work
	
private:
	
	inline string			pad(string & objectName);
	int						_padLength;
	
	inline bool			    is_int(const boost::any & operand);
	inline bool			    is_float(const boost::any & operand);
	inline bool			    is_string(const boost::any & operand);
	inline bool			    is_char_ptr(const boost::any & operand);
	inline bool			    is_bool(const boost::any & operand);
	
	map<string, boost::any>	_anyProps;
	
	Scene*					_currentScene;
	map<string, Scene *>	_scenes;
	
	map<string, string>		_allStates;
	
};

typedef Singleton<AppModel> AppModelSingleton;					// Global declaration

static AppModel * _appModel	= AppModelSingleton::Instance();	// this is my idea of a compromise:
																// no defines, keeps introspection
																// but allows data sharing between classes
#endif