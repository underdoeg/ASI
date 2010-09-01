/*
 *  asiData.cpp
 *  asiExample
 *
 *  Created by Philip Whitfield on 8/26/10.
 *  Copyright 2010 undef.ch. All rights reserved.
 *
 */

#include "ofxAsi.h"

bool asiData::useRelPaths = false;
string asiData::relPath = "";

std::map<string, asiObjectBase*> asiData::objects;
std::map<string, asiImage*> asiData::images;
std::map<string, asiScene*> asiData::scenes;
std::map<string, asiSound*> asiData::sounds;

int autoNumber = 0;

asiData::asiData(){

};

asiData::~asiData(){

};

asiObjectBase* asiData::getObject(string name){
	return objects[name];
}
void asiData::addObject(asiObjectBase* obj){
	objects[obj->name] = obj;
}

asiImage* asiData::getImage(string name){
	return images[name];
}
void asiData::addImage(asiImage* img){
	images[img->name] = img;
}

asiSound* asiData::getSound(string name){
	return sounds[name];
}
void asiData::addSound(asiSound* snd){
	sounds[snd->name] = snd;
}

asiScene* asiData::getScene(string name){
	return scenes[name];
}
void asiData::addScene(asiScene* scn){
	ofxAsi::addScene(scn);
	scenes[scn->name] = scn;
}
int asiData::nextAutoNumber(){
	return autoNumber++;
}