/*
 *  KeyboardController.cpp
 *  Bunyip
 *
 *  Created by gameover on 23/08/11.
 *  Copyright 2011 trace media. All rights reserved.
 *
 */

#include "KeyboardController.h"

//--------------------------------------------------------------
KeyboardController::KeyboardController() {
	
	LOG_NOTICE("Constructing KeyboardController");
	
	_appModel->_keyboardModel = new KeyboardModel();
	
//	_appModel->_keyboardModel->registerFunction("KeyboardController::test", 
//												MakeDelegate(this, &KeyboardController::test));
	
	ofAddListener(ofEvents.keyPressed, this, &KeyboardController::keyPressed);
    ofAddListener(ofEvents.keyReleased, this, &KeyboardController::keyReleased);
	
}

//--------------------------------------------------------------
KeyboardController::~KeyboardController() {
	
	LOG_NOTICE("Destructing KeyboardController");
	
	ofRemoveListener(ofEvents.keyPressed, this, &KeyboardController::keyPressed);
    ofRemoveListener(ofEvents.keyReleased, this, &KeyboardController::keyReleased);
	
	delete _appModel->_keyboardModel;
	
}



void KeyboardController::test(string mov) {
	cout << mov << endl;
	//cout << "here" << endl;

}

//--------------------------------------------------------------
void KeyboardController::keyPressed(ofKeyEventArgs &e) {
	executeFunction(e.key, kKEY_DOWN);}

//--------------------------------------------------------------
void KeyboardController::keyReleased(ofKeyEventArgs &e) {
	executeFunction(e.key, kKEY_UP);
}

//--------------------------------------------------------------
void KeyboardController::executeFunction(int key, key_st status) {
	
	KeyMessage km(key, status, 0);
	//km.print(true);

	map<KeyMessage, DelegateType>::iterator it_type;
	
	it_type = _appModel->_keyboardModel->_mappedKeyboardType.find(km);
	
	if (it_type != _appModel->_keyboardModel->_mappedKeyboardType.end()) {
		
		DelegateType dt = it_type->second;
		
		switch (dt) {
			case GO_DELEGATE_NONE:
			{
				map<KeyMessage, MappedDelegate<InputParams0<KeyMessage>			> >	 ::iterator	it0;
				it0  = _appModel->_keyboardModel->_mappedKeyboardParams0.find(km);
				DelegateMemento dm = it0->second.getDelegateMemento();
				Delegate0 funcToExec;
				funcToExec.SetMemento(dm);
				funcToExec();
				break;
			}
			case GO_DELEGATE_STRING:
			{
				map<KeyMessage, MappedDelegate<InputParams1<KeyMessage, string	> > >::iterator	it1s;
				it1s = _appModel->_keyboardModel->_mappedKeyboardParamsString1.find(km);
				DelegateMemento dm = it1s->second.getDelegateMemento();
				DelegateString1 funcToExec;
				funcToExec.SetMemento(dm);
				funcToExec(it1s->second.getInputParams().getParam1());
				break;
			}
			case GO_DELEGATE_INT:
			{
				map<KeyMessage, MappedDelegate<InputParams1<KeyMessage, int		> > >::iterator	it1i;
				it1i = _appModel->_keyboardModel->_mappedKeyboardParamsInt1.find(km);
				DelegateMemento dm = it1i->second.getDelegateMemento();
				DelegateInt1 funcToExec;
				funcToExec.SetMemento(dm);
				funcToExec(it1i->second.getInputParams().getParam1());
				break;
			}
			case GO_DELEGATE_FLOAT:
			{
				map<KeyMessage, MappedDelegate<InputParams1<KeyMessage, float	> > >::iterator	it1f;
				it1f = _appModel->_keyboardModel->_mappedKeyboardParamsFloat1.find(km);
				DelegateMemento dm = it1f->second.getDelegateMemento();
				DelegateFloat1 funcToExec;
				funcToExec.SetMemento(dm);
				funcToExec(it1f->second.getInputParams().getParam1());
				break;
			}
			case GO_DELEGATE_BOOL:
			{
				map<KeyMessage, MappedDelegate<InputParams1<KeyMessage, bool	> > >::iterator	it1b;
				it1b = _appModel->_keyboardModel->_mappedKeyboardParamsBool1.find(km);
				DelegateMemento dm = it1b->second.getDelegateMemento();
				DelegateBool1 funcToExec;
				funcToExec.SetMemento(dm);
				funcToExec(it1b->second.getInputParams().getParam1());
				break;
			}
			case GO_DELEGATE_STRING_STRING:
			{
				map<KeyMessage, MappedDelegate<InputParams2<KeyMessage, string, string > > >::iterator	it2ss;
				it2ss = _appModel->_keyboardModel->_mappedKeyboardParamsStringString2.find(km);
				DelegateMemento dm = it2ss->second.getDelegateMemento();
				DelegateStringString2 funcToExec;
				funcToExec.SetMemento(dm);
				funcToExec(it2ss->second.getInputParams().getParam1(), it2ss->second.getInputParams().getParam2());
				break;
			}
			case GO_DELEGATE_INT_INT:
			{
				map<KeyMessage, MappedDelegate<InputParams2<KeyMessage, int, int > > >::iterator	it2ii;
				it2ii = _appModel->_keyboardModel->_mappedKeyboardParamsIntInt2.find(km);
				DelegateMemento dm = it2ii->second.getDelegateMemento();
				DelegateIntInt2 funcToExec;
				funcToExec.SetMemento(dm);
				funcToExec(it2ii->second.getInputParams().getParam1(), it2ii->second.getInputParams().getParam2());
				break;
			}
			case GO_DELEGATE_FLOAT_FLOAT:
			{
				map<KeyMessage, MappedDelegate<InputParams2<KeyMessage, float, float > > >::iterator	it2ff;
				it2ff = _appModel->_keyboardModel->_mappedKeyboardParamsFloatFloat2.find(km);
				DelegateMemento dm = it2ff->second.getDelegateMemento();
				DelegateFloatFloat2 funcToExec;
				funcToExec.SetMemento(dm);
				funcToExec(it2ff->second.getInputParams().getParam1(), it2ff->second.getInputParams().getParam2());
				break;
			}
			case GO_DELEGATE_BOOL_BOOL:
			{
				map<KeyMessage, MappedDelegate<InputParams2<KeyMessage, bool, bool > > >::iterator	it2bb;
				it2bb = _appModel->_keyboardModel->_mappedKeyboardParamsBoolBool2.find(km);
				DelegateMemento dm = it2bb->second.getDelegateMemento();
				DelegateBoolBool2 funcToExec;
				funcToExec.SetMemento(dm);
				funcToExec(it2bb->second.getInputParams().getParam1(), it2bb->second.getInputParams().getParam2());
				break;
			}
			case GO_DELEGATE_STRING_INT:
			{
				map<KeyMessage, MappedDelegate<InputParams2<KeyMessage, string, int > > >::iterator	it2si;
				it2si = _appModel->_keyboardModel->_mappedKeyboardParamsStringInt2.find(km);
				DelegateMemento dm = it2si->second.getDelegateMemento();
				DelegateStringInt2 funcToExec;
				funcToExec.SetMemento(dm);
				funcToExec(it2si->second.getInputParams().getParam1(), it2si->second.getInputParams().getParam2());
				break;
			}
			case GO_DELEGATE_STRING_FLOAT:
			{
				map<KeyMessage, MappedDelegate<InputParams2<KeyMessage, string, float > > >::iterator	it2sf;
				it2sf = _appModel->_keyboardModel->_mappedKeyboardParamsStringFloat2.find(km);
				DelegateMemento dm = it2sf->second.getDelegateMemento();
				DelegateStringFloat2 funcToExec;
				funcToExec.SetMemento(dm);
				funcToExec(it2sf->second.getInputParams().getParam1(), it2sf->second.getInputParams().getParam2());
				break;
			}
			case GO_DELEGATE_STRING_BOOL:
			{
				map<KeyMessage, MappedDelegate<InputParams2<KeyMessage, string, bool > > >::iterator	it2sb;
				it2sb = _appModel->_keyboardModel->_mappedKeyboardParamsStringBool2.find(km);
				DelegateMemento dm = it2sb->second.getDelegateMemento();
				DelegateStringBool2 funcToExec;
				funcToExec.SetMemento(dm);
				funcToExec(it2sb->second.getInputParams().getParam1(), it2sb->second.getInputParams().getParam2());
				break;
			}
			case GO_DELEGATE_INT_STRING:
			{
				map<KeyMessage, MappedDelegate<InputParams2<KeyMessage, int, string > > >::iterator	it2is;
				it2is = _appModel->_keyboardModel->_mappedKeyboardParamsIntString2.find(km);
				DelegateMemento dm = it2is->second.getDelegateMemento();
				DelegateIntString2 funcToExec;
				funcToExec.SetMemento(dm);
				funcToExec(it2is->second.getInputParams().getParam1(), it2is->second.getInputParams().getParam2());
				break;
			}
			case GO_DELEGATE_INT_FLOAT:
			{
				map<KeyMessage, MappedDelegate<InputParams2<KeyMessage, int, float > > >::iterator	it2if;
				it2if = _appModel->_keyboardModel->_mappedKeyboardParamsIntFloat2.find(km);
				DelegateMemento dm = it2if->second.getDelegateMemento();
				DelegateIntFloat2 funcToExec;
				funcToExec.SetMemento(dm);
				funcToExec(it2if->second.getInputParams().getParam1(), it2if->second.getInputParams().getParam2());
				break;
			}
			case GO_DELEGATE_INT_BOOL:
			{
				map<KeyMessage, MappedDelegate<InputParams2<KeyMessage, int, bool > > >::iterator	it2ib;
				it2ib = _appModel->_keyboardModel->_mappedKeyboardParamsIntBool2.find(km);
				DelegateMemento dm = it2ib->second.getDelegateMemento();
				DelegateIntBool2 funcToExec;
				funcToExec.SetMemento(dm);
				funcToExec(it2ib->second.getInputParams().getParam1(), it2ib->second.getInputParams().getParam2());
				break;
			}
			case GO_DELEGATE_FLOAT_STRING:
			{
				map<KeyMessage, MappedDelegate<InputParams2<KeyMessage, float, string > > >::iterator	it2fs;
				it2fs = _appModel->_keyboardModel->_mappedKeyboardParamsFloatString2.find(km);
				DelegateMemento dm = it2fs->second.getDelegateMemento();
				DelegateFloatString2 funcToExec;
				funcToExec.SetMemento(dm);
				funcToExec(it2fs->second.getInputParams().getParam1(), it2fs->second.getInputParams().getParam2());
				break;
			}
			case GO_DELEGATE_FLOAT_INT:
			{
				map<KeyMessage, MappedDelegate<InputParams2<KeyMessage, float, int > > >::iterator	it2fi;
				it2fi = _appModel->_keyboardModel->_mappedKeyboardParamsFloatInt2.find(km);
				DelegateMemento dm = it2fi->second.getDelegateMemento();
				DelegateFloatInt2 funcToExec;
				funcToExec.SetMemento(dm);
				funcToExec(it2fi->second.getInputParams().getParam1(), it2fi->second.getInputParams().getParam2());
				break;
			}
			case GO_DELEGATE_FLOAT_BOOL:
			{
				map<KeyMessage, MappedDelegate<InputParams2<KeyMessage, float, bool > > >::iterator	it2fb;
				it2fb = _appModel->_keyboardModel->_mappedKeyboardParamsFloatBool2.find(km);
				DelegateMemento dm = it2fb->second.getDelegateMemento();
				DelegateFloatBool2 funcToExec;
				funcToExec.SetMemento(dm);
				funcToExec(it2fb->second.getInputParams().getParam1(), it2fb->second.getInputParams().getParam2());
				break;
			}
			case GO_DELEGATE_BOOL_STRING:
			{
				map<KeyMessage, MappedDelegate<InputParams2<KeyMessage, bool, string > > >::iterator	it2bs;
				it2bs = _appModel->_keyboardModel->_mappedKeyboardParamsBoolString2.find(km);
				DelegateMemento dm = it2bs->second.getDelegateMemento();
				DelegateBoolString2 funcToExec;
				funcToExec.SetMemento(dm);
				funcToExec(it2bs->second.getInputParams().getParam1(), it2bs->second.getInputParams().getParam2());
				break;
			}
			case GO_DELEGATE_BOOL_INT:
			{
				map<KeyMessage, MappedDelegate<InputParams2<KeyMessage, bool, int > > >::iterator	it2bi;
				it2bi = _appModel->_keyboardModel->_mappedKeyboardParamsBoolInt2.find(km);
				DelegateMemento dm = it2bi->second.getDelegateMemento();
				DelegateBoolInt2 funcToExec;
				funcToExec.SetMemento(dm);
				funcToExec(it2bi->second.getInputParams().getParam1(), it2bi->second.getInputParams().getParam2());
				break;
			}
			case GO_DELEGATE_BOOL_FLOAT:
			{
				map<KeyMessage, MappedDelegate<InputParams2<KeyMessage, bool, float > > >::iterator	it2bf;
				it2bf = _appModel->_keyboardModel->_mappedKeyboardParamsBoolFloat2.find(km);
				DelegateMemento dm = it2bf->second.getDelegateMemento();
				DelegateBoolFloat2 funcToExec;
				funcToExec.SetMemento(dm);
				funcToExec(it2bf->second.getInputParams().getParam1(), it2bf->second.getInputParams().getParam2());
				break;
			}
		}
	}
	
}