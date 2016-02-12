#include "MainScene.h"
#include "editor-support/cocostudio/CocoStudio.h"
#include "CocosGUI.h"
#include "Bubble.h"
#include "MapScene.h"
#include "ResultScene.h"
#include <iomanip>

USING_NS_CC;
using namespace cocostudio;
using namespace cocos2d::ui;

void MainSceneAlerm::render()
{
    std::stringstream ss;
    int d = getDay();
    if(d > 0){
        ss << d;
        ss << "Days";
    }
    int h = getHour();
    if(h < 0){
        ss << h;
        ss << ":";
    }
    ss << std::setfill('0') << std::setw(2) << getMin();
    ss << ":";
    int s = getSec();
    ss << std::setfill('0') << std::setw(2) << s;
    static_cast<TextBMFont*>(_node)->setString(ss.str());
}

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
    useTouchMaker(this);
    return true;
}

void MainScene::onEnter()
{
    Layer::onEnter();
    _csb->getChildByName<TextBMFont*>("point")->setString("0");
    const StageData stageData = getStageData();
    auto board = _csb->getChildByName("Board");
    for(int i = 0; i < stageData.bubbleCount; i++){
        auto bubble = Bubble::create(this, board, stageData.minSpeed, stageData.maxSpeed);
        _bubbles.push_back(bubble);
    }
    for(int i = 0; i < Bubble::TYPE::LAST; i++){
        setCounter(i, 0);
    }
    setAlerm();
    nextTurn();
    setonEnterTransitionDidFinishCallback([&](){
        showStartMessage();
    });
    auto button = static_cast<Widget*>(_csb->getChildByName("menu_button"));
    onTouch(button, [](Ref* ref){
        auto scene = MapScene::createScene();
        auto t = TransitionPageTurn::create(0.5, scene, true);
        Director::getInstance()->replaceScene(t);
    });
}

void MainScene::onExit()
{
    _bubbles.clear();
    Layer::onExit();
}

void MainScene::setAlerm()
{
    auto alermDisplay = _csb->getChildByName("alerm");
    const auto timeLimit = getStageData().timeLimit;
    if(timeLimit > 1){
        _alerm = std::make_shared<MainSceneAlerm>();
        _alerm->setRemainningSec(timeLimit);
        _alerm->start(alermDisplay);
        _alerm->setFinishCallback([&](){
            gameOver();
        });
    }else{
        alermDisplay->removeFromParent();
    }
}

void MainScene::showStartMessage()
{
    Director::getInstance()->getEventDispatcher()->setEnabled(false);
    std::stringstream ss;
    const StageData stageData = getStageData();
    if(stageData.turnLimit > 0){
        ss << std::to_string(stageData.turnLimit) + "ターン";
    }
    if(stageData.timeLimit > 0){
        ss << std::to_string(stageData.timeLimit) + "sec";
    }
    ss << "いないに";
    ss << std::to_string(stageData.conditions[Bubble::TYPE::FIRE]) + "コンボしよう";
    auto seq = Sequence::create(CallFuncN::create([](Ref* ref){
                                    static_cast<Node*>(ref)->setPosition(Vec2(480, 500));
                                }),
                                MoveTo::create(0.5f, Vec2(320, 500)),
                                DelayTime::create(3.0f),
                                CallFuncN::create([](Ref* ref){
                                    Director::getInstance()->getEventDispatcher()->setEnabled(true);
                                    static_cast<Node*>(ref)->removeFromParent();
                                }),
                                nullptr);
    showMessage(ss.str(), seq);
}

void MainScene::countBubble(Bubble* bubble, bool secondary)
{
    _counts[bubble->getType()] ++;
    addPoint(bubble->getPoint());
    _csb->getChildByName<TextBMFont*>("point")->setString(std::to_string(getPoint()));
    if(_currentType == bubble->getType()){
        _counts[Bubble::TYPE::FIRE] ++;
        incrementEffect(Bubble::TYPE::FIRE);
    }else if(!secondary){
        _currentType = bubble->getType();
        _counts[Bubble::TYPE::FIRE] = 1;
    }
    setCounter(Bubble::TYPE::FIRE, _counts[Bubble::TYPE::FIRE]);
    setCounter(bubble->getCounterIndex(), _counts[bubble->getType()]);
    incrementEffect(bubble->getCounterIndex());
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
    ss << std::to_string(getStageData().turnLimit);
    auto turnLabel = static_cast<TextBMFont*>(_csb->getChildByName("count_turn"));
    turnLabel->setString(ss.str());
    if(isGameOver()){
        gameOver();
    }
}

bool MainScene::isClear()
{
    auto clearConditions = 0;
    const StageData stageData = getStageData();
    for(int i = 0; i < stageData.conditions.size(); i++){
        if(_counts.at(i) >= stageData.conditions[i]){
            clearConditions++;
        }
    }
    return clearConditions >= stageData.conditions.size();
}

bool MainScene::isGameOver()
{
    if(_turn >= getStageData().turnLimit){
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

void MainScene::setCounter(const int i, const int count)
{
    auto name = "count_" + std::to_string(i);
    std::stringstream ss;
    ss << count;
    ss << "/";
    ss << getStageData().conditions[i];
    auto counter = static_cast<TextBMFont*>(_csb->getChildByName("counts")->getChildByName(name));
    if(counter == nullptr){
        return;
    }
    counter->setString(ss.str());
}

void MainScene::incrementEffect(const int i)
{
    const std::vector<const std::string> names = {"icon", "count"};
    for(auto& s: names){
        auto node = _csb->getChildByName("counts")->getChildByName(s + "_" + std::to_string(i));
        auto scale = node->cocos2d::Node::getScale();
        auto seq = Sequence::create(ScaleTo::create(0.1f, scale * 1.2),
                                    ScaleTo::create(0.1f, scale      ), nullptr);
        node->runAction(seq);
    }
}

\
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
