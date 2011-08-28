/*
 *  DebugView.h
 *  Bunyip
 *
 *  Created by gameover on 23/08/11.
 *  Copyright 2011 trace media. All rights reserved.
 *
 */


#ifndef _H_DEBUGVIEW
#define _H_DEBUGVIEW

#include "BaseView.h"
#include "AppModel.h"
#include "KinectModel.h"

class DebugView : public BaseView {
	
public:
	
	DebugView(float width, float height);	//ctor
	
	void update();
	
private:
	
	
};

#endif