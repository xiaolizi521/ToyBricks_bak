//
//  RotateSprite.h
//  Paopao_Game
//
//  Created by user on 13-2-22.
//
//

#ifndef __Paopao_Game__RotateSprite__
#define __Paopao_Game__RotateSprite__

#include <iostream>
#include "cocos2d.h"
using namespace cocos2d;

//
//
//  作用是，重新设置了锚点后，依然让其围绕中心旋转
//
//
//
//
class RotateSprite : public CCSprite
{
    
public:
    virtual ~RotateSprite();
    virtual CCAffineTransform nodeToParentTransform(void);
    static RotateSprite* createRotateSprite(const char* fileName);
    static RotateSprite* createRotateSpriteWithTexture(CCTexture2D* texture);
};


#endif /* defined(__Paopao_Game__RotateSprite__) */
