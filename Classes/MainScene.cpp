#include "MainScene.h"
#include "editor-support/cocostudio/CocoStudio.h"
#include "CocosGUI.h"
#include "Bubble.h"
#include "StageData.h"
#include "MapScene.h"
#include "ResultScene.h"

USING_NS_CC;
using namespace cocostudio;
using namespace cocos2d::ui;

std::string comboCount = "count_4";

Scene* MainScene::createScene(const int stageNo)
{
    auto scene = Scene::create();
    auto layer = MainScene::create();
    layer->setStageNo(stageNo);
    scene->addChild(layer);
    return scene;
}

bool MainScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    _csb = CSLoader::createNode("Scene/MainScene/MainScene.csb");
    this->addChild(_csb);
    return true;
}

void MainScene::onEnter()
{
    const StageData stageData = stagesData[_stageNo];
    setCounter(comboCount, 0);
    auto board = _csb->getChildByName("Board");
    setStageData(stageData);
    for(int i = 0; i < stageData.bubbleCount; i++){
        auto bubble = Bubble::create(this, board, stageData.minSpeed, stageData.maxSpeed, true);
        _bubbles.push_back(bubble);
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
    auto button = static_cast<Widget*>(_csb->getChildByName("menu_button"));
    button->setTouchEnabled(true);
    button->addTouchEventListener([](Ref* ref, Widget::TouchEventType event){
        if(event != Widget::TouchEventType::ENDED){
            return;
        }
        auto scene = MapScene::createScene();
        auto t = TransitionPageTurn::create(0.5, scene, true);
        Director::getInstance()->replaceScene(t);
    });
    Layer::onEnter();
}

void MainScene::onExit()
{
    _bubbles.clear();
    Layer::onExit();
}

void MainScene::showStartMessage()
{
    Director::getInstance()->getEventDispatcher()->setEnabled(false);
    std::stringstream ss;
    ss << std::to_string(_turnLimit) + "ターンいないに";
    ss << std::to_string(_conditions[Bubble::TYPE::BOMB]) + "コンボしよう";
    auto seq = Sequence::create(CallFuncN::create([](Ref* ref){
                                    static_cast<Node*>(ref)->setPosition(Vec2(480, 500));
                                }),
                                MoveTo::create(0.5f, Vec2(320, 500)),
                                DelayTime::create(1.5f),
                                CallFuncN::create([](Ref* ref){
                                    Director::getInstance()->getEventDispatcher()->setEnabled(true);
                                    static_cast<Node*>(ref)->removeFromParent();
                                }),
                                nullptr);
    showMessage(ss.str(), seq);
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
        _counts[Bubble::TYPE::BOMB] = 1;
    }
    setCounter(comboCount, _counts[Bubble::TYPE::BOMB]);
    setCounter(bubble->getCounterName(), _counts[bubble->getType()]);
    nextTurn();
}

void MainScene::nextTurn()
{
    _turn ++;
    for(auto b: _bubbles){
        b->nextTurn();
    }
    if(isClear()){
        stageClear();
        return;
    }
    std::stringstream ss;
    ss << std::to_string(_turn);
    ss << "/";
    ss << std::to_string(_turnLimit);
    auto turnLabel = static_cast<TextBMFont*>(_csb->getChildByName("count_turn"));
    turnLabel->setString(ss.str());
    if(isGameOver()){
        gameOver();
    }
}

bool MainScene::isClear()
{
    auto clearConditions = 0;
    for(int i = 0; i < _conditions.size(); i++){
        if(_counts.at(i) >= _conditions[i]){
            clearConditions++;
        }
    }
    return clearConditions >= _conditions.size();
}

bool MainScene::isGameOver()
{
    if(_turn >= _turnLimit){
        return true;
    }
    auto itr = std::find_if(_bubbles.begin(), _bubbles.end(), [](std::shared_ptr<Bubble> bubble){
        return bubble->isVisible();
    });
    if(itr == _bubbles.end()){
        return true;
    }
    return false;
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
    UserDefault::getInstance()->setIntegerForKey(kplayableStageNo, _stageNo + 1);
    Director::getInstance()->getEventDispatcher()->setEnabled(false);
    auto seq = Sequence::create(CallFuncN::create([](Ref* ref){
                                    static_cast<Node*>(ref)->setPosition(Vec2(320, 600));
                                }),
                                DelayTime::create(1.5f),
                                FadeOut::create(0.5f),
                                CallFuncN::create([](Ref* ref){
                                    auto scene = ResultScene::createScene();
                                    TransitionFadeUp::create(1.0f, scene);
                                    auto d = Director::getInstance();
                                    d->replaceScene(scene);
                                    d->getEventDispatcher()->setEnabled(true);
                                }),
                                nullptr);
    showMessage("くりあ!!", seq);
}

void MainScene::gameOver()
{
    Director::getInstance()->getEventDispatcher()->setEnabled(false);
    auto seq = Sequence::create(CallFuncN::create([](Ref* ref){
        static_cast<Node*>(ref)->setPosition(Vec2(320, 600));
    }),
                                DelayTime::create(1.5f),
                                FadeOut::create(0.5f),
                                CallFuncN::create([](Ref* ref){
        auto scene = MapScene::createScene();
        TransitionTurnOffTiles::create(2.0f, scene);
        auto d = Director::getInstance();
        d->replaceScene(scene);
        d->getEventDispatcher()->setEnabled(true);
    }),
                                nullptr);
    showMessage("くりあしっぱい", seq);
}

void MainScene::showMessage(const std::string message, FiniteTimeAction* actions)
{
    auto node = CSLoader::createNode("Scene/MainScene/Message.csb");
    auto n = node->getChildByName("bg_message")->getChildByName("message_label");
    auto label = static_cast<TextBMFont*>(n);
    label->setString(message);
    _csb->addChild(node);
    node->runAction(actions);
}
