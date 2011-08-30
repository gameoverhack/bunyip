/*
 *  MidiModel.h
 *  Bunyip
 *
 *  Created by gameover on 30/08/11.
 *  Copyright 2011 trace media. All rights reserved.
 *
 */

/*
 *  MidiModel.h
 *  Bunyip
 *
 *  Created by gameover on 24/08/11.
 *  Copyright 2011 trace media. All rights reserved.
 *
 */

#ifndef _H_MIDIMODEL
#define _H_MIDIMODEL

#include "AppModel.h"

class MidiModel {
	
public:
	
	MidiModel() {
		LOG_NOTICE("Constructing MidiModel");
	};
	
	~MidiModel() {
		LOG_NOTICE("Destructing MidiModel");
	};	
	
	
	void registerEvent(int channel, int status, int byteOne, int byteTwo, midi_ct comparisonType, string helpMessage, string functionToCall) {
		
		if (comparisonType == kMIDI_PASS_BYTE_ONE) {
			registerEvent(channel, status, byteOne, byteTwo, kMIDI_PASS_BYTE_ONE_INTERNAL_USE, helpMessage, functionToCall, -1);
			return;
		} else if (comparisonType == kMIDI_PASS_BYTE_TWO) {
			registerEvent(channel, status, byteOne, byteTwo, kMIDI_PASS_BYTE_TWO_INTERNAL_USE, helpMessage, functionToCall, -1);
			return;
		} else if (comparisonType == kMIDI_PASS_BYTE_BOTH) {
			registerEvent(channel, status, byteOne, byteTwo, kMIDI_PASS_BYTE_BOTH_INTERNAL_USE, helpMessage, functionToCall, -1, -1);
			return;
		}
		
		MidiMessage midiMessage(0, channel, status, byteOne, byteTwo, 0, comparisonType); 
		InputParams0<MidiMessage> inputParams(midiMessage);
		registerInputToFunction(functionToCall, inputParams, helpMessage);
	}
	
	template<class Param1>
	void registerEvent(int channel, int status, int byteOne, int byteTwo, midi_ct comparisonType, string helpMessage, string functionToCall, Param1 param1) {
		
		if (comparisonType == kMIDI_PASS_BYTE_ONE) {
			registerEvent(channel, status, byteOne, byteTwo, kMIDI_PASS_BYTE_ONE_INTERNAL_USE, helpMessage, functionToCall, param1, -1);
			return;
		} else if (comparisonType == kMIDI_PASS_BYTE_TWO) {
			registerEvent(channel, status, byteOne, byteTwo, kMIDI_PASS_BYTE_TWO_INTERNAL_USE, helpMessage, functionToCall, param1, -1);
			return;
		} else if (comparisonType == kMIDI_PASS_BYTE_BOTH) {
			LOG_ERROR("Maximum of two parameters, so can't pass both param1, byteOne AND bytTwo as well!!");
			abort();
		} else if (comparisonType == kMIDI_PASS_BYTE_ONE_INTERNAL_USE) {
			comparisonType = kMIDI_PASS_BYTE_ONE;
		} else if (comparisonType == kMIDI_PASS_BYTE_TWO_INTERNAL_USE) {
			comparisonType = kMIDI_PASS_BYTE_TWO;
		}
		
		MidiMessage midiMessage(0, channel, status, byteOne, byteTwo, 0, comparisonType); 
		InputParams1<MidiMessage, Param1> inputParams(midiMessage, param1);
		registerInputToFunction(functionToCall, inputParams, helpMessage);
	}
	
	template<class Param1>
	void registerEvent(int channel, int status, int byteOne, int byteTwo, midi_ct comparisonType, string helpMessage, string functionToCall, Param1 &param1, bool variableIsPointer) {
		
		if (comparisonType == kMIDI_PASS_BYTE_ONE) {
			registerEvent(channel, status, byteOne, byteTwo, kMIDI_PASS_BYTE_ONE_INTERNAL_USE, helpMessage, functionToCall, &param1, -1);
			return;
		} else if (comparisonType == kMIDI_PASS_BYTE_TWO) {
			registerEvent(channel, status, byteOne, byteTwo, kMIDI_PASS_BYTE_TWO_INTERNAL_USE, helpMessage, functionToCall, &param1, -1);
			return;
		} else if (comparisonType == kMIDI_PASS_BYTE_BOTH) {
			LOG_ERROR("Maximum of two parameters, so can't pass both param1, byteOne AND bytTwo as well!!");
			abort();
		} else if (comparisonType == kMIDI_PASS_BYTE_ONE_INTERNAL_USE) {
			comparisonType = kMIDI_PASS_BYTE_ONE;
		} else if (comparisonType == kMIDI_PASS_BYTE_TWO_INTERNAL_USE) {
			comparisonType = kMIDI_PASS_BYTE_TWO;
		}
		
		MidiMessage midiMessage(0, channel, status, byteOne, byteTwo, 0, comparisonType); 
		InputParams1<MidiMessage, Param1> inputParams(midiMessage, &param1);
		registerInputToFunction(functionToCall, inputParams, helpMessage);
	}
	
	template<class Param1, class Param2>
	void registerEvent(int channel, int status, int byteOne, int byteTwo, midi_ct comparisonType, string helpMessage, string functionToCall, Param1 param1, Param2 param2) {
		
		if (comparisonType == kMIDI_PASS_BYTE_ONE || comparisonType == kMIDI_PASS_BYTE_TWO || comparisonType == kMIDI_PASS_BYTE_BOTH) {
			LOG_ERROR("Maximum of two parameters, so can't pass the midi values as well as two params!!");
			abort();
		} else if (comparisonType == kMIDI_PASS_BYTE_ONE_INTERNAL_USE) {
			comparisonType = kMIDI_PASS_BYTE_ONE;
		} else if (comparisonType == kMIDI_PASS_BYTE_TWO_INTERNAL_USE) {
			comparisonType = kMIDI_PASS_BYTE_TWO;
		} else if (comparisonType == kMIDI_PASS_BYTE_BOTH_INTERNAL_USE) {
			comparisonType = kMIDI_PASS_BYTE_BOTH;
		}
		
		MidiMessage midiMessage(0, channel, status, byteOne, byteTwo, 0, comparisonType); 
		InputParams2<MidiMessage, Param1, Param2> inputParams(midiMessage, param1, param2);
		registerInputToFunction(functionToCall, inputParams, helpMessage);
	}
	
	template<class Param1, class Param2>
	void registerEvent(int channel, int status, int byteOne, int byteTwo, midi_ct comparisonType, string helpMessage, string functionToCall, Param1 &param1, Param2 param2, bool parameter1IsPointer) {
		
		if (comparisonType == kMIDI_PASS_BYTE_ONE || comparisonType == kMIDI_PASS_BYTE_TWO || comparisonType == kMIDI_PASS_BYTE_BOTH) {
			LOG_ERROR("Maximum of two parameters, so can't pass the midi values as well as two params!!");
			abort();
		} else if (comparisonType == kMIDI_PASS_BYTE_ONE_INTERNAL_USE) {
			comparisonType = kMIDI_PASS_BYTE_ONE;
		} else if (comparisonType == kMIDI_PASS_BYTE_TWO_INTERNAL_USE) {
			comparisonType = kMIDI_PASS_BYTE_TWO;
		} else if (comparisonType == kMIDI_PASS_BYTE_BOTH_INTERNAL_USE) {
			comparisonType = kMIDI_PASS_BYTE_BOTH;
		}
		
		MidiMessage midiMessage(0, channel, status, byteOne, byteTwo, 0, comparisonType); 
		InputParams2<MidiMessage, Param1, Param2> inputParams(midiMessage, &param1, param2);
		registerInputToFunction(functionToCall, inputParams, helpMessage);
	}
	
	template<class Param1, class Param2>
	void registerEvent(int channel, int status, int byteOne, int byteTwo, midi_ct comparisonType, string helpMessage, string functionToCall, Param1 &param1, Param2 &param2, bool parameter1IsPointer, bool parameter2IsPointer) {
		
		if (comparisonType == kMIDI_PASS_BYTE_ONE || comparisonType == kMIDI_PASS_BYTE_TWO || comparisonType == kMIDI_PASS_BYTE_BOTH) {
			LOG_ERROR("Maximum of two parameters, so can't pass the midi values as well as two params!!");
			abort();
		} else if (comparisonType == kMIDI_PASS_BYTE_ONE_INTERNAL_USE) {
			comparisonType = kMIDI_PASS_BYTE_ONE;
		} else if (comparisonType == kMIDI_PASS_BYTE_TWO_INTERNAL_USE) {
			comparisonType = kMIDI_PASS_BYTE_TWO;
		} else if (comparisonType == kMIDI_PASS_BYTE_BOTH_INTERNAL_USE) {
			comparisonType = kMIDI_PASS_BYTE_BOTH;
		}
		
		MidiMessage midiMessage(0, channel, status, byteOne, byteTwo, 0, comparisonType); 
		InputParams2<MidiMessage, Param1, Param2> inputParams(midiMessage, &param1, &param2);
		registerInputToFunction(functionToCall, inputParams, helpMessage);
	}
	
	template <class InputParams>
	void registerInputToFunction(string uniqueFunctionID, InputParams inputParameters, string usage = "") {
		
		map<string, DelegateMemento>::iterator it = _appModel->_registeredFunctions.find(uniqueFunctionID);
		
		if (it != _appModel->_registeredFunctions.end()) {
			
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
		for (int i = 0; i < _midiUsage.size(); i++) {
			out << _midiUsage[i] << endl;
		}
		
		if (log) {
			LOG_NOTICE(out.str());
		}
		
		return out.str();
		
	};
	
	void executeFunction(MidiMessage midiMessage) {
		
		midiMessage.print(true);
		
		map<MidiMessage, DelegateType>::iterator it_type;
		
		it_type = _mappedMidiType.find(midiMessage);
		
		bool comparisonMatched = false;
		MidiMessage originalMidiMessage = it_type->first;
		midi_ct comparisonType = originalMidiMessage.getComparisonType();
		
		if (it_type != _mappedMidiType.end()) {
			switch (comparisonType) {
				case kMIDI_ANY:
					comparisonMatched = true;
					break;
				case kMIDI_PASS_BYTE_ONE:
				case kMIDI_PASS_BYTE_TWO:
				case kMIDI_PASS_BYTE_BOTH:
					comparisonMatched = true;
					break;
				case kMIDI_EQUAL:
					if (originalMidiMessage.getByteTwo() == midiMessage.getByteTwo()) comparisonMatched = true;
					break;
				case kMIDI_GREATER:
					if (originalMidiMessage.getByteTwo() > midiMessage.getByteTwo()) comparisonMatched = true;
					break;
				case kMIDI_LESSER:
					if (originalMidiMessage.getByteTwo() < midiMessage.getByteTwo()) comparisonMatched = true;
					break;
				case kMIDI_EQUAL_GREATER:
					if (originalMidiMessage.getByteTwo() >= midiMessage.getByteTwo()) comparisonMatched = true;
					break;
				case kMIDI_EQUAL_LESSER:
					if (originalMidiMessage.getByteTwo() <= midiMessage.getByteTwo()) comparisonMatched = true;
					break;
				// TODO: Ranges!!
			}			
		}
				
		if (comparisonMatched) {
			
			DelegateType dt = it_type->second;
			
			switch (dt) {
				case GO_DELEGATE_NONE:
				{
					map<MidiMessage, MappedDelegate<InputParams0<MidiMessage>			> >	 ::iterator	it0;
					it0  = _mappedMidiParams0.find(midiMessage);
					DelegateMemento dm = it0->second.getDelegateMemento();
					Delegate0 funcToExec;
					funcToExec.SetMemento(dm);
					funcToExec();
					break;
				}
				case GO_DELEGATE_STRING:
				{
					map<MidiMessage, MappedDelegate<InputParams1<MidiMessage, string	> > >::iterator	it1s;
					it1s = _mappedMidiParamsString1.find(midiMessage);
					DelegateMemento dm = it1s->second.getDelegateMemento();
					DelegateString1 funcToExec;
					funcToExec.SetMemento(dm);
					funcToExec(it1s->second.getInputParams().getParam1());
					break;
				}
				case GO_DELEGATE_INT:
				{
					map<MidiMessage, MappedDelegate<InputParams1<MidiMessage, int		> > >::iterator	it1i;
					it1i = _mappedMidiParamsInt1.find(midiMessage);
					DelegateMemento dm = it1i->second.getDelegateMemento();
					DelegateInt1 funcToExec;
					funcToExec.SetMemento(dm);
					if (comparisonType == kMIDI_PASS_BYTE_ONE) {
						funcToExec(originalMidiMessage.getByteOne());
					} else if (comparisonType == kMIDI_PASS_BYTE_TWO) {
						funcToExec(originalMidiMessage.getByteTwo());
					} else funcToExec(it1i->second.getInputParams().getParam1());
					break;
				}
				case GO_DELEGATE_FLOAT:
				{
					map<MidiMessage, MappedDelegate<InputParams1<MidiMessage, float	> > >::iterator	it1f;
					it1f = _mappedMidiParamsFloat1.find(midiMessage);
					DelegateMemento dm = it1f->second.getDelegateMemento();
					DelegateFloat1 funcToExec;
					funcToExec.SetMemento(dm);
					funcToExec(it1f->second.getInputParams().getParam1());
					break;
				}
				case GO_DELEGATE_BOOL:
				{
					map<MidiMessage, MappedDelegate<InputParams1<MidiMessage, bool	> > >::iterator	it1b;
					it1b = _mappedMidiParamsBool1.find(midiMessage);
					DelegateMemento dm = it1b->second.getDelegateMemento();
					DelegateBool1 funcToExec;
					funcToExec.SetMemento(dm);
					funcToExec(it1b->second.getInputParams().getParam1());
					break;
				}
				case GO_DELEGATE_STRING_STRING:
				{
					map<MidiMessage, MappedDelegate<InputParams2<MidiMessage, string, string > > >::iterator	it2ss;
					it2ss = _mappedMidiParamsStringString2.find(midiMessage);
					DelegateMemento dm = it2ss->second.getDelegateMemento();
					DelegateStringString2 funcToExec;
					funcToExec.SetMemento(dm);
					funcToExec(it2ss->second.getInputParams().getParam1(), it2ss->second.getInputParams().getParam2());
					break;
				}
				case GO_DELEGATE_INT_INT:
				{
					map<MidiMessage, MappedDelegate<InputParams2<MidiMessage, int, int > > >::iterator	it2ii;
					it2ii = _mappedMidiParamsIntInt2.find(midiMessage);
					DelegateMemento dm = it2ii->second.getDelegateMemento();
					DelegateIntInt2 funcToExec;
					funcToExec.SetMemento(dm);
					if (comparisonType == kMIDI_PASS_BYTE_ONE) {
						funcToExec(it2ii->second.getInputParams().getParam1(), originalMidiMessage.getByteOne());
					} else if (comparisonType == kMIDI_PASS_BYTE_TWO) {
						funcToExec(it2ii->second.getInputParams().getParam1(), originalMidiMessage.getByteTwo());
					} else if (comparisonType == kMIDI_PASS_BYTE_BOTH) {
						funcToExec(originalMidiMessage.getByteOne(), originalMidiMessage.getByteTwo());
					} else funcToExec(it2ii->second.getInputParams().getParam1(), it2ii->second.getInputParams().getParam2());
					break;
				}
				case GO_DELEGATE_FLOAT_FLOAT:
				{
					map<MidiMessage, MappedDelegate<InputParams2<MidiMessage, float, float > > >::iterator	it2ff;
					it2ff = _mappedMidiParamsFloatFloat2.find(midiMessage);
					DelegateMemento dm = it2ff->second.getDelegateMemento();
					DelegateFloatFloat2 funcToExec;
					funcToExec.SetMemento(dm);
					funcToExec(it2ff->second.getInputParams().getParam1(), it2ff->second.getInputParams().getParam2());
					break;
				}
				case GO_DELEGATE_BOOL_BOOL:
				{
					map<MidiMessage, MappedDelegate<InputParams2<MidiMessage, bool, bool > > >::iterator	it2bb;
					it2bb = _mappedMidiParamsBoolBool2.find(midiMessage);
					DelegateMemento dm = it2bb->second.getDelegateMemento();
					DelegateBoolBool2 funcToExec;
					funcToExec.SetMemento(dm);
					funcToExec(it2bb->second.getInputParams().getParam1(), it2bb->second.getInputParams().getParam2());
					break;
				}
				case GO_DELEGATE_STRING_INT:
				{
					map<MidiMessage, MappedDelegate<InputParams2<MidiMessage, string, int > > >::iterator	it2si;
					it2si = _mappedMidiParamsStringInt2.find(midiMessage);
					DelegateMemento dm = it2si->second.getDelegateMemento();
					DelegateStringInt2 funcToExec;
					funcToExec.SetMemento(dm);
					if (comparisonType == kMIDI_PASS_BYTE_ONE) {
						funcToExec(it2si->second.getInputParams().getParam1(), originalMidiMessage.getByteOne());
					} else if (comparisonType == kMIDI_PASS_BYTE_TWO) {
						funcToExec(it2si->second.getInputParams().getParam1(), originalMidiMessage.getByteTwo());
					} else funcToExec(it2si->second.getInputParams().getParam1(), it2si->second.getInputParams().getParam2());
					break;
				}
				case GO_DELEGATE_STRING_FLOAT:
				{
					map<MidiMessage, MappedDelegate<InputParams2<MidiMessage, string, float > > >::iterator	it2sf;
					it2sf = _mappedMidiParamsStringFloat2.find(midiMessage);
					DelegateMemento dm = it2sf->second.getDelegateMemento();
					DelegateStringFloat2 funcToExec;
					funcToExec.SetMemento(dm);
					funcToExec(it2sf->second.getInputParams().getParam1(), it2sf->second.getInputParams().getParam2());
					break;
				}
				case GO_DELEGATE_STRING_BOOL:
				{
					map<MidiMessage, MappedDelegate<InputParams2<MidiMessage, string, bool > > >::iterator	it2sb;
					it2sb = _mappedMidiParamsStringBool2.find(midiMessage);
					DelegateMemento dm = it2sb->second.getDelegateMemento();
					DelegateStringBool2 funcToExec;
					funcToExec.SetMemento(dm);
					funcToExec(it2sb->second.getInputParams().getParam1(), it2sb->second.getInputParams().getParam2());
					break;
				}
				case GO_DELEGATE_INT_STRING:
				{
					map<MidiMessage, MappedDelegate<InputParams2<MidiMessage, int, string > > >::iterator	it2is;
					it2is = _mappedMidiParamsIntString2.find(midiMessage);
					DelegateMemento dm = it2is->second.getDelegateMemento();
					DelegateIntString2 funcToExec;
					funcToExec.SetMemento(dm);
					funcToExec(it2is->second.getInputParams().getParam1(), it2is->second.getInputParams().getParam2());
					break;
				}
				case GO_DELEGATE_INT_FLOAT:
				{
					map<MidiMessage, MappedDelegate<InputParams2<MidiMessage, int, float > > >::iterator	it2if;
					it2if = _mappedMidiParamsIntFloat2.find(midiMessage);
					DelegateMemento dm = it2if->second.getDelegateMemento();
					DelegateIntFloat2 funcToExec;
					funcToExec.SetMemento(dm);
					funcToExec(it2if->second.getInputParams().getParam1(), it2if->second.getInputParams().getParam2());
					break;
				}
				case GO_DELEGATE_INT_BOOL:
				{
					map<MidiMessage, MappedDelegate<InputParams2<MidiMessage, int, bool > > >::iterator	it2ib;
					it2ib = _mappedMidiParamsIntBool2.find(midiMessage);
					DelegateMemento dm = it2ib->second.getDelegateMemento();
					DelegateIntBool2 funcToExec;
					funcToExec.SetMemento(dm);
					funcToExec(it2ib->second.getInputParams().getParam1(), it2ib->second.getInputParams().getParam2());
					break;
				}
				case GO_DELEGATE_FLOAT_STRING:
				{
					map<MidiMessage, MappedDelegate<InputParams2<MidiMessage, float, string > > >::iterator	it2fs;
					it2fs = _mappedMidiParamsFloatString2.find(midiMessage);
					DelegateMemento dm = it2fs->second.getDelegateMemento();
					DelegateFloatString2 funcToExec;
					funcToExec.SetMemento(dm);
					funcToExec(it2fs->second.getInputParams().getParam1(), it2fs->second.getInputParams().getParam2());
					break;
				}
				case GO_DELEGATE_FLOAT_INT:
				{
					map<MidiMessage, MappedDelegate<InputParams2<MidiMessage, float, int > > >::iterator	it2fi;
					it2fi = _mappedMidiParamsFloatInt2.find(midiMessage);
					DelegateMemento dm = it2fi->second.getDelegateMemento();
					DelegateFloatInt2 funcToExec;
					funcToExec.SetMemento(dm);
					if (comparisonType == kMIDI_PASS_BYTE_ONE) {
						funcToExec(it2fi->second.getInputParams().getParam1(), originalMidiMessage.getByteOne());
					} else if (comparisonType == kMIDI_PASS_BYTE_TWO) {
						funcToExec(it2fi->second.getInputParams().getParam1(), originalMidiMessage.getByteTwo());
					} else funcToExec(it2fi->second.getInputParams().getParam1(), it2fi->second.getInputParams().getParam2());
					break;
				}
				case GO_DELEGATE_FLOAT_BOOL:
				{
					map<MidiMessage, MappedDelegate<InputParams2<MidiMessage, float, bool > > >::iterator	it2fb;
					it2fb = _mappedMidiParamsFloatBool2.find(midiMessage);
					DelegateMemento dm = it2fb->second.getDelegateMemento();
					DelegateFloatBool2 funcToExec;
					funcToExec.SetMemento(dm);
					funcToExec(it2fb->second.getInputParams().getParam1(), it2fb->second.getInputParams().getParam2());
					break;
				}
				case GO_DELEGATE_BOOL_STRING:
				{
					map<MidiMessage, MappedDelegate<InputParams2<MidiMessage, bool, string > > >::iterator	it2bs;
					it2bs = _mappedMidiParamsBoolString2.find(midiMessage);
					DelegateMemento dm = it2bs->second.getDelegateMemento();
					DelegateBoolString2 funcToExec;
					funcToExec.SetMemento(dm);
					funcToExec(it2bs->second.getInputParams().getParam1(), it2bs->second.getInputParams().getParam2());
					break;
				}
				case GO_DELEGATE_BOOL_INT:
				{
					map<MidiMessage, MappedDelegate<InputParams2<MidiMessage, bool, int > > >::iterator	it2bi;
					it2bi = _mappedMidiParamsBoolInt2.find(midiMessage);
					DelegateMemento dm = it2bi->second.getDelegateMemento();
					DelegateBoolInt2 funcToExec;
					funcToExec.SetMemento(dm);
					if (comparisonType == kMIDI_PASS_BYTE_ONE) {
						funcToExec(it2bi->second.getInputParams().getParam1(), originalMidiMessage.getByteOne());
					} else if (comparisonType == kMIDI_PASS_BYTE_TWO) {
						funcToExec(it2bi->second.getInputParams().getParam1(), originalMidiMessage.getByteTwo());
					} else funcToExec(it2bi->second.getInputParams().getParam1(), it2bi->second.getInputParams().getParam2());
					break;
				}
				case GO_DELEGATE_BOOL_FLOAT:
				{
					map<MidiMessage, MappedDelegate<InputParams2<MidiMessage, bool, float > > >::iterator	it2bf;
					it2bf = _mappedMidiParamsBoolFloat2.find(midiMessage);
					DelegateMemento dm = it2bf->second.getDelegateMemento();
					DelegateBoolFloat2 funcToExec;
					funcToExec.SetMemento(dm);
					funcToExec(it2bf->second.getInputParams().getParam1(), it2bf->second.getInputParams().getParam2());
					break;
				}
			}
		}
		
	}
	
private:
	
	void storeUsage(MidiMessage midiMessage, string usage) {
		
		char c = (char)midiMessage.getByteOne();
		ostringstream usestream;
		
		usestream << "'" << c << "'" << " - " << usage;
		
		usage = usestream.str();
		
		LOG_VERBOSE("Created midi usage: " + usage);
		
		_midiUsage.push_back(usage);
	}
	
	void setMappedDelegate(MidiMessage midiMessage, MappedDelegate<InputParams0<MidiMessage> > md) {
		LOG_VERBOSE("Store p0");
		_mappedMidiType.insert(pair<MidiMessage, DelegateType> (midiMessage, GO_DELEGATE_NONE));
		_mappedMidiParams0.insert(pair<MidiMessage, MappedDelegate< InputParams0<MidiMessage> > > (midiMessage, md));
	};
	
	void setMappedDelegate(MidiMessage midiMessage, MappedDelegate<InputParams1<MidiMessage, string> > md) {
		LOG_VERBOSE("Store p1 string");
		_mappedMidiType.insert(pair<MidiMessage, DelegateType> (midiMessage, GO_DELEGATE_STRING));
		_mappedMidiParamsString1.insert(pair< MidiMessage, MappedDelegate< InputParams1< MidiMessage, string> > > (midiMessage, md));
	};
	
	void setMappedDelegate(MidiMessage midiMessage, MappedDelegate<InputParams1<MidiMessage, float> > md) {
		LOG_VERBOSE("Store p1 float");
		_mappedMidiType.insert(pair<MidiMessage, DelegateType> (midiMessage, GO_DELEGATE_FLOAT));
		_mappedMidiParamsFloat1.insert(pair< MidiMessage, MappedDelegate<InputParams1<MidiMessage, float> > > (midiMessage, md));
	};
	
	void setMappedDelegate(MidiMessage midiMessage, MappedDelegate<InputParams1<MidiMessage, int> > md) {
		LOG_VERBOSE("Store p1 int");
		_mappedMidiType.insert(pair<MidiMessage, DelegateType> (midiMessage, GO_DELEGATE_INT));
		_mappedMidiParamsInt1.insert(pair< MidiMessage, MappedDelegate< InputParams1<MidiMessage, int> > > (midiMessage, md));
	};
	
	void setMappedDelegate(MidiMessage midiMessage, MappedDelegate<InputParams1<MidiMessage, bool> > md) {
		LOG_VERBOSE("Store p1 bool");
		_mappedMidiType.insert(pair<MidiMessage, DelegateType> (midiMessage, GO_DELEGATE_BOOL));
		_mappedMidiParamsBool1.insert(pair< MidiMessage, MappedDelegate<InputParams1<MidiMessage, bool> >	> (midiMessage, md));
	};
	
	void setMappedDelegate(MidiMessage midiMessage, MappedDelegate<InputParams2<MidiMessage, string, string> > md) {
		LOG_VERBOSE("Store p2 string string");
		_mappedMidiType.insert(pair<MidiMessage, DelegateType> (midiMessage, GO_DELEGATE_STRING_STRING));
		_mappedMidiParamsStringString2.insert(pair< MidiMessage, MappedDelegate< InputParams2< MidiMessage, string, string> > > (midiMessage, md));
	};
	
	void setMappedDelegate(MidiMessage midiMessage, MappedDelegate<InputParams2<MidiMessage, string, float> > md) {
		LOG_VERBOSE("Store p2 string float");
		_mappedMidiType.insert(pair<MidiMessage, DelegateType> (midiMessage, GO_DELEGATE_STRING_FLOAT));
		_mappedMidiParamsStringFloat2.insert(pair< MidiMessage, MappedDelegate<InputParams2<MidiMessage, string, float> > > (midiMessage, md));
	};
	
	void setMappedDelegate(MidiMessage midiMessage, MappedDelegate<InputParams2<MidiMessage, string, int> > md) {
		LOG_VERBOSE("Store p2 string int");
		_mappedMidiType.insert(pair<MidiMessage, DelegateType> (midiMessage, GO_DELEGATE_STRING_INT));
		_mappedMidiParamsStringInt2.insert(pair< MidiMessage, MappedDelegate< InputParams2<MidiMessage, string, int> > > (midiMessage, md));
	};
	
	void setMappedDelegate(MidiMessage midiMessage, MappedDelegate<InputParams2<MidiMessage, string, bool> > md) {
		LOG_VERBOSE("Store p2 string bool");
		_mappedMidiType.insert(pair<MidiMessage, DelegateType> (midiMessage, GO_DELEGATE_STRING_BOOL));
		_mappedMidiParamsStringBool2.insert(pair< MidiMessage, MappedDelegate<InputParams2<MidiMessage, string, bool> >	> (midiMessage, md));
	};
	
	void setMappedDelegate(MidiMessage midiMessage, MappedDelegate<InputParams2<MidiMessage, float, float> > md) {
		LOG_VERBOSE("Store p2 float float");
		_mappedMidiType.insert(pair<MidiMessage, DelegateType> (midiMessage, GO_DELEGATE_FLOAT_FLOAT));
		_mappedMidiParamsFloatFloat2.insert(pair< MidiMessage, MappedDelegate< InputParams2< MidiMessage, float, float> > > (midiMessage, md));
	};
	
	void setMappedDelegate(MidiMessage midiMessage, MappedDelegate<InputParams2<MidiMessage, float, string> > md) {
		LOG_VERBOSE("Store p2 float string");
		_mappedMidiType.insert(pair<MidiMessage, DelegateType> (midiMessage, GO_DELEGATE_FLOAT_STRING));
		_mappedMidiParamsFloatString2.insert(pair< MidiMessage, MappedDelegate<InputParams2<MidiMessage, float, string> > > (midiMessage, md));
	};
	
	void setMappedDelegate(MidiMessage midiMessage, MappedDelegate<InputParams2<MidiMessage, float, int> > md) {
		LOG_VERBOSE("Store p2 float int");
		_mappedMidiType.insert(pair<MidiMessage, DelegateType> (midiMessage, GO_DELEGATE_FLOAT_INT));
		_mappedMidiParamsFloatInt2.insert(pair< MidiMessage, MappedDelegate< InputParams2<MidiMessage, float, int> > > (midiMessage, md));
	};
	
	void setMappedDelegate(MidiMessage midiMessage, MappedDelegate<InputParams2<MidiMessage, float, bool> > md) {
		LOG_VERBOSE("Store p2 float bool");
		_mappedMidiType.insert(pair<MidiMessage, DelegateType> (midiMessage, GO_DELEGATE_FLOAT_BOOL));
		_mappedMidiParamsFloatBool2.insert(pair< MidiMessage, MappedDelegate<InputParams2<MidiMessage, float, bool> >	> (midiMessage, md));
	};
	
	void setMappedDelegate(MidiMessage midiMessage, MappedDelegate<InputParams2<MidiMessage, int, int> > md) {
		LOG_VERBOSE("Store p2 int int");
		_mappedMidiType.insert(pair<MidiMessage, DelegateType> (midiMessage, GO_DELEGATE_INT_INT));
		_mappedMidiParamsIntInt2.insert(pair< MidiMessage, MappedDelegate< InputParams2< MidiMessage, int, int> > > (midiMessage, md));
	};
	
	void setMappedDelegate(MidiMessage midiMessage, MappedDelegate<InputParams2<MidiMessage, int, string> > md) {
		LOG_VERBOSE("Store p2 int string");
		_mappedMidiType.insert(pair<MidiMessage, DelegateType> (midiMessage, GO_DELEGATE_INT_STRING));
		_mappedMidiParamsIntString2.insert(pair< MidiMessage, MappedDelegate<InputParams2<MidiMessage, int, string> > > (midiMessage, md));
	};
	
	void setMappedDelegate(MidiMessage midiMessage, MappedDelegate<InputParams2<MidiMessage, int, float> > md) {
		LOG_VERBOSE("Store p2 int float");
		_mappedMidiType.insert(pair<MidiMessage, DelegateType> (midiMessage, GO_DELEGATE_INT_FLOAT));
		_mappedMidiParamsIntFloat2.insert(pair< MidiMessage, MappedDelegate< InputParams2<MidiMessage, int, float> > > (midiMessage, md));
	};
	
	void setMappedDelegate(MidiMessage midiMessage, MappedDelegate<InputParams2<MidiMessage, int, bool> > md) {
		LOG_VERBOSE("Store p2 int bool");
		_mappedMidiType.insert(pair<MidiMessage, DelegateType> (midiMessage, GO_DELEGATE_INT_BOOL));
		_mappedMidiParamsIntBool2.insert(pair< MidiMessage, MappedDelegate<InputParams2<MidiMessage, int, bool> >	> (midiMessage, md));
	};
	
	void setMappedDelegate(MidiMessage midiMessage, MappedDelegate<InputParams2<MidiMessage, bool, bool> > md) {
		LOG_VERBOSE("Store p2 bool bool");
		_mappedMidiType.insert(pair<MidiMessage, DelegateType> (midiMessage, GO_DELEGATE_BOOL_BOOL));
		_mappedMidiParamsBoolBool2.insert(pair< MidiMessage, MappedDelegate< InputParams2< MidiMessage, bool, bool> > > (midiMessage, md));
	};
	
	void setMappedDelegate(MidiMessage midiMessage, MappedDelegate<InputParams2<MidiMessage, bool, string> > md) {
		LOG_VERBOSE("Store p2 bool string");
		_mappedMidiType.insert(pair<MidiMessage, DelegateType> (midiMessage, GO_DELEGATE_BOOL_STRING));
		_mappedMidiParamsBoolString2.insert(pair< MidiMessage, MappedDelegate<InputParams2<MidiMessage, bool, string> > > (midiMessage, md));
	};
	
	void setMappedDelegate(MidiMessage midiMessage, MappedDelegate<InputParams2<MidiMessage, bool, float> > md) {
		LOG_VERBOSE("Store p2 bool float");
		_mappedMidiType.insert(pair<MidiMessage, DelegateType> (midiMessage, GO_DELEGATE_BOOL_FLOAT));
		_mappedMidiParamsBoolFloat2.insert(pair< MidiMessage, MappedDelegate< InputParams2<MidiMessage, bool, float> > > (midiMessage, md));
	};
	
	void setMappedDelegate(MidiMessage midiMessage, MappedDelegate<InputParams2<MidiMessage, bool, int> > md) {
		LOG_VERBOSE("Store p2 bool int");
		_mappedMidiType.insert(pair<MidiMessage, DelegateType> (midiMessage, GO_DELEGATE_BOOL_INT));
		_mappedMidiParamsBoolInt2.insert(pair< MidiMessage, MappedDelegate<InputParams2<MidiMessage, bool, int> >	> (midiMessage, md));
	};
	
	// making these public for now until i work out a nicer way to return
	map< MidiMessage, DelegateType >												_mappedMidiType;
	vector<string>																	_midiUsage;
	
	map< MidiMessage, MappedDelegate<InputParams0<MidiMessage> > >					_mappedMidiParams0;
	
	map< MidiMessage, MappedDelegate<InputParams1<MidiMessage, string> > >			_mappedMidiParamsString1;
	map< MidiMessage, MappedDelegate<InputParams1<MidiMessage, float> > >			_mappedMidiParamsFloat1;
	map< MidiMessage, MappedDelegate<InputParams1<MidiMessage, int> > >				_mappedMidiParamsInt1;
	map< MidiMessage, MappedDelegate<InputParams1<MidiMessage, bool> > >			_mappedMidiParamsBool1;
	
	map< MidiMessage, MappedDelegate<InputParams2<MidiMessage, string, string> > >	_mappedMidiParamsStringString2;
	map< MidiMessage, MappedDelegate<InputParams2<MidiMessage, string, float> > >	_mappedMidiParamsStringFloat2;
	map< MidiMessage, MappedDelegate<InputParams2<MidiMessage, string, int> > >		_mappedMidiParamsStringInt2;
	map< MidiMessage, MappedDelegate<InputParams2<MidiMessage, string, bool> > >	_mappedMidiParamsStringBool2;
	
	map< MidiMessage, MappedDelegate<InputParams2<MidiMessage, float, float> > >	_mappedMidiParamsFloatFloat2;
	map< MidiMessage, MappedDelegate<InputParams2<MidiMessage, float, string> > >	_mappedMidiParamsFloatString2;
	map< MidiMessage, MappedDelegate<InputParams2<MidiMessage, float, int> > >		_mappedMidiParamsFloatInt2;
	map< MidiMessage, MappedDelegate<InputParams2<MidiMessage, float, bool> > >		_mappedMidiParamsFloatBool2;
	
	map< MidiMessage, MappedDelegate<InputParams2<MidiMessage, int, int> > >		_mappedMidiParamsIntInt2;
	map< MidiMessage, MappedDelegate<InputParams2<MidiMessage, int, string> > >		_mappedMidiParamsIntString2;
	map< MidiMessage, MappedDelegate<InputParams2<MidiMessage, int, float> > >		_mappedMidiParamsIntFloat2;
	map< MidiMessage, MappedDelegate<InputParams2<MidiMessage, int, bool> > >		_mappedMidiParamsIntBool2;
	
	map< MidiMessage, MappedDelegate<InputParams2<MidiMessage, bool, bool> > >		_mappedMidiParamsBoolBool2;
	map< MidiMessage, MappedDelegate<InputParams2<MidiMessage, bool, string> > >	_mappedMidiParamsBoolString2;
	map< MidiMessage, MappedDelegate<InputParams2<MidiMessage, bool, float> > >		_mappedMidiParamsBoolFloat2;
	map< MidiMessage, MappedDelegate<InputParams2<MidiMessage, bool, int> > >		_mappedMidiParamsBoolInt2;
	
};

typedef Singleton<MidiModel> MidiModelSingleton;					// Global declaration

static MidiModel * _midiModel	= MidiModelSingleton::Instance();	// this is my idea of a compromise:
// no defines, keeps introspection
// but allows data sharing between classes

#endif