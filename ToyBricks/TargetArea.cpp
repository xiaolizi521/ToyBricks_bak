//
//  TargetArea.cpp
//  ToyBricks
//
//  Created by user on 13-4-6.
//
//

#include "TargetArea.h"
#include "Config.h"
#include "Util.h"
#include "GameResources.h"

TargetArea::TargetArea():
m_indexX(0),
m_indexY(0),
m_row(0),
m_column(0)
{
    
}


void TargetArea::onEnter()
{
    CCNode::onEnter();
    
    
    CCLog(" [TargetArea::onEnter] m_indexX:%d,m_indexY:%d",m_indexX,m_indexY);
    
    setAnchorPoint(ccp(0, 0));
    setPosition(ccp(40*m_indexX, 40*m_indexY));
    
    for (int i = 0; i < m_row; ++i) {
        for (int j = 0; j < m_column; ++j) {
            CCSprite* sprite = CCSprite::createWithTexture(getMyTexture(c_target_image));
            sprite->setAnchorPoint(ccp(0, 0));
            sprite->setPosition(ccp(i*40,j*40));
            addChild(sprite);
        }
    }
}



void TargetArea::setIndexX(int ix){
    m_indexX = ix;
}
void TargetArea::setIndexY(int iy){
    m_indexY = iy;
}
void TargetArea::setRow(int row){
    m_row = row;
}
void TargetArea::setColumn(int column){
    m_column = column;
}


