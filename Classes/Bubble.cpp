//
//  Bubble.cpp
//  pudding
//
//  Created by Atsushi Yoshida on 2015/10/18.
//
//

#include "Bubble.h"
#include "MainScene.h"
#include "CocosGUI.h"
#include <random>

using namespace cocos2d::ui;

const float Bubble::SCALE = 0.8f;

Bubble::Bubble(MainScene* scene, Node* board, int minSpeed, int maxSpeed, bool remobable)
: _scene(scene)
, _remobable(remobable)
, _image(nullptr)
, _frame(nullptr)
, _minSpeed(minSpeed)
, _maxSpeed(maxSpeed)
, _invisibleTurn(0)
{
    _frame = Node::create();
    auto pathName = path(Bubble::TYPE::BLUE);
    _image = Button::create(pathName, pathName, pathName, Button::TextureResType::PLIST);
    _frame->addChild(_image);
    setRandomType();
    _image->addTouchEventListener([&](Ref* ref, Widget::TouchEventType eventType){
        if(eventType == Widget::TouchEventType::BEGAN){
            onTouchBegan();
        }
    });
    _image->setScale(Bubble::SCALE);
    board->addChild(_frame);
    move();
}

std::shared_ptr<Bubble> Bubble::create(MainScene* scene, Node* board, const int minSpeed, const int maxSpeed, bool remobable)
{
    auto boardSize = board->getContentSize();
    auto bubble = std::make_shared<Bubble>(scene, board, minSpeed, maxSpeed, remobable);
    return bubble;
}

void Bubble::onTouchBegan()
{
    hide();
    _scene->countBubble(this);
    setRandomType();
}

const std::string Bubble::path(TYPE type)
{
    switch(type){
        case TYPE::BLUE:
            return "Image/icon_soul.png";
        case TYPE::RED:
            return "Image/icon_pumpkin.png";
        case TYPE::YELLOW:
            return "Image/icon_star_off.png";
        case TYPE::WHITE:
            return "Image/icon_skull.png";
        case TYPE::BOMB:
            return "Image/icon_time.png";
        case TYPE::LAST:
            CCASSERT(false, "TYPE::LAST is invalid.");
    }
}

void Bubble::setRandomType()
{
    std::random_device rnd;
    std::mt19937 mt(rnd());
    std::uniform_int_distribution<> randomType(0, TYPE::BOMB - 1);
    _type = static_cast<TYPE>(randomType(mt));
    const std::string pathName = path(_type);
    _image->loadTextureNormal(pathName, Button::TextureResType::PLIST);
    _image->loadTextureDisabled(pathName, Button::TextureResType::PLIST);
    _image->loadTexturePressed(pathName, Button::TextureResType::PLIST);
}

void Bubble::hide()
{
    _image->setVisible(false);
    _invisibleTurn = static_cast<int>(getType()) + 1;
}

void Bubble::nextTurn()
{
    if(_invisibleTurn > 0){
        _invisibleTurn --;
    }else{
        _invisibleTurn = 0;
        _image->setVisible(true);
    }
}

const std::string Bubble::getCounterName()
{
    return "count_" + std::to_string(static_cast<int>(getType()));
}

void Bubble::move()
{
    const Size size = _frame->getParent()->getContentSize();
    const Vec2 p = Vec2(random(0, static_cast<int>(size.width)), random(0, static_cast<int>(size.height)));
    const float d = static_cast<float>(random(_minSpeed, _maxSpeed));
    auto seq = Sequence::create(MoveTo::create(10.0/d, p), CallFunc::create([&](){
        move();
    }), nullptr);
    _image->runAction(seq);
}

bool Bubble::isVisible()
{
    return _image->isVisible();
}