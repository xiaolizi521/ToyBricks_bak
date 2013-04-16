//
//  ChangeableSprite.cpp
//  Zuma_V4
//
//  Created by user on 13-1-23.
//
//

#include "ChangeableSprite.h"

/**************************************************
            构造方法和析构函数
 **************************************************/
ChangeableSprite::ChangeableSprite():
m_selectorTarget(NULL),
m_isDown(false),
m_ButtonClick_Func(NULL),
m_touchPriority(0),
m_currentState(true), //  默认的状态的 true,即为第一帧
m_enable(true)
{
    
};


ChangeableSprite::~ChangeableSprite(){}

ChangeableSprite* ChangeableSprite::createChangeableSprite(const char* fileName,int columns,int rows,int tPriority)
{
    ChangeableSprite* changeableSprite = new ChangeableSprite();
    changeableSprite->m_touchPriority = tPriority;
    
    changeableSprite->tileSpriteInit(fileName, columns, rows);
    
    if (changeableSprite && changeableSprite->initWithSpriteFrame((CCSpriteFrame*)changeableSprite->m_frameArray->objectAtIndex(changeableSprite->m_currentIndex))) {
        
        changeableSprite->autorelease();
        return changeableSprite;
    }
    CC_SAFE_DELETE(changeableSprite);
    return changeableSprite;
}

ChangeableSprite* ChangeableSprite::createChangeableSprite(CCTexture2D* texture,int columns,int rows,int tPriority)
{
    ChangeableSprite* changeableSprite = new ChangeableSprite();
    changeableSprite->m_touchPriority = tPriority;
    
    changeableSprite->tileSpriteInit(texture, columns, rows);
    
    if (changeableSprite && changeableSprite->initWithSpriteFrame((CCSpriteFrame*)changeableSprite->m_frameArray->objectAtIndex(changeableSprite->m_currentIndex))) {
        
        changeableSprite->autorelease();
        return changeableSprite;
    }
    CC_SAFE_DELETE(changeableSprite);
    return changeableSprite;

}


/**************************************************
                重写触屏相关函数----
 **************************************************/
void ChangeableSprite::onEnter()
{
    //注册监听   1.dele类，2.优先级，3.YES为阻碍其他类的move 和 end
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, m_touchPriority, true);
    
    TileSprite::onEnter();
}


// 别忘记加入 TouchDispatcher  ,TouchDispatcher一般放在onenter 绑定，onexit 删除
bool ChangeableSprite::ccTouchBegan(CCTouch* touch, CCEvent* event)
{
    if (!m_enable) {
        return false;
    }
    
    
    CCPoint touchPoint = touch->getLocation();
    
    if (boundingBox().containsPoint(touchPoint)) {
        m_isDown = true;
        return true;
    }
    return false;
}

void ChangeableSprite::ccTouchMoved(CCTouch* touch, CCEvent* event)
{
   CCPoint touchPoint = touch->getLocation();
    if (!boundingBox().containsPoint(touchPoint)  || !m_isDown ) {
        m_isDown = false;
        return;
    }    
}

void ChangeableSprite::ccTouchEnded(CCTouch* touch, CCEvent* event)
{
    CCPoint touchPoint = touch->getLocation();
    if (boundingBox().containsPoint(touchPoint) && m_isDown) {
        /* 相当于产生了click事件 */
        if (m_ButtonClick_Func) {
            
            //来个点击效果
            CCActionInterval* sAction = CCScaleTo::create(0.05, 1.2);
            CCActionInterval* sAction2 = CCScaleTo::create(0.05, 1);
            CCCallFunc*  callFun = CCCallFunc::create(this,callfunc_selector(ChangeableSprite::clicked));
            runAction(CCSequence::create(sAction,sAction2,callFun,NULL)); 
        }
        m_isDown = false;
    }
}

void ChangeableSprite::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent)
{
    m_isDown = false;
}   

void ChangeableSprite::clicked()
{
    setCurrentState(!m_currentState);
    (m_selectorTarget->*m_ButtonClick_Func)();
}


void ChangeableSprite::onExit()
{
    //移除监听
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
    
    TileSprite::onExit();
}

void ChangeableSprite::setCurrentState(bool mState)
{
    m_currentState = mState;
    if (m_currentState) {
        
        setCurrentIndex(0);
    }else
    {
        setCurrentIndex(1);
    }
}

void ChangeableSprite::setOnClickListener(CCObject* target,ButtonClick_Func mCallback)
{
    m_ButtonClick_Func = mCallback;
    m_selectorTarget = target;
}


void ChangeableSprite::setEnable(bool flag)
{
    m_enable = flag;
    if (!flag) {
        
        // 显示为不能点击
        setCurrentIndex(2);
    }
}

