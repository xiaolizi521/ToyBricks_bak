//
//  ButtonSprite.h
//  Zuma_V4
//
//  Created by user on 13-1-28.
//
//

#ifndef __Zuma_V4__ButtonSprite__
#define __Zuma_V4__ButtonSprite__

#include <iostream>
#include "CallBack.h"
#include "cocos2d.h"
using namespace cocos2d;



class ButtonSprite : public CCSprite,public CCTouchDelegate
{
protected:
    // touch 事件优先级
    int m_touchPriority;
    
    bool m_isDown;
    
    // update  2013-02-17
    // click handle
    ButtonClick_Func m_BtnClick_Func;

    // update 2013-03-27
    CCObject* m_selectorTarget;
    
public:
    ButtonSprite();
    virtual ~ButtonSprite();
       
    //
    // update  2013-02-17
    // 调整按钮的默认优先级,设置为最高优先级
    static ButtonSprite* createButtonSprite(const char* fileName,int tPriority = kCCMenuHandlerPriority);
    
    static ButtonSprite* createButtonSprite(CCTexture2D* texture,int tPriority = kCCMenuHandlerPriority);
    
    static ButtonSprite* createButtonSpriteWithSpriteFrame(CCSpriteFrame *pSpriteFrame,int tPriority = kCCMenuHandlerPriority);
    
    /* 触摸相关 */
    virtual void onEnter();
    virtual void onExit();
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    // optional
    
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);
    
    
    //update  2013-02-17
    void clicked();
    
    void setOnClickListener(CCObject* target,ButtonClick_Func tBtnClickFunc);

};




#endif /* defined(__Zuma_V4__ButtonSprite__) */
