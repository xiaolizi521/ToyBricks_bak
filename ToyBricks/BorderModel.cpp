//
//  BorderModel.cpp
//  ToyBricks
//
//  Created by user on 13-4-15.
//
//

#include "BorderModel.h"
#include "GameResources.h"
#include "RotateSprite.h"
#include "GameScene.h"
#include "Map.h"

BorderModel::BorderModel():
m_transformIndex(0),
m_backIndex(0)
{
    
}

BorderModel::~BorderModel()
{
    
}

void BorderModel::onEnter()
{
    Model::onEnter();
    
    setAnchorPoint(ccp(0, 0));
    
    addBorder();
    
}

void BorderModel::addBorder(){
    
    if (m_backIndex <= 0 || m_transformIndex <= 0) {
        return;
    }
    
    CCLog("m_transformIndex:%d",m_transformIndex);
    
    RotateSprite* border = RotateSprite::createRotateSprite(back_names[m_backIndex-1].c_str());
    border->setPosition(ccp(100, 100));
    border->setAnchorPoint(ccp(0, 0));
    addChild(border,10);
    transform(m_transformIndex, border);
}

void BorderModel::transform(int tIndex,CCSprite* sprite)
{
    //  total eight transform
    if (tIndex == 2) {
        sprite->setRotation(90);
    }else if (tIndex == 3)
    {
        sprite->setRotation(180);
    }else if(tIndex == 4)
    {
        sprite->setRotation(270);
    }else if (tIndex == 5)
    {
        sprite->setFlipY(true);
    }else if (tIndex == 6)
    {
        sprite->setRotation(-90);
        sprite->setFlipY(true);
    }else if (tIndex == 7)
    {
        sprite->setRotation(180);
        sprite->setFlipY(true);
    }else if (tIndex == 8)
    {
        sprite->setRotation(90);
        sprite->setFlipY(true);
    }
}

Model* BorderModel::createCustomModel()
{
    Model* model = new Model;
    model->setIndexX(m_indexX);
    model->setIndexY(m_indexY);
    model->setColor(m_color);
    model->setArray(m_array, 25);
    model->setBorthor(this);
    return model;
}

bool BorderModel::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    return false;
}

void BorderModel::moveToDir(int dir)
{

}

void BorderModel::moveToPropPosition()
{
   // int xy[2] = {getPositionX(),getPositionY()};
    if (isRepeadWithMapArray()) {
        
        m_indexX = m_preIndexX;
        m_indexY = m_preIndexY;
        
        setPosition(m_indexX*40,m_indexY*40);
        
     //   int dir = getDirection(xy);
     //   moveToDir(dir);
        
    }else
    {
        m_preIndexX = m_indexX;
        m_preIndexY = m_indexY;
        setPosition(m_indexX*40, m_indexY*40);
//        m_collisionBox.origin.x = m_indexX*40;
//        m_collisionBox.origin.y = m_indexY*40;
    }
}
