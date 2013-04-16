//
//  SuccessLayer.cpp
//  ToyBricks
//
//  Created by user on 13-4-10.
//
//

#include "SuccessLayer.h"
#include "Util.h"
#include "GameResources.h"
#include "Config.h"
#include "ButtonSprite.h"
#include "MainMenu.h"
#include "GameScene.h"
#include "Chapter.h"

void SuccessLayer::onEnter()
{
    CCLayer::onEnter();
    
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, kCCMenuHandlerPriority, true);
    
    //  Translucent effect
    CCLayerColor* bg = CCLayerColor::create(ccc4(0, 0, 0, 128), G_width, G_height);
    addChild(bg);
    
    // set a dialog bg
    CCSprite* dialogBg = CCSprite::create("successDialogBg.png");
    dialogBg->setPosition(ccp(G_width/2, G_height/2));
    addChild(dialogBg);
    
    
    // 加上三个按钮
//    ButtonSprite* homeBtn = ButtonSprite::createButtonSprite(getMyTexture(c_dialog_home));
//    homeBtn->setPosition(ccp(105, G_height/2));
//    homeBtn->setOnClickListener(this,click_selector(SuccessLayer::homeBtnClicked));
//    addChild(homeBtn);

    CCMenuItemImage* homeBtn = CCMenuItemImage::create("dialoghome.png","dialoghomeSelected.png", this, menu_selector(SuccessLayer::homeBtnClicked));
    homeBtn->setPosition(ccp(178, 437));
    
    
    // reset button
//    ButtonSprite* resetBtn = ButtonSprite::createButtonSprite(getMyTexture(c_dialog_reset));
//    resetBtn->setPosition(ccp(320, G_height/2));
//    resetBtn->setOnClickListener(this, click_selector(SuccessLayer::resetBtnClicked));
//    addChild(resetBtn);

    CCMenuItemImage* resetBtn = CCMenuItemImage::create("dialogreset.png", "dialogresetSelected.png", this,menu_selector(SuccessLayer::resetBtnClicked));
    resetBtn->setPosition(ccp(320,437));
    
    // next button
//    ButtonSprite* nextBtn = ButtonSprite::createButtonSprite(getMyTexture(c_dialog_next));
//    nextBtn->setPosition(ccp(530, G_height/2));
//    nextBtn->setOnClickListener(this,click_selector(SuccessLayer::nextBtnClicked));
//    addChild(nextBtn);
    
    CCMenuItemImage* nextBtn = CCMenuItemImage::create("dialogNextLevel.png", "dialogNextLevelSelected.png", this, menu_selector(SuccessLayer::nextBtnClicked));
    nextBtn->setPosition(ccp(464, G_height/2));
    
    CCMenu* pMenu = CCMenu::create(homeBtn,resetBtn,nextBtn,NULL);
    pMenu->setPosition(ccp(0, 0));
    addChild(pMenu);
}


void SuccessLayer::homeBtnClicked(){
    CCLog(" [homeBtnClicked] ");
    CCScene* pScene = CCScene::create();
    
    MainMenu* pLayer = new MainMenu;
    pLayer->autorelease();
    
    pScene->addChild(pLayer);
    
    CCDirector::sharedDirector()->replaceScene(pScene);
}
void SuccessLayer::resetBtnClicked(){
        CCLog(" [resetBtnClicked] ");
    GameScene* pScene = new GameScene(Game->m_difficult,Game->m_level);
    pScene->autorelease();
    
    CCDirector::sharedDirector()->replaceScene(pScene);
}
void SuccessLayer::nextBtnClicked(){
     CCLog(" [nextBtnClicked] ");
    
    int totalLevelCount = getTotalCount(Game->m_difficult);
    
    if (Game->m_level >= totalLevelCount) {
        // jump to chapter scene
        CCScene* pScene = CCScene::create();
        Chapter* pLayer = new Chapter;
        pLayer->autorelease();
        pScene->addChild(pLayer);
        CCDirector::sharedDirector()->replaceScene(pScene);
    }else
    {
        ++Game->m_level;
        GameScene* pScene = new GameScene(Game->m_difficult,Game->m_level);
        pScene->autorelease();
        CCDirector::sharedDirector()->replaceScene(pScene);
    }
}

bool SuccessLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    return true;
}