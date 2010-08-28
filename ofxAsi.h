/*
 *  ofxAsi.h
 *  asiExample
 *
 *  Created by Philip Whitfield on 8/26/10.
 *  Copyright 2010 undef.ch. All rights reserved.
 *
 */

#ifndef _CLASS_ofxAsi_
#define _CLASS_ofxAsi_

#include "ofMain.h"
#include "asiScene.h"
#include "asiTypes.h"
#include "ofxXmlSettings.h"
#include "asiImage.h"
#include "asiAnimator.h"
#include "asiCamera.h"
#include "ofx3DUtils.h"
#include <map>

class ofxAsi{
public:
	ofxAsi();
	~ofxAsi();
	
	static void addScene(asiScene* scn){
		scenes.push_back(scn);
	}
	
	static ofxAsi* getSingleton(){
		if(!hasSingleton){
			singleton = new ofxAsi();
			hasSingleton = true;
		}
		return singleton;
	}
	
	static void init(){
		glEnable(GL_DEPTH_TEST);
		glClearDepth(1.0);				
		glDepthFunc(GL_LEQUAL);				
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_BLEND);
		glAlphaFunc(GL_GREATER,0.1);
		glEnable(GL_ALPHA_TEST);				
		glEnable(GL_TEXTURE_2D);					
		glEnable(GL_CULL_FACE);
		glDisable(GL_CULL_FACE);
		
		ofxAsi* asi = getSingleton();
		asi->autoListen();
		
		for(int i=0;i<scenes.size();i++){
			scenes[i]->animator.restart();
		}
	}
	
	static void update(){
		for(int i=0;i<scenes.size();i++){
			scenes[i]->update(ofGetElapsedTimeMillis());
		}
	}
	
	static void draw(){
		if(doEasyCam)
			easyCam->place();
		for(int i=0;i<scenes.size();i++){
			scenes[i]->draw();
		}
	}
	
	static void enableEasyCam(){
		doEasyCam = true;
		easyCam = new ofxEasyCam();
		easyCam->up(0,-1,0);
	}
	
	static void disableEasyCam(){
		doEasyCam = false;
	}
	
	void autoListen();
	void update(ofEventArgs &e);
	void draw(ofEventArgs &e);

	static bool doEasyCam;
protected:
private:
	static vector<asiScene*> scenes;
	static ofxAsi* singleton;
	static bool hasSingleton;
	static ofxEasyCam* easyCam;
};

#endif