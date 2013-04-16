//
//  LevelItemSprite.h
//  ToyBricks
//
//  Created by user on 13-4-9.
//
//

#ifndef __ToyBricks__LevelItemSprite__
#define __ToyBricks__LevelItemSprite__

#include <iostream>
#include "cocos2d.h"
#include "ButtonSprite.h"
using namespace cocos2d;


class LevelItemSprite : public ButtonSprite
{
protected:
    
    ButtonClick_FuncND m_BtnClick_FuncND;
    
    int m_param;
    
public:    
    
    LevelItemSprite();
    
    virtual ~LevelItemSprite(){};
    
    void setLevelCount(CCObject* target,ButtonClick_FuncND funND,int count,int totalCount);
    
    void setOnClickListener(CCObject* target,ButtonClick_FuncND funND,int param);
    
    // create
    static LevelItemSprite* createLevelItemSprite(CCTexture2D* texture,int tPriority = kCCMenuHandlerPriority);
    
    virtual  void clicked();
    
    void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
};


#endif /* defined(__ToyBricks__LevelItemSprite__) */
