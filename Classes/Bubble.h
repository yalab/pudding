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
#include "lib/Touchable.h"

USING_NS_CC;
using namespace cocos2d::ui;

class MainScene;

class Bubble : private Touchable
{
public:
    static const float SCALE;
    enum TYPE {GREEN, RED, BLUE, YELLOW, LAST};
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
    void setType(const TYPE type);
    void hide();
    void show();
    void nextTurn();
    const int getCounterIndex();
    bool isVisible();
    inline const int getPoint(){
        return 5;
    }
private:
    void burst(bool secondary = false);
    inline MainScene* getScene(){ return _scene; }
    inline Node* getFrame(){ return _frame; }
    bool isIncludeRadius(Bubble* other, const int radius);
    bool isContainStrait(Bubble* other, const int interval, const bool vertical);
    const Vec2 getPosition(){ return _image->getPosition(); }
    const int _maxSpeed;
    const int _minSpeed;
    void move();
    void render();
    const std::string path(TYPE type);
    void onTouchBegan();
    void burstNormal(bool secondary);
    void burstSpecial(const std::string& particleName, std::function<bool(Bubble* bubble)> hitTest);
    TYPE _type;
    MainScene* _scene;
    Button* _image;
    Node* _frame;
    int _invisibleTurn;
    bool _special;
};

constexpr int COUNTER_N = Bubble::TYPE::LAST + 1;

#endif /* defined(__pudding__Bubble__) */
