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
#include "CocosGUI.h"

USING_NS_CC;
using namespace cocos2d::ui;

class MainScene;

class Bubble{
public:
    enum TYPE {CAKE, PUDDING, CANDY, COOKIE};
    Bubble(MainScene* scene, Node* board, const int x, const int y, Bubble::TYPE type, bool removable);
    virtual ~Bubble(){};
    static std::shared_ptr<Bubble> create(MainScene* scene, Node* board, const int x, const int y, bool remobable);
    inline TYPE getType(){ return _type; }
private:
    void onTouchBegan();
    void setType(TYPE type);
    int _x;
    int _y;
    TYPE _type;
    bool _remobable;
    MainScene* _scene;
    Button* _image;
};

#endif /* defined(__pudding__Bubble__) */
