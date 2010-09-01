/*
 *  asiSound.cpp
 *  tvShow2
 *
 *  Created by Philip Whitfield on 8/30/10.
 *  Copyright 2010 undef.ch. All rights reserved.
 *
 */

#include "asiSound.h"
#include "asiData.h"

asiSound::asiSound(){
	
};

asiSound::~asiSound(){
	
};

void asiSound::load(string path){
	snd.loadSound(asiData::toPath(path));
	cout << snd.bLoadedOk << endl;
};

void asiSound::volume(float vol){
	snd.setVolume(vol);
};

void asiSound::play(){
	snd.play();
};

void asiSound::stop(){
	snd.stop();
};