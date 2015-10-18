//
//  Bubble.h
//  pudding
//
//  Created by Atsushi Yoshida on 2015/10/18.
//
//

#ifndef __pudding__Bubble__
#define __pudding__Bubble__

#include "cocos2d.h"
USING_NS_CC;

class Bubble{
public:
    enum TYPE {CAKE, PUDDING, CANDY, COOKIE};
    Bubble(const int x, const int y, Bubble::TYPE type);
    virtual ~Bubble(){};
    static std::shared_ptr<Bubble> create(Node* board, const int x, const int y);
private:
    void setType(TYPE type);
    int _x;
    int _y;
    TYPE _type;
    Sprite* _image;
};

#endif /* defined(__pudding__Bubble__) */
