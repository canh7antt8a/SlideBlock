//
//  GameScene.h
//  SlideBlock
//
//  Created by Hoang Nguyen on 11/28/16.
//
//

#ifndef GameScene_h
#define GameScene_h

#include <stdio.h>
#include "cocos2d.h"
#include "GameBoard.h"
#include "GameObject.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

class GameScene : public Layer, DelegateNotification
{
private:
    int level;
    GameBoard* gameboard;
    GameObject* touchObject;
    Vec2 posTouchBeginMaxtrix;
    Vec2 posTouchBegin;
    Size winSize ;
    
    Label* lbLevelGame;
    Label* lbMoveGame;
    Label* lbTimeGame;
    ui::Button* btnBackSlot;
    ui::Button* btnNextSlot;
    
    Vec2 oldHeaderVec;
    
    int status;
    int styleGame;
    int countMove;
    float timeSecondRunGame;
    int timeMinuse;
    int hightLevel;
public:
    GameScene();
    virtual ~GameScene();
    void update(float dt);
    static Scene* createGameScene(int level, int style);
    void  initUpdateUI();
    CREATE_FUNC(GameScene);
    
    
    bool onTouchOneByOneBegan(Touch* mTouch, Event* pEvent);
    void onTouchOneByOneMove(Touch* mTouch, Event* pEvent);
    void onTouchOneByOneEnd(Touch* mTouch, Event* pEvent);
    void moveGameObjectWhenTouch(Vec2 headPosMaxtrix, Vec2 lastPosMaxtrix, const Vec2& posTouch);
    
    void createHeaderGame();
    void createFooterGame();
    
    void buttonClickGameScene(Ref* pSender);
    virtual void sendNotificationForGameScene();
    void createPopUpPause();
    
    void onEnter();
    void onExit();
};

#endif /* GameScene_h */
