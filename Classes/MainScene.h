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
    {
        for(int i = 0; i < Bubble::TYPE::LAST; i++){
//            _counts[i] = 0;
        }
    }
    void countBubble(Bubble* bubble);
    inline void setCurrentType(Bubble::TYPE type){ _currentType = type; }
    virtual bool init();
    CREATE_FUNC(MainScene);
    Bubble::TYPE _currentType;
    std::unordered_map<int, int> _counts;
    Node* _csb;
private:
    void setCounter(const std::string& name, const int count);
};

#endif // __MAIN_SCENE_H__
