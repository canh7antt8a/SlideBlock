//
//  ProgressBarCustom.h
//  PikachuConnect
//
//  Created by NguyenHoang on 8/18/16.
//
//
#ifndef ProgressBarCustom_h
#define ProgressBarCustom_h

#include <stdio.h>
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "GameDefine.h"
USING_NS_CC;



class DelegateProgress {
    public:
        virtual void setStatusProressTime(int status) = 0;
        virtual void sendStatusGame() = 0;
};

class ProgressBarCustom: public Node
{
public:
    ui::LoadingBar* loadingbar;
    int statusLoaing;
    int value;
    DelegateProgress* mDelegate;
    int countTime;
    int levelGame;
    float percenUpdate;
public:
    void createUIProgressBar(const Vec2& pos);
    ProgressBarCustom();
    virtual ~ProgressBarCustom();
    virtual void onEnter();
    virtual void onExit();
    void update(float dt);
    void setStatus(int status);
    void setvalue(float value);
    float getValue();
    static ProgressBarCustom* getInstaceProgress(int valueLoading,  int status);
    void setDelegate(DelegateProgress* delegate);
    void setLevelGame(int level);
    void setTimeUpdate(float dt);
};

#endif /* ProgressBarCustom_h */
