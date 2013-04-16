//
//  AnimationSprite.h
//  Zuma_V4
//
//  Created by user on 13-1-20.
//
//

#ifndef __Zuma_V4__AnimationSprite__
#define __Zuma_V4__AnimationSprite__

#include <iostream>
#include "cocos2d.h"
using namespace cocos2d;

class AnimationSprite: public CCSprite
{
protected:
    
    // 存放帧数
    CCArray* m_frameArray;
    
    int m_currentIndex;
    
    // 初始化
    void initAnimationSprite(const char* fileName,int columns,int rows,int totalFrame);
    
     void initAnimationSprite(CCTexture2D* texture,int columns,int rows,int totalFrame);
    
public:
    virtual ~AnimationSprite();
    
    static AnimationSprite* createAnimationSprite(const char* fileName,int columns,int rows);
    
    static AnimationSprite* createAnimationSprite(const char* fileName,int columns,int rows,int totalFrame);
    
    static AnimationSprite* createAnimationSprite(CCTexture2D* texture,int columns,int rows);
    
    static AnimationSprite* createAnimationSprite(CCTexture2D* texture,int columns,int rows,int totalFrame);

    // 开始动画
    void animation(float duration,bool forever = true);
    
    //动画完毕后，一个回调函数
    void animation(float duration,CCCallFuncN* callFunN);
    
    
    // 暂停动画
    void pauseAnimation();
    
    //恢复动画
    void resumeAnimation();
    
    // 只执行一次动画的回调函数
    void executeOnceAnimationCallback();
};



#endif /* defined(__Zuma_V4__AnimationSprite__) */
