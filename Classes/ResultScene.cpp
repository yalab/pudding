//
//  ResultScene.cpp
//  pudding
//
//  Created by Atsushi Yoshida on 2015/12/13.
//
//

#include "ResultScene.h"
#include "editor-support/cocostudio/CocoStudio.h"
#include "CocosGUI.h"
#include "MapScene.h"

using namespace cocos2d::ui;

Scene* ResultScene::createScene()
{
    auto scene = Scene::create();
    auto layer = ResultScene::create();
    scene->addChild(layer);
    return scene;
}

bool ResultScene::init()
{
    Layer::init();
    _csb = CSLoader::createNode("Scene/ResultScene/ResultScene.csb");
    this->addChild(_csb);
    return true;
}

void ResultScene::onEnter()
{
    Layer::onEnter();
    auto button = static_cast<Button*>(_csb->getChildByName("back_button"));
    button->setTouchEnabled(true);
    button->addTouchEventListener([](Ref* ref, Widget::TouchEventType type){
        if(type != Widget::TouchEventType::ENDED){
            return;
        }
        auto scene = MapScene::createScene();
        auto t = TransitionCrossFade::create(1.0, scene);
        Director::getInstance()->replaceScene(t);
    });
}