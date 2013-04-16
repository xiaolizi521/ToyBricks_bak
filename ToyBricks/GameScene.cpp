//
//  GameScene.cpp
//  ToyBricks
//
//  Created by user on 13-4-2.
//
//

#include "GameScene.h"
#include "TargetArea.h"
#include "GameResources.h"
#include "Map.h"
#include "Controller.h"
#include "SuccessLayer.h"

GameScene* GameScene::m_game = NULL;

GameScene::GameScene(int difficult,int level):
m_difficult(difficult),
m_targetArea(NULL),
m_level(level)
{
    m_ModelVector = new vector<BorderModel*>;
    m_mVector = new vector<Model*>;
    m_game = this;
}

GameScene::~GameScene()
{
    // release models
    vector<BorderModel*>::iterator it = m_ModelVector->begin();
    while (it!=m_ModelVector->end()) {
        BorderModel* model = (*it);
        CC_SAFE_DELETE(model);
        ++it;
    }
    
    
    //release m_ModelVector
    CC_SAFE_DELETE(m_ModelVector);
    
    
    // ~[ release normal models]
    vector<Model*>::iterator vIt = m_mVector->begin();
    while (vIt!=m_mVector->end()) {
        Model* model = (*vIt);
        CC_SAFE_DELETE(model);
        ++vIt;
    }
    CC_SAFE_DELETE(m_mVector);
    //-------------------------------
    
    // release targetArea
    CC_SAFE_DELETE(m_targetArea);
    
    // safe release map
    CC_SAFE_RELEASE(m_map);
}

void GameScene::onEnter()
{
    CCScene::onEnter();
    
    CCSprite* bgSprite = CCSprite::createWithTexture(getMyTexture(c_gamebg));
    bgSprite->setAnchorPoint(ccp(0, 0));
    addChild(bgSprite);
    
    // add map
    m_map = Map::createMap(m_difficult,m_level);
    m_map->retain();
    m_map->setAnchorPoint(ccp(0, 0));
    m_map->setPosition(ccp(0, 80));
    addChild(m_map);
    
    // add game title
    
    
    
    // add Level Title  and button
    Controller* controllerLayer = new Controller;
    controllerLayer->autorelease();
    addChild(controllerLayer);

}

void GameScene::checkSuccess()
{
    int tX = m_targetArea->getIndexX();
    int tY = m_targetArea->getIndexY();
    int sum = 0;
    for (int i = 0; i < tX; ++i) {
        for (int j = 0; j < tY; ++j) {
            sum += m_map->m_grid[tY + i][tX + j];
        }
    }
    
    if(sum == m_targetArea->getRow() * m_targetArea->getColumn())
    {
        CCLog(" ---- 游戏过关 !!----");
        SuccessLayer* pLayer = new SuccessLayer;
        pLayer->autorelease();
        
        addChild(pLayer,100);
    }
}

