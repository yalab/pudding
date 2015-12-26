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
    static const float SCALE;
    enum TYPE {WHITE, RED, BLUE, YELLOW, BOMB, LAST};
    Bubble(MainScene* scene, Node* board, const int minSpeed, const int maxSpeed);
    virtual ~Bubble()
    {
        _image = nullptr;
        _scene = nullptr;
        _frame = nullptr;
    };
    static std::shared_ptr<Bubble> create(MainScene* scene, Node* board, const int minSpeed, const int maxSpeed);
    inline const TYPE getType(){ return _type; }
    void setRandomType();
    void hide();
    void nextTurn();
    const std::string getCounterName();
    bool isVisible();
private:
    const int _maxSpeed;
    const int _minSpeed;
    void move();
    void render();
    const std::string path(TYPE type);
    void onTouchBegan();
    TYPE _type;
    MainScene* _scene;
    Button* _image;
    Node* _frame;
    int _invisibleTurn;
};

#endif /* defined(__pudding__Bubble__) */
