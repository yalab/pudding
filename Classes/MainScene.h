#ifndef __MAIN_SCENE_H__
#define __MAIN_SCENE_H__

#include "cocos2d.h"
#include "Bubble.h"

class Bubble;

class MainScene : public cocos2d::Layer
{
public:
    enum MAX {X = 5, Y = 5};
    static std::array<std::shared_ptr<Bubble>, MAX::X * MAX::Y> BUBBLES;
    static cocos2d::Scene* createScene();
    
    MainScene()
    : _currentType(Bubble::TYPE::LAST)
    , _count(0)
    {
    }
    void selectBubble(Bubble* bubble);
    inline void setCurrentType(Bubble::TYPE type){ _currentType = type; }
    virtual bool init();
    CREATE_FUNC(MainScene);
    Bubble::TYPE _currentType;
    int _count;
    Node* _csb;
};

#endif // __MAIN_SCENE_H__
