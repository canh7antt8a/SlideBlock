//
//  SettingScene.cpp
//  SlideBlock
//
//  Created by Nguyen Chi Hoang on 3/7/17.
//
//

#include "SettingScene.h"
#include "HomeScene.h"
#include "GameDefine.h"
#include "SimpleAudioEngine.h"
#define TAG_BTN_RESTARTDATA 134
#define TAG_BTN_BACK_SETTING 135
#define TAG_BTN_MUSIC_ON_OFF 136
#define TAG_BTN_THEME_ON_OFF 137

SettingScene::~SettingScene()
{
    
}
Scene* SettingScene::createSettingScene()
{
    auto scene = Scene::create();
    auto layer = SettingScene::create();
    scene->addChild(layer);
    return scene;
}
bool SettingScene::init()
{
    if(!Layer::init())
    {
        return false;
    }
    winsize = Director::getInstance()->getWinSize();
    if( UserDefault::getInstance()->getBoolForKey("ONTHEME", true))
    {
        Sprite* spBg = Sprite::create("bgHomeScene.png");
        spBg->setPosition(Vec2(winsize.width/2, winsize.height/2));
        this->addChild(spBg,1);
    }
    else
    {
        Sprite* spBg = Sprite::create("bgHomeScene_Off.png");
        spBg->setPosition(Vec2(winsize.width/2, winsize.height/2));
        this->addChild(spBg,1);
    }
    
    
    /*
     Touch event
     */
    /*Add Event*/
    auto lister = EventListenerTouchOneByOne::create();
    lister->setSwallowTouches(true);
    lister->onTouchBegan = CC_CALLBACK_2(SettingScene::onTouchOneByOneBegan, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(lister, this);
    
    /*
     image layerSetting
     */
    settingSpr = Sprite::create("bg_setting.png");
    settingSpr->setPosition(Vec2(winsize.width/2, winsize.height/2));
    this->addChild(settingSpr,2);
    
    /*
     Button Restart data
     */
    btnRestartData = ui::Button::create("resetdata_normal.png","resetdata_pressed.png","",ui::Widget::TextureResType::LOCAL);
    btnRestartData->setPosition(Vec2(settingSpr->getPositionX(), settingSpr->getPositionY() - settingSpr->getContentSize().height*0.3));
    btnRestartData->setTag(TAG_BTN_RESTARTDATA);
    btnRestartData->addClickEventListener(CC_CALLBACK_1(SettingScene::btnClickButton,this));
    this->addChild(btnRestartData,2);
    
    musicSpr = Sprite::create("music.png");
    musicSpr->setPosition(Vec2(settingSpr->getPositionX() - musicSpr->getContentSize().width*1.2, settingSpr->getPositionY() + musicSpr->getContentSize().height*0.4));
    this->addChild(musicSpr,3);
    
    themeSpr = Sprite::create("themes.png");
    themeSpr->setPosition(Vec2(settingSpr->getPositionX() + themeSpr->getContentSize().width*1.2, settingSpr->getPositionY() + themeSpr->getContentSize().height*0.4));
    this->addChild(themeSpr,3);
    
    /*
     thumbSwitchMusic
     */
    thumbSwitchMusic = Sprite::create("bg_choose_onoff.png");
    thumbSwitchMusic->setPosition(Vec2( musicSpr->getPosition().x , musicSpr->getPosition().y - musicSpr->getContentSize().height*0.7));
    this->addChild(thumbSwitchMusic,4);
    
    btnOnOffMusic = ui::Button::create();
    btnOnOffMusic->loadTextures("button_choose.png","","",ui::Widget::TextureResType::LOCAL);
    btnOnOffMusic->setTag(TAG_BTN_MUSIC_ON_OFF);
    btnOnOffMusic->addClickEventListener(CC_CALLBACK_1(SettingScene::btnClickButton,this));
    
    positionMusicON = Vec2(thumbSwitchMusic->getPositionX() + thumbSwitchMusic->getContentSize().width*0.4, thumbSwitchMusic->getPositionY());
    positionMusicOFF = Vec2(thumbSwitchMusic->getPositionX() - thumbSwitchMusic->getContentSize().width*0.4, thumbSwitchMusic->getPositionY());
    
    lbOnMusic = Label::createWithTTF("On", "HKABEL.TTF", 30);
    lbOnMusic->setPosition(Vec2(positionMusicON.x - lbOnMusic->getContentSize().width/2, positionMusicON.y));
    lbOffMusic = Label::createWithTTF("Off", "HKABEL.TTF", 30);
    lbOffMusic->setPosition(Vec2(positionMusicOFF.x + lbOffMusic->getContentSize().width/2, positionMusicOFF.y));
    
    
    isOnMusic =  UserDefault::getInstance()->getBoolForKey("ONMUSIC", true);
    if(isOnMusic)
    {
        btnOnOffMusic->setPosition(positionMusicON);
        isOnMusic = true;
        lbOnMusic->setVisible(false);
        lbOffMusic->setVisible(true);
    }
    else
    {
        btnOnOffMusic->setPosition(positionMusicOFF);
        isOnMusic = false;
        lbOnMusic->setVisible(true);
        lbOffMusic->setVisible(false);
    }
    this->addChild(lbOnMusic,5);
    this->addChild(lbOffMusic,5);
    this->addChild(btnOnOffMusic , 5);
    
    
    /*
     thumbSwitchTheme
     */
    thumbSwitchTheme = Sprite::create("bg_choose_themes.png");
    thumbSwitchTheme->setPosition(Vec2( themeSpr->getPosition().x , themeSpr->getPosition().y - themeSpr->getContentSize().height*0.72));
    this->addChild(thumbSwitchTheme,4);
    
    positionThemeON = Vec2(thumbSwitchTheme->getPositionX() + thumbSwitchTheme->getContentSize().width*0.4, thumbSwitchTheme->getPositionY());
    
    positionThemeOFF = Vec2(thumbSwitchTheme->getPositionX() - thumbSwitchTheme->getContentSize().width*0.4, thumbSwitchTheme->getPositionY());
    
    btnOnOffTheme = ui::Button::create();
    btnOnOffTheme->loadTextures("button_choose.png","","",ui::Widget::TextureResType::LOCAL);
    btnOnOffTheme->setTag(TAG_BTN_THEME_ON_OFF);
    btnOnOffTheme->addClickEventListener(CC_CALLBACK_1(SettingScene::btnClickButton,this));
    
    
    isOnTheme = UserDefault::getInstance()->getBoolForKey("ONTHEME", true);
    
    lbOnTheme = Label::createWithTTF("On", "HKABEL.TTF", 30);
    lbOnTheme->setPosition(Vec2(positionThemeON.x - lbOnTheme->getContentSize().width/2, positionThemeON.y));
    
    lbOffTheme = Label::createWithTTF("Off", "HKABEL.TTF", 30);
    lbOffTheme->setPosition(Vec2(positionThemeOFF.x + lbOffTheme->getContentSize().width/2, positionMusicOFF.y));
    if(isOnTheme)
    {
        btnOnOffTheme->setPosition(positionThemeON);
        isOnTheme = true;
        lbOnTheme->setVisible(false);
        lbOffTheme->setVisible(true);
    }
    else
    {
        btnOnOffTheme->setPosition(positionThemeOFF);
        isOnTheme = false;
        lbOnTheme->setVisible(true);
        lbOffTheme->setVisible(false);
    }
    this->addChild(lbOnTheme,5);
    this->addChild(lbOffTheme,5);
    this->addChild(btnOnOffTheme , 5);
    
    
    
    
    /*Button Back*/
    ui::Button* btnBack = ui::Button::create("backscene_normal.png","backscene_pressed.png","",ui::Widget::TextureResType::LOCAL);
    btnBack->setPosition(Vec2(btnBack->getContentSize().height/2,btnBack->getContentSize().height/2));
    btnBack->setTag(TAG_BTN_BACK_SETTING);
    btnBack->addClickEventListener(CC_CALLBACK_1(SettingScene::btnClickButton,this));
    this->addChild(btnBack,1234);
    
    this->scheduleUpdate();
    return true;
}
void SettingScene::update(float dt)
{
    
}
bool SettingScene::onTouchOneByOneBegan(Touch* mTouch, Event* pEvent)
{
    Vec2 posTouchBegin = mTouch->getLocation();
    
    if(posTouchBegin.y > positionMusicON.y - thumbSwitchMusic->getContentSize().height/2 && posTouchBegin.y <  positionMusicON.y + thumbSwitchMusic->getContentSize().height/2)
    {
        if(posTouchBegin.x > (positionMusicON.x + positionMusicOFF.x)/2 && posTouchBegin.x < positionMusicON.x && !isOnMusic)
        {
            btnOnOffMusic->runAction(MoveTo::create(0.2f, positionMusicON));
            isOnMusic = true;
            lbOnMusic->setVisible(false);
            lbOffMusic->setVisible(true);
            UserDefault::getInstance()->setBoolForKey("ONMUSIC", true);
        }
        if(posTouchBegin.x < (positionMusicON.x + positionMusicOFF.x)/2 && posTouchBegin.x > positionMusicOFF.x &&isOnMusic)
        {
            btnOnOffMusic->runAction(MoveTo::create(0.2f, positionMusicOFF));
            isOnMusic = false;
            lbOnMusic->setVisible(true);
            lbOffMusic->setVisible(false);
            
            UserDefault::getInstance()->setBoolForKey("ONMUSIC", false);
        }
    }
    if(posTouchBegin.y > positionThemeON.y - thumbSwitchTheme->getContentSize().height/2 && posTouchBegin.y <  positionThemeON.y + thumbSwitchTheme->getContentSize().height/2)
    {
        if(posTouchBegin.x > (positionThemeON.x + positionThemeOFF.x)/2 && posTouchBegin.x < positionThemeON.x && !isOnTheme)
        {
            btnOnOffTheme->runAction(MoveTo::create(0.14f, positionThemeON));
            isOnTheme = true;
            
            lbOnTheme->setVisible(false);
            lbOffTheme->setVisible(true);
            UserDefault::getInstance()->setBoolForKey("ONTHEME", true);
            Director::getInstance()->replaceScene(SettingScene::createSettingScene());
        }
        if(posTouchBegin.x < (positionThemeON.x + positionThemeOFF.x)/2 && posTouchBegin.x > positionThemeOFF.x && isOnTheme)
        {
            btnOnOffTheme->runAction(MoveTo::create(0.14f, positionThemeOFF));
            isOnTheme = false;
            lbOnTheme->setVisible(true);
            lbOffTheme->setVisible(false);
            UserDefault::getInstance()->setBoolForKey("ONTHEME", false);
            Director::getInstance()->replaceScene(SettingScene::createSettingScene());
        }
    }
    return true;
}

void SettingScene::createSwitchWith(Sprite* bgSwitch,  ui::Button* btnOff,  ui::Button* btnOn)
{
    
}
void SettingScene::btnClickButton(Ref* pSender)
{
    
    int  tag =  ((ui::Button*)pSender)->getTag();
    if (tag == TAG_BTN_BACK_SETTING)
    {
        Director::getInstance()->replaceScene(HomeScene::createHomeScene());
    }
    if (tag == TAG_BTN_MUSIC_ON_OFF)
    {
        if(isOnMusic)
        {
            isOnMusic = false;
            btnOnOffMusic->runAction(MoveTo::create(0.2f, positionMusicOFF));
            
            lbOnMusic->setVisible(true);
            lbOffMusic->setVisible(false);
            UserDefault::getInstance()->setBoolForKey("ONMUSIC", false);
            
            CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.0f);
            CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(0.0f);
            
        }
        else
        {
            isOnMusic = true;
            btnOnOffMusic->runAction(MoveTo::create(0.2f, positionMusicON));
            lbOnMusic->setVisible(false);
            lbOffMusic->setVisible(true);
            UserDefault::getInstance()->setBoolForKey("ONMUSIC", true);
            CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(1.0f);
            CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(1.0f);
        }
    }
    if(tag == TAG_BTN_THEME_ON_OFF)
    {
        if(isOnTheme)
        {
            isOnTheme = false;
            btnOnOffTheme->runAction(MoveTo::create(0.14f, positionThemeOFF));
            lbOnTheme->setVisible(true);
            lbOffTheme->setVisible(false);
            UserDefault::getInstance()->setBoolForKey("ONTHEME", false);
            Director::getInstance()->replaceScene(SettingScene::createSettingScene());
        }
        else
        {
            isOnTheme = true;
            btnOnOffTheme->runAction(MoveTo::create(0.14f, positionThemeON));
            lbOnTheme->setVisible(false);
            lbOffTheme->setVisible(true);
            UserDefault::getInstance()->setBoolForKey("ONTHEME", true);
            Director::getInstance()->replaceScene(SettingScene::createSettingScene());
        }
    }
    if(tag == TAG_BTN_RESTARTDATA)
    {
        for (int i = 1; i <= 100; i++) {
            char bufferMoveBestDisplay[512] = {0};
            sprintf(bufferMoveBestDisplay, "MoveBest-%d-%d", 1, i);
            UserDefault::getInstance()->setIntegerForKey(bufferMoveBestDisplay,1000);
        }
        for (int i = 1; i <= 100; i++) {
            char bufferMoveBestDisplay[512] = {0};
            sprintf(bufferMoveBestDisplay, "MoveBest-%d-%d", 2, i);
            UserDefault::getInstance()->setIntegerForKey(bufferMoveBestDisplay,1000);
        }
        for (int i = 1; i <= 100; i++) {
            char bufferMoveBestDisplay[512] = {0};
            sprintf(bufferMoveBestDisplay, "MoveBest-%d-%d", 3, i);
            UserDefault::getInstance()->setIntegerForKey(bufferMoveBestDisplay,1000);
        }
        for (int i = 1; i <= 100; i++) {
            char bufferMoveBestDisplay[512] = {0};
            sprintf(bufferMoveBestDisplay, "MoveBest-%d-%d", 4, i);
            UserDefault::getInstance()->setIntegerForKey(bufferMoveBestDisplay,1000);
        }
        
        UserDefault::getInstance()->setIntegerForKey(USER_HIGHT_LEVEL_EASY, 1);
        UserDefault::getInstance()->setIntegerForKey(USER_HIGHT_LEVEL_MEDIUM, 1);
        UserDefault::getInstance()->setIntegerForKey(USER_HIGHT_LEVEL_HARD, 1);
        UserDefault::getInstance()->setIntegerForKey(USER_HIGHT_LEVEL_EXPERT, 1);
        UserDefault::getInstance()->setBoolForKey("ONTHEME", true);
        UserDefault::getInstance()->setBoolForKey("ONMUSIC", true);
        Director::getInstance()->replaceScene(SettingScene::createSettingScene());
        
    }
}
void SettingScene::onEnter()
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
void SettingScene::onExit()
{
    Layer::onExit();
    Director::getInstance()->getEventDispatcher()->removeEventListenersForTarget(this);
    
}
