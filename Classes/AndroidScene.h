//
//  AndroidScene.h
//  SlideBlock
//
//  Created by Hoang Nguyen on 12/10/16.
//
//

#ifndef AndroidScene_h
#define AndroidScene_h

#include <stdio.h>

#include "cocos2d.h"
using namespace cocos2d;
class AndroidScene: public Layer{
public:
    static Scene* CreateScene();
    virtual bool init();
    CREATE_FUNC(AndroidScene);
    void update(float dt);
};
#endif /* AndroidScene_h */
