//
//  Chapter.h
//  ToyBricks
//
//  Created by user on 13-4-2.
//
//

#ifndef __ToyBricks__Chapter__
#define __ToyBricks__Chapter__

#include <iostream>

#include "cocos2d.h"
using namespace cocos2d;


class Chapter : public CCLayer
{
public:
    virtual ~Chapter();
    virtual void onEnter();
    
    Chapter();
    virtual void keyBackClicked();
    
    // callback
    void noobBtnClicked(CCObject* sender);
    void easyBtnClicked(CCObject* sender);
    void normalBtnClicked(CCObject* sender);
    void expertBtnClicked(CCObject* sender);
    void challengeBtnClicked(CCObject* sender);
    
    void backBtnClicked();
};

#endif /* defined(__ToyBricks__Chapter__) */
