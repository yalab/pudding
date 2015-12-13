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
#include "StageData.h"

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
    const int playableStageNo = UserDefault::getInstance()->getIntegerForKey(kplayableStageNo);
    this->addChild(_csb);
    auto area = static_cast<ScrollView*>(_csb->getChildByName("stages"));
    area->setDirection(ScrollView::Direction::BOTH);
    area->scrollToBottom(0.0f, false);
    auto bg = area->getChildByName("bg");
    for(int stageNo = 0; stageNo < stagesData.size(); stageNo++){
        if(stageNo > playableStageNo){
            break;
        }
        auto button = ImageView::create("Image/icon_question.png");
        auto w = stageNo % 5 + 1;
        auto h = stageNo / 5 + 1;
        
        button->setPosition(Vec2(w * 100, h * 120));
        bg->addChild(button);
        button->setTouchEnabled(true);
        button->addTouchEventListener([stageNo](Ref* ref, Widget::TouchEventType eventType){
        auto scene = MainScene::createScene(stageNo);
        auto t = TransitionPageTurn::create(0.5, scene, false);
            Director::getInstance()->replaceScene(t);
        });
    }
    auto resetButton = static_cast<Button*>(area->getChildByName("reset_button"));
    resetButton->addTouchEventListener([](Ref* ref, Widget::TouchEventType event){
        if(event != Widget::TouchEventType::ENDED){
            return;
        }
        UserDefault::getInstance()->setIntegerForKey(kplayableStageNo, 0);
        auto scene = MapScene::createScene();
        Director::getInstance()->replaceScene(scene);
    });
    return true;
}