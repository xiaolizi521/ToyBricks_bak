//
//  Controller.h
//  ToyBricks
//
//  Created by user on 13-4-9.
//
//

#ifndef __ToyBricks__Controller__
#define __ToyBricks__Controller__

#include <iostream>
#include "cocos2d.h"
using namespace cocos2d;



class LevelLayer;

class Controller : public CCLayer
{
protected:

public:
    
    virtual ~Controller();
    virtual void onEnter();
    
    //
    void preBtnClicked(CCObject* pSender);
    void nextBtnClicked(CCObject* pSender);

    void homeBtnClicked(CCObject* pSender);
    void resetBtnClicked(CCObject* pSender);
    void selectLevelBtnClicked(CCObject* pSender);
    void shareBtnClicked(CCObject* pSender);
    
    virtual void keyBackClicked();
    void backBtnClicked();
};



#endif /* defined(__ToyBricks__Controller__) */
