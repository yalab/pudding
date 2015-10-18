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

Bubble::Bubble(const int x, const int y, Bubble::TYPE type)
: _x(x)
, _y(y)
, _type(type)
{
}

std::shared_ptr<Bubble> Bubble::create(Node* board, const int x, const int y)
{
    int margin = 10;
    auto boardSize = board->getContentSize();
    TYPE type = Bubble::TYPE::COOKIE;
    auto bubble = std::make_shared<Bubble>(x, y, type);
    auto image = ImageView::create("sweets/item_cake.png", ImageView::TextureResType::PLIST);
    image->setScale(0.2f);
    Size size(20, 20);
    image->setPosition(Vec2(size.width * x + margin,
                            size.height * y + margin));
    board->addChild(image);
    return bubble;
}

void Bubble::setType(TYPE type)
{
    _type = type;
}
