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

void MainScene::selectBubble(Bubble* bubble)
{
    log("count %i", _count);
    if(_currentType == bubble->getType()){
        _count ++;
    }else{
        _currentType = bubble->getType();
        _count = 1;
    }
    std::stringstream ss;
    ss << _count;
    static_cast<TextBMFont*>(_csb->getChildByName("CurrentCount"))->setString(ss.str());
}