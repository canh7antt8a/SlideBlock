//
//  GameScene.cpp
//  SlideBlock
//
//  Created by Hoang Nguyen on 11/28/16.
//
//

#include "GameScene.h"
#include "GameDefine.h"
#include "LevelGame.h"
#include "HomeScene.h"
#include "SimpleAudioEngine.h"
#include "BFSSildeBlock.h"
#include "Admob.h"
#include "AdmodAndroid.h"
#define TAG_BTN_PAUSE_GAMESCENE 189
#define TAG_BTN_REPLAY_GAMESCENE 190
#define TAG_BTN_BACK_GAMESCENE 200
#define TAG_BTN_NEXTSLOT_GAMESCENE 201
#define TAG_BTN_BACKSLOT_GAMESCENE 202


#define TAG_POPUP_RESUME 203
#define TAG_POPUP_REPLAY 204
#define TAG_POPUP_MENU 205
#define TAG_BTN_SUGGESS_GAME 206

#define COLOR4V Color4B(6,75,38,100)
static char bufferLevel[128] = {0};
static char bufferCountMove[128] = {0};
static char bufferTimeGame[1024] = {0};

GameScene::GameScene()
{
    
}
GameScene::~GameScene()
{
    
}
Scene* GameScene::createGameScene(int level, int style)
{
    auto scene = Scene::create();
    auto layer = new GameScene();
    layer->level = level;
    layer->styleGame = style;
    layer->initUpdateUI();
    scene->addChild(layer);
    return scene;
}


void GameScene::update(float dt)
{
    
    if(status == IDLE)
    {
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
        Admob::getInstance()->hideBanner();
#endif
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
        AdmodAndroid::hideBanner();
#endif
        timeSecondRunGame += dt;
        if(timeSecondRunGame > 59)
        {
            timeSecondRunGame = 0.0f;
            timeMinuse ++;
        }
        if(timeMinuse < 10)
        {
            if(timeSecondRunGame > 9.5f)
            {
                sprintf(bufferTimeGame, "0%d:%.0f",timeMinuse,timeSecondRunGame);
            }
            else
            {
                sprintf(bufferTimeGame, "0%d:0%.0f",timeMinuse,timeSecondRunGame);
            }
        }
        else
        {
            if(timeSecondRunGame > 9.5f)
            {
                sprintf(bufferTimeGame, "%d:%.0f",timeMinuse, timeSecondRunGame);
            }
            else
            {
                sprintf(bufferTimeGame, "%d:0%.0f",timeMinuse,timeSecondRunGame);
            }
        }
        lbTimeGame->setString(bufferTimeGame);
    }
}

void GameScene::initUpdateUI()
{
    /*setup background*/
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    Admob::getInstance()->hideBanner();
#endif
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
    AdmodAndroid::hideBanner();
#endif
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("bgsound.mp3", true);
    winSize = Director::getInstance()->getWinSize();
    if( UserDefault::getInstance()->getBoolForKey("ONTHEME", true))
    {
        Sprite* spBg = Sprite::create("bgHomeScene.png");
        spBg->setPosition(Vec2(winSize.width/2, winSize.height/2));
        this->addChild(spBg,1);
    }
    else
    {
        Sprite* spBg = Sprite::create("bgHomeScene_Off.png");
        spBg->setPosition(Vec2(winSize.width/2, winSize.height/2));
        this->addChild(spBg,1);
    }
    hightLevel = 0;
    if(styleGame == EASY_LEVEL)
    {
        hightLevel = UserDefault::getInstance()->getIntegerForKey(USER_HIGHT_LEVEL_EASY,1);
    }
    else if (styleGame == MEDIUM_LEVEL)
    {
        hightLevel = UserDefault::getInstance()->getIntegerForKey(USER_HIGHT_LEVEL_MEDIUM,1);
    }
    else if (styleGame == HARD_LEVEL)
    {
        hightLevel = UserDefault::getInstance()->getIntegerForKey(USER_HIGHT_LEVEL_HARD, 1);
    }
    else
    {
        hightLevel = UserDefault::getInstance()->getIntegerForKey(USER_HIGHT_LEVEL_EXPERT, 1);
    }
    
    //hightLevel = 100;
    status = PAUSE;
    countMove = 0;
    timeMinuse = 0;
    timeSecondRunGame = 0.0f;
    
    gameboard = new GameBoard(styleGame);
    gameboard->setDelegateForGame(this);
    gameboard->createAvaiableMaxtrixGameBoard();
    gameboard->setPosition(Vec2(80, 200));
    gameboard->setStartCacularPositionGameBoard(Vec2(80,200));
    char fileName[512] = {0};
    sprintf(fileName, "level-%d-%d.xml",styleGame, level);
    gameboard->readLevelFromXMLFile(fileName);
    this->addChild(gameboard,100);
    
    
    //setup-header for game
    createHeaderGame();
    createFooterGame();
    
    
    /*Add Event*/
    auto lister = EventListenerTouchOneByOne::create();
    lister->setSwallowTouches(true);
    lister->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchOneByOneBegan, this);
    lister->onTouchMoved = CC_CALLBACK_2(GameScene::onTouchOneByOneMove, this);
    lister->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchOneByOneEnd, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(lister, this);
    gameboard->printAviable();
    this->scheduleUpdate();
}

void GameScene::createHeaderGame()
{
    Sprite* spBgHeader = Sprite::create("box_time.png");
    spBgHeader->setPosition(Vec2(winSize.width/2, winSize.height - spBgHeader->getContentSize().height/2));
    this->addChild(spBgHeader,2);
    
    /*btnPause*/
    ui::Button* btnPause = ui::Button::create("pause_normal.png","pause_pressed.png","",ui::Widget::TextureResType::LOCAL);
    btnPause->setPosition(Vec2(spBgHeader->getPositionX() + spBgHeader->getContentSize().width/2 - btnPause->getContentSize().width*0.8, spBgHeader->getPositionY() + btnPause->getContentSize().height*0.4));
    btnPause->addClickEventListener(CC_CALLBACK_1(GameScene::buttonClickGameScene,this));
    btnPause->setTag(TAG_BTN_PAUSE_GAMESCENE);
    this->addChild(btnPause,3);
    
    
    ui::Button* btnReplay = ui::Button::create("replay_normal.png","replay_pressed.png","",ui::Widget::TextureResType::LOCAL);
    btnReplay->setPosition(Vec2(btnPause->getPositionX() - btnReplay->getContentSize().width*1.1, btnPause->getPositionY()));
    btnReplay->addClickEventListener(CC_CALLBACK_1(GameScene::buttonClickGameScene,this));
    btnReplay->setTag(TAG_BTN_REPLAY_GAMESCENE);
    this->addChild(btnReplay,3);
    
    /*Move Best*/
    auto labelMoveBest = Label::createWithTTF("MoveBest : --", "HKABEL.TTF", 30);
    labelMoveBest->setPosition(Vec2(btnReplay->getPositionX() - btnReplay->getContentSize().width/2, btnReplay->getPositionY() - btnReplay->getContentSize().height*0.66));
    labelMoveBest->setAnchorPoint(Vec2(0, 0.5f));
    this->addChild(labelMoveBest,3);
    
    char bufferMoveBestDisplay[512] = {0};
    sprintf(bufferMoveBestDisplay, "MoveBest-%d-%d", styleGame, level);
    int countMoveBestPrevious = UserDefault::getInstance()->getIntegerForKey(bufferMoveBestDisplay,1000);
    
    /*
     */
    if(countMoveBestPrevious != 1000)
    {
        char bufferCountMoveBest[256] = {0};
        sprintf(bufferCountMoveBest, "MoveBest : %d", countMoveBestPrevious);
        labelMoveBest->setString(bufferCountMoveBest);
    }
    
    /*
     Sprite level
     */
    Sprite* spLevelTheme = Sprite::create("box_level.png");
    spLevelTheme->setPosition(Vec2(btnReplay->getPositionX() - btnReplay->getContentSize().width*1.9, btnReplay->getPositionY() + spLevelTheme->getContentSize().height/4));
    this->addChild(spLevelTheme,3);
    
    /*Sprite Move*/
    Sprite* spMoveTheme = Sprite::create("box_moves.png");
    spMoveTheme->setPosition(Vec2(spLevelTheme->getPositionX(), spLevelTheme->getPositionY() - spLevelTheme->getContentSize().height*1.1));
    this->addChild(spMoveTheme,3);
    
    
    /*
     Label* lbLevelGame;
     */
    sprintf(bufferLevel, "%d", level);
    lbLevelGame = Label::createWithTTF(bufferLevel, "HKABEL.TTF", 40);
    lbLevelGame->setPosition(Vec2(spLevelTheme->getPositionX() + spLevelTheme->getContentSize().width*0.2, spLevelTheme->getPositionY() + + lbLevelGame->getContentSize().height/10));
    this->addChild(lbLevelGame,4);
    
    
    /*
     Label* lbCountMoveGame;
     */
    sprintf(bufferCountMove, "%d", countMove);
    lbMoveGame = Label::createWithTTF(bufferCountMove, "HKABEL.TTF", 40);
    lbMoveGame->setPosition(Vec2(spMoveTheme->getPositionX() + spMoveTheme->getContentSize().width*0.2, spMoveTheme->getPositionY() + lbMoveGame->getContentSize().height/10));
    this->addChild(lbMoveGame,4);
    
    
    lbTimeGame = Label::createWithTTF("00:00", "HKABEL.TTF", 36);
    lbTimeGame->setPosition(Vec2(spBgHeader->getPositionX(), spBgHeader->getPositionY() - spBgHeader->getContentSize().height*0.36));
    this->addChild(lbTimeGame,4);
    
}


void GameScene::createFooterGame()
{
    /*Button Back game*/
    ui::Button* btnBackGame = ui::Button::create("backscene_normal.png","backscene_pressed.png","",ui::Widget::TextureResType::LOCAL);
    btnBackGame->setPosition(Vec2(btnBackGame->getContentSize().height/2,btnBackGame->getContentSize().height/2));
    btnBackGame->setTag(TAG_BTN_BACK_GAMESCENE);
    btnBackGame->addClickEventListener(CC_CALLBACK_1(GameScene::buttonClickGameScene,this));
    this->addChild(btnBackGame,100);
    
    btnBackSlot = ui::Button::create();
    btnNextSlot = ui::Button::create();
    if(level == 1)
    {
        btnBackSlot->loadTextures("back_end.png","","",ui::Widget::TextureResType::LOCAL);
        btnBackSlot->setEnabled(false);
        if(level == hightLevel)
        {
            btnNextSlot->loadTextures("next_end.png","","",ui::Widget::TextureResType::LOCAL);
            btnNextSlot->setEnabled(false);
        }
        else
        {
            btnNextSlot->loadTextures("next_normal.png","next_pressed.png","",ui::Widget::TextureResType::LOCAL);
            btnNextSlot->setEnabled(true);
        }
    }
    else
    {
        btnBackSlot->loadTextures("back_normal.png","back_pressed.png","",ui::Widget::TextureResType::LOCAL);
        btnNextSlot->setEnabled(true);
        
        
        if(level == hightLevel)
        {
            btnNextSlot->loadTextures("next_end.png","","",ui::Widget::TextureResType::LOCAL);
            btnNextSlot->setEnabled(false);
        }
        else
        {
            btnNextSlot->loadTextures("next_normal.png","next_pressed.png","",ui::Widget::TextureResType::LOCAL);
            
            btnNextSlot->setEnabled(true);
        }
    }
    
    /*Button Back Slot*/
    btnBackSlot->setPosition(Vec2(winSize.width/2 - btnBackSlot->getContentSize().width*0.6,btnBackGame->getPositionY()));
    btnBackSlot->setTag(TAG_BTN_BACKSLOT_GAMESCENE);
    btnBackSlot->addClickEventListener(CC_CALLBACK_1(GameScene::buttonClickGameScene,this));
    this->addChild(btnBackSlot,100);
    
    /*Button Next Slot*/
    btnNextSlot->setPosition(Vec2(winSize.width/2 + btnNextSlot->getContentSize().width*0.6,btnBackGame->getPositionY()));
    btnNextSlot->setTag(TAG_BTN_NEXTSLOT_GAMESCENE);
    btnNextSlot->addClickEventListener(CC_CALLBACK_1(GameScene::buttonClickGameScene,this));
    this->addChild(btnNextSlot,100);
    
    
    ui::Button* btnsuggestGame = ui::Button::create("goiy_normal.png","goiy_pressed.png","",ui::Widget::TextureResType::LOCAL);
    btnsuggestGame->setTag(TAG_BTN_SUGGESS_GAME);
    btnsuggestGame->setPosition(Vec2(winSize.width - btnsuggestGame->getContentSize().width/2, btnNextSlot->getPositionY()));
    btnsuggestGame->addClickEventListener(CC_CALLBACK_1(GameScene::buttonClickGameScene,this));
    btnsuggestGame->setVisible(false);
    this->addChild(btnsuggestGame,100);
    
    
    if(gameboard->getTargetPosition().y == 2 )
    {
        Sprite* bgThumbGameBoard = Sprite::create("bg_ingame2.png");
        bgThumbGameBoard->setPosition(Vec2(winSize.width/2 + 28, winSize.height/2 - 44));
        this->addChild(bgThumbGameBoard,5);
    }
    if(gameboard->getTargetPosition().y == 3)
    {
        Sprite* bgThumbGameBoard = Sprite::create("bg_ingame3.png");
        bgThumbGameBoard->setPosition(Vec2(winSize.width/2 + 28, winSize.height/2 - 44));
        this->addChild(bgThumbGameBoard,5);
    }
    
    
}

void GameScene::buttonClickGameScene(Ref* pSender)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("soundClick.mp3");
    int  tag =  ((ui::Button*)pSender)->getTag();
    if(tag == TAG_BTN_BACK_GAMESCENE)
    {
        Director::getInstance()->replaceScene(HomeScene::createHomeScene());
    }
    if(tag == TAG_BTN_REPLAY_GAMESCENE)
    {
        Director::getInstance()->replaceScene(GameScene::createGameScene(level, styleGame));
    }
    if(tag == TAG_BTN_PAUSE_GAMESCENE)
    {
        CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
        this->createPopUpPause();
    }
    if(tag == TAG_POPUP_MENU)
    {
        Director::getInstance()->replaceScene(HomeScene::createHomeScene());
    }
    if(tag == TAG_POPUP_REPLAY)
    {
        CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("bgsound.mp3",true);
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
        Admob::getInstance()->hideBanner();
#endif
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
        AdmodAndroid::hideBanner();
#endif
        
        Director::getInstance()->replaceScene(GameScene::createGameScene(level, styleGame));
    }
    if(tag == TAG_POPUP_RESUME)
    {
        CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("bgsound.mp3",true);
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
        Admob::getInstance()->hideBanner();
#endif
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
        AdmodAndroid::hideBanner();
#endif
        status =IDLE;
        if(this->getChildByTag(1256))
        {
            this->removeChildByTag(1256);
        }
    }
    
    if(tag == TAG_BTN_BACKSLOT_GAMESCENE)
    {
        if(level % 8 == 0)
        {
#if  CC_TARGET_PLATFORM == CC_PLATFORM_IOS
            Admob::getInstance()->loadInterstitial();
            Admob::getInstance()->showInterstitial();
#endif
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
            AdmodAndroid::showFullAdvertiment();
#endif
        }
        if(level != 1)
        {
            Director::getInstance()->replaceScene(GameScene::createGameScene(level-1, styleGame));
        }
    }
    if(tag == TAG_BTN_NEXTSLOT_GAMESCENE)
    {
        if(level % 8 == 0)
        {
#if  CC_TARGET_PLATFORM == CC_PLATFORM_IOS
            Admob::getInstance()->loadInterstitial();
            Admob::getInstance()->showInterstitial();
#endif
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
            AdmodAndroid::showFullAdvertiment();
#endif
        }
        //        hightLevel  = 100;
        if(level <= hightLevel)
        {
            Director::getInstance()->replaceScene(GameScene::createGameScene(level+1, styleGame));
        }
    }
    if(tag == TAG_BTN_SUGGESS_GAME)
    {
        BFSSildeBlockByLove::getInstanceSolved()->solvingBoard(gameboard);
    }
}


void GameScene::createPopUpPause()
{
    status = PAUSE;
    LayerColor* pauseLayer  = LayerColor::create(COLOR4V, winSize.width, winSize.height);
    pauseLayer->setPosition(Vec2(0,0));
    pauseLayer->setTag(1256);
    this->addChild(pauseLayer,1000);
    
    auto lister = EventListenerTouchOneByOne::create();
    lister->setSwallowTouches(true);
    lister->onTouchBegan = [=](Touch* pTouch, Event* mEvent)
    {
        
        return true;
    };
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(lister, pauseLayer);
    
    if( UserDefault::getInstance()->getBoolForKey("ONTHEME", true))
    {
        Sprite* bgPause = Sprite::create("bgHomeScene.png");
        bgPause->setPosition(Vec2(winSize.width/2, winSize.height/2));
        pauseLayer->addChild(bgPause,-1);
    }
    else
    {
        Sprite* bgPause = Sprite::create("bgHomeScene_Off.png");
        bgPause->setPosition(Vec2(winSize.width/2, winSize.height/2));
        pauseLayer->addChild(bgPause,-1);
    }
    
    
    
    Sprite* thumbPause = Sprite::create("bg_pause.png");
    thumbPause->setPosition(Vec2(winSize.width/2, winSize.height/2));
    pauseLayer->addChild(thumbPause,1);
    
    
    /*btnPlay*/
    ui::Button* btnResume = ui::Button::create("resume_normal.png","resume_pressed.png","",ui::Widget::TextureResType::LOCAL);
    btnResume->setPosition(Vec2(thumbPause->getPositionX(), thumbPause->getPositionY() - btnResume->getContentSize().height*0.56));
    btnResume->addClickEventListener(CC_CALLBACK_1(GameScene::buttonClickGameScene,this));
    btnResume->setTag(TAG_POPUP_RESUME);
    pauseLayer->addChild(btnResume,3);
    
    
    /*btnReplayPause*/
    ui::Button* btnReplayPauseGame = ui::Button::create("replay_normal.png","replay_pressed.png","",ui::Widget::TextureResType::LOCAL);
    btnReplayPauseGame->setPosition(Vec2(btnResume->getPositionX() + btnReplayPauseGame->getContentSize().width*1.1, btnResume->getPositionY()));
    btnReplayPauseGame->addClickEventListener(CC_CALLBACK_1(GameScene::buttonClickGameScene,this));
    btnReplayPauseGame->setTag(TAG_POPUP_REPLAY);
    pauseLayer->addChild(btnReplayPauseGame,3);
    
    /*btnHome*/
    ui::Button* btnMenu = ui::Button::create("menu_normal.png","menu_pressed.png","",ui::Widget::TextureResType::LOCAL);
    btnMenu->setPosition(Vec2(btnResume->getPositionX() - btnMenu->getContentSize().width*1.1, btnResume->getPositionY()));
    btnMenu->addClickEventListener(CC_CALLBACK_1(GameScene::buttonClickGameScene,this));
    btnMenu->setTag(TAG_POPUP_MENU);
    pauseLayer->addChild(btnMenu,3);
    
}


bool GameScene::onTouchOneByOneBegan(Touch* mTouch, Event* pEvent)
{
    posTouchBegin = mTouch->getLocation();
    posTouchBeginMaxtrix = gameboard->convertPositionToPosMaxtrix(mTouch->getLocation());
    
    if(posTouchBeginMaxtrix.x >= 0 && posTouchBeginMaxtrix.x < MAX_WIDTH_GAMEBOARD && posTouchBeginMaxtrix.y >= 0 && posTouchBeginMaxtrix.y < MAX_HEIGHT_GAMEBOARD)
    {
        status = IDLE;
        touchObject = gameboard->getGameObjectAtPosition(mTouch->getLocation());
        if(touchObject)
        {
            oldHeaderVec = touchObject->getHeadMaxtrix();
        }
        return true;
    }
    return false;
}
void GameScene::onTouchOneByOneMove(Touch* mTouch, Event* pEvent)
{
    if(touchObject != NULL)
    {
        Vec2 posMoveTouch = mTouch->getLocation();
        Vec2 posTouchMoveMaxtrix = gameboard->convertPositionToPosMaxtrix(posMoveTouch);
        if(posTouchBeginMaxtrix.x == posTouchMoveMaxtrix.x && posTouchBeginMaxtrix.y == posTouchMoveMaxtrix.y)
        {
            return;
        }
        Vec2 headPosObject = touchObject->getHeadMaxtrix();
        Vec2 lastPosObject = touchObject->getLastMaxtrix();
        if( touchObject->getTypeDirector() == VERTICAL){
            
            if(posTouchMoveMaxtrix.y > posTouchBeginMaxtrix.y){
                //Up
                int distanceY = posTouchMoveMaxtrix.y - posTouchBeginMaxtrix.y;
                int temp = touchObject->getLastMaxtrix().y;
                int maxY = temp + distanceY;
                int deltaY = 0;
                if (maxY >= MAX_HEIGHT_GAMEBOARD)
                {
                    maxY = MAX_HEIGHT_GAMEBOARD;
                }
                for ( int i = temp ; i < maxY; i++){
                    if(gameboard->arrayAvaibleMaxtrix.at(headPosObject.x + i*MAX_WIDTH_GAMEBOARD) == VISIABLE){
                        break;
                    }
                    else{
                        deltaY ++;
                    }
                }
                
                if(lastPosObject.y + deltaY > MAX_HEIGHT_GAMEBOARD)
                {
                    this->moveGameObjectWhenTouch(Vec2(headPosObject.x, MAX_HEIGHT_GAMEBOARD - touchObject->getHeightObject()), Vec2(lastPosObject.x, MAX_HEIGHT_GAMEBOARD),posMoveTouch);
                }
                else{
                    this->moveGameObjectWhenTouch(Vec2(headPosObject.x, headPosObject.y + deltaY), Vec2(lastPosObject.x, lastPosObject.y + deltaY),posMoveTouch);
                }
            }
            if(posTouchMoveMaxtrix.y < posTouchBeginMaxtrix.y){
                //Down
                int distanceY = posTouchBeginMaxtrix.y - posTouchMoveMaxtrix.y;
                int temp = touchObject->getHeadMaxtrix().y;
                int minY = temp - distanceY;
                int deltaY = 0;
                if(minY <= 0){
                    minY = 0;
                }
                for (int i = temp - 1; i >= minY ; i--){
                    if(gameboard->arrayAvaibleMaxtrix.at(headPosObject.x + i*MAX_WIDTH_GAMEBOARD) == VISIABLE){
                        break;
                    }
                    else{
                        deltaY ++;
                    }
                }
                if(headPosObject.y - deltaY < 0)
                {
                    this->moveGameObjectWhenTouch(Vec2(headPosObject.x, 0), Vec2(lastPosObject.x, touchObject->getHeightObject()),posMoveTouch);
                }
                else{
                    this->moveGameObjectWhenTouch(Vec2(headPosObject.x, headPosObject.y - deltaY), Vec2(lastPosObject.x, lastPosObject.y - deltaY),posMoveTouch);
                }
            }
        }
        if( touchObject->getTypeDirector() == HONORITAL)
        {
            if(posTouchMoveMaxtrix.x > posTouchBeginMaxtrix.x){
                //Right
                int distanceX = posTouchMoveMaxtrix.x - posTouchBeginMaxtrix.x;
                int temp = touchObject->getLastMaxtrix().x;
                int maxX = temp + distanceX;
                int deltaX = 0;
                if (maxX >= MAX_WIDTH_GAMEBOARD){
                    maxX = MAX_WIDTH_GAMEBOARD;
                }
                for ( int i = temp ; i < maxX; i++){
                    
                    if(gameboard->arrayAvaibleMaxtrix.at(i + headPosObject.y*MAX_WIDTH_GAMEBOARD) == VISIABLE){
                        break;
                    }
                    else{
                        deltaX ++;
                    }
                }
                if(headPosObject.x + deltaX > MAX_WIDTH_GAMEBOARD)
                {
                    this->moveGameObjectWhenTouch(Vec2(MAX_HEIGHT_GAMEBOARD - touchObject->getLenghtObject(), headPosObject.y ), Vec2(MAX_HEIGHT_GAMEBOARD, lastPosObject.y),posMoveTouch);
                }
                else{
                    this->moveGameObjectWhenTouch(Vec2(headPosObject.x + deltaX, headPosObject.y ), Vec2(lastPosObject.x + deltaX, lastPosObject.y),posMoveTouch);
                }
                
            }
            if(posTouchMoveMaxtrix.x < posTouchBeginMaxtrix.x){
                //Left
                int distanceX = posTouchBeginMaxtrix.x - posTouchMoveMaxtrix.x;
                int temp = touchObject->getHeadMaxtrix().x;
                int minX = temp - distanceX;
                int deltaX = 0;
                if (minX <= 0){
                    minX = 0;
                }
                for ( int i = temp -1; i >= minX; i--){
                    
                    if(gameboard->arrayAvaibleMaxtrix.at(i + headPosObject.y*MAX_WIDTH_GAMEBOARD) == VISIABLE)
                    {
                        break;
                    }
                    else
                    {
                        deltaX ++;
                    }
                }
                if(headPosObject.x - deltaX  < 0)
                {
                    this->moveGameObjectWhenTouch(Vec2(0, headPosObject.y ), Vec2(touchObject->getLenghtObject(), lastPosObject.y),posMoveTouch);
                }
                else{
                    this->moveGameObjectWhenTouch(Vec2(headPosObject.x - deltaX, headPosObject.y ), Vec2(lastPosObject.x - deltaX, lastPosObject.y),posMoveTouch);
                }
            }
        }
        posTouchBeginMaxtrix = posTouchMoveMaxtrix;
        posTouchBegin = posMoveTouch;
    }
    
}
void GameScene::onTouchOneByOneEnd(Touch* mTouch, Event* pEvent)
{
    /**
     Count move for touch
     */
    if(touchObject != nullptr)
    {
        if(oldHeaderVec.x != touchObject->getHeadMaxtrix().x || oldHeaderVec.y != touchObject->getHeadMaxtrix().y)
        {
            countMove ++;
            sprintf(bufferCountMove, "%d", countMove);
            lbMoveGame->setString(bufferCountMove);
            CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("soundmove.mp3");
        }
    }
    if(touchObject)
    {
        touchObject = nullptr;
        oldHeaderVec = Vec2(-1, -1);
    }
    
}

void GameScene::sendNotificationForGameScene()
{
    CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("win.mp3");
    level ++;
    if (level >= hightLevel)
    {
        if(styleGame == EASY_LEVEL)
        {
            UserDefault::getInstance()->setIntegerForKey(USER_HIGHT_LEVEL_EASY, level);
        }
        else if (styleGame == MEDIUM_LEVEL)
        {
            UserDefault::getInstance()->setIntegerForKey(USER_HIGHT_LEVEL_MEDIUM, level);
        }
        else if (styleGame == HARD_LEVEL)
        {
            UserDefault::getInstance()->setIntegerForKey(USER_HIGHT_LEVEL_HARD, level);
        }
        else
        {
            UserDefault::getInstance()->setIntegerForKey(USER_HIGHT_LEVEL_EXPERT, level);
        }
    }
    if(level <= 100)
    {
        char bufferMoveBest[512] = {0};
        sprintf(bufferMoveBest, "MoveBest-%d-%d", styleGame, level-1);
        int moveBestPrevious = UserDefault::getInstance()->getIntegerForKey(bufferMoveBest,1000);
        if(moveBestPrevious > countMove)
        {
            UserDefault::getInstance()->setIntegerForKey(bufferMoveBest, countMove);
        }
        this->unschedule("UpdateLevel");
        this->scheduleOnce([=]( float dt){
            Director::getInstance()->replaceScene(GameScene::createGameScene(level, styleGame));
        }, 0.4f, "UpdateLevel");
    }
}
/*
 Move Game Objec when Touch here
 */
void GameScene::moveGameObjectWhenTouch(Vec2 headPosMaxtrix, Vec2 lastPosMaxtrix, const Vec2& posTouch)
{
    
    gameboard->printAviable();
    Vec2 oldhead= touchObject->getHeadMaxtrix();
    Vec2 ollast = touchObject->getLastMaxtrix();
    gameboard->setAviableGameBoardPostoPos(oldhead, ollast, DIVISIBALE);
    touchObject->movePostion(gameboard->convertPosMaxtrixToPosition(headPosMaxtrix), headPosMaxtrix, lastPosMaxtrix);
    Vec2 newHead = touchObject->getHeadMaxtrix();
    Vec2 newLast = touchObject->getLastMaxtrix();
    gameboard->setAviableGameBoardPostoPos(newHead, newLast, VISIABLE);
    gameboard->printAviable();
    gameboard->checkWinGame();
}

void GameScene::onEnter()
{
    Layer::onEnter();
    EventListenerKeyboard *keyboardEvent = EventListenerKeyboard::create();
    keyboardEvent->onKeyReleased = [](EventKeyboard::KeyCode keyCode, Event*){
        if(keyCode == EventKeyboard::KeyCode::KEY_BACK){
            Director::getInstance()->replaceScene(HomeScene::createHomeScene());
        }
    };
    
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyboardEvent, this);
}
void GameScene::onExit()
{
    Layer::onExit();
    Director::getInstance()->getEventDispatcher()->removeEventListenersForTarget(this);
    
}
/*
 Delegate for gameboard
 */
