/*
 *  asiAnimator.cpp
 *  asiExample
 *
 *  Created by Philip Whitfield on 8/26/10.
 *  Copyright 2010 undef.ch. All rights reserved.
 *
 */

#include "asiAnimator.h"
#include "asiScene.h"

asiAnimator::asiAnimator(){
	frame = 0;
	state = PLAY;
	timeLast = ofGetElapsedTimeMillis();
};

asiAnimator::~asiAnimator(){
	
};

float asiAnimator::bezierPoint(float a, float b, float c, float d, float t) {
	float t1 = 1.0f - t;
	return a*t1*t1*t1 + 3*b*t*t1*t1 + 3*c*t*t*t1 + d*t*t*t;
}

void asiAnimator::pause(){
	state = PAUSE;
}

void asiAnimator::stop(){
	state = STOP;
	jumpToFrame(1);
}

void asiAnimator::play(){
	if(state == STOP)
		timeOffset = timeLast;
	state = PLAY;
}

void asiAnimator::restart(){
	timeOffset = timeLast;
}

bool asiAnimator::isPaused(){
	return state == PAUSE;
}
bool asiAnimator::isStoped(){
	return state == STOP;
}
bool asiAnimator::isPlaying(){
	return state == PLAY;
}

void asiAnimator::step(int millis){
	if(frameEnd == 0)
		return;
	if(state == PAUSE)
		timeOffset+=millis-timeLast;
	else if(state == PLAY){
		double fp = 1.f/fps;
		float fr = ((millis-timeOffset)%int((frameEnd+1)*fps))*fp;
		jumpToFrame(fr);
	}
	timeLast = millis;
}

void asiAnimator::jumpToFrame(float fr){
	frame = fr;
	for(int i=0;i<tweens.size();i++){
		tweens[i]->update(frame);
	}
	for(int i=0;i<sequences.size();i++){
		sequences[i]->update(frame);
	}
	int thisFrame = (int)floorf(frame);
	
	if(thisFrame != lastFrame){ //only continue if frame is new
		for(int i=0;i<markers.size();i++){
			if(markers[i].frame == thisFrame){
				static asiMarkerEvent e;
				e.scene = scene;
				e.animator = this;
				e.marker = markers[i];
				ofNotifyEvent(onMarker, e);
			}
		}
		
		if(thisFrame == frameEnd){
			static asiAnimatorEvent e(thisFrame);
			ofNotifyEvent(onEnd, e);
		}
		
		if(thisFrame == 0){
			if(scene->settings.loop){
				static asiAnimatorEvent e(thisFrame);
				ofNotifyEvent(onStart, e);
			}
		}
	}
	lastFrame = thisFrame;
}

void asiAnimator::addTween(asiTween* tween){
	tweens.push_back(tween);
}

void asiAnimator::addSequence(asiSequence* seq){
	sequences.push_back(seq);
}

void asiAnimator::addMarker(string name, int frame){
	asiMarker m;
	m.frame = frame;
	m.name = name;
	markers.push_back(m);
}

void asiAnimator::draw(){
	ofPushMatrix();
	for(int i=0;i<tweens.size();i++){
		tweens[i]->draw();
		ofTranslate(0,100,0);
	}
	ofPopMatrix();
}