/*
 *  DisplayController.h
 *  Bunyip
 *
 *  Created by gameover on 25/08/11.
 *  Copyright 2011 trace media. All rights reserved.
 *
 */

#ifndef _H_DISPLAYCONTROLLER
#define _H_DISPLAYCONTROLLER

#include "BaseState.h"

enum {
	kDISPLAYCONTROLLER_INIT,
	kDISPLAYCONTROLLER_EDIT,
	kDISPLAYCONTROLLER_READY,
	kDISPLAYCONTROLLER_ERROR
};

class DisplayController : public BaseState {

public:
	
	DisplayController();
	~DisplayController();
	
	void registerStates();
	
	bool addDisplay(int x, int y, int width, int height, string name);
	bool addViewport(int x, int y, int width, int height, string name);
	
	void setFullscreen(bool b);
	void toggleFullscreen();
	
private:
	
	
	
};

#endif