//
//  SettingScene.h
//  SlideBlock
//
//  Created by Nguyen Chi Hoang on 3/7/17.
//
//

#ifndef SettingScene_h
#define SettingScene_h

#include <stdio.h>
#include "cocos2d.h"
#include "ui/CocosGUI.h"
USING_NS_CC;
class SettingScene : public Layer {
public:
    Size winsize;
    Sprite* settingSpr;
    Sprite* musicSpr;
    Sprite* themeSpr;
    ui::Button* btnRestartData;
    
    Sprite* thumbSwitchMusic;
    ui::Button* btnOnOffMusic;
    Vec2 positionMusicON;
    Vec2 positionMusicOFF;
    Label* lbOnMusic;
    Label* lbOffMusic;
    bool isOnMusic;
    
    
    Sprite* thumbSwitchTheme;
    ui::Button* btnOnOffTheme;
    Vec2 positionThemeON;
    Vec2 positionThemeOFF;
    Label* lbOnTheme;
    Label* lbOffTheme;
    bool isOnTheme;
    
    
public:
    virtual bool init();
    virtual ~SettingScene();
    static Scene* createSettingScene();
       void btnClickButton(Ref* pSender);
    CREATE_FUNC(SettingScene);
    virtual void update(float dt);
    void createSwitchWith(Sprite* bgSwitch,  ui::Button* btnOff,  ui::Button* btnOn);
     bool onTouchOneByOneBegan(Touch* mTouch, Event* pEvent);
    
    void onEnter();
    void onExit();
};
#endif /* SettingScene_h */
