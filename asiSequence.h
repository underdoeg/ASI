/*
 *  asiSequence.h
 *  asiExample
 *
 *  Created by Philip Whitfield on 8/26/10.
 *  Copyright 2010 undef.ch. All rights reserved.
 *
 */

#ifndef _CLASS_asiSequence_
#define _CLASS_asiSequence_

class asiSequence{
public:
	asiSequence();
	~asiSequence();
	void update(float frame);
	virtual void start()=0;
	virtual void stop()=0;
    int startFrame;
	int length;
	bool running;
protected:
private:
};

#endif