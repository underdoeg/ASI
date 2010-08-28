/*
 *  asiData.h
 *  asiExample
 *
 *  Created by Philip Whitfield on 8/26/10.
 *  Copyright 2010 undef.ch. All rights reserved.
 *
 */

#ifndef _CLASS_asiData_
#define _CLASS_asiData_

#include "ofMain.h"

class asiObjectBase;
class asiScene;
class asiImage;

class asiData{
public:
      asiData();
      ~asiData();
	
	static string toPath(string path){
		if(useRelPaths)
			return relPath+path;
		else
			return path;
	}
	
	static asiObjectBase* getObject(string name);
	static void addObject(asiObjectBase* obj);
	
	static asiImage* getImage(string name);
	static void addImage(asiImage* obj);
	
	static asiScene* getScene(string name);
	static void addScene(asiScene* scn);
	
	static int nextAutoNumber();
	
	static bool useRelPaths;
	static string relPath;
	
protected:
private:
	static std::map<string, asiScene*> scenes;
	static std::map<string, asiObjectBase*> objects;
	static std::map<string, asiImage*> images;
	
};

#endif