//
//  GameDefine.h
//  SlideBlock
//
//  Created by Hoang Nguyen on 11/29/16.
//
//

#ifndef GameDefine_h
#define GameDefine_h

#define END_LEVEL 5
#define TOTAL_ROW 4
#define TOTAL_COLUM 5

#define MAX_WIDTH_GAMEBOARD 6
#define MAX_HEIGHT_GAMEBOARD 6
#define SIZE_SHAPE_WIDTH      80
#define SIZE_SHAPE_HEIGTH      80


#define DIRECTOR_HOME 123
#define DIRECTOR_MODE 124

#define EASY_LEVEL 1
#define MEDIUM_LEVEL 2
#define HARD_LEVEL 3
#define EXPERT_LEVEL 4


#define USER_HIGHT_LEVEL_EASY "EasyLevel"
#define USER_HIGHT_LEVEL_MEDIUM "MediumLevel"
#define USER_HIGHT_LEVEL_HARD "HardLevel"
#define USER_HIGHT_LEVEL_EXPERT "ExpertLevel"

typedef enum
{
    VERTICAL = 0,
    HONORITAL = 1
}TYPE_GAME;

typedef enum
{
    NORMARL = 0,
    SPACE = 1,
}TYPESPACE_OB;

typedef enum
{
    DIVISIBALE = 0,
    VISIABLE = 1
}AVAIBLE_SHAPE;


typedef enum
{
    LEFT = 0,
    RIGHT = 1,
    TOP = 2,
    DOWN = 3
}TYPE_MOVE;



typedef enum
{
    IDLE = 0,
    PAUSE,
    WIN,
    GAMEOVER
}STATUS_GAME;



#endif /* GameDefine_h */
