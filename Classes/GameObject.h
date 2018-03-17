//
//  GameObject.h
//  SlideBlock
//
//  Created by Hoang Nguyen on 11/29/16.
//
//

#ifndef GameObject_h
#define GameObject_h

#include <stdio.h>
#include "cocos2d.h"
USING_NS_CC;

class GameObject: public Sprite
{
private:
    Vec2 headPosition;
    Vec2 lastPosition;
    Vec2 position;
    int typeDirector;
    int typeSpace;
    
    Vec2 headMaxtrix;
    Vec2 lastMaxtrix;
    int lenghtObject;
    int heightObject;
    bool isMoveSloved;
    
    int identifer;
public:
    GameObject();
    virtual ~GameObject();
    void setHeadAndLastPosion(const Vec2& head, const Vec2& last);
    void setPostionWithGameObject();
    void createWithFileName(const char* fileName);
    void setHeadAndPosMaxtrix(const Vec2& headMaxtrix, const Vec2& lastMaxtrix);
    void movePostion(const Vec2& positon, const Vec2& newheadMaxtrix, const Vec2& newLastMaxtrix);
    Vec2 getLastMaxtrix();
    Vec2 getHeadMaxtrix();
    int getLenghtObject();
    int getHeightObject();
    void setTypeSpace(int typeSpace);
    int getTypeSpaceObject();
    void moveGameWin(const Vec2& pos);
    void setDirectorType(int typeDirection);
    int getTypeDirector();
    
    bool getMovedSloved();
    void setStatusMoveSloved(bool isSloved);
    
    void setIndentifer(int identifer);
    int getIdentifer();
};

#endif /* GameObject_h */
