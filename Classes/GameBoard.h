//
//  GameBoard.h
//  SlideBlock
//
//  Created by Hoang Nguyen on 11/29/16.
//
//

#ifndef GameBoard_h
#define GameBoard_h

#include <stdio.h>
#include "cocos2d.h"
#include "GameObject.h"
#include "LevelGame.h"
USING_NS_CC;


class DelegateNotification
{
public:
    virtual void sendNotificationForGameScene() = 0;
};

class GameBoard : public Layer
{
public:
        std::vector<int> arrayAvaibleMaxtrix;
private:
    Vec2 posStartCacularGameboard;
    std::vector<GameObject*> arrayObject;
    Vec2 targetPosWin;
    int modeGame;

    DelegateNotification* delegate;
public:
    GameBoard(int modeGame);
    virtual~GameBoard();
    Vec2 convertPositionToPosMaxtrix(const Vec2& position);
    Vec2 convertPosMaxtrixToPosition(const Vec2& posMaxtrix);
    void setStartCacularPositionGameBoard(const Vec2& pos);
    Vec2 getPositonGameboard();
    GameObject* getGameObjectAtPosition(const Vec2& pos);
    
    void setAviableGameBoardPostoPos(const Vec2& pos1, const Vec2& pos2, int visibale);
    void printAviable();
    Vec2 getTargetPosition();
    void setPosTargetGameboard(Vec2 point);
    void readLevelFromXMLFile(const char* fileName);
    bool checkWinGame();
    Vec2 converOutSideGameBoard(const Vec2& pos);
    void createAvaiableMaxtrixGameBoard();
    
    void setDelegateForGame(DelegateNotification* delegate);
    std::vector<GameObject*> getAllBlockGameBoard();
    void setNewArrayGameObject(std::vector<GameObject*> newArray);
    std::vector<int> getMaxtrixAvable();
    
    /*Delegate Object*/
    virtual void sendProcessing();
};
#endif /* GameBoard_h */
