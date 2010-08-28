/*
 *  asiScene.h
 *  asiExample
 *
 *  Created by Philip Whitfield on 8/26/10.
 *  Copyright 2010 undef.ch. All rights reserved.
 *
 */

#ifndef _CLASS_asiScene_
#define _CLASS_asiScene_

#include "asiTypes.h"
#include "ofxXmlSettings.h"
#include "asiObject.h"
#include "asiAnimator.h"
#include "asiCamera.h"

class asiScene: public asiObjectContainer{
public:
      asiScene();
      ~asiScene();
	void update(int millis);
	void draw();
	
	void setCamera(asiCamera* cam);
	asiAnimator* getAnimator();
	
	asiSettings settings;
	string name;
	asiAnimator animator;
	asiCamera* camera;
	bool hasCamera;
protected:
private:
};

#endif