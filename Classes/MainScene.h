#ifndef __MAIN_SCENE_H__
#define __MAIN_SCENE_H__

#include "cocos2d.h"

class Bubble;
class MainScene : public cocos2d::Layer
{
public:
    enum MAX {NEXT = 5, X = 5, Y = 5};

    static std::array<std::shared_ptr<Bubble>, MAX::X * MAX::Y> BUBBLES;
    static std::array<std::shared_ptr<Bubble>, MAX::NEXT> NEXT_BUBBLES;

    static cocos2d::Scene* createScene();
    std::shared_ptr<Bubble> currentBubble();
    virtual bool init();
    CREATE_FUNC(MainScene);
};

#endif // __MAIN_SCENE_H__
