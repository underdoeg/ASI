/*
 *  asiUtils.h
 *  asiExample
 *
 *  Created by Philip Whitfield on 8/26/10.
 *  Copyright 2010 undef.ch. All rights reserved.
 *
 */
#ifndef ASI_UTILS
#define ASI_UTILS

#include "ofxXmlSettings.h"
#include "ofxVectorMath.h"
#include "ofxAsi.h"

class asiXML{
public: 
	static void parse(string path, asiSettings settings=asiSettings()){
		ofxXmlSettings xml;
		xml.loadFile(path);
		
		if(xml.getAttribute("root", "relRes", 0, 0) == 1){
			asiData::useRelPaths = true;
			asiData::relPath = ofToDataPath(path, true);
			vector<string> path = ofSplitString(asiData::relPath, "/");
			asiData::relPath = "";
			for(int i=0;i<path.size()-1;i++){
				asiData::relPath+= "/"+path[i];
			}
			asiData::relPath+="/";
		}
		
		xml.pushTag("root", 0);
		xmlToScenes(settings, &xml);
		xmlToImages(&xml);
	}
	
	static void xmlToObjects(ofxXmlSettings* xml, asiObjectContainer* container){
		for(int i=0;i<xml->getNumTags("object");i++){
			asiObject* obj = new asiObject();
			obj->set(xmlNodeToVec3f(xml, "object", i));
			obj->scale.set(xml->getAttribute("object", "sx", 0.f, i), xml->getAttribute("object", "sy", 0.f, i), xml->getAttribute("object", "sz", 0.f, i));
			obj->rotation.set(xml->getAttribute("object", "rx", 0.f, i), xml->getAttribute("object", "ry", 0.f, i), xml->getAttribute("object", "rz", 0.f, i));
			obj->name = xml->getAttribute("object", "name", "noName", i);
			
			xml->pushTag("object", i);
			
			//parse vertexes
			for(int j=0;j<xml->getNumTags("v");j++){
				asiVert v;
				v.set(xmlNodeToVec3f(xml, "v", j));
				obj->addVert(v);
			}
			
			//parse faces
			for (int j=0;j<xml->getNumTags("face"); j++) {
				asiFace face;
				
				face.img = xml->getAttribute("texFace", "img", "", j);
				
				xml->pushTag("face", j);
				for (int k=0; k<xml->getNumTags("vRef"); k++) {
					face.indexes.push_back(xml->getAttribute("vRef", "index", 0, k));
				}
				xml->popTag();
				if(xml->getNumTags("texFace")>0){
					xml->pushTag("texFace", j);
					for (int k=0; k<xml->getNumTags("uv"); k++) {
						face.uv.push_back(ofxVec2f(xml->getAttribute("uv", "u", 0, k), xml->getAttribute("uv", "v", 0, k)));
					}
					xml->popTag();
				}
				obj->faces.push_back(face);
			}
			
			obj->setOriginal();
			
			asiData::addObject(obj);
			container->addObject(obj);
			
			xmlToAnim(xml, obj);
			
			xmlToObjects(xml, obj);
			
			xml->popTag();
			
		}
	}
	
	static void xmlToImages(ofxXmlSettings* xml){
		for (int i=0;i<xml->getNumTags("img"); i++){
			asiImage* img = new asiImage;
			img->name = xml->getAttribute("img", "name", "none", i);
			img->loadImg(xml->getAttribute("img", "file", "/", i));
			asiData::addImage(img);
		}
	}
	
	static void xmlToAnim(ofxXmlSettings* xml, asiObjectBase* obj){
		xml->pushTag("anim", 0);
		//read animation data
		for(int j=0;j<xml->getNumTags("frames");j++){
			asiTween* t = new asiTween;
			t->path = xml->getAttribute("frames", "path", "", j);
			t->index = xml->getAttribute("frames", "indx", 0, j);
			xml->pushTag("frames", j);
			for(int k=0;k<xml->getNumTags("key");k++){
				asiKeyframe kf;// = new coKeyFrame;
				kf.p.x = xml->getAttribute("key", "coX", 0.f, k);
				kf.p.y = xml->getAttribute("key", "coY", 0.f, k);
				kf.h1.x = xml->getAttribute("key", "h1X", 0.f, k);
				kf.h1.y = xml->getAttribute("key", "h1Y", 0.f, k);
				kf.h2.x = xml->getAttribute("key", "h2X", 0.f, k);
				kf.h2.y = xml->getAttribute("key", "h2Y", 0.f, k);
				t->addKeyFrame(kf);
			}
			xml->popTag();
			if(obj->linkTween(t))
				obj->scene->animator.addTween(t);
		}
		xml->popTag();
	}
	
	static void xmlToMarkers(ofxXmlSettings* xml, asiAnimator* animator){
		xml->pushTag("markers", 0);
		for(int i=0;i<xml->getNumTags("marker");i++){
			animator->addMarker(xml->getAttribute("marker", "name", "noName", i), xml->getAttribute("marker", "frame", 0, i));
		}
		xml->popTag();
	}
	
	static void xmlToCamera(ofxXmlSettings* xml, asiScene* scene){
		if(xml->getNumTags("cam")>0){
			asiCamera* cam = new asiCamera;
			cam->set(xmlNodeToVec3f(xml, "cam", 0));
			cam->name = xml->getAttribute("cam", "name", "none", 0);
			cam->rotation.set(xml->getAttribute("cam", "rx", 0.f, 0), xml->getAttribute("cam", "ry", 0.f, 0), xml->getAttribute("cam", "rz", 0.f, 0));
			cam->clipStart = xml->getAttribute("cam", "clipStart", .1f, 0);
			cam->clipEnd = xml->getAttribute("cam", "clipEnd", 100.f, 0.f);
			cam->lensAngle = xml->getAttribute("cam", "lens", .8f, 0.f);
			cam->imgWidth = xml->getAttribute("cam", "imgW", 1280, 0);
			cam->imgHeight = xml->getAttribute("cam", "imgH", 720, 0);
			xml->pushTag("cam", 0);
			if(scene->settings.autoResize)
				ofSetWindowShape(cam->imgWidth, cam->imgHeight);
			scene->setCamera(cam);
			xmlToAnim(xml, cam);
			xml->popTag();
		}
	}
	
	static void xmlToScenes(asiSettings s, ofxXmlSettings* xml){
		for(int i=0;i<xml->getNumTags("scene");i++){
			asiScene* scn = new asiScene;
			scn->settings = s;
			scn->animator.fps = xml->getAttribute("scene", "fps", 30, 0);
			scn->animator.frameEnd = xml->getAttribute("scene", "frameEnd", 1, 0);
			scn->name = xml->getAttribute("scene", "name", "scene", 0);
			xml->pushTag("scene", i);
			
			xmlToMarkers(xml, &scn->animator);
			
			//parse objects
			xml->pushTag("objects", 0);
			xmlToObjects(xml, scn);
			xml->popTag();
			
			xmlToCamera(xml, scn);
			
			asiData::addScene(scn);
			
			xml->popTag(); //end of scene tag
		}
	}
	
	static ofxVec3f xmlNodeToVec3f(ofxXmlSettings* xml, string name, int pos){
		ofxVec3f vec;
		vec.set(xml->getAttribute(name, "x", 0.f, pos), xml->getAttribute(name, "y", 0.f, pos), xml->getAttribute(name, "z", 0.f, pos));
		return vec;
	}
};
#endif