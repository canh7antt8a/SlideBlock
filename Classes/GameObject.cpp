//
//  GameObject.cpp
//  SlideBlock
//
//  Created by Hoang Nguyen on 11/29/16.
//
//

#include "GameObject.h"
#include "GameDefine.h"
#define TIME_RUNACTION 0.05
GameObject::GameObject()
{
    isMoveSloved = false;
}
GameObject::~GameObject()
{
    
}
void GameObject::setHeadAndPosMaxtrix(const Vec2& headMaxtrix, const Vec2& lastMaxtrix)
{
    this->headMaxtrix = headMaxtrix;
    this->lastMaxtrix = lastMaxtrix;
    if(headMaxtrix.x == lastMaxtrix.x)
    {
        typeDirector = VERTICAL;
    }
    else
    {
        typeDirector = HONORITAL;
    }
    
    lenghtObject = lastMaxtrix.x  - headMaxtrix.x;
    heightObject = lastMaxtrix.y - headMaxtrix.y;
}
void GameObject::setStatusMoveSloved(bool isSloved){
    this->isMoveSloved = isSloved;
}
void GameObject::setHeadAndLastPosion(const Vec2& head, const Vec2& last)
{
    this->headPosition = head;
    this->lastPosition = last;
    this->position = head;
}
void GameObject::setPostionWithGameObject()
{
    this->setAnchorPoint(Vec2::ZERO);
    this->setPosition(position);
}
void GameObject::moveGameWin(const Vec2& pos)
{
    auto action1 = MoveTo::create(TIME_RUNACTION*2.0, pos);
    this->runAction(Sequence::create(action1, NULL));
}

void GameObject::createWithFileName(const char* fileName)
{
    Sprite::initWithFile(fileName);
}
Vec2 GameObject::getLastMaxtrix()
{
    return lastMaxtrix;
}
Vec2 GameObject::getHeadMaxtrix()
{
    return headMaxtrix;
}

void GameObject::movePostion(const Vec2& positon, const Vec2& newheadMaxtrix, const Vec2& newLastMaxtrix)
{
    int delta = 0;
    if(newheadMaxtrix.x == this->headMaxtrix.x && newheadMaxtrix.y != this->headMaxtrix.y)
    {
        delta = std::abs(newheadMaxtrix.y - this->headMaxtrix.y);
    }
    if(newheadMaxtrix.y == this->headMaxtrix.y && newheadMaxtrix.x != this->headMaxtrix.x)
    {
         delta = std::abs(newheadMaxtrix.x - this->headMaxtrix.x);
    }
    this->headMaxtrix = newheadMaxtrix;
    this->lastMaxtrix = newLastMaxtrix;
    this->setPosition(positon);
}
void GameObject::setDirectorType(int typeDirection)
{
    this->typeDirector = typeDirection;
}
int GameObject::getLenghtObject()
{
    return lenghtObject;
}
int GameObject::getHeightObject()
{
    return heightObject;
}
void GameObject::setTypeSpace(int typeSpace)
{
    this->typeSpace = typeSpace;
}
int GameObject::getTypeSpaceObject()
{
    return typeSpace;
}

int GameObject::getTypeDirector()
{
    return typeDirector;
}
bool GameObject::getMovedSloved(){
    return isMoveSloved;
}

void GameObject::setIndentifer(int identifer){
    this->identifer = identifer;
}
int GameObject::getIdentifer(){
    return identifer;
}

