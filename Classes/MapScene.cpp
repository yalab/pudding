//
//  MapScene.cpp
//  pudding
//
//  Created by Atsushi Yoshida on 2015/12/11.
//
//

#include "MapScene.h"
#include "editor-support/cocostudio/CocoStudio.h"
#include "CocosGUI.h"
#include "MainScene.h"

USING_NS_CC;
using namespace cocostudio;
using namespace cocos2d::ui;

Scene* MapScene::createScene()
{
    auto scene = Scene::create();
    auto layer = MapScene::create();
    scene->addChild(layer);
    return scene;
}

bool MapScene::init()
{
    _csb = CSLoader::createNode("Scene/MapScene/MapScene.csb");
    this->addChild(_csb);
    auto area = static_cast<ScrollView*>(_csb->getChildByName("stages"));
    area->setDirection(ScrollView::Direction::BOTH);
    area->scrollToBottom(0.0f, false);
    auto nodes = area->getChildByName("bg")->getChildren();
    for(auto n: nodes){
        auto node = static_cast<Widget*>(n);
        const int stageNo = std::stoi(node->getName().substr(5));
        log("stage %i", stageNo);
        node->setTouchEnabled(true);
        node->addTouchEventListener([stageNo](Ref* ref, Widget::TouchEventType eventType){
            auto scene = MainScene::createScene(stageNo);
            auto t = TransitionPageTurn::create(0.5, scene, false);
            Director::getInstance()->replaceScene(t);
        });
    }
    return true;
}