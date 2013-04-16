//
//  TileSprite.cpp
//  Zuma_V4
//
//  Created by user on 13-1-19.
//
//

#include "TileSprite.h"

void TileSprite::onEnter()
{
    CCSprite::onEnter();
}


TileSprite::~TileSprite(){
    
    CC_SAFE_RELEASE(m_frameArray);
}

void TileSprite::setCurrentIndex(int mIndex)
{
    m_currentIndex = mIndex;
    setDisplayFrame( (CCSpriteFrame*)m_frameArray->objectAtIndex(mIndex));
}

TileSprite* TileSprite::createTileSprite(const char* fileName,int columns,int rows)
{
    TileSprite* pobSprite = new TileSprite();
    pobSprite->tileSpriteInit(fileName,columns,rows);
    
    if (pobSprite && pobSprite->initWithSpriteFrame((CCSpriteFrame*)pobSprite->m_frameArray->objectAtIndex(pobSprite->m_currentIndex))) {
        pobSprite->autorelease();
        return pobSprite;
    }
    CC_SAFE_DELETE(pobSprite);
    return pobSprite;
}


/*
 * TileSprite 初始化
 */
void TileSprite::tileSpriteInit(const char* fileName,int columns,int rows)
{
    CCTexture2D* texture = CCTextureCache::sharedTextureCache()->addImage(fileName);
  
    tileSpriteInit(texture, columns, rows);
}

void TileSprite::tileSpriteInit(CCTexture2D* texture, int columns, int rows)
{
    m_currentIndex = 0;
    m_frameArray = CCArray::createWithCapacity(columns*rows);
    m_frameArray->retain();
    
    this->m_columns = columns;
    this->m_rows = rows;
    
    CCSize size = texture->getContentSize();
    
    float width = size.width / columns;
    float height = size.height / rows;
    
    // 创建CCSpriteFrame
    for (int i = 0; i < rows; i++) {
        for (int j= 0 ; j <columns; j++) {
            CCSpriteFrame* frame = CCSpriteFrame::createWithTexture(texture, CCRectMake(j*width, i*height, width, height));
            m_frameArray->addObject(frame);
        }
    }
}
