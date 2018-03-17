//
//  BFSSildeBlock.cpp
//  SlideBlock
//
//  Created by Nguyen Chi Hoang on 3/13/17.
//
//

#include "BFSSildeBlock.h"
#include "GameObject.h"
#include "GameDefine.h"

static BFSSildeBlockByLove* object = NULL;


BFSSildeBlockByLove* BFSSildeBlockByLove::getInstanceSolved()
{
    if(object == NULL)
    {
        object  = new BFSSildeBlockByLove();
    }
    return object;
}

BFSSildeBlockByLove::BFSSildeBlockByLove()
{
    
}
BFSSildeBlockByLove::~BFSSildeBlockByLove()
{
    
}

void BFSSildeBlockByLove::solvingBoard(GameBoard* gameBoard)
{
    CCLOG("Searching for a solution...");
    std::list<GameBoard*> queue;
    queue.push_back(gameBoard);
    
    while(!queue.empty()){
        GameBoard* gameboardCopy = *queue.begin();
        std::vector<int> arrayAvaibleMaxtrix = gameboardCopy->getMaxtrixAvable();
        std::vector<GameObject*> arraysObject = gameboardCopy->getAllBlockGameBoard();
        std::vector<GameBoard*> previous;
        queue.pop_front();
        gameboardCopy->printAviable();
        
        GameObject* target = nullptr;
        for(std::vector<GameObject*>::iterator it = arraysObject.begin(); it != arraysObject.end(); ++it) {
            if((*it)->getTypeSpaceObject() == SPACE){
                target = *it;
                break;
            }
        }
        bool allClear = true;
        int y_Maxtrix = target->getLastMaxtrix().y;
        for (int x= target->getLastMaxtrix().x; x< MAX_WIDTH_GAMEBOARD ; x++) {
            if(arrayAvaibleMaxtrix.at(x + y_Maxtrix*MAX_WIDTH_GAMEBOARD) == VISIABLE){
                allClear = false;
                break;
            }
        }
        if(allClear){
            /*
             Win
             */
            return;
        }
        std::vector<GameObject*> arrayBlockWaitMove;
        std::vector<GameObject*> arrayBlockMoved;
        for (std::vector<GameObject*>::iterator it = arraysObject.begin(); it != arraysObject.end(); ++it) {
            if((*it)->getMovedSloved() == false){
                arrayBlockWaitMove.push_back(*it);
            }else{
                arrayBlockMoved.push_back(*it);
            }
        }
        for(std::vector<GameObject*>::iterator it = arrayBlockWaitMove.begin(); it != arrayBlockWaitMove.end(); ++it) {
            GameObject* object = *it;
            gameboardCopy->printAviable();
            object->setStatusMoveSloved(true);
            if (object->getTypeDirector() == HONORITAL) {
                // Can the block move to the left?
                if (object->getHeadMaxtrix().x-1 >=0 && arrayAvaibleMaxtrix.at(object->getHeadMaxtrix().x-1 + object->getLastMaxtrix().y*MAX_WIDTH_GAMEBOARD) == DIVISIBALE) {
                    
                    /**
                     Get previous gameboard
                     */
                    if(!previous.empty()){
                        GameBoard* previousGameboard = previous.at(previous.size()-1);
                        if (this->checkPrevious(object,this->getObjectWithID(object->getIdentifer(), previousGameboard),Vec2(object->getHeadMaxtrix().x-1, object->getHeadMaxtrix().y)) == false){
                            this->moveBFSS(object, gameboardCopy, Vec2(object->getHeadMaxtrix().x-1, object->getHeadMaxtrix().y),  Vec2(object->getLastMaxtrix().x-1, object->getLastMaxtrix().y));
                            break;
                        }
                    }
                }
                // Can the block move to the right?
                if (object->getLastMaxtrix().x+1 <= MAX_WIDTH_GAMEBOARD && arrayAvaibleMaxtrix.at(object->getHeadMaxtrix().x +1 + object->getLastMaxtrix().y*MAX_WIDTH_GAMEBOARD) == DIVISIBALE) {
                    
                    if(!previous.empty()){
                        GameBoard* previousGameboard = previous.at(previous.size()-1);
                        if(this->checkPrevious(object,this->getObjectWithID(object->getIdentifer(), previousGameboard),Vec2(object->getHeadMaxtrix().x+1, object->getHeadMaxtrix().y)) == false){
                            this->moveBFSS(object, gameboardCopy, Vec2(object->getHeadMaxtrix().x+1, object->getHeadMaxtrix().y),  Vec2(object->getLastMaxtrix().x+1, object->getLastMaxtrix().y));
                            
                            break;
                        }
                    }
                }
            }else {
                // Can the block move up?
                if (object->getLastMaxtrix().y + 1 <= MAX_HEIGHT_GAMEBOARD && arrayAvaibleMaxtrix.at(object->getHeadMaxtrix().x + object->getLastMaxtrix().y *MAX_WIDTH_GAMEBOARD) == DIVISIBALE) {
                    
                    if(!previous.empty()){
                        GameBoard* previousGameboard = previous.at(previous.size()-1);
                        if(this->checkPrevious(object,this->getObjectWithID(object->getIdentifer(), previousGameboard),Vec2(object->getHeadMaxtrix().x, object->getHeadMaxtrix().y+1)) == false){
                            this->moveBFSS(object, gameboardCopy, Vec2(object->getHeadMaxtrix().x, object->getHeadMaxtrix().y+1),  Vec2(object->getLastMaxtrix().x, object->getLastMaxtrix().y+1));
                            break;
                        }
                    }
                }
                // Can the block move down?
                if (object->getHeadMaxtrix().y-1 >=0 && arrayAvaibleMaxtrix.at(object->getHeadMaxtrix().x + (object->getHeadMaxtrix().y - 1 )*MAX_WIDTH_GAMEBOARD) == DIVISIBALE) {
                    if(!previous.empty()){
                        GameBoard* previousGameboard = previous.at(previous.size()-1);
                        if(this->checkPrevious(object,this->getObjectWithID(object->getIdentifer(), previousGameboard),Vec2(object->getHeadMaxtrix().x, object->getHeadMaxtrix().y-1)) == false){
                            this->moveBFSS(object, gameboardCopy, Vec2(object->getHeadMaxtrix().x, object->getHeadMaxtrix().y-1),  Vec2(object->getLastMaxtrix().x, object->getLastMaxtrix().y-1));
                            break;
                        }
                    }
                }
            }
        }
        
        GameObject* endObject = arrayBlockWaitMove.at(arrayBlockWaitMove.size()-1);
        if(endObject->getMovedSloved() ==true){
            for (std::vector<GameObject*>::iterator it = arraysObject.begin(); it != arraysObject.end(); ++it) {
                (*it)->setStatusMoveSloved(false);
            }
        }
        previous.push_back(gameboardCopy);
        queue.push_back(gameboardCopy);
    }
}
bool BFSSildeBlockByLove::checkPrevious(GameObject* objectA, GameObject* previousObject, const Vec2& newMaxtrix){
    if(objectA->getIdentifer() == previousObject->getIdentifer() && objectA->getTypeDirector() == previousObject->getTypeDirector()){
        if(previousObject->getHeadMaxtrix().x == newMaxtrix.x && newMaxtrix.y == previousObject->getHeadMaxtrix().y){
            return true;
        }else{
            return false;
        }
    }
    return false;
}

GameObject* BFSSildeBlockByLove::getObjectWithID(int identifer,  GameBoard* tempGameboard){
    GameObject* object = nullptr;
    std::vector<GameObject*> arrayAllObject = tempGameboard->getAllBlockGameBoard();
    for(std::vector<GameObject*>::iterator it = arrayAllObject.begin(); it != arrayAllObject.end(); ++it){
        if((*it)->getIdentifer() == identifer){
            object = (*it);
        }
    }
    return object;
}
void BFSSildeBlockByLove::moveBFSS(GameObject* object, GameBoard* gameBoard,const Vec2& newHeadMaxtix, const Vec2& newLastMaxtrix){
    gameBoard->printAviable();
    Vec2 oldhead= object->getHeadMaxtrix();
    Vec2 ollast = object->getLastMaxtrix();
    gameBoard->setAviableGameBoardPostoPos(oldhead, ollast, DIVISIBALE);
    
    object->movePostion(gameBoard->convertPosMaxtrixToPosition(newHeadMaxtix),newHeadMaxtix, newLastMaxtrix);
    
    Vec2 newHead = object->getHeadMaxtrix();
    Vec2 newLast = object->getLastMaxtrix();
    gameBoard->setAviableGameBoardPostoPos(newHead, newLast, VISIABLE);
    gameBoard->printAviable();
    
}

