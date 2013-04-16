//
//  SuccessLayer.h
//  ToyBricks
//
//  Created by user on 13-4-10.
//
//

#ifndef __ToyBricks__SuccessLayer__
#define __ToyBricks__SuccessLayer__

#include <iostream>
#include "cocos2d.h"
using namespace cocos2d;


class SuccessLayer : public CCLayer
{
public:
    virtual void onEnter();
    
    
    //
    void homeBtnClicked();
    void resetBtnClicked();
    void nextBtnClicked();
    
    // use to stop touch event transfer
     virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
};


#endif /* defined(__ToyBricks__SuccessLayer__) */
