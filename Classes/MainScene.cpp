#include "MainScene.h"
#include "editor-support/cocostudio/CocoStudio.h"
#include "CocosGUI.h"
#include "Bubble.h"
#include "StageData.h"

USING_NS_CC;
using namespace cocostudio;
using namespace cocos2d::ui;

std::vector<const std::shared_ptr<Bubble>> MainScene::BUBBLES;

std::string comboCount = "count_4";

Scene* MainScene::createScene()
{
    auto scene = Scene::create();
    auto layer = MainScene::create();
    scene->addChild(layer);
    return scene;
}

bool MainScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Image/sweets.plist");
    _csb = CSLoader::createNode("MainScene/MainScene.csb");
    this->addChild(_csb);
    const StageData stageData = stagesData[0];
    setCounter(comboCount, 0);
    auto board = _csb->getChildByName("Board");
    setStageData(stageData);
    for(int i = 0; i < stageData.bubbleCount; i++){
        auto bubble = Bubble::create(this, board, stageData.minSpeed, stageData.maxSpeed, true);
        BUBBLES.push_back(bubble);
    }

    for(int i = 0; i < Bubble::TYPE::LAST; i++){
        std::stringstream s;
        s << "count_";
        s << i;
        setCounter(s.str(), 0);
        
        std::stringstream ss;
        ss << "max_";
        ss << i;
        setCounter(ss.str(), _conditions[i]);
    }
    nextTurn();
    setonEnterTransitionDidFinishCallback([&](){
        showStartMessage();
    });
    return true;
}

void MainScene::showStartMessage()
{
    Director::getInstance()->getEventDispatcher()->setEnabled(false);
    auto node = CSLoader::createNode("MainScene/Message.csb");
    auto n = node->getChildByName("bg_message")->getChildByName("message_label");
    auto label = static_cast<TextBMFont*>(n);
    std::stringstream ss;
    ss << std::to_string(_turnLimit) + "ターンいないに";
    ss << std::to_string(_conditions[Bubble::TYPE::BOMB]) + "コンボしよう";
    label->setString(ss.str());
    node->setPosition(Vec2(480, 500));
    _csb->addChild(node);
    
    auto seq = Sequence::create(MoveTo::create(0.5f, Vec2(320, 500)),
                                DelayTime::create(1.5f),
                                CallFuncN::create([](Ref* ref){
                                    Director::getInstance()->getEventDispatcher()->setEnabled(true);
                                    static_cast<Node*>(ref)->removeFromParent();
                                }),
                                nullptr);
    node->runAction(seq);
}

void MainScene::countBubble(Bubble* bubble)
{
    _counts[bubble->getType()] ++;
    auto combo = _csb->getChildByName("combo_label");
    if(_currentType == bubble->getType()){
        _counts[Bubble::TYPE::BOMB] ++;
        combo->setVisible(true);
        incrementEffect(combo);
    }else{
        combo->setVisible(false);
        _currentType = bubble->getType();
        _counts[Bubble::TYPE::BOMB] = 0;
    }
    setCounter(comboCount, _counts[Bubble::TYPE::BOMB]);
    setCounter(bubble->getCounterName(), _counts[bubble->getType()]);
    for(auto b: BUBBLES){
        b->nextTurn();
    }
    nextTurn();
}

void MainScene::nextTurn()
{
    _turn ++;

    std::stringstream ss;
    ss << std::to_string(_turn);
    ss << "/";
    ss << std::to_string(_turnLimit);
    auto turnLabel = static_cast<TextBMFont*>(_csb->getChildByName("count_turn"));
    turnLabel->setString(ss.str());
    if(_turn > _turnLimit){
        gameOver();
    }
    auto clearConditions = 0;
    for(int i = 0; i < _conditions.size(); i++){
        if(_counts.at(i) >= _conditions[i]){
            clearConditions++;
        }
    }
    if(clearConditions >= _conditions.size()){
        stageClear();
    }
}

void MainScene::setCounter(const std::string& name, const int count)
{
    std::stringstream ss;
    ss << count;
    auto counter = static_cast<TextBMFont*>(_csb->getChildByName(name));
    if(counter == nullptr){
        return;
    }
    counter->setString(ss.str());
    incrementEffect(counter);
}

void MainScene::incrementEffect(Node* node)
{
    auto scale = node->cocos2d::Node::getScale();
    auto seq = Sequence::create(ScaleTo::create(0.1f, scale * 1.2),
                                ScaleTo::create(0.1f, scale      ), nullptr);
    node->runAction(seq);
}

void MainScene::setStageData(const StageData& stageData)
{
    for(int i = 0; i < stageData.rates.size(); i++){
        _rates[i] = stageData.rates[i];
    }

    for(int i = 0; i < stageData.conditions.size(); i++){
        _conditions[i] = stageData.conditions[i];
    }
    _turnLimit = stageData.turnLimit;
}

void MainScene::stageClear()
{
    log("StageClear");
}

void MainScene::gameOver()
{
    log("GameOver");
}
