//
//  Util.cpp
//  ToyBricks
//
//  Created by user on 13-4-6.
//
//

#include "Util.h"
#include "Config.h"

CCTexture2D* getMyTexture(const char* fileName)
{
    CCTextureCache* cache = CCTextureCache::sharedTextureCache();
    return cache->textureForKey(fileName);
}

float getDistance(float x1,float y1,float x2,float y2)
{
    float x = (x1 - x2)*(x1 - x2);
    float y = (y1 - y2)*(y1 - y2);
    return sqrtf(x + y);
}

int getTotalCount(int difficult)
{
    if (difficult == 1) {
        return G_NOOB;
    }else if (difficult == 2)
    {
        return G_EASY;
    }else if (difficult == 3)
    {
        return G_NORMAL;
    }else if(difficult == 4)
    {
        return G_Expert;
    }else if (difficult == 5)
    {
        return G_Challenge;
    }else
    {
        return 0;
    }
}