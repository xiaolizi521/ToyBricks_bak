//
//  GameScene.h
//  ToyBricks
//
//  Created by user on 13-4-2.
//
//

#ifndef __ToyBricks__GameScene__
#define __ToyBricks__GameScene__

#include <iostream>
#include <vector>
#include "cocos2d.h"
#include "Model.h"
#include "BorderModel.h"
#include "TargetArea.h"
using namespace cocos2d;
using namespace std;

#define Game GameScene::m_game


class Map;
class GameScene : public CCScene
{
private:
    

public:
    
    Map* m_map;
    
    // all bordermodels
    vector<BorderModel*>* m_ModelVector;
    
    // all models
    vector<Model*>* m_mVector;

    // targetArea
    TargetArea* m_targetArea;
    
    int m_difficult;
    int m_level;
    
    GameScene(int difficult,int level);
    
    static GameScene* m_game;
    
    virtual ~GameScene();
    
    virtual void onEnter();
    
    void checkSuccess();
};


#endif /* defined(__ToyBricks__GameScene__) */
