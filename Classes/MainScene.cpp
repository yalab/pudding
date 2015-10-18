#include "MainScene.h"
#include "editor-support/cocostudio/CocoStudio.h"
#include "CocosGUI.h"
#include "Bubble.h"
#include <array>
USING_NS_CC;
using namespace cocostudio;
using namespace cocos2d::ui;

std::array<std::shared_ptr<Bubble>, MainScene::MAX::X * MainScene::MAX::Y> MainScene::BUBBLES;
std::array<std::shared_ptr<Bubble>, MainScene::MAX::NEXT> MainScene::NEXT_BUBBLES;

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
    auto csb = CSLoader::createNode("Scene/MainScene.csb");
    this->addChild(csb);
    
    auto nextArea = csb->getChildByName("NextArea");
    for(int i = 0; i < MAX::NEXT; i++){
        auto bubble = Bubble::create(this, nextArea, 0, i, false);
        NEXT_BUBBLES[i] = bubble;
    }
    
    auto board = csb->getChildByName("Board");
    for(int y = 0; y < MAX::Y; y++){
        for(int x = 0; x < MAX::X; x++){
            auto bubble = Bubble::create(this, board, x, y, true);
            auto n = y * MAX::X + x;
            BUBBLES[n] = bubble;
        }
    }
    
    return true;
}

std::shared_ptr<Bubble> MainScene::currentBubble()
{
    return NEXT_BUBBLES.front();
}