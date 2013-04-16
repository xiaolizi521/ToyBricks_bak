//
//  LevelLayer.h
//  ToyBricks
//
//  Created by user on 13-4-9.
//
//

#ifndef __ToyBricks__LevelLayer__
#define __ToyBricks__LevelLayer__

#include <iostream>
#include "cocos2d.h"
#include <vector>
using namespace cocos2d;
using namespace std;

const static int kRow = 7;
const static int kColumn = 5;
const static int kCountOfPage = kRow*kColumn;


class LevelItemSprite;
class LevelLayer : public CCLayer
{
protected:
    
    int m_firstLevel;
    vector<LevelItemSprite*> m_levelItemVector;
    
  //  ccColor4B m_Bgcolor;
    
    int m_totalLevelCount;
public:
    LevelLayer(int totalLevel);
    virtual void onEnter();
    virtual ~LevelLayer();
    
    // the up layer,use can see;
    bool m_showingLayer;
    
    //
    void loadPage();
    void setFirstLevel(int level);
    
    void levelItemClicked(CCObject* obj,void* param);

  //  void setBg(ccColor4B color){m_Bgcolor = color;}
};



#endif /* defined(__ToyBricks__LevelLayer__) */
