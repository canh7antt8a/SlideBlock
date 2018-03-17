//
//  BFSSildeBlock.h
//  SlideBlock
//
//  Created by Nguyen Chi Hoang on 3/13/17.
//
//

#ifndef BFSSildeBlock_h
#define BFSSildeBlock_h
#include <stdio.h>
#include "GameBoard.h"

class BFSSildeBlockByLove
{
private:
    GameBoard* gameBoard;
public:
    static BFSSildeBlockByLove* getInstanceSolved();
    BFSSildeBlockByLove();
    virtual ~BFSSildeBlockByLove();
    void solvingBoard(GameBoard* gameBoard);
    
    void moveBFSS(GameObject* object, GameBoard* gameBoard,const Vec2& newHeadMaxtix, const Vec2& newLastMaxtrix);
    
    GameObject* getObjectWithID(int identifer, GameBoard* tempGameboard);
    
    bool checkPrevious(GameObject* objectA, GameObject* previousObject, const Vec2& newMaxtrix);
};

#endif /* BFSSildeBlock_h */
