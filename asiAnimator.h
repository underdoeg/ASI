/*
 *  asiAnimator.h
 *  asiExample
 *
 *  Created by Philip Whitfield on 8/26/10.
 *  Copyright 2010 undef.ch. All rights reserved.
 *
 */

#ifndef _CLASS_asiAnimator_
#define _CLASS_asiAnimator_


#include "ofMain.h"
#include "asiSequence.h"

class asiObject;
class asiScene;
class asiAnimator;

struct asiMarker{
	int frame;
	string name;
};

struct asiKeyframe{
	ofPoint h1;
	ofPoint h2;
	ofPoint p;
};


class asiAnimatorEvent{
public:
	asiAnimatorEvent(int f=0){
		frame = f;
	}
	int frame;
	
};

class asiMarkerEvent{
public:
	asiMarker marker;
	asiScene* scene;
	asiAnimator* animator;
};

class asiTween {
public:
	std::vector<asiKeyframe> frames;
	float* val;
	string path;
	int index;
	
	
	float bezierPoint(float x0, float x1, float x2, float x3, float t) {
		float   ax, bx, cx;
		float   ay, by, cy;
		float   t2, t3;
		float   x;
		
		// polynomial coefficients
		cx = 3.0f * (x1 - x0);
		bx = 3.0f * (x2 - x1) - cx;
		ax = x3 - x0 - cx - bx;
		
		t2 = t * t;
		t3 = t2 * t;
		x = (ax * t3) + (bx * t2) + (cx * t) + x0;
		
		return x;
	}
	
	void update(float t){
		for(int i=0;i<frames.size()-1;i++){
			asiKeyframe* f1 = &frames[i];
			asiKeyframe* f2 = &frames[i+1];
			if(f1->p.x<t && f2->p.x>t){
				t = t-f1->p.x;
				t /=(f2->p.x-f1->p.x);
				*val = f1->p.y+(f2->p.y-f1->p.y)*t;
				*val = bezierPoint(f1->p.y, f1->h2.y, f2->h1.y, f2->p.y, t);
				return;
			}
		}
		//we are over the last frame, so force to position
		*val = frames.back().p.y;
	}
	
	void draw(){
		ofSetColor(0,0,0);
		ofDrawBitmapString(path+" "+ofToString(index), 0, 0);
		ofPushMatrix();
		ofTranslate(0,50,0);
		ofScale(5,60,0);
		ofNoFill();
		for(int i=0;i<frames.size()-1;i++){
			asiKeyframe* f1 = &frames[i];
			asiKeyframe* f2 = &frames[i+1];
			ofBezier(f1->p.x, f1->p.y, f1->h2.x, f1->h2.y, f2->h1.x, f2->h1.y, f2->p.x, f2->p.y);
		}
		ofPopMatrix();
	}
	
	void addKeyFrame(asiKeyframe k){
		frames.push_back(k);
	}
};

class asiAnimator{
public:
	asiAnimator();
	~asiAnimator();
	static float bezierPoint(float a, float b, float c, float d, float t);
	void step(int millis);
	void draw();
	void addTween(asiTween* tween);
	void addSequence(asiSequence* seq);
	void addMarker(string name, int frame);
	ofEvent<asiAnimatorEvent> onStart;
	ofEvent<asiAnimatorEvent> onEnd;
	ofEvent<asiMarkerEvent> onMarker;
	
	float frame;
	int frameEnd;
	float fps;
	int lastFrame;
	asiScene* scene;
protected:
private:
	std::vector<asiTween*> tweens;
	std::vector<asiSequence*> sequences;
	std::vector<asiMarker> markers;
};

#endif