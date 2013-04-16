//
//  ChangeableSprite.h
//  Zuma_V4
//
//  Created by user on 13-1-23.
//
//

#ifndef __Zuma_V4__ChangeableSprite__
#define __Zuma_V4__ChangeableSprite__

#include <iostream>
#include "TileSprite.h"
#include "CallBack.h"

/*
 * 可切换状态的按钮,注意使用两段式构造方法
 */

class ChangeableSprite : public TileSprite,public CCTouchDelegate
{
   // true表示显示第一帧,false表示显示第二帧
    bool m_currentState;

    ButtonClick_Func m_ButtonClick_Func;
    
    // update 2013-03-27
    CCObject* m_selectorTarget;
    
protected:

    // 是否有效
    bool m_enable;
    
    bool m_isDown;
    ChangeableSprite();
    int m_touchPriority;
public:
    virtual ~ChangeableSprite();
    
    static ChangeableSprite* createChangeableSprite(const char* fileName,int columns,int rows,int tPriority = kCCMenuHandlerPriority);
    
    static ChangeableSprite* createChangeableSprite(CCTexture2D* texture,int columns,int rows,int tPriority = kCCMenuHandlerPriority);
    
    
    //重写触屏相关函数----
    virtual void onEnter();
    virtual void onExit();
    virtual bool ccTouchBegan(CCTouch* touch, CCEvent* event);
    virtual void ccTouchMoved(CCTouch* touch, CCEvent* event);
    virtual void ccTouchEnded(CCTouch* touch, CCEvent* event);
    virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);
    
    void setOnClickListener(CCObject* target,ButtonClick_Func mCallback);
    
    void setCurrentState(bool mState);
    void clicked();
    
    void setEnable(bool flag);
};


#endif /* defined(__Zuma_V4__ChangeableSprite__) */
