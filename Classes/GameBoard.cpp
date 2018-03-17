
//
//  GameBoard.cpp
//  SlideBlock
//
//  Created by Hoang Nguyen on 11/29/16.
//
//

#include "GameBoard.h"
#include "GameDefine.h"
#include "GameObject.h"

#include <iostream>

#define SHAPE_WIDTH_HEIGHT 80

GameBoard::GameBoard(int modeGame)
{
    if(!arrayObject.empty())
    {
        arrayObject.clear();
    }
    if(!arrayAvaibleMaxtrix.empty())
    {
        arrayAvaibleMaxtrix.clear();
    }
    this->modeGame = modeGame;
}
GameBoard::~GameBoard()
{
    
}

void GameBoard::createAvaiableMaxtrixGameBoard()
{
    for (int i = 0; i < MAX_HEIGHT_GAMEBOARD; i++)
    {
        for (int j = 0; j < MAX_WIDTH_GAMEBOARD; j++)
        {
            arrayAvaibleMaxtrix.push_back(DIVISIBALE);
        }
    }
}



void GameBoard::readLevelFromXMLFile(const char* fileName)
{
    LevelGame* levelData = new LevelGame();
    levelData->createDataWithFile(fileName);
    std::vector<DataGame*> data = levelData->getDataForLevel();
    
    for (int i = 0; i < data.size(); i++)
    {
        if( i != data.size() - 1)
        {
            GameObject* object = new GameObject();
            char fileName[1024] = {0};
            object->setHeadAndPosMaxtrix(Vec2(data.at(i)->x1, data.at(i)->y1), Vec2(data.at(i)->x2, data.at(i)->y2));
            if(data.at(i)->typeObject == SPACE)
            {
                if(data.at(i)->x1 == data.at(i)->x2)
                {
                    sprintf(fileName, "space_vertical_%d_%d.png",modeGame,object->getHeightObject());
                }
                if(data.at(i)->y1 == data.at(i)->y2)
                {
                    sprintf(fileName, "space_horizontal_%d_%d.png",modeGame,object->getLenghtObject());
                }
            }
            else
            {
                if(data.at(i)->x1 == data.at(i)->x2)
                {
                    sprintf(fileName, "vertical_%d_%d.png",modeGame,object->getHeightObject());
                }
                if(data.at(i)->y1 == data.at(i)->y2)
                {
                    sprintf(fileName, "horizontal_%d_%d.png",modeGame,object->getLenghtObject());
                }
            }
            object->setIndentifer(i);
            object->createWithFileName(fileName);
            object->setHeadAndLastPosion(this->convertPosMaxtrixToPosition(Vec2(data.at(i)->x1, data.at(i)->y1)), this->convertPosMaxtrixToPosition(Vec2(data.at(i)->x2, data.at(i)->y2)));
            object->setPostionWithGameObject();
            object->setTypeSpace(data.at(i)->typeObject);
            this->addChild(object,10);
            arrayObject.push_back(object);
            this->setAviableGameBoardPostoPos(Vec2(data.at(i)->x1, data.at(i)->y1), Vec2(data.at(i)->x2, data.at(i)->y2), VISIABLE);
        }
        else
        {
            this->setPosTargetGameboard(Vec2(data.at(i)->x1, data.at(i)->y1));
        }
    }
}
void GameBoard::setAviableGameBoardPostoPos(const Vec2& pos1, const Vec2& pos2, int visibale)
{
    if(pos1.x == pos2.x)
    {
        int minY = 0;
        int maxY = 0;
        if(pos1.y < pos2.y)
        {
            minY = pos1.y;
            maxY = pos2.y;
        }
        else
        {
            minY = pos2.y;
            maxY = pos1.y;
        }
        for (int i = minY ; i < maxY; i++)
        {
            arrayAvaibleMaxtrix.at(pos1.x + i*MAX_WIDTH_GAMEBOARD) = visibale;
        }
    }
    else
    {
        int minX = 0;
        int maxX = 0;
        if(pos1.x < pos2.x)
        {
            minX = pos1.x;
            maxX = pos2.x;
        }
        else
        {
            minX = pos2.x;
            maxX = pos1.x;
        }
        
        for (int i = minX ; i < maxX; i++)
        {
            arrayAvaibleMaxtrix.at(i +  pos1.y*MAX_WIDTH_GAMEBOARD) = visibale;
        }
    }
}


GameObject* GameBoard::getGameObjectAtPosition(const Vec2& pos)
{
    float delX = (pos.x - posStartCacularGameboard.x) / SIZE_SHAPE_WIDTH;
    float delY = (pos.y - posStartCacularGameboard.y) / SIZE_SHAPE_HEIGTH;
    Vec2 compare(delX,delY);
    
    int intdelX = (pos.x - posStartCacularGameboard.x) / SIZE_SHAPE_WIDTH;
    int intdelY = (pos.y - posStartCacularGameboard.y) / SIZE_SHAPE_HEIGTH;
    Vec2 intVector(intdelX,intdelY);
    for (int i = 0; i < arrayObject.size(); i++)
    {
        GameObject* object = arrayObject.at(i);
        Vec2 headerMaxtrix = object->getHeadMaxtrix();
        Vec2 lastMaxtrix = object->getLastMaxtrix();
        if(object->getTypeDirector() == HONORITAL)
        {
            if(compare.x > headerMaxtrix.x && compare.x < lastMaxtrix.x && intVector.y == headerMaxtrix.y)
            {
                return object;
            }
        }
        if(object->getTypeDirector() == VERTICAL)
        {
            if(compare.y > headerMaxtrix.y && compare.y < lastMaxtrix.y && intVector.x == headerMaxtrix.x)
            {
                return object;
            }
        }
    }
    return NULL;
}

Vec2 GameBoard::convertPositionToPosMaxtrix(const Vec2& position)
{
    
    Vec2 vec2Result;
    Vec2 posRealGameBoard = position - posStartCacularGameboard;
    int x_Maxtrix  = posRealGameBoard.x/SIZE_SHAPE_WIDTH;
    int y_Maxtrix = posRealGameBoard.y/SIZE_SHAPE_WIDTH;
    vec2Result = Vec2(x_Maxtrix, y_Maxtrix);
    return vec2Result;
}
Vec2 GameBoard::convertPosMaxtrixToPosition(const Vec2& posMaxtrix)
{
    if(posMaxtrix.x < 0 || posMaxtrix.y < 0 || posMaxtrix.x > MAX_WIDTH_GAMEBOARD-1 || posMaxtrix.y > MAX_HEIGHT_GAMEBOARD-1)
    {
        return Vec2(-1,-1);
    }
    else
    {
        float pointX = posMaxtrix.x * SIZE_SHAPE_WIDTH ;
        float pointY = posMaxtrix.y * SIZE_SHAPE_HEIGTH ;
        return Vec2(pointX,pointY);
    }
    
}
Vec2 GameBoard::converOutSideGameBoard(const Vec2& pos)
{
    float pointX = pos.x * SIZE_SHAPE_WIDTH ;
    float pointY = pos.y * SIZE_SHAPE_HEIGTH ;
    return Vec2(pointX,pointY);
}
void GameBoard::setStartCacularPositionGameBoard(const Vec2& pos)
{
    this->posStartCacularGameboard = pos;
}
void GameBoard::setPosTargetGameboard(Vec2 point)
{
    this->targetPosWin = point;
}

Vec2 GameBoard::getPositonGameboard()
{
    return posStartCacularGameboard;
}

Vec2 GameBoard::getTargetPosition()
{
    return targetPosWin;
}
bool GameBoard::checkWinGame()
{
    for (int i = 0 ; i < arrayObject.size(); i++)
    {
        GameObject* touchObject = arrayObject.at(i);
        if(touchObject->getTypeSpaceObject() == SPACE)
        {
            if(touchObject != NULL && touchObject->getTypeSpaceObject() == SPACE )
            {
                Vec2 targetPos = targetPosWin;
                Vec2 newHead = touchObject->getHeadMaxtrix();
                Vec2 newLast = touchObject->getLastMaxtrix();
                if(touchObject->getTypeDirector() ==HONORITAL)
                {
                    if(newHead.x == targetPos.x || newLast.x == targetPos.x )
                    {
                        this->unschedule("updateWinHonizental");
                        this->scheduleOnce([=](float dt){
                            touchObject->moveGameWin(Vec2(touchObject->getPosition().x + SHAPE_WIDTH_HEIGHT*4, touchObject->getPosition().y));                            CCLOG("WIN ---- HONITIAL");
                            if(delegate)
                            {
                                delegate->sendNotificationForGameScene()
                                ;
                            }
                        }, 0.06f, "updateWinHonizental");
                        
                    }
                }
                if(touchObject->getTypeDirector() == VERTICAL)
                {
                    if( newHead.y == targetPos.y || newLast.y == targetPos.y)
                    {
                        this->unschedule("updateWinHonizental");
                        this->scheduleOnce([=](float dt){
                            touchObject->moveGameWin(Vec2(touchObject->getPosition().x, touchObject->getPosition().y + SHAPE_WIDTH_HEIGHT*4));
                            CCLOG("WIN ---- VERTICAL");
                            if(delegate)
                            {
                                delegate->sendNotificationForGameScene()
                                ;
                            }
                        }, 0.06f, "updateWinHonizental");
                    }
                }
            }
            
        }
    }
    return false;
}

std::vector<int> GameBoard::getMaxtrixAvable()
{
    return arrayAvaibleMaxtrix;
}
void GameBoard::setNewArrayGameObject(std::vector<GameObject*> newArray)
{
    this->arrayObject.swap(newArray);
}
void GameBoard::sendProcessing()
{
    
}
std::vector<GameObject*> GameBoard::getAllBlockGameBoard()
{
    return arrayObject;
}
void GameBoard::setDelegateForGame(DelegateNotification* delegate)
{
    this->delegate = delegate;
}

void GameBoard::printAviable()
{
    std::cout<<"\n"<<"\n";
    for (int i = MAX_HEIGHT_GAMEBOARD-1 ; i >= 0; i--)
    {
        for (int j = 0; j < MAX_WIDTH_GAMEBOARD; j++)
        {
            std::cout<< arrayAvaibleMaxtrix.at(j + i* MAX_WIDTH_GAMEBOARD) << " ";
        }
        std::cout<<"\n"<<"\n";
    }
    std::cout<<"\n"<<"\n";
}
