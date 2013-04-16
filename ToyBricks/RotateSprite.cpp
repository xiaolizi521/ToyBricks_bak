//
//  RotateSprite.cpp
//  Paopao_Game
//
//  Created by user on 13-2-22.
//
//

#include "RotateSprite.h"

RotateSprite::~RotateSprite()
{
    
}


CCAffineTransform RotateSprite::nodeToParentTransform(void)
{
    CCPoint tempPoint = getAnchorPoint();
    setAnchorPoint(ccp(0.5, 0.5));
    
    
    CCAffineTransform t = CCSprite::nodeToParentTransform();
    
    setAnchorPoint(tempPoint);
    
    return t;
}

//
//
//
//  create
RotateSprite* RotateSprite::createRotateSprite(const char* fileName)
{
    RotateSprite* bob = new RotateSprite();
    if (bob && bob->initWithFile(fileName)) {
        bob->autorelease();
        return bob;
    }
    CC_SAFE_DELETE(bob);
    return NULL;
}

RotateSprite* RotateSprite::createRotateSpriteWithTexture(CCTexture2D* texture)
{
    RotateSprite* bob = new RotateSprite();
    if (bob && bob->initWithTexture(texture)) {
        bob->autorelease();
        return bob;
    }
    CC_SAFE_DELETE(bob);
    return NULL;
}