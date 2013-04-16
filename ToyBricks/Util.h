//
//  Util.h
//  ToyBricks
//
//  Created by user on 13-4-6.
//
//

#ifndef __ToyBricks__Util__
#define __ToyBricks__Util__

#include <iostream>
#include "cocos2d.h"
using namespace cocos2d;

CCTexture2D* getMyTexture(const char* fileName);


float getDistance(float x1,float y1,float x2,float y2);

int getTotalCount(int difficult);

#endif /* defined(__ToyBricks__Util__) */
