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
void asiData::addScene(asiScene* scn){
	ofxAsi::addScene(scn);
	scenes[scn->name] = scn;
}
int asiData::nextAutoNumber(){
	return autoNumber++;
}