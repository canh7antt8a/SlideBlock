//
//  HomeScene.h
//  SlideBlock
//
//  Created by Hoang Nguyen on 12/9/16.
//
//

#ifndef HomeScene_h
#define HomeScene_h

#include <stdio.h>
#include "cocos2d.h"
#include "ui/CocosGUI.h"
USING_NS_CC;
class HomeScene : public Layer {
public:
    Size winsize;
    ui::Button* btnPlay;
    ui::Button* btnPuzzle;
    ui::Button* btnMore;
    
    ui::Button* btnHelp;
    ui::Button* btnSetting;
public:
    HomeScene();
    virtual bool init();
    virtual ~HomeScene();
    static Scene* createHomeScene();
    CREATE_FUNC(HomeScene);
    void createButton();
    void btnClickButtonHome(Ref* pSender);
    
    void onEnter();
    void onExit();
};
#endif /* HomeScene_h */
