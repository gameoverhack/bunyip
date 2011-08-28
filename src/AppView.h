/*
 *  AppView.h
 *  emptyExample
 *
 *  Created by gameover on 22/08/11.
 *  Copyright 2011 trace media. All rights reserved.
 *
 */

#ifndef _H_APPVIEW
#define _H_APPVIEW

#include "BaseView.h"
#include "SceneView.h"
#include "DebugView.h"

class AppView : public BaseView {
	
public:
	
	AppView(float width, float height);		//ctor
	~AppView();								//dtor
	
	void update();
	void draw();
	
private:
	
	DebugView*		_debugView;
	SceneView*		_sceneView;
	
protected:
	
};

#endif