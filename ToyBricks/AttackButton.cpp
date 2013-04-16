//
//  AttackButton.cpp
//  Paopao_Game
//
//  Created by user on 13-2-21.
//
//

#include "AttackButton.h"

AttackButton::AttackButton():
m_BtnClick_Func(NULL),
m_selectorTarget(NULL),
m_enable(true),
m_touchPriority(0)
{
    
}

AttackButton::~AttackButton(){
   
}
void AttackButton::onEnter()
{
    TileSprite::onEnter();
    
    // 添加触摸相关
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, m_touchPriority, true);
    
}

void AttackButton::onExit()
{
    TileSprite::onExit();
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
    
}

bool AttackButton::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    if (!m_enable) {
        
        //
        return false;
    }
    
    
    CCPoint touchPoint = getParent()->convertTouchToNodeSpace(pTouch);
    if (boundingBox().containsPoint(touchPoint)) {
        if (m_BtnClick_Func) {
            this->setCurrentIndex(1);
            (m_selectorTarget->*m_BtnClick_Func)();
        }
        
        return true;
    }
    return false;
}

void AttackButton::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent){
    
}
void AttackButton::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent){
    
    if (m_enable) {
         this->setCurrentIndex(0);
    }else
    {
        this->setCurrentIndex(2);
    }
}
void AttackButton::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent){
    if (m_enable) {
        this->setCurrentIndex(0);
    }else
    {
        this->setCurrentIndex(2);
    }
}


void AttackButton::setOnClickListener(CCObject* target,ButtonClick_Func tButtonClick_Func)
{
    m_BtnClick_Func = tButtonClick_Func;
    m_selectorTarget = target;
}



//
//
//  create
AttackButton* AttackButton::createAttackButton(const char* fileName, int columns, int rows,int touchPriority)
{
    AttackButton* bob = new AttackButton();
    bob->m_touchPriority = touchPriority;
    bob->tileSpriteInit(fileName, columns, rows);
    
    if (bob && bob->initWithSpriteFrame((CCSpriteFrame*)bob->m_frameArray->objectAtIndex(bob->m_currentIndex))) {
        bob->autorelease();
        return bob;
    }
    CC_SAFE_DELETE(bob);
    return bob;
}
AttackButton* AttackButton::createAttackButton(CCTexture2D* texture, int columns, int rows,int touchPriority)
{
    AttackButton* bob = new AttackButton();
    bob->m_touchPriority = touchPriority;
    bob->tileSpriteInit(texture, columns, rows);
    
    if (bob && bob->initWithSpriteFrame((CCSpriteFrame*)bob->m_frameArray->objectAtIndex(bob->m_currentIndex))) {
        bob->autorelease();
        return bob;
    }
    CC_SAFE_DELETE(bob);
    return bob;
}


void AttackButton::setEnable(bool flag)
{
    m_enable = flag;
    
    if (!m_enable) {
        
        // 显示第三帧
        setCurrentIndex(2);
    }else
    {
        // 显示第一帧
        setCurrentIndex(0);
    }
        
}

