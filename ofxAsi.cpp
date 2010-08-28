/*
 *  ofxAsi.cpp
 *  asiExample
 *
 *  Created by Philip Whitfield on 8/26/10.
 *  Copyright 2010 undef.ch. All rights reserved.
 *
 */

#include "ofxAsi.h"

vector<asiScene*> ofxAsi::scenes;
bool ofxAsi::hasSingleton = false;
ofxAsi* ofxAsi::singleton;
ofxEasyCam* ofxAsi::easyCam = NULL;
bool ofxAsi::doEasyCam = false;

ofxAsi::ofxAsi(){

};

ofxAsi::~ofxAsi(){

};

void ofxAsi::update(ofEventArgs &e){
	update();
}

void ofxAsi::draw(ofEventArgs &e){
	draw();
}

void ofxAsi::autoListen(){
	ofAddListener(ofEvents.update, this, &ofxAsi::update);
	ofAddListener(ofEvents.draw, this, &ofxAsi::draw);
}