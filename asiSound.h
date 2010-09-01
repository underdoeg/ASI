/*
 *  asiSound.h
 *  tvShow2
 *
 *  Created by Philip Whitfield on 8/30/10.
 *  Copyright 2010 undef.ch. All rights reserved.
 *
 */

#ifndef _CLASS_asiSound_
#define _CLASS_asiSound_

#include "ofMain.h"
#include "asiTypes.h"
#include "asiSequence.h"

class asiSound{
public:
	asiSound();
	~asiSound();
	void load(string path);
	void volume(float vol);
	ofSoundPlayer snd;
	string name;
	void play();
	void stop();
protected:
private:
};

class asiSoundSequence: public asiSequence{
public:
	void start(){
		snd->volume(volume);
		snd->play();
	}
	
	void stop(){
		snd->stop();
	}
	asiSound* snd;
	float volume;
};

#endif