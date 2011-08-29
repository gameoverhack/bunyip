/*
 *  KeyboardModel.h
 *  Bunyip
 *
 *  Created by gameover on 24/08/11.
 *  Copyright 2011 trace media. All rights reserved.
 *
 */

#ifndef _H_KEYBOARDMODEL
#define _H_KEYBOARDMODEL

#include "AppDataTypes.h"

class KeyboardModel {
	
public:
	
	KeyboardModel() {
		LOG_NOTICE("Constructing KeyboardModel");
	};
	
	~KeyboardModel() {
		LOG_NOTICE("Destructing KeyboardModel");
	};	
	
	
	void registerKey(int key, key_st keyType, string helpMessage, string functionToCall) {
		KeyMessage keyboardMessage(key, keyType, 0);
		InputParams0<KeyMessage> inputParams(keyboardMessage);
		registerInputToFunction(functionToCall, inputParams, helpMessage);
	}
	
	template<class Param1>
	void registerKey(int key, key_st keyType, string helpMessage, string functionToCall, Param1 param1) {
		KeyMessage keyboardMessage(key, keyType, 0);
		InputParams1<KeyMessage, Param1> inputParams(keyboardMessage, param1);
		registerInputToFunction(functionToCall, inputParams, helpMessage);
	}
	
	template<class Param1>
	void registerKey(int key, key_st keyType, string helpMessage, string functionToCall, Param1 &param1, bool variableIsPointer) {
		KeyMessage keyboardMessage(key, keyType, 0);
		InputParams1<KeyMessage, Param1> inputParams(keyboardMessage, &param1);
		registerInputToFunction(functionToCall, inputParams, helpMessage);
	}
	
	template<class Param1, class Param2>
	void registerKey(int key, key_st keyType, string helpMessage, string functionToCall, Param1 param1, Param2 param2) {
		KeyMessage keyboardMessage(key, keyType, 0);
		InputParams2<KeyMessage, Param1, Param2> inputParams(keyboardMessage, param1, param2);
		registerInputToFunction(functionToCall, inputParams, helpMessage);
	}
	
	template<class Param1, class Param2>
	void registerKey(int key, key_st keyType, string helpMessage, string functionToCall, Param1 &param1, Param2 param2, bool parameter1IsPointer) {
		KeyMessage keyboardMessage(key, keyType, 0);
		InputParams2<KeyMessage, Param1, Param2> inputParams(keyboardMessage, &param1, param2);
		registerInputToFunction(functionToCall, inputParams, helpMessage);
	}
	
	template<class Param1, class Param2>
	void registerKey(int key, key_st keyType, string helpMessage, string functionToCall, Param1 &param1, Param2 &param2, bool parameter1IsPointer, bool parameter2IsPointer) {
		KeyMessage keyboardMessage(key, keyType, 0);
		InputParams2<KeyMessage, Param1, Param2> inputParams(keyboardMessage, &param1, &param2);
		registerInputToFunction(functionToCall, inputParams, helpMessage);
	}
	
	// function registration for dynamic/virtualization
	template <class DelegateType>
	void registerFunction(string uniqueFunctionID, DelegateType delegate) {
		_registeredFunctions.insert(pair<string, DelegateMemento>(uniqueFunctionID, delegate.GetMemento()));
	}
	
	template <class InputParams>
	void registerInputToFunction(string uniqueFunctionID, InputParams inputParameters, string usage = "") {
		
		map<string, DelegateMemento>::iterator it = _registeredFunctions.find(uniqueFunctionID);
		
		if (it != _registeredFunctions.end()) {
			
			LOG_VERBOSE("Adding function map for: " + uniqueFunctionID);
			MappedDelegate<InputParams> md(uniqueFunctionID, it->second, inputParameters);
			setMappedDelegate(inputParameters.getMessageMap(), md);
			
			if (usage == "") {
				int nParams = inputParameters.getNumParams();
				ostringstream params;
				switch (nParams) {
					case 0:
						params << "()";
						break;
					case 1:
						params << "(" << inputParameters.getParam1() << ")";
						break;
					case 2:
						params << "(" << inputParameters.getParam1() << ", " << inputParameters.getParam1() << ")";
						break;
				}
				
				usage = uniqueFunctionID + params.str();
			}
			
			storeUsage(inputParameters.getMessageMap(), usage);
			
		} else {
			
			LOG_VERBOSE("No function registered for: " + uniqueFunctionID);
			abort();
			
		}
		
	}
	
	string getAllKeyboardUsageAsList(bool log = false) {
		
		ostringstream out;
		for (int i = 0; i < _keyboardUsage.size(); i++) {
			out << _keyboardUsage[i] << endl;
		}
		
		if (log) {
			LOG_NOTICE(out.str());
		}
		
		return out.str();
		
	};
	
	// making these public for now until i work out a nicer way to return
	map< KeyMessage, DelegateType >											_mappedKeyboardType;
	vector<string>															_keyboardUsage;
	
	map< KeyMessage, MappedDelegate<InputParams0<KeyMessage> > >			_mappedKeyboardParams0;
	
	map< KeyMessage, MappedDelegate<InputParams1<KeyMessage, string> > >			_mappedKeyboardParamsString1;
	map< KeyMessage, MappedDelegate<InputParams1<KeyMessage, float> > >				_mappedKeyboardParamsFloat1;
	map< KeyMessage, MappedDelegate<InputParams1<KeyMessage, int> > >				_mappedKeyboardParamsInt1;
	map< KeyMessage, MappedDelegate<InputParams1<KeyMessage, bool> > >				_mappedKeyboardParamsBool1;
	
	map< KeyMessage, MappedDelegate<InputParams2<KeyMessage, string, string> > >	_mappedKeyboardParamsStringString2;
	map< KeyMessage, MappedDelegate<InputParams2<KeyMessage, string, float> > >		_mappedKeyboardParamsStringFloat2;
	map< KeyMessage, MappedDelegate<InputParams2<KeyMessage, string, int> > >		_mappedKeyboardParamsStringInt2;
	map< KeyMessage, MappedDelegate<InputParams2<KeyMessage, string, bool> > >		_mappedKeyboardParamsStringBool2;
	
	map< KeyMessage, MappedDelegate<InputParams2<KeyMessage, float, float> > >		_mappedKeyboardParamsFloatFloat2;
	map< KeyMessage, MappedDelegate<InputParams2<KeyMessage, float, string> > >		_mappedKeyboardParamsFloatString2;
	map< KeyMessage, MappedDelegate<InputParams2<KeyMessage, float, int> > >		_mappedKeyboardParamsFloatInt2;
	map< KeyMessage, MappedDelegate<InputParams2<KeyMessage, float, bool> > >		_mappedKeyboardParamsFloatBool2;
	
	map< KeyMessage, MappedDelegate<InputParams2<KeyMessage, int, int> > >			_mappedKeyboardParamsIntInt2;
	map< KeyMessage, MappedDelegate<InputParams2<KeyMessage, int, string> > >		_mappedKeyboardParamsIntString2;
	map< KeyMessage, MappedDelegate<InputParams2<KeyMessage, int, float> > >		_mappedKeyboardParamsIntFloat2;
	map< KeyMessage, MappedDelegate<InputParams2<KeyMessage, int, bool> > >			_mappedKeyboardParamsIntBool2;
	
	map< KeyMessage, MappedDelegate<InputParams2<KeyMessage, bool, bool> > >		_mappedKeyboardParamsBoolBool2;
	map< KeyMessage, MappedDelegate<InputParams2<KeyMessage, bool, string> > >		_mappedKeyboardParamsBoolString2;
	map< KeyMessage, MappedDelegate<InputParams2<KeyMessage, bool, float> > >		_mappedKeyboardParamsBoolFloat2;
	map< KeyMessage, MappedDelegate<InputParams2<KeyMessage, bool, int> > >			_mappedKeyboardParamsBoolInt2;
	
	
private:
	
	map<string, DelegateMemento>	_registeredFunctions;
	
	void storeUsage(KeyMessage km, string usage) {
		
		char c = (char)km.getKey();
		ostringstream usestream;
		
		usestream << "'" << c << "'" << " - " << usage;
		
		usage = usestream.str();
		
		LOG_VERBOSE("Created key usage: " + usage);
		
		_keyboardUsage.push_back(usage);
	}
	
	void setMappedDelegate(KeyMessage km, MappedDelegate<InputParams0<KeyMessage> > md) {
		LOG_VERBOSE("Store p0");
		_mappedKeyboardType.insert(pair<KeyMessage, DelegateType> (km, GO_DELEGATE_NONE));
		_mappedKeyboardParams0.insert(pair<KeyMessage, MappedDelegate< InputParams0<KeyMessage> > > (km, md));
	};
	
	void setMappedDelegate(KeyMessage km, MappedDelegate<InputParams1<KeyMessage, string> > md) {
		LOG_VERBOSE("Store p1 string");
		_mappedKeyboardType.insert(pair<KeyMessage, DelegateType> (km, GO_DELEGATE_STRING));
		_mappedKeyboardParamsString1.insert(pair< KeyMessage, MappedDelegate< InputParams1< KeyMessage, string> > > (km, md));
	};
	
	void setMappedDelegate(KeyMessage km, MappedDelegate<InputParams1<KeyMessage, float> > md) {
		LOG_VERBOSE("Store p1 float");
		_mappedKeyboardType.insert(pair<KeyMessage, DelegateType> (km, GO_DELEGATE_FLOAT));
		_mappedKeyboardParamsFloat1.insert(pair< KeyMessage, MappedDelegate<InputParams1<KeyMessage, float> > > (km, md));
	};
	
	void setMappedDelegate(KeyMessage km, MappedDelegate<InputParams1<KeyMessage, int> > md) {
		LOG_VERBOSE("Store p1 int");
		_mappedKeyboardType.insert(pair<KeyMessage, DelegateType> (km, GO_DELEGATE_INT));
		_mappedKeyboardParamsInt1.insert(pair< KeyMessage, MappedDelegate< InputParams1<KeyMessage, int> > > (km, md));
	};
	
	void setMappedDelegate(KeyMessage km, MappedDelegate<InputParams1<KeyMessage, bool> > md) {
		LOG_VERBOSE("Store p1 bool");
		_mappedKeyboardType.insert(pair<KeyMessage, DelegateType> (km, GO_DELEGATE_BOOL));
		_mappedKeyboardParamsBool1.insert(pair< KeyMessage, MappedDelegate<InputParams1<KeyMessage, bool> >	> (km, md));
	};
	
	void setMappedDelegate(KeyMessage km, MappedDelegate<InputParams2<KeyMessage, string, string> > md) {
		LOG_VERBOSE("Store p2 string string");
		_mappedKeyboardType.insert(pair<KeyMessage, DelegateType> (km, GO_DELEGATE_STRING_STRING));
		_mappedKeyboardParamsStringString2.insert(pair< KeyMessage, MappedDelegate< InputParams2< KeyMessage, string, string> > > (km, md));
	};
	
	void setMappedDelegate(KeyMessage km, MappedDelegate<InputParams2<KeyMessage, string, float> > md) {
		LOG_VERBOSE("Store p2 string float");
		_mappedKeyboardType.insert(pair<KeyMessage, DelegateType> (km, GO_DELEGATE_STRING_FLOAT));
		_mappedKeyboardParamsStringFloat2.insert(pair< KeyMessage, MappedDelegate<InputParams2<KeyMessage, string, float> > > (km, md));
	};
	
	void setMappedDelegate(KeyMessage km, MappedDelegate<InputParams2<KeyMessage, string, int> > md) {
		LOG_VERBOSE("Store p2 string int");
		_mappedKeyboardType.insert(pair<KeyMessage, DelegateType> (km, GO_DELEGATE_STRING_INT));
		_mappedKeyboardParamsStringInt2.insert(pair< KeyMessage, MappedDelegate< InputParams2<KeyMessage, string, int> > > (km, md));
	};
	
	void setMappedDelegate(KeyMessage km, MappedDelegate<InputParams2<KeyMessage, string, bool> > md) {
		LOG_VERBOSE("Store p2 string bool");
		_mappedKeyboardType.insert(pair<KeyMessage, DelegateType> (km, GO_DELEGATE_STRING_BOOL));
		_mappedKeyboardParamsStringBool2.insert(pair< KeyMessage, MappedDelegate<InputParams2<KeyMessage, string, bool> >	> (km, md));
	};
	
	void setMappedDelegate(KeyMessage km, MappedDelegate<InputParams2<KeyMessage, float, float> > md) {
		LOG_VERBOSE("Store p2 float float");
		_mappedKeyboardType.insert(pair<KeyMessage, DelegateType> (km, GO_DELEGATE_FLOAT_FLOAT));
		_mappedKeyboardParamsFloatFloat2.insert(pair< KeyMessage, MappedDelegate< InputParams2< KeyMessage, float, float> > > (km, md));
	};
	
	void setMappedDelegate(KeyMessage km, MappedDelegate<InputParams2<KeyMessage, float, string> > md) {
		LOG_VERBOSE("Store p2 float string");
		_mappedKeyboardType.insert(pair<KeyMessage, DelegateType> (km, GO_DELEGATE_FLOAT_STRING));
		_mappedKeyboardParamsFloatString2.insert(pair< KeyMessage, MappedDelegate<InputParams2<KeyMessage, float, string> > > (km, md));
	};
	
	void setMappedDelegate(KeyMessage km, MappedDelegate<InputParams2<KeyMessage, float, int> > md) {
		LOG_VERBOSE("Store p2 float int");
		_mappedKeyboardType.insert(pair<KeyMessage, DelegateType> (km, GO_DELEGATE_FLOAT_INT));
		_mappedKeyboardParamsFloatInt2.insert(pair< KeyMessage, MappedDelegate< InputParams2<KeyMessage, float, int> > > (km, md));
	};
	
	void setMappedDelegate(KeyMessage km, MappedDelegate<InputParams2<KeyMessage, float, bool> > md) {
		LOG_VERBOSE("Store p2 float bool");
		_mappedKeyboardType.insert(pair<KeyMessage, DelegateType> (km, GO_DELEGATE_FLOAT_BOOL));
		_mappedKeyboardParamsFloatBool2.insert(pair< KeyMessage, MappedDelegate<InputParams2<KeyMessage, float, bool> >	> (km, md));
	};
	
	void setMappedDelegate(KeyMessage km, MappedDelegate<InputParams2<KeyMessage, int, int> > md) {
		LOG_VERBOSE("Store p2 int int");
		_mappedKeyboardType.insert(pair<KeyMessage, DelegateType> (km, GO_DELEGATE_INT_INT));
		_mappedKeyboardParamsIntInt2.insert(pair< KeyMessage, MappedDelegate< InputParams2< KeyMessage, int, int> > > (km, md));
	};
	
	void setMappedDelegate(KeyMessage km, MappedDelegate<InputParams2<KeyMessage, int, string> > md) {
		LOG_VERBOSE("Store p2 int string");
		_mappedKeyboardType.insert(pair<KeyMessage, DelegateType> (km, GO_DELEGATE_INT_STRING));
		_mappedKeyboardParamsIntString2.insert(pair< KeyMessage, MappedDelegate<InputParams2<KeyMessage, int, string> > > (km, md));
	};
	
	void setMappedDelegate(KeyMessage km, MappedDelegate<InputParams2<KeyMessage, int, float> > md) {
		LOG_VERBOSE("Store p2 int float");
		_mappedKeyboardType.insert(pair<KeyMessage, DelegateType> (km, GO_DELEGATE_INT_FLOAT));
		_mappedKeyboardParamsIntFloat2.insert(pair< KeyMessage, MappedDelegate< InputParams2<KeyMessage, int, float> > > (km, md));
	};
	
	void setMappedDelegate(KeyMessage km, MappedDelegate<InputParams2<KeyMessage, int, bool> > md) {
		LOG_VERBOSE("Store p2 int bool");
		_mappedKeyboardType.insert(pair<KeyMessage, DelegateType> (km, GO_DELEGATE_INT_BOOL));
		_mappedKeyboardParamsIntBool2.insert(pair< KeyMessage, MappedDelegate<InputParams2<KeyMessage, int, bool> >	> (km, md));
	};
	
	void setMappedDelegate(KeyMessage km, MappedDelegate<InputParams2<KeyMessage, bool, bool> > md) {
		LOG_VERBOSE("Store p2 bool bool");
		_mappedKeyboardType.insert(pair<KeyMessage, DelegateType> (km, GO_DELEGATE_BOOL_BOOL));
		_mappedKeyboardParamsBoolBool2.insert(pair< KeyMessage, MappedDelegate< InputParams2< KeyMessage, bool, bool> > > (km, md));
	};
	
	void setMappedDelegate(KeyMessage km, MappedDelegate<InputParams2<KeyMessage, bool, string> > md) {
		LOG_VERBOSE("Store p2 bool string");
		_mappedKeyboardType.insert(pair<KeyMessage, DelegateType> (km, GO_DELEGATE_BOOL_STRING));
		_mappedKeyboardParamsBoolString2.insert(pair< KeyMessage, MappedDelegate<InputParams2<KeyMessage, bool, string> > > (km, md));
	};
	
	void setMappedDelegate(KeyMessage km, MappedDelegate<InputParams2<KeyMessage, bool, float> > md) {
		LOG_VERBOSE("Store p2 bool float");
		_mappedKeyboardType.insert(pair<KeyMessage, DelegateType> (km, GO_DELEGATE_BOOL_FLOAT));
		_mappedKeyboardParamsBoolFloat2.insert(pair< KeyMessage, MappedDelegate< InputParams2<KeyMessage, bool, float> > > (km, md));
	};
	
	void setMappedDelegate(KeyMessage km, MappedDelegate<InputParams2<KeyMessage, bool, int> > md) {
		LOG_VERBOSE("Store p2 bool int");
		_mappedKeyboardType.insert(pair<KeyMessage, DelegateType> (km, GO_DELEGATE_BOOL_INT));
		_mappedKeyboardParamsBoolInt2.insert(pair< KeyMessage, MappedDelegate<InputParams2<KeyMessage, bool, int> >	> (km, md));
	};
	
};

typedef Singleton<KeyboardModel> KeyboardModelSingleton;					// Global declaration

static KeyboardModel * _keyModel	= KeyboardModelSingleton::Instance();	// this is my idea of a compromise:
// no defines, keeps introspection
// but allows data sharing between classes

#endif