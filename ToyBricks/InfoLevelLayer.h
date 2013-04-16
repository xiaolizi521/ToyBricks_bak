//
//  InfoLevelLayer.h
//  ToyBricks
//
//  Created by user on 13-4-10.
//
//

#ifndef __ToyBricks__InfoLevelLayer__
#define __ToyBricks__InfoLevelLayer__

#include <iostream>

#include "cocos2d.h"
using namespace cocos2d;


class LevelScene;
class InfoLevelLayer : public CCLayer
{
    
protected:
    
    LevelScene* m_levelScene;
    
public:
    InfoLevelLayer(LevelScene* levelScene);
    virtual void onEnter();
    virtual ~InfoLevelLayer();
    
    virtual void keyBackClicked();
    //
    void  createPreAndNextPageBtn();
    void prePageBtnClicked();
    void nextPageBtnClicked();
    
    void backBtnClicked();
    
    void setPrePageBtnVisiable(bool flag);
    void setNextPageBtnVisiable(bool flag);
};

#endif /* defined(__ToyBricks__InfoLevelLayer__) */
