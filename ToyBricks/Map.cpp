//
//  Map.cpp
//  ToyBricks
//
//  Created by user on 13-4-8.
//
//

#include "Map.h"
#include "Config.h"
#include "GameScene.h"
#include "tinyxml.h"
#include "BorderModel.h"


Map::~Map(){}
Map::Map(int difficult,int level):
m_difficult(difficult),
m_level(level)
{
    for (int row = 0; row < 18; ++row) {
        for (int column = 0; column < 16; ++column) {
            m_grid[row][column] = 0;
        }
    }
}

void  Map::loadLevelData(int difficult,int level)
{
    char fileName[30] = {0};
    sprintf(fileName,"levels/chapter_%d/level_%d.xml",difficult,level);
    loadLevelData(fileName);
}

void Map::onEnter()
{
    CCLayerColor::onEnter();
    
    setAnchorPoint(ccp(0, 0));
    
    loadLevelData(Game->m_difficult,Game->m_level);
        
    printMapData();
}

Map* Map::createMap(int difficult,int level)
{
    Map* map = new Map(difficult,level);
    if (map && map->initWithColor(ccc4(0, 0, 0, 0),G_Map_Width, G_Map_Height)) {
        map->autorelease();
        return map;
    }
    CC_SAFE_DELETE(map);
    return NULL;
}


void  Map::loadLevelData(const char* fileName)
{
    const char* filePath = CCFileUtils::sharedFileUtils()->fullPathFromRelativePath(fileName);
    unsigned long size;
    char *pFileContent = (char*)CCFileUtils::sharedFileUtils()->getFileData(filePath , "r", &size);

    TiXmlDocument* myDocument = new TiXmlDocument;
    myDocument->Parse(pFileContent,0,TIXML_ENCODING_UTF8);

    int data[25] = {0};
    
    TiXmlElement* rootElement = myDocument->RootElement();  // root
    
    TiXmlElement* modelsElement = rootElement->FirstChildElement();  // models
    
    TiXmlElement* modElement = modelsElement->FirstChildElement(); // model
    
    CCLog("开始解析.............");
    int color = 0;
    
    while (modElement) {
        
        BorderModel* borderModel = new BorderModel;
        borderModel->setAnchorPoint(ccp(0, 0));
        
        TiXmlAttribute* indexAttribute = modElement->FirstAttribute();  //获得model的indexX属性
        while ( indexAttribute ) {
            
            CCLog("name:%s ; value:%s",indexAttribute->Name(),indexAttribute->Value());
            
            if (strcmp(indexAttribute->Name(),"indexX") == 0) {
                borderModel->setIndexX(atoi(indexAttribute->Value()));
            }else if (strcmp(indexAttribute->Name(),"indexY") == 0)
            {
                borderModel->setIndexY(atoi(indexAttribute->Value()));
            }else if(strcmp(indexAttribute->Name(),"backIndex") == 0)
            {
                borderModel->setBackIndex(atoi(indexAttribute->Value()));
            }else if (strcmp(indexAttribute->Name(),"transform") == 0)
            {
                borderModel->setTransformIndex(atoi(indexAttribute->Value()));
            }
            
            indexAttribute = indexAttribute->Next();
        }
        
        const char* charArr = modElement->GetText();
        
        for (int i = 0; i < 25; i++) {
            data[i] = charArr[i] - 48;
        }
        
        borderModel->setArray(data, 25);
        borderModel->setColor(color);
        
        Model* mMod = borderModel->createCustomModel();
        addChild(mMod,1);
        addChild(borderModel,kZOREDER_MODEL);
        
        ++color;
        if (color >= 7) {
            color = 0;
        }
        
        // 填充 map
        fillMapGrid(mMod);
        
        Game->m_ModelVector->push_back(borderModel);
        Game->m_mVector->push_back(mMod);
        
        CCLog("%s",modElement->GetText());
        
        modElement = modElement->NextSiblingElement();
    }
    
    
    //-----------  targetArea ----------解析
    TiXmlElement* targetAreaElement = modelsElement->NextSiblingElement();  // targetArea
    
    Game->m_targetArea = new TargetArea;
    
    //  targetArea 属性
    TiXmlAttribute* attr = targetAreaElement->FirstAttribute();
    
    while (attr) {
        
        CCLog("name:%s;value:%s",attr->Name(),attr->Value());
        if (strcmp(attr->Name(), "indexX") == 0) {
            Game->m_targetArea->setIndexX(atoi(attr->Value()));
        }else if(strcmp(attr->Name(),"indexY") == 0)
        {
            Game->m_targetArea->setIndexY(atoi(attr->Value()));
        }
        
        attr = attr->Next();
    }
    
    
    // 再获得  targetArea child
    TiXmlElement* childElement = targetAreaElement->FirstChildElement();
    while (childElement) {
        
        CCLog("name:%s;value:%s",childElement->Value(),childElement->GetText());
        
        if (strcmp(childElement->Value(),"row")) {
            Game->m_targetArea->setRow(atoi(childElement->GetText()));
        }else if(strcmp(childElement->Value(),"column"))
        {
            Game->m_targetArea->setColumn(atoi(childElement->GetText()));
        }
        
        childElement = childElement->NextSiblingElement();
    }
    
    addChild(Game->m_targetArea,kZORDER_TARGETAREA);
    
    delete myDocument;
    
    CCLog(" [.........................] ");
}


void Map::fillMapGrid(Model* model)
{
    int startX = model->getIndexX();
    int startY = model->getIndexY();
    int* array = model->getArray();
    
    int count = 0;
    for (int i = 0; i < 25; ++i) {
        if (array[i]  == 1) {
            int row = i/5;
            int column = i%5;
            m_grid[startY+row][startX+column] = 1;
            model->setArrayInMapIndex(count,(startY+row)*16 + (startX+column) );
            ++count;
        }
    }
}

void Map::printMapData()
{
    cout << "-----------------------------------" << endl;
    for (int i = 17; i >= 0; i--) {
        for (int j = 0; j < 16; ++j) {
            cout << m_grid[i][j];
        }
        cout << endl;
    }
}