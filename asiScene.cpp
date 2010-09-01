/*
 *  asiScene.cpp
 *  asiExample
 *
 *  Created by Philip Whitfield on 8/26/10.
 *  Copyright 2010 undef.ch. All rights reserved.
 *
 */

#include "asiScene.h"


asiScene::asiScene(){
	scene = this;
	hasCamera = false;
	animator.scene = this;
};

asiScene::~asiScene(){

};

void asiScene::update(int millis){
	if(settings.play)
		animator.step(millis);
};

void asiScene::draw(){
	ofEnableAlphaBlending();
	if(settings.play){
		if(hasCamera && settings.doCamera)
			camera->place();
		drawObjects();
	}
	ofDisableAlphaBlending();
};

asiAnimator* asiScene::getAnimator(){
	return &animator;
}

void asiScene::setCamera(asiCamera* cam){
	camera = cam;
	hasCamera = true;
	addObject(cam);
}