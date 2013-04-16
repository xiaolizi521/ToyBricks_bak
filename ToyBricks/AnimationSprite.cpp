//
//  AnimationSprite.cpp
//  Zuma_V4
//
//  Created by user on 13-1-20.
//
//

#include "AnimationSprite.h"

const int kTagSpriteAnimation = 1;


void AnimationSprite::initAnimationSprite(const char* fileName,int columns,int rows,int totalFrame)
{
    CCTexture2D* texture = CCTextureCache::sharedTextureCache()->addImage(fileName);

    initAnimationSprite(texture, columns, rows, totalFrame);
}

void AnimationSprite::initAnimationSprite(CCTexture2D* texture,int columns,int rows,int totalFrame)
{
    m_currentIndex = 0;
    m_frameArray = CCArray::createWithCapacity(columns * rows);
    m_frameArray->retain();
    
    CCSize size = texture->getContentSize();
    
    float width = size.width / columns;
    float height = size.height / rows;
    
    int tCounter = 0;
    // 创建CCSpriteFrame
    for (int i = 0; i < rows; i++) {
        for (int j= 0 ; j <columns; j++) {
            CCSpriteFrame* frame = CCSpriteFrame::createWithTexture(texture, CCRectMake(j*width, i*height, width, height));
            m_frameArray->addObject(frame);
            
            tCounter++;
            if (tCounter >= totalFrame) {
                return;
            }
        }
    }

}


AnimationSprite::~AnimationSprite(){
    CC_SAFE_RELEASE(m_frameArray);
}

AnimationSprite* AnimationSprite::createAnimationSprite(const char* fileName,int columns,int rows,int totalFrame)
{
    AnimationSprite* sprite = new AnimationSprite();
    sprite->initAnimationSprite(fileName, columns, rows, totalFrame);
    /*
     * 二段世 构造函数
     */
    if (sprite && sprite->initWithSpriteFrame((CCSpriteFrame*)sprite->m_frameArray->objectAtIndex(sprite->m_currentIndex))) {
        
        sprite->autorelease();
        
        return sprite;
    }
    
    CC_SAFE_DELETE(sprite);
    
    return sprite;
}

AnimationSprite* AnimationSprite::createAnimationSprite(const char* fileName,int columns,int rows)
{
    return createAnimationSprite(fileName, columns, rows,columns * rows);
}

AnimationSprite* AnimationSprite::createAnimationSprite(CCTexture2D* texture,int columns,int rows)
{
    return createAnimationSprite(texture, columns, rows,columns * rows);
}

AnimationSprite* AnimationSprite::createAnimationSprite(CCTexture2D* texture,int columns,int rows,int totalFrame)
{
    AnimationSprite* bob = new AnimationSprite();
    bob->initAnimationSprite(texture, columns, rows, totalFrame);
    /*
     * 二段世 构造函数
     */
    if (bob && bob->initWithSpriteFrame((CCSpriteFrame*)bob->m_frameArray->objectAtIndex(bob->m_currentIndex))) {
        
        bob->autorelease();
        
        return bob;
    }
    
    CC_SAFE_DELETE(bob);
    
    return NULL;
}

//
//
// 只执行一次，执行完毕后调用回调方法
void AnimationSprite::animation(float duration,CCCallFuncN* callFunN)
{
    // 先判断是否有action,如果有则先删除 再创建
    CCAction* action = (CCAction*)getActionManager()->getActionByTag(kTagSpriteAnimation,this);
    
    if (action) {
        getActionManager()->removeAction(action);
    }
    
    /* 这里面的实现方式有几种,可以使用action来实现，也可以利用schedule来实现 */
    CCAnimation* pAnimation = CCAnimation::createWithSpriteFrames(m_frameArray,duration);
    
    CCAnimate* mAnimate = CCAnimate::create(pAnimation);
    
    //  只执行一次，就将自己删除
    CCCallFunc* mCallFunc = CCCallFunc::create(this,callfunc_selector(AnimationSprite::executeOnceAnimationCallback));

    CCActionInterval* seqAction = (CCActionInterval*)CCSequence::create(mAnimate,callFunN,mCallFunc,NULL);
    
    seqAction->setTag(kTagSpriteAnimation);
    
    runAction(seqAction);
}


void AnimationSprite::animation(float duration,bool forever /* default is true */)
{
    
    // 先判断是否有action,如果有则先删除 再创建
    CCAction* action = (CCAction*)getActionManager()->getActionByTag(kTagSpriteAnimation,this);
    
    if (action) {
        getActionManager()->removeAction(action);
    }
    
    /* 这里面的实现方式有几种,可以使用action来实现，也可以利用schedule来实现 */
    CCAnimation* pAnimation = CCAnimation::createWithSpriteFrames(m_frameArray,duration);
    
    CCAnimate* mAnimate = CCAnimate::create(pAnimation);
    
    if (forever) {
        
        CCAction* repeatAction = CCRepeatForever::create(mAnimate);
        
        repeatAction->setTag(kTagSpriteAnimation);
        
        runAction(repeatAction);
    }else
    {
        //  只执行一次，就将自己删除
        
        CCCallFunc* mCallFunc = CCCallFunc::create(this,callfunc_selector(AnimationSprite::executeOnceAnimationCallback));
        CCActionInterval* seqAction = (CCActionInterval*)CCSequence::create(mAnimate,mCallFunc,NULL);

        seqAction->setTag(kTagSpriteAnimation);
        
        runAction(seqAction);
    }
}


void AnimationSprite::executeOnceAnimationCallback()
{
    this->removeFromParentAndCleanup(true);
}

void AnimationSprite::pauseAnimation()
{    
    getActionManager()->pauseTarget(this);
}

void AnimationSprite::resumeAnimation()
{
    getActionManager()->resumeTarget(this);
}

