/*
 *  GuiController.h
 *  Bunyip
 *
 *  Created by gameover on 30/08/11.
 *  Copyright 2011 trace media. All rights reserved.
 *
 */

#ifndef _H_GUICONTROLLER
#define _H_GUICONTROLLER

#include "ofMain.h"

#include "AppModel.h"
#include "KeyboardModel.h"
#include "MidiModel.h"

class GuiController : public ofBaseApp {
	
public:
	
	GuiController();
	~GuiController();
	
	void	setup();
	void	addSceneGui(Scene* scene);
	
private:
	
};

#endif
