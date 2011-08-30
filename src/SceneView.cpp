/*
 *  SceneView.cpp
 *  Bunyip
 *
 *  Created by gameover on 26/08/11.
 *  Copyright 2011 trace media. All rights reserved.
 *
 */

#include "SceneView.h"
//--------------------------------------------------------------
SceneView::SceneView(float width, float height) : BaseView(width ,height) {
	
	LOG_NOTICE("Constructing SceneView");
	_shader1Tex.allocate(width, height, GL_RGBA);
	_shader1FBO.setup(width, height);
	_shader1FBO.attach(_shader1Tex);
	
	_shader2Tex.allocate(width, height, GL_RGBA);
	_shader2FBO.setup(width, height);
	_shader2FBO.attach(_shader2Tex);
	
	_shaders[0].setup(ofToDataPath("shaders/blur_vertical"), ofToDataPath("shaders/blur_vertical"));
	_shaders[1].setup(ofToDataPath("shaders/blur_horizontal"), ofToDataPath("shaders/blur_horizontal"));
	_shaders[2].setup(ofToDataPath("shaders/blend"), ofToDataPath("shaders/blend"));

}

/*--------------------------------------------------------------
 SceneView::~SceneView() {
 
 LOG_NOTICE("Destroying SceneView");
 
 }*/

//--------------------------------------------------------------
void SceneView::update() {
	
	Scene* currentScene = _appModel->getCurrentScene();
	
	if (currentScene== NULL) return;
	
	_shader1FBO.begin();
	{

		glClearColor(0.0, 0.0, 0.0, 0.0); // transparent clear colour
		glClear(GL_COLOR_BUFFER_BIT);
		
		for (int layer = 0; layer < currentScene->getNumberOfKinectLayers(); layer++) {
			
			glPushMatrix();
			
			KinectView* kinectLayer = currentScene->getKinectLayer(layer);
			ViewPort* viewPort		 = kinectLayer->getViewPort();
			
			float x = viewPort->getX();
			float y = viewPort->getY();
			float width = viewPort->getWidth();
			float height = viewPort->getHeight();
			
			kinectLayer->draw(x, y, width, height);
			
			glPopMatrix();
		}
		
	}
	_shader1FBO.end();
	
    if(currentScene->getNumberOfKinectLayers() > 0) {
        int blurSize = boost::any_cast<int>(_appModel->getProperty("blurIterations"));
        
        for (int pass = 0; pass < pow((double)blurSize, 2); pass++) {
            
            _shader2FBO.begin();
            {
                glClearColor(0.0, 0.0, 0.0, 1.0); // transparent clear colour
                glClear(GL_COLOR_BUFFER_BIT);
                _shaders[0].begin();
                {
                    _shaders[0].setTexture("texture", _shader1Tex, 1);
                    _shaders[0].setUniform1f("blurSize", (float)blurSize);
                    ofSetColor(255, 255, 255, 255);
                    glBegin(GL_TRIANGLE_STRIP);
                    glTexCoord2f(0, 0);	glVertex2f(0, 0);
                    glTexCoord2f(0, _viewHeight); glVertex2f(0, _viewHeight);
                    glTexCoord2f(_viewWidth, 0); glVertex2f(_viewWidth, 0);
                    glTexCoord2f(_viewWidth, _viewHeight); glVertex2f(_viewWidth, _viewHeight);
                    glEnd();
                }
                _shaders[0].end();
            }
            _shader2FBO.end();
            
            _shader1FBO.begin();
            {
                _shaders[1].begin();
                {
                    _shaders[1].setTexture("texture", _shader2Tex, 1);
                    _shaders[1].setUniform1f("blurSize", (float)blurSize);
                    ofSetColor(255, 255, 255, 255);
                    glBegin(GL_TRIANGLE_STRIP);
                    glTexCoord2f(0, 0);	glVertex2f(0, 0);
                    glTexCoord2f(0, _viewHeight); glVertex2f(0, _viewHeight);
                    glTexCoord2f(_viewWidth, 0); glVertex2f(_viewWidth, 0);
                    glTexCoord2f(_viewWidth, _viewHeight); glVertex2f(_viewWidth, _viewHeight);
                    glEnd();
                    _shaders[1].end();
                }
            }
            _shader1FBO.end();
            
        }
    }
	
	
	_shader2FBO.begin();
	{
		glClearColor(0.0, 0.0, 0.0, 1.0); // transparent clear colour
		glClear(GL_COLOR_BUFFER_BIT);
		
		ofSetColor(255,255,255, 255); // no tinting
		
		for (int layer = 0; layer < currentScene->getNumberOfVideoLayers(); layer++) {
			VideoView* videoLayer = currentScene->getVideoLayer(layer);
			videoLayer->draw(0, 0, _viewWidth, _viewHeight); // fuck you you mother fucking massive cunt face fucker
		}
	}
	_shader2FBO.end();
	
	_viewFBO.begin();
	{

		glPushMatrix();
		
		//glScalef(0.1, 0.1, 1.0);
		_shader2Tex.draw(0, 0, _viewWidth, _viewHeight);
		_shader1Tex.draw(0, 0, _viewWidth, _viewHeight);
		
		glPopMatrix();
	
		

		
	}
	_viewFBO.end();
	
}

