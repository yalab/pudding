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
    enum TYPE {BLUE, RED, GREEN, BOMB, LAST};
    Bubble(MainScene* scene, Node* board, const int x, const int y, bool removable);
    virtual ~Bubble(){};
    static std::shared_ptr<Bubble> create(MainScene* scene, Node* board, const int x, const int y, bool remobable);
    inline TYPE getType(){ return _type; }
    void moveTo(const int x, const int y);
    void setRandomType();    
private:
    void render();
    const std::string path(TYPE type);
    void onTouchBegan();
    int _x;
    int _y;
    TYPE _type;
    bool _remobable;
    MainScene* _scene;
    Button* _image;
    void onDeleted();
};

#endif /* defined(__pudding__Bubble__) */
