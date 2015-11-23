#include "MainScene.h"
#include "editor-support/cocostudio/CocoStudio.h"
#include "CocosGUI.h"
#include "Bubble.h"
#include <array>
USING_NS_CC;
using namespace cocostudio;
using namespace cocos2d::ui;

std::array<std::shared_ptr<Bubble>, MainScene::MAX::X * MainScene::MAX::Y> MainScene::BUBBLES;

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

    auto board = _csb->getChildByName("Board");
    for(int y = 0; y < MAX::Y; y++){
        for(int x = 0; x < MAX::X; x++){
            auto bubble = Bubble::create(this, board, x, y, true);
            auto n = y * MAX::X + x;
            BUBBLES[n] = bubble;
        }
    }
    return true;
}

void MainScene::touchBubble(Bubble* bubble)
{
    _counts[bubble->getType()] ++;
    if(_currentType == bubble->getType()){
        _counts[Bubble::TYPE::LAST] ++;
    }else{
        _currentType = bubble->getType();
        _counts[Bubble::TYPE::LAST] = 0;
    }
    bubble->hide();
    setCounter("combo_count", _counts[Bubble::TYPE::LAST]);
    setCounter(bubble->getCounterName(), _counts[bubble->getType()]);
    for(auto b: BUBBLES){
        b->nextTurn();
    }
    for(auto c: _counts){
        log("count: %i %i", c.first, c.second);
    }
}

void MainScene::setCounter(const std::string& name, const int count)
{
    std::stringstream ss;
    ss << count;
    auto counter = static_cast<TextBMFont*>(_csb->getChildByName(name));
    counter->setString(ss.str());
}