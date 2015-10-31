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

Bubble::Bubble(MainScene* scene, Node* board, const int x, const int y, bool remobable)
: _scene(scene)
, _x(x)
, _y(y)
, _remobable(remobable)
, _image(nullptr)
{
    setRandomType();
    _image->addTouchEventListener([&](Ref* ref, Widget::TouchEventType eventType){
        if(eventType == Widget::TouchEventType::BEGAN){
            onTouchBegan();
        }
    });
    _image->setScale(0.2f);
    board->addChild(_image);
    moveTo(x, y);
}

std::shared_ptr<Bubble> Bubble::create(MainScene* scene, Node* board, const int x, const int y, bool remobable)
{
    auto boardSize = board->getContentSize();
    auto bubble = std::make_shared<Bubble>(scene, board, x, y, remobable);
    return bubble;
}

void Bubble::onTouchBegan()
{
    if(_scene->currentBubble()->getType() == this->getType()){
        onDeleted();
    }
    log("%i, %i, %i", _x, _y, _type);
}

const std::string Bubble::path(TYPE type)
{
    switch(type){
        case TYPE::BLUE:
            return "Image/icon_soul.png";
        case TYPE::RED:
            return "Image/icon_pumpkin.png";
        case TYPE::GREEN:
            return "Image/icon_star_off.png";
        case TYPE::BOMB:
            return "Image/icon_skull.png";
        case TYPE::LAST:
            CCASSERT(false, "TYPE::LAST is invalid.");
    }
}

void Bubble::onDeleted()
{
    _image->setVisible(false);
    _scene->slideNextBubble();
}

void Bubble::setRandomType()
{
    std::random_device rnd;
    std::mt19937 mt(rnd());
    std::uniform_int_distribution<> randomType(0, TYPE::LAST - 1);
    _type = static_cast<TYPE>(randomType(mt));
    const std::string pathName = path(_type);
    if(_image){
        _image->loadTextureNormal(pathName, Button::TextureResType::PLIST);
    }else{
        _image = Button::create(pathName, pathName, pathName, Button::TextureResType::PLIST);
    }
    
}

void Bubble::moveTo(const int x, const int y)
{
    const int margin = 10;
    const int frameMargin = 20;
    Size size(20, 20);
    auto pos = Vec2(frameMargin + size.width * x + margin * x,
                    frameMargin + size.height * y + margin * y);
    _image->setPosition(pos);
}