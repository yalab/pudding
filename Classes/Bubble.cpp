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

using namespace cocos2d::ui;

Bubble::Bubble(MainScene* scene, Node* board, const int x, const int y, Bubble::TYPE type, bool remobable)
: _scene(scene)
, _x(x)
, _y(y)
, _type(type)
, _remobable(remobable)
{
    const int margin = 10;
    const int frameMargin = 20;
    auto path = "sweets/item_cake.png";
    _image = Button::create(path, path, path, Button::TextureResType::PLIST);
    _image->addTouchEventListener([&](Ref* ref, Widget::TouchEventType eventType){
        if(eventType == Widget::TouchEventType::BEGAN){
            onTouchBegan();
        }
    });
    _image->setScale(0.2f);
    Size size(20, 20);
    _image->setPosition(Vec2(frameMargin + size.width * x + margin * x,
                            frameMargin + size.height * y + margin * y));
    board->addChild(_image);

}

std::shared_ptr<Bubble> Bubble::create(MainScene* scene, Node* board, const int x, const int y, bool remobable)
{
    auto boardSize = board->getContentSize();
    TYPE type = Bubble::TYPE::COOKIE;
    auto bubble = std::make_shared<Bubble>(scene, board, x, y, type, remobable);
    return bubble;
}

void Bubble::setType(TYPE type)
{
    _type = type;
}

void Bubble::onTouchBegan()
{
    if(_scene->currentBubble()->getType() == this->getType()){
        _image->setVisible(false);
    }
    log("%i, %i", _x, _y);
}
