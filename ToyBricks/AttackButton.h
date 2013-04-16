//
//  AttackButton.h
//  Paopao_Game
//
//  Created by user on 13-2-21.
//
//

#ifndef __Paopao_Game__AttackButton__
#define __Paopao_Game__AttackButton__

#include <iostream>
#include <ctime>
#include "cocos2d.h"
#include "TileSprite.h"
#include "CallBack.h"
using namespace cocos2d;


class AttackButton : public TileSprite,public CCTouchDelegate
{
protected:
    bool m_enable;
   
    // 触摸优先级
    int m_touchPriority;
    
    //  用来回调
    ButtonClick_Func m_BtnClick_Func;
    
    // update 2013-03-27
    CCObject* m_selectorTarget;
    
    AttackButton();
public:
    
    virtual ~AttackButton();
    virtual void onEnter();
    
    virtual void onExit();
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    // optional
    
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);
    
    
    void setOnClickListener(CCObject* target,ButtonClick_Func tButtonClick_Func);
    
    void setEnable(bool flag);
public:
    
    //
    //
    //  create
    static AttackButton* createAttackButton(const char* fileName, int columns, int rows,int touchPriority = kCCMenuHandlerPriority);
    
    static AttackButton* createAttackButton(CCTexture2D* texture, int columns, int rows,int touchPriority = kCCMenuHandlerPriority);
};

#endif /* defined(__Paopao_Game__AttackButton__) */
