//
//  DataGame.h
//  SlideBlock
//
//  Created by Hoang Nguyen on 12/8/16.
//
//

#ifndef DataGame_h
#define DataGame_h

#include <stdio.h>

class DataGame
{
public:
    int x1;
    int y1;
    int x2;
    int y2;
    int typeObject;
public:
    DataGame(int x1, int y1,int x2, int y2, int typeObject);
    virtual ~DataGame();
};

#endif /* DataGame_hpp */
