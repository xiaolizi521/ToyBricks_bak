//
//  ButtonSprite.cpp
//  Zuma_V4
//
//  Created by user on 13-1-28.
//
//

#include "ButtonSprite.h"

/**********************************************
            构造函数和析构函数
 **********************************************/
ButtonSprite::ButtonSprite():
m_isDown(false),
m_selectorTarget(NULL)
{
    m_touchPriority = 0;
    m_BtnClick_Func = 0;
}
ButtonSprite::~ButtonSprite(){};


void ButtonSprite::onEnter(){
    CCSprite::onEnter();
    
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,m_touchPriority, true);
};
void ButtonSprite::onExit(){
    CCSprite::onExit();
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
};


bool ButtonSprite::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent){
    CCPoint touchPoint = getParent()->convertTouchToNodeSpace(pTouch);
    if (boundingBox().containsPoint(touchPoint) && !m_isDown && isVisible()) {
        m_isDown = true;
        return true;
    }
    
    return false;
};
// optional

void ButtonSprite::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent){
    
    CCPoint touchPoint = getParent()->convertTouchToNodeSpace(pTouch);

    float deltaX = pTouch->getDelta().x;
    
    deltaX = deltaX > 0 ? deltaX : -deltaX;
    
    if (!boundingBox().containsPoint(touchPoint)  || !m_isDown || deltaX > 15) {
        m_isDown = false;
        return;
    }
    
};
void ButtonSprite::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent){
    CCPoint touchPoint = getParent()->convertTouchToNodeSpace(pTouch);
    if (boundingBox().containsPoint(touchPoint) && m_isDown) {
        /* 相当于产生了click事件 */
        if (m_BtnClick_Func) {
            //来个点击效果
            CCActionInterval* sAction = CCScaleTo::create(0.06, 1.2);
            CCActionInterval* sAction2 = CCScaleTo::create(0.06, 1);
            CCCallFunc*  callFun = CCCallFunc::create(this,callfunc_selector(ButtonSprite::clicked));
            runAction(CCSequence::create(sAction,sAction2,callFun,NULL));

        }
        m_isDown = false;
    }
};


void ButtonSprite::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent){
    m_isDown = false;
};

ButtonSprite* ButtonSprite::createButtonSprite(const char* fileName,int tPriority)
{
    ButtonSprite* button  = new ButtonSprite();
    button->m_touchPriority = tPriority;
    if (button && button->initWithFile(fileName)) {
        button->autorelease();
        return button;
    }
    CC_SAFE_DELETE(button);
    return button;
}

ButtonSprite* ButtonSprite::createButtonSprite(CCTexture2D* texture,int tPriority)
{
    ButtonSprite* button  = new ButtonSprite();
    button->m_touchPriority = tPriority;
    if (button && button->initWithTexture(texture)) {
        button->autorelease();
        return button;
    }
    CC_SAFE_DELETE(button);
    return button;
}


ButtonSprite* ButtonSprite::createButtonSpriteWithSpriteFrame(CCSpriteFrame *pSpriteFrame,int tPriority)
{
    ButtonSprite *pobSprite = new ButtonSprite();
    pobSprite->m_touchPriority = tPriority;
    if (pSpriteFrame && pobSprite && pobSprite->initWithSpriteFrame(pSpriteFrame))
    {
        pobSprite->autorelease();
        return pobSprite;
    }
    CC_SAFE_DELETE(pobSprite);
    return NULL;
}

//
// update
void ButtonSprite::setOnClickListener(CCObject* target,ButtonClick_Func tBtnClickFunc)
{
    m_BtnClick_Func = tBtnClickFunc;
    m_selectorTarget = target;
}

void ButtonSprite::clicked()
{
    (m_selectorTarget->*m_BtnClick_Func)();
}
