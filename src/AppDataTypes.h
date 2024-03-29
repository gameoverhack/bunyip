/*
 *  AppDataTypes.h
 *  Jungle
 *
 *  Created by gameover on 30/06/11.
 *  Copyright 2011 trace media. All rights reserved.
 *
 */

#ifndef _H_APPDATATYPES
#define _H_APPDATATYPES

#include "ofMain.h"

#include <boost/serialization/serialization.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

// see http://www.codeproject.com/KB/cpp/FastDelegate.aspx
#include "FastDelegate.h"
#include "FastDelegateBind.h"
#include "Logger.h"
#include <map>

using namespace fastdelegate;
using std::map;
using std::pair;

enum key_st {
	kKEY_DOWN,
	kKEY_UP
};

// TODO: Ranges??
enum midi_ct {
	kMIDI_ANY,
	kMIDI_PASS_BYTE_TWO,
	kMIDI_PASS_BYTE_ONE,
	kMIDI_PASS_BYTE_BOTH,
	kMIDI_EQUAL,
	kMIDI_GREATER,
	kMIDI_LESSER,
	kMIDI_EQUAL_GREATER,
	kMIDI_EQUAL_LESSER,
	kMIDI_PASS_BYTE_TWO_INTERNAL_USE,
	kMIDI_PASS_BYTE_ONE_INTERNAL_USE,
	kMIDI_PASS_BYTE_BOTH_INTERNAL_USE
};

enum DelegateType {
	GO_DELEGATE_NONE,
	GO_DELEGATE_STRING,
	GO_DELEGATE_INT,
	GO_DELEGATE_FLOAT,
	GO_DELEGATE_BOOL,
	GO_DELEGATE_STRING_STRING,
	GO_DELEGATE_INT_INT,
	GO_DELEGATE_FLOAT_FLOAT,
	GO_DELEGATE_BOOL_BOOL,
	GO_DELEGATE_STRING_INT,
	GO_DELEGATE_STRING_FLOAT,
	GO_DELEGATE_STRING_BOOL,
	GO_DELEGATE_INT_STRING,
	GO_DELEGATE_INT_FLOAT,
	GO_DELEGATE_INT_BOOL,
	GO_DELEGATE_FLOAT_STRING,
	GO_DELEGATE_FLOAT_INT,
	GO_DELEGATE_FLOAT_BOOL,
	GO_DELEGATE_BOOL_STRING,
	GO_DELEGATE_BOOL_INT,
	GO_DELEGATE_BOOL_FLOAT
};

typedef FastDelegate0<>					Delegate0;
typedef FastDelegate1<string>			DelegateString1;
typedef FastDelegate1<int>				DelegateInt1;
typedef FastDelegate1<float>			DelegateFloat1;
typedef FastDelegate1<bool>				DelegateBool1;
typedef FastDelegate2<string, string>	DelegateStringString2;
typedef FastDelegate2<int, int>			DelegateIntInt2;
typedef FastDelegate2<float, float>		DelegateFloatFloat2;
typedef FastDelegate2<bool, bool>		DelegateBoolBool2;
typedef FastDelegate2<float, string>	DelegateFloatString2;
typedef FastDelegate2<float, int>		DelegateFloatInt2;
typedef FastDelegate2<float, bool>		DelegateFloatBool2;
typedef FastDelegate2<string, int>		DelegateStringInt2;
typedef FastDelegate2<string, float>	DelegateStringFloat2;
typedef FastDelegate2<string, bool>		DelegateStringBool2;
typedef FastDelegate2<int, string>		DelegateIntString2;
typedef FastDelegate2<int, float>		DelegateIntFloat2;
typedef FastDelegate2<int, bool>		DelegateIntBool2;
typedef FastDelegate2<bool, string>		DelegateBoolString2;
typedef FastDelegate2<bool, float>		DelegateBoolFloat2;
typedef FastDelegate2<bool, int>		DelegateBoolInt2;

class MidiMessage {

public:
	
	MidiMessage(int port, int channel, int status, int byteOne, int byteTwo, double timestamp, midi_ct comparisonType = kMIDI_ANY)
	: _port(port), _channel(channel), _status(status), _byteOne(byteOne), _byteTwo(byteTwo), _timestamp(timestamp), _comparisonType(comparisonType) {};
	
	int const		getPort() const {return _port;};
    int	const		getChannel() const {return _channel;};
    int const		getStatus() const {return _status;};
    int const		getByteOne() const {return _byteOne;};
    int const		getByteTwo() const {return _byteTwo;};
    double const	getTimestamp() const {return _timestamp;};
	midi_ct const	getComparisonType() const {return _comparisonType;};
	
	string	print(bool log = false) {
		
		ostringstream out;
		out	<< "port: " << getPort() 
			<< " channel: " << getChannel() 
			<< " status: " << getStatus() 
			<< " byteOne: " << getByteOne() 
			<< " byteTwo: " << getByteTwo() 
			<< " timestamp: " << getTimestamp()
			<< " comparison: " << getComparisonType();
		
		if (log) LOG_VERBOSE("MIDI: " + out.str());
		
		return out.str();
		
	};
	
	// NB: only checking byteOne and status -> upto program to evaluate byteTwo!!!
	bool operator== ( const MidiMessage& rhs ) const {return (getStatus() == rhs.getStatus() && getByteOne() == rhs.getByteOne());};
	bool operator!= ( const MidiMessage& rhs ) const {return (getStatus() != rhs.getStatus() || getByteOne() != rhs.getByteOne());};
	bool operator<  ( const MidiMessage& rhs ) const {return (getStatus() < rhs.getStatus() || (!(getStatus() < rhs.getStatus()) && getByteOne() < rhs.getByteOne()));};
	bool operator>  ( const MidiMessage& rhs ) const {return (getStatus() > rhs.getStatus() || (!(getStatus() > rhs.getStatus()) && getByteOne() > rhs.getByteOne()));};
	bool operator<=  ( const MidiMessage& rhs ) const {return (getStatus() <= rhs.getStatus() && getByteOne() <= rhs.getByteOne());};
	bool operator>=  ( const MidiMessage& rhs ) const {return (getStatus() >= rhs.getStatus() && getByteOne() >= rhs.getByteOne());};
	
private:
	
    const int		_port;
    const int		_channel;
    const int		_status;
    const int		_byteOne;
    const int		_byteTwo;
    const double 	_timestamp;
	const midi_ct	_comparisonType;

};

class KeyMessage {
	
public:
	
	KeyMessage(const int key, const key_st status, const double timestamp)
	: _key(key), _status(status), _timestamp(timestamp) {};
	
	int const		getKey() const {return _key;};
    key_st const	getStatus() const {return _status;};
	double const 	getTimestamp() const {return _timestamp;};
	
	string const	print(bool log = false) const {
		
		ostringstream out;
		out	<< "key: " << getKey() 
		<< " status: " << getStatus()
		<< " timestamp: " << getTimestamp();
		if (log) LOG_VERBOSE("MIDI: " + out.str());
		
		return out.str();
		
	};
	
	bool operator== ( const KeyMessage& rhs ) const {return (getKey() == rhs.getKey() && getStatus() == rhs.getStatus());};
	bool operator!= ( const KeyMessage& rhs ) const {return (getKey() != rhs.getKey() || getStatus() != rhs.getStatus());};
	bool operator<  ( const KeyMessage& rhs ) const {return (getKey() < rhs.getKey() || (!(getKey() < rhs.getKey()) && getStatus() < rhs.getStatus()));};
	bool operator>  ( const KeyMessage& rhs ) const {return (getKey() > rhs.getKey() || (!(getKey() > rhs.getKey()) && getStatus() > rhs.getStatus()));};
	bool operator<=  ( const KeyMessage& rhs ) const {return (getKey() <= rhs.getKey() && getStatus() <= rhs.getStatus());};
	bool operator>=  ( const KeyMessage& rhs ) const {return (getKey() >= rhs.getKey() && getStatus() >= rhs.getStatus());};
	
private:
	
    const int		_key;
	const key_st	_status;
	const double 	_timestamp;
	
};

/*class MidiCompare {
public:
	bool operator() (const MidiMessage& lhs, const MidiMessage& rhs) const
	{return (lhs.getByteOne()!=rhs.getByteOne() || lhs.getChannel()!=rhs.getChannel());}
};

class KeyCompare {
public:
	bool operator() (const KeyMessage& lhs, const KeyMessage& rhs) const
	{return (lhs.getKey()!=rhs.getKey() || lhs.getStatus()!=rhs.getStatus());}
};*/

template <class MessageType>
class InputParams0 {
	
public:
	
	//InputParams0() : _type("InputParams0"), _numParams(0) {};
	InputParams0(MessageType key) : _key(key), _type("InputParams0"), _numParams(0) {};

	string		getType() {return _type;};
	int			getNumParams() {return _numParams;};
	
	//void		setMessageMap(MessageType key) {_key = key;};
	MessageType	getMessageMap() {return _key;};
	
	//void		setParam1(int &param1) {_param1 = NULL;};	// dummy (should never be called)
	int			getParam1() {return *_param1;};				// dummy (should never be called)
	
	//void		setParam2(int &param2) {_param2 = NULL;};	// dummy (should never be called)
	int			getParam2() {return *_param2;};				// dummy (should never be called)
	
private:
	
	string		_type;
	int			_numParams;
	
	MessageType	_key;
	
	int*		_param1; // dummy
	int*		_param2; // dummy
	
};

template <class MessageType, typename Param1>
class InputParams1 {

public:
	
	//InputParams1() : _type("InputParams1"), _numParams(1) {};
	InputParams1(MessageType key, Param1 &param1, bool parameter1IsPointer) : _key(key), _param1pnt(&param1), _type("InputParams1"), _numParams(1), _parameter1IsPointer(true) {};
	InputParams1(MessageType key, Param1 param1) : _key(key), _param1abs(param1), _type("InputParams1"), _numParams(1), _parameter1IsPointer(false) {};
	
	string		getType() {return _type;};
	int			getNumParams() {return _numParams;};
	
	//void		setMessageMap(MessageType key) {_key = key;};
	MessageType	getMessageMap() {return _key;};
	
	//void		setParam1(Param1 &param1) {_param1 = &param1;};
	Param1		getParam1() {if(_parameter1IsPointer) return *_param1pnt; else return _param1abs;};
	
	//void		setParam2(int &param2) {_param2pnt = NULL;};	// dummy (should never be called)
	int			getParam2() {return *_param2pnt;};				// dummy (should never be called)
	
private:
	
	string		_type;
	int			_numParams;
	
	MessageType	_key;
	
	bool		_parameter1IsPointer;
	
	Param1		_param1abs;
	int			_param2abs; // dummy
	Param1*		_param1pnt;
	int*		_param2pnt; // dummy
	
};

template <class MessageType, class Param1, class Param2>
class InputParams2 {
	
public:
	
	InputParams2(MessageType key, Param1 param1, Param2 param2) 
	: _key(key), _param1abs(param1), _param2abs(param2), _type("InputParams2"), _numParams(2), _parameter1IsPointer(false), _parameter2IsPointer(false) {};
	InputParams2(MessageType key, Param1 & param1, Param2 param2, bool parameter1IsPointer) 
	: _key(key), _param1pnt(&param1), _param2abs(param2), _type("InputParams2"), _numParams(2), _parameter1IsPointer(true), _parameter2IsPointer(false) {};
	InputParams2(MessageType key, Param1 & param1, Param2 & param2, bool parameter1IsPointer, bool parameter2IsPointer) 
	: _key(key), _param1pnt(&param1), _param2pnt(&param2), _type("InputParams2"), _numParams(2), _parameter1IsPointer(true), _parameter2IsPointer(true) {};

	string		getType() {return _type;};
	int			getNumParams() {return _numParams;};
	
	//void		setMessageMap(MessageType key) {_key = key;};
	MessageType	getMessageMap() {return _key;};
	
	//void		setParam1(Param1 &param1) {_param1 = &param1;};
	Param1		getParam1() {if(_parameter1IsPointer) return *_param1pnt; else return _param1abs;};
	
	//void		setParam2(Param2 &param2) {_param2 = &param2;};
	Param2		getParam2() {if(_parameter2IsPointer) return *_param2pnt; else return _param2abs;};
	
private:
	
	string		_type;
	int			_numParams;
	
	MessageType	_key;
	
	bool		_parameter1IsPointer;
	bool		_parameter2IsPointer;
	
	Param1*		_param1pnt;
	Param2*		_param2pnt;
	Param1		_param1abs;
	Param2		_param2abs;
	
};

template <class InputParams>
class MappedDelegate {
	
public:
	
	//MappedDelegate() : _uniqueFunctionID("") {};
	
	MappedDelegate(string uniqueFunctionID, DelegateMemento delegateMemento, InputParams inputParams) 
	: _uniqueFunctionID(uniqueFunctionID), _delegateMemento(delegateMemento), _inputParams(inputParams) {};
	
	string			getUniqueFunctionID() {return _uniqueFunctionID;};
	InputParams		getInputParams() {return _inputParams;};
	DelegateMemento	getDelegateMemento() {return _delegateMemento;};
	
private:
	
	string				_uniqueFunctionID;
	InputParams			_inputParams;
	DelegateMemento		_delegateMemento;

	
	
};


/*
template <class DelegateType>
class MappedDelegate {
	
public:
	
	MappedDelegate(DelegateType delegate) : _delegate(delegate){};
	
	/*MappedDelegate(CallbackClass * callbackClass, void (CallbackClass::*callbackMethod)()) {
		_delegate.bind(callbackClass, callbackMethod);
	};
	
	MappedDelegate(CallbackClass * callbackClass, void (CallbackClass::*callbackMethod)(Param1)) {
		_delegate.bind(callbackClass, callbackMethod);
	};
	
	MappedDelegate(CallbackClass * callbackClass, void (CallbackClass::*callbackMethod)(Param1, Param2)) {
		_delegate.bind(callbackClass, callbackMethod);
	};
	
	DelegateMemento getDelegateMem() {return _delegate.GetMemento();};
	
	DelegateType getDelegate() {return _delegate;};  
	
private:
	
	DelegateType			_delegate;
	
};
*/

#endif
