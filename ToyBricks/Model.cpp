//
//  Model.cpp
//  ToyBricks
//
//  Created by user on 13-4-2.
//
//

#include "Model.h"
#include "Config.h"
#include "GameScene.h"
#include "Map.h"
#include <cmath>
#include "BorderModel.h"

const static string kFileNameArray[] = {
    c_s1,
    c_s2,
    c_s3,
    c_s4,
    c_s5,
    c_s6,
    c_s7
};





Model::Model():
m_maxX(0),
m_minX(0),
m_maxY(0),
m_minY(0),
m_length(0),
m_preIndexX(0),
m_preIndexY(0),
m_arrayInMapArray(NULL),
m_borthor(NULL),
m_color(0)
{
    for (int i = 0; i < 25; i++) {
        m_array[i] = 0;
    }
    m_collisionBox = CCRectMake(0, 0, 200, 200);
}

Model::~Model()
{
    delete [] m_arrayInMapArray;
}


void Model::onEnter()
{
    CCNode::onEnter();
    
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0,true);
    
    
    //   setAnchorPoint(ccp(0, 0));
    setPosition(ccp(40*m_indexX,m_indexY*40));
    
    m_collisionBox.origin.x = 40*m_indexX;
    m_collisionBox.origin.y = m_indexY*40;
    
    
    m_preIndexX = m_indexX;
    m_preIndexY = m_indexY;
    
    //  compute bounds
    computeBounds();
    
    
    for (int i = 0; i < 25; ++i) {
        int row = i/5;
        int column = i%5;
        
        if (m_array[i] == 1) {
            ++m_length;
            
            CCSprite* sprite = CCSprite::createWithTexture(getMyTexture(kFileNameArray[m_color].c_str()));
            sprite->setAnchorPoint(ccp(0, 0));
            sprite->setPosition(ccp(column*40,row*40));
            addChild(sprite);
            
            m_rectVec.push_back(sprite->boundingBox());
        }else
        {
            //            CCSprite* sprite = CCSprite::createWithTexture(getMyTexture(c_shadow_bg));
            //            sprite->setAnchorPoint(ccp(0, 0));
            //            sprite->setPosition(ccp(column*40,row*40));
            //            addChild(sprite);
        }
    }
    
    m_arrayInMapArray = new int[m_length];
    
}



void Model::computeBounds()
{
    
    //---- minY
    int row = 0;
    int sum = 0;
    while (row < 5) {
        
        sum = 0;
        for (int column = 0; column < 5; ++column) {
            sum += m_array[row*5 + column];
        }
        
        if (sum > 0) {
            break;
        }
        ++row;
    }
    
    if (row >= 5) {
        CCLog("-------  found Error!!! -----");
        return;
    }
    
    m_minY = -row*40;
    
    //----- maxY
    row = 4;
    while (row >= 0) {
        sum = 0;
        for (int column = 0; column < 5; ++column) {
            sum += m_array[row*5+column];
        }
        
        if (sum > 0) {
            break;
        }
        
        --row;
    }
    
    if (row < 0) {
        CCLog("---- Error!!!");
    }
    
    m_maxY = G_Map_Height - 200 + (4 - row)*40;
    
    //----- minX
    int column = 0;
    while (column < 5) {
        sum = 0;
        for (int r = 0; r < 5; ++r) {
            sum += m_array[r*5 + column];
        }
        
        if (sum > 0) {
            break;
        }
        
        ++column;
    }
    
    if (column >= 5) {
        CCLog("Error!!!");
    }
    
    m_minX = -column*40;
    
    //----maxX
    column = 4;
    while (column >= 0) {
        sum = 0;
        for (int r = 0; r< 5; ++r) {
            sum += m_array[r*5 + column];
        }
        
        if (sum > 0) {
            break;
        }
        --column;
    }
    
    m_maxX = G_Map_Width - 200 + ( 4 - column)*40;
    
    //--------------
    // print Log
    //CCLog("m_minX:%d,m_maxX:%d,m_minY:%d,m_maxY:%d",m_minX,m_maxX,m_minY,m_maxY);
    
}


int* Model::getArray()
{
    return m_array;
}

vector<CCRect>* Model::getRectVec()
{
    return &m_rectVec;
}


bool Model::isTouched(float x,float y)
{
    CCPoint point = ccp(x, y);
    
    return isTouched(point);
}

bool Model::isTouched(const CCPoint& point)
{
    vector<CCRect>::iterator it = m_rectVec.begin();
    while (it!=m_rectVec.end()) {
        CCRect rect = (*it);
        if (rect.containsPoint(point)) {
            return true;
        }
        ++it;
    }
    return false;
}


void Model::setIndexX(int ix){
    m_indexX = ix;
}
void Model::setIndexY(int iy){
    m_indexY = iy;
}


void Model::setArray(int* p, int length)
{
    for (int i=0; i < length; ++i) {
        m_array[i] = p[i];
    }
}

void Model::debugPrint()
{
    for (int i=0; i<25; ++i) {
        cout << m_array[i];
    }
    cout << endl;
}

void Model::printPosition()
{
    cout << "x:" << getPositionX() << "; y :" << getPositionY() << endl;
}


void Model::onExit()
{
    CCNode::onExit();
    
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
}

CCRect Model::getCollisionBox() const
{
    return m_collisionBox;
}

//--------------------- CCTouchDelegate
bool Model::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent){
    
    CCPoint touchPoint = getParent()->convertTouchToNodeSpace(pTouch);
    
    CCPoint relativePoint = convertTouchToNodeSpace(pTouch);
    
    if (m_collisionBox.containsPoint(touchPoint)) {
        if (isTouched(relativePoint)) {
            
           // setScale(1.05);
            
            getParent()->reorderChild(this,getZOrder()+5);
            
            return true;
        }
    }
    
    return false;
}
// optional

void Model::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent){
    
    CCPoint  deltaPoint = pTouch->getDelta();
    CCPoint cp = getPosition();
    
    // can not over bounds
    if (cp.x + deltaPoint.x <= m_minX) {
        
        setPositionX(m_minX);
        
    }else if(cp.x + deltaPoint.x >= m_maxX)
    {
        setPositionX(m_maxX);
        
    }else
    {
        setPositionX(cp.x + deltaPoint.x);
    }
    
    if (cp.y + deltaPoint.y <= m_minY) {
        setPositionY(m_minY);
    }else if (cp.y + deltaPoint.y >= m_maxY)
    {
        setPositionY(m_maxY);
    }else
    {
        setPositionY(cp.y + deltaPoint.y);
    }
    
    
    //  we will compute the prop position
    setBortherPropPosition();
}

void Model::setBortherPropPosition()
{
    int xy[2] = {0};
    getResultXY(xy, getPositionX(), getPositionY());
    
    if (m_borthor) {
        m_borthor->setPosition(xy[0],xy[1]);
        m_borthor->m_indexX = xy[0] / 40;
        m_borthor->m_indexY = xy[1] / 40;
        
        m_borthor->moveToPropPosition();
        
//        
//        // 先将之前在 mapArray里面的设置成-1
//        for (int i = 0; i < m_length; ++i) {
//            
//            int pRow = m_borthor->m_arrayInMapArray[i]/16;
//            int pColumn = m_borthor->m_arrayInMapArray[i]%16;
//            
//            Game->m_map->m_grid[pRow][pColumn] = 0;
//        }
//        
//        if (m_borthor->isRepeadWithMapArray()) {
//            int dir = m_borthor->getDirection(xy);
//            m_borthor->moveToDir(dir);
//        }
    }
}

void Model::setPropPosition()
{
#if 0
    //need to set prop  x y, m_collisionBox
    int xy[2] = {0};
    getResultXY(xy, getPositionX(), getPositionY());
    
    setPosition(ccp(xy[0], xy[1]));
    m_collisionBox.origin.x = xy[0];
    m_collisionBox.origin.y = xy[1];
    
    m_indexX = xy[0] / 40;
    m_indexY = xy[1] / 40;
    
    
    // 先将之前在 mapArray里面的设置成 0
    for (int i = 0; i < m_length; ++i) {
        
        int pRow = m_arrayInMapArray[i]/16;
        int pColumn = m_arrayInMapArray[i]%16;
        
        Game->m_map->m_grid[pRow][pColumn] = 0;
    }
    
    // Two box can not be coincidence
    // 先检查现在的位置是否已经有了square
    if (isRepeadWithMapArray()) {
        //   如果重复了
        CCLog("重复了，需要重新计算位置......");
        
        int dir = getDirection(xy);
        
        CCLog("dir:%d",dir);
        
        moveToDir(dir);
        
    }else
    {
        afterMove();
    }
    
    getParent()->reorderChild(this,kZOREDER_MODEL);
    Game->checkSuccess();
#endif
    
    setPosition(m_borthor->getPosition());
    m_indexX = m_borthor->m_indexX;
    m_indexY = m_borthor->m_indexY;
    m_preIndexX = m_indexX;
    m_preIndexY = m_indexY;
    
    // 先将之前在 mapArray里面的设置成 0
    for (int i = 0; i < m_length; ++i) {
        
        int pRow = m_arrayInMapArray[i]/16;
        int pColumn = m_arrayInMapArray[i]%16;
        
        Game->m_map->m_grid[pRow][pColumn] = 0;
    }
    
    Game->m_map->fillMapGrid(this);
    m_collisionBox.origin.x = m_indexX*40;
    m_collisionBox.origin.y = m_indexY*40;
    
    getParent()->reorderChild(this,kZOREDER_MODEL);
    getParent()->reorderChild(m_borthor, kZORDER_BACK_MORDEL);
    Game->checkSuccess();
}

void Model::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent){
    
  //  setScale(1);
    setPropPosition();
}

void Model::afterMove()
{
    Game->m_map->fillMapGrid(this);
    m_preIndexX = m_indexX;
    m_preIndexY = m_indexY;
    
    setPosition(m_indexX*40, m_indexY*40);
    m_collisionBox.origin.x = m_indexX*40;
    m_collisionBox.origin.y = m_indexY*40;
}


void Model::restorePre()
{
    m_indexX = m_preIndexX;
    m_indexY = m_preIndexY;
    
    
    setPosition(ccp(m_indexX*40, m_indexY*40));
    
    m_collisionBox.origin.x = m_indexX*40;
    m_collisionBox.origin.y = m_indexY*40;
    Game->m_map->fillMapGrid(this);
}

void Model::moveToDir(int dir)
{
    if (dir == kUp) {
        m_indexY++;
        while (isRepeadWithMapArray() && m_indexY <= m_preIndexY) {
            m_indexY++;
        }
        
        if (m_indexY > m_maxY / 40) {
            restorePre();
        }else
        {
            if (isRepeadWithMapArray()) {
                restorePre();
                return;
            }
            afterMove();
        }
    }else if(dir == kDown  && m_indexY >= m_preIndexY )
    {
        m_indexY--;
        while (isRepeadWithMapArray()) {
            --m_indexY;
        }
        
        if (m_indexY < m_minY / 40) {
            restorePre();
        }else
        {
            if (isRepeadWithMapArray()) {
                restorePre();
                return;
            }
            afterMove();
        }
    }else if (dir == kLeft  && m_indexX >= m_preIndexX)
    {
        m_indexX--;
        while (isRepeadWithMapArray()) {
            --m_indexX;
        }
        if (m_indexX < m_minX / 40) {
            restorePre();
        }else
        {
            if (isRepeadWithMapArray()) {
                restorePre();
                return;
            }
            afterMove();
        }
    }else if(dir == kRight && m_indexX <= m_preIndexX)
    {
        m_indexX++;
        while (isRepeadWithMapArray()) {
            m_indexX++;
        }
        
        if (m_indexX > m_maxX / 40) {
            restorePre();
        }else
        {
            if (isRepeadWithMapArray()) {
                restorePre();
                return;
            }
            afterMove();
        }
    }else
    {
        CCLog("那这样就出错了");
    }
}


// this method is very important
int Model::getDirection(int* xy)
{
    // 先计算角度,在角度方向上进行适配位置
    float cosAngle = (xy[0] - m_preIndexX*40)/getDistance(m_preIndexX*40, m_preIndexY*40, xy[0], xy[1]);
    
    // this return value >= 0
    float angle = acosf(cosAngle) *  180 / M_PI ;
    
    if (angle >= 0 ) {
        
        // Y轴右边
        if (angle <= 45) {
            return kLeft;
        }else if(angle >= 135)
        {
            return kRight;
        }else if (xy[1] >= m_preIndexY*40)
        {
            return kDown;
        }else
        {
            return kUp;
        }
        
    }else
    {
        CCLog(" [终于发现 angle < 0 了] ");
        return NULL;
    }
}

bool Model::isRepeadWithMapArray()
{
    bool isRepeat = false;
    for (int i=0; i<25; ++i) {
        int row = i/5;
        int column = i%5;
        if (m_array[i]  == 1 && Game->m_map->m_grid[m_indexY+row][m_indexX + column] == 1) {
            isRepeat = true;
            break;
        }
    }
    return isRepeat;
}


void Model::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent){
    CCLog(" [Model::ccTouchCancelled.........] ");
}

//   reference editor code
void Model::getResultXY(int* result,float reallyX,float reallyY)
{
    int rs = reallyY / 40;
    int cs = reallyX / 40;
    
    int topLeftX = cs * 40;
    int topLeftY = rs * 40;
    
    // 分为 4 个部分
    if(reallyX - topLeftX >= 20)
    {
        // 右边
        if(reallyY - topLeftY >= 20)
        {
            // 右下
            result[0] = topLeftX + 40;
            result[1] = topLeftY + 40;
        }else
        {
            // 右上
            result[0] = topLeftX + 40;
            result[1] = topLeftY;
        }
    }else
    {
        // 左边
        if(reallyY - topLeftY >= 20)
        {
            // 左下
            result[0] = topLeftX;
            result[1] = topLeftY + 40;
        }else
        {
            // 左上
            result[0] = topLeftX;
            result[1] = topLeftY;
        }
    }
}



void Model::setArrayInMapIndex(int index,int mapIndex)
{
    m_arrayInMapArray[index] = mapIndex;
}


