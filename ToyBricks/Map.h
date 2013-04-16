//
//  Map.h
//  ToyBricks
//
//  Created by user on 13-4-8.
//
//

#ifndef __ToyBricks__Map__
#define __ToyBricks__Map__

#include <iostream>

#include "cocos2d.h"
using namespace cocos2d;
class Model;


const static int kZORDER_BACK_MORDEL = 3;
const static int kZORDER_TARGETAREA = 1;
const static int kZOREDER_MODEL = 2;

//
//  需要有一个  18 X 16  的格子 
class Map : public CCLayerColor
{
protected:

    Map(int difficult,int level);
    
    int m_difficult;
    int m_level;
    
public:
    
    int m_grid[18][16];
    
public:
    
    virtual ~Map();
    
    static Map* createMap(int difficult,int level);
    
    virtual void onEnter();
    
    // load level data
    void  loadLevelData(const char* fileName);
    void  loadLevelData(int difficult,int level);

    void fillMapGrid(Model* model);
    
    void printMapData();
};

#endif /* defined(__ToyBricks__Map__) */
