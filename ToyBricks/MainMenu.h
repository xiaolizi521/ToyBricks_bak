//
//  MainMenu.h
//  ToyBricks
//
//  Created by user on 13-4-2.
//
//

#ifndef __ToyBricks__MainMenu__
#define __ToyBricks__MainMenu__

#include <iostream>

#include "cocos2d.h"
using namespace cocos2d;


class MainMenu : public CCLayer
{
    
public:
    MainMenu();
    
    virtual ~MainMenu();
    
    virtual void onEnter();
    
   // void playBtnClicked();
    
    // load resources
    void loadGameResources();
    
    //
    void playBtnClicked(CCObject* pSender);
    void moreBtnClicked(CCObject* pSender);
};

#endif /* defined(__ToyBricks__MainMenu__) */
