#ifndef __MAIN_SCENE_H__
#define __MAIN_SCENE_H__

#include "cocos2d.h"
#include "Bubble.h"
#include <array>

class Bubble;
class StageData;

class MainScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene(const int stageNo);
    
    MainScene()
    : _currentType(Bubble::TYPE::LAST)
    , _turn(-1)
    , _turnLimit(0)
    , _csb(nullptr)
    {
        for(int i = 0; i < Bubble::TYPE::LAST; i++){
            _counts[i] = 0;
        }
    }
    void countBubble(Bubble* bubble, bool secondary);
    inline void setCurrentType(Bubble::TYPE type){ _currentType = type; }
    inline void setStageNo(const int stageNo){ _stageNo = stageNo; }
    inline const std::vector<const std::shared_ptr<Bubble>> getBubbles(){ return _bubbles; }
    virtual bool init();
    void onEnter();
    void onExit();
    CREATE_FUNC(MainScene);
    void incrementEffect(Node* node);
    void setStageData(const StageData& stageData);
    void nextTurn();
    void gameOver();
    void stageClear();
    inline const int getComboCount(){ return _counts[Bubble::TYPE::BOMB]; };
private:
    bool isClear();
    bool isGameOver();
    void showMessage(const std::string message, FiniteTimeAction* actions);
    std::vector<const std::shared_ptr<Bubble>> _bubbles;
    int _stageNo;
    Bubble::TYPE _currentType;
    Node* _csb;
    void showStartMessage();
    int _turn;
    void setCounter(const int i, const int count);
    std::array<int, Bubble::TYPE::LAST> _counts;
    std::array<int, Bubble::TYPE::LAST> _rates;
    std::array<int, Bubble::TYPE::LAST> _conditions;
    int _turnLimit;
};

#endif // __MAIN_SCENE_H__
