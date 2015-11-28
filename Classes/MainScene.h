#ifndef __MAIN_SCENE_H__
#define __MAIN_SCENE_H__

#include "cocos2d.h"
#include "Bubble.h"
#include <array>

class Bubble;

typedef struct StageData{
    const int no;
    std::array<int, Bubble::TYPE::LAST> rates;
    std::array<int, Bubble::TYPE::LAST> conditions;
} StageData;

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
            _counts[i] = 0;
        }
    }
    void countBubble(Bubble* bubble);
    inline void setCurrentType(Bubble::TYPE type){ _currentType = type; }
    virtual bool init();
    CREATE_FUNC(MainScene);
    Bubble::TYPE _currentType;
    std::unordered_map<int, int> _counts;
    Node* _csb;
    void incrementEffect(Node* node);
    void setStageData(StageData& stageData);
private:
    void setCounter(const std::string& name, const int count);
    int _no;
    std::array<int, Bubble::TYPE::LAST> _rates;
    std::array<int, Bubble::TYPE::LAST> _conditions;
};

#endif // __MAIN_SCENE_H__
