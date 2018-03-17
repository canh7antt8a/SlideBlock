//
//  LevelScene.cpp
//  SlideBlock
//
//  Created by Hoang Nguyen on 12/9/16.
//
//

#include "LevelScene.h"
#include "GameScene.h"
#include "GameDefine.h"
#include "ModeGameScene.h"
#include "SimpleAudioEngine.h"
#include "HomeScene.h"
#include "Admob.h"
#include "AdmodAndroid.h"
#define TAG_BTN_BACK_LEVEL_SCENE 167
#define COLOR4V Color4B(6,75,38,0)


#define BUFFER 40

LevelScene::LevelScene()
{
    
}
LevelScene::~LevelScene()
{
    
}
Scene* LevelScene::createLevelGameScene(int typeLevel, int director)
{
    auto scene = Scene::create();
    auto layer = new LevelScene();
    layer->typeLevel = typeLevel;
    layer->director = director;
    layer->initUI();
    scene->addChild(layer);
    return scene;
}
void LevelScene::initUI()
{
    CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    
    int adLevel = UserDefault::getInstance()->getIntegerForKey("ADFULLLEVEL", 1);
    UserDefault::getInstance()->setIntegerForKey("ADFULLLEVEL", adLevel + 1);
    if(adLevel % 8 == 0)
    {
#if  CC_TARGET_PLATFORM == CC_PLATFORM_IOS
        Admob::getInstance()->loadInterstitial();
        Admob::getInstance()->showInterstitial();
#endif
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
        AdmodAndroid::showFullAdvertiment();
#endif
    }
    else
    {
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
        Admob::getInstance()->showBanner(AdmobPosition::TopCenter);
#endif
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
        AdmodAndroid::showBanner();
#endif
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
    
    ui::Button* btnBack = ui::Button::create("backscene_normal.png","backscene_pressed.png","",ui::Widget::TextureResType::LOCAL);
    btnBack->setPosition(Vec2(btnBack->getContentSize().height/2,btnBack->getContentSize().height/2));
    btnBack->setTag(TAG_BTN_BACK_LEVEL_SCENE);
    btnBack->addClickEventListener(CC_CALLBACK_1(LevelScene::btnClickButton,this));
    this->addChild(btnBack,1234);
    
    Sprite* titleSpr;
    if(typeLevel == EASY_LEVEL)
    {
        titleSpr = Sprite::create("box_easy.png");
        hightLevel = UserDefault::getInstance()->getIntegerForKey(USER_HIGHT_LEVEL_EASY, 1);
    }
    if(typeLevel == MEDIUM_LEVEL)
    {
        titleSpr = Sprite::create("box_normal.png");
        hightLevel = UserDefault::getInstance()->getIntegerForKey(USER_HIGHT_LEVEL_MEDIUM, 1);
        
    }
    if(typeLevel == HARD_LEVEL)
    {
        titleSpr = Sprite::create("box_hard.png");
        hightLevel = UserDefault::getInstance()->getIntegerForKey(USER_HIGHT_LEVEL_HARD, 1);
        
    }
    if(typeLevel == EXPERT_LEVEL)
    {
        titleSpr = Sprite::create("box_expert.png");
        hightLevel = UserDefault::getInstance()->getIntegerForKey(USER_HIGHT_LEVEL_EXPERT, 1);
        
    }
    titleSpr->setPosition(Vec2(winsize.width/2, winsize.height*0.8));
    this->addChild(titleSpr,2);
    
    char bufferLevel[128] = {0};
    sprintf(bufferLevel, "1-%d", END_LEVEL*TOTAL_ROW*TOTAL_COLUM);
    Label* lbLevel = Label::createWithTTF(bufferLevel, "HKABEL.TTF", 36);
    lbLevel->setPosition(Vec2(titleSpr->getPositionX(), titleSpr->getPositionY() - titleSpr->getContentSize().height*0.3f));
    this->addChild(lbLevel,3);
    
    /*
     btn Next and Previous
     */
    currentPage = hightLevel/(TOTAL_COLUM*TOTAL_ROW);
    btnPrevious = ui::Button::create("button_back_normal.png","button_back_pressed.png","",ui::Widget::TextureResType::LOCAL);
    btnNext =  ui::Button::create("button_next_normal.png","button_next_pressed.png","",ui::Widget::TextureResType::LOCAL);
    btnNext->setEnabled(true);
    btnPrevious->setEnabled(true);
    btnPrevious->setPosition(Vec2(titleSpr->getPositionX() - titleSpr->getContentSize().width*0.8, titleSpr->getPositionY() + titleSpr->getContentSize().height*0.2));
    btnNext->setPosition(Vec2(titleSpr->getPositionX() + titleSpr->getContentSize().width*0.8, titleSpr->getPositionY() + titleSpr->getContentSize().height*0.2));
    this->addChild(btnPrevious,1235);
    this->addChild(btnNext,1235);
    
    // hightLevel= 100;
    
    /*
     CreateLevelGame
     */
    pageView = cocos2d::ui::PageView::create();
    pageView->setTouchEnabled(true);
    pageView->setContentSize(Size(winsize.width, winsize.height));
    pageView->setDirection(ui::ScrollView::Direction::HORIZONTAL);
    pageView->removeAllItems();
    
    for (int i = 0; i < END_LEVEL + 1 ; i++)
    {
        auto layout = cocos2d::ui::Layout::create();
        layout->setContentSize(Size(winsize.width, winsize.height));
        LayerColor* color = LayerColor::create(COLOR4V, winsize.width, winsize.height);
        color->setAnchorPoint(Vec2::ZERO);
        color->setPosition(Vec2(0,0));
        layout->addChild(color);
        
        Sprite* imgSprite = Sprite::create("bg_level.png");
        imgSprite->setPosition(Vec2(winsize.width/2, winsize.height*0.42));
        layout->addChild(imgSprite);
        
        for (int j = 0; j < TOTAL_COLUM; j++)
        {
            for (int k = 0; k < TOTAL_ROW; k++)
            {
                int index = (i - 1)*TOTAL_ROW*TOTAL_COLUM + (k + j*TOTAL_ROW) + 1;
                
                auto buttonLevel = ui::Button::create();
                if(index <= hightLevel)
                {
                    buttonLevel->loadTextures("level_open.png","","",ui::Widget::TextureResType::LOCAL);
                    auto label = Label::createWithTTF("", "HKABEL.TTF", 32);
                    char str[512] = {0};
                    sprintf(str, "%d",index);
                    label->setString(str);
                    label->setPosition(Vec2(buttonLevel->getContentSize().width/2, buttonLevel->getContentSize().height/2));
                    buttonLevel->addChild(label,100);
                    buttonLevel->setEnabled(true);
                }
                else
                {
                    buttonLevel->loadTextures("level_lock.png","","",ui::Widget::TextureResType::LOCAL);
                    buttonLevel->setEnabled(false);
                }
               
                
                buttonLevel->addClickEventListener(CC_CALLBACK_1(LevelScene::btnClickButtonLevel,this));
                buttonLevel->setTag(index + 1000);
                float height = winsize.height/2 + (TOTAL_ROW/2*buttonLevel->getContentSize().height/3*2) - j*(buttonLevel->getContentSize().height + 8.0f);
                buttonLevel->setPosition(Vec2(buttonLevel->getContentSize().width*1.5 + (buttonLevel->getContentSize().width + BUFFER)*k,height));
                
                layout->addChild(buttonLevel);
            }
        }
        
        pageView->insertPage(layout, i);
    }
    pageView->removeItem(0);
    pageView->scrollToItem(END_LEVEL - 2);
    pageView->setCurrentPageIndex(currentPage);
    pageView->addEventListener(CC_CALLBACK_2(LevelScene::pageViewEventCustom, this));
    this->addChild(pageView,4);
    
    
}

void LevelScene::pageViewEventCustom(Ref *pSender, cocos2d::ui::PageView::EventType type)
{
    switch (type)
    {
        case cocos2d::ui::PageView::EventType::TURNING:
        {
            
        }
            break;
            
        default:
            break;
    }
    
}
void LevelScene::btnClickButtonLevel(Ref* pSender)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("soundClick.mp3");
    int  tag =  ((ui::Button*)pSender)->getTag();
    Director::getInstance()->replaceScene(GameScene::createGameScene(tag-1000, typeLevel));
}

void LevelScene::btnClickButton(Ref* pSender)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("soundClick.mp3");
    int  tag =  ((ui::Button*)pSender)->getTag();
    if(tag == TAG_BTN_BACK_LEVEL_SCENE)
    {
        if(director == DIRECTOR_HOME)
        {
            Director::getInstance()->replaceScene(HomeScene::createHomeScene());
        }
        else
        {
            Director::getInstance()->replaceScene(ModeGameScene::createModeGameScene());
        }
    }
}


void LevelScene::onEnter()
{
    Layer::onEnter();
    EventListenerKeyboard *keyboardEvent = EventListenerKeyboard::create();
    keyboardEvent->onKeyReleased = [](EventKeyboard::KeyCode keyCode, Event*){
        if(keyCode == EventKeyboard::KeyCode::KEY_BACK){
            Director::getInstance()->popScene();
        }
    };
    
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyboardEvent, this);
}
void LevelScene::onExit(){
    Layer::onExit();
    Director::getInstance()->getEventDispatcher()->removeEventListenersForTarget(this);
}

