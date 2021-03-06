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
#include <complex>
#include <cmath>

using namespace cocos2d::ui;

const float Bubble::SCALE = 0.8f;

Bubble::Bubble(MainScene* scene, Node* board, int minSpeed, int maxSpeed)
: _scene(scene)
, _image(nullptr)
, _frame(nullptr)
, _minSpeed(minSpeed)
, _maxSpeed(maxSpeed)
, _invisibleTurn(0)
, _special(false)
{
    _frame = Node::create();
    auto pathName = path(Bubble::TYPE::BLUE);
    _image = Button::create(pathName, pathName, pathName, Button::TextureResType::PLIST);
    _frame->addChild(_image);
    setRandomType();
    onTouch(_image, [&](Ref* ref){
        onTouchBegan();
    });
    _image->setScale(Bubble::SCALE);
    board->addChild(_frame);
    move();
}

std::shared_ptr<Bubble> Bubble::create(MainScene* scene, Node* board, const int minSpeed, const int maxSpeed)
{
    auto boardSize = board->getContentSize();
    auto bubble = std::make_shared<Bubble>(scene, board, minSpeed, maxSpeed);
    return bubble;
}

void Bubble::onTouchBegan()
{
    burst();
    getScene()->nextTurn();
}

void Bubble::burst(bool secondary)
{
    if(!isVisible()){
        return;
    }
    hide();
    
    if(!_special){
        burstNormal(secondary);
        return;
    }
    switch(getType()){
    case TYPE::RED:
        burstSpecial("Particles/bomb.plist", [&](Bubble* other){
            return isIncludeRadius(other, 200);
        });
        break;
    case TYPE::YELLOW:
        burstSpecial("Particles/thunder.plist", [&](Bubble* other){
            return isContainStrait(other, 20, true);
        });
        break;
    case TYPE::GREEN:
        burstSpecial("Particles/thunder.plist", [&](Bubble* other){
            return isContainStrait(other, 20, false);
        });
        break;
    case TYPE::BLUE:
        stopAll(2.0);
        break;
    default:
        break;
    }
}

void Bubble::burstNormal(bool secondary)
{
    auto scene = getScene();
    scene->countBubble(this, secondary);
    const StageData stageData = getScene()->getStageData();
    auto comboCount = scene->getComboCount();
    const int special = stageData.specials[getType()];
    if(!secondary &&  special > 0 && comboCount % special == 0){
        _special = true;
        setType(getType());
        show();
    }else{
        setRandomType();
    }
}

void Bubble::burstSpecial(const std::string& particleName, std::function<bool(Bubble*)> hitTest)
{
    auto particle = ParticleSystemQuad::create(particleName);
    particle->setPosition(getPosition());
    auto scene = getScene();
    scene->addChild(particle);
    const auto bubbles = scene->getBubbles();
    for(auto bubble: bubbles){
        if(bubble.get() == this){
            continue;
        }
        if(hitTest(bubble.get())){
            bubble->burst(true);
        }
    }
}

const std::string Bubble::path(TYPE type)
{
    if(_special){
        switch(type){
        case TYPE::RED:
            return "Image/bubble-fire.png";
        case TYPE::YELLOW:
            return "Image/bubble-lightning.png";
        case TYPE::BLUE:
            return "Image/bubble-ice.png";
        case TYPE::GREEN:
            return "Image/bubble-wind.png";
        case TYPE::LAST:
            CCASSERT(false, "TYPE::LAST is invalid.");
        }
    }else{
        switch(type){
        case TYPE::BLUE:
            return "Image/bubble-blue.png";
        case TYPE::RED:
            return "Image/bubble-red.png";
        case TYPE::YELLOW:
            return "Image/bubble-yellow.png";
        case TYPE::GREEN:
            return "Image/bubble-green.png";
        case TYPE::LAST:
            CCASSERT(false, "TYPE::LAST is invalid.");
        }
    }
}

void Bubble::setRandomType()
{
    std::random_device rnd;
    std::mt19937 mt(rnd());
    std::uniform_int_distribution<> randomType(0, TYPE::LAST - 1);
    setType(static_cast<TYPE>(randomType(mt)));
}

void Bubble::setType(const TYPE type)
{
    _type = type;
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

void Bubble::show()
{
    _image->setVisible(true);
    _invisibleTurn = 0;
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

const int Bubble::getCounterIndex()
{
    return static_cast<int>(getType());
}

void Bubble::move()
{
    const Size size = _frame->getParent()->getContentSize();
    const Vec2 p = Vec2(random(0, static_cast<int>(size.width)), random(0, static_cast<int>(size.height)));
    const float d = static_cast<float>(random(_minSpeed, _maxSpeed));
    auto seq = Sequence::create(MoveTo::create(10.0/d, p), CallFunc::create([&](){
        move();
    }), nullptr);
    _image->stopAllActions();
    
    float t = random(0.3, 0.8);
    float volume = random(0.8, 1.4);
    auto infrate = ScaleTo::create(t, volume);
    auto defate  = ScaleTo::create(t, 1.0);
    auto frate = RepeatForever::create(Sequence::create(infrate, defate, nullptr));
    _image->runAction(frate);
    _image->runAction(seq);
}

void Bubble::stop(const float sec)
{
    _image->stopAllActions();
    _image->scheduleOnce([&](float dt){
        move();
    }, sec, "stop");
}

void Bubble::stopAll(const float sec)
{
    auto scene = getScene();
    const auto bubbles = scene->getBubbles();
    for(auto bubble: bubbles){
        bubble->stop(sec);
    }
}


bool Bubble::isVisible()
{
    return _image->isVisible();
}

bool Bubble::isIncludeRadius(Bubble* other, const int radius)
{
    const auto p1 = getPosition();
    const auto p2 = other->getPosition();
    auto x = std::abs(p2.x - p1.x);
    auto y = std::abs(p2.y - p1.y);
    auto r = std::sqrt(std::pow(x, 2) + std::pow(y, 2));
    return r < radius;
}

bool Bubble::isContainStrait(Bubble* other, const int interval, const bool vertical)
{
    auto frameSize = getFrame()->getParent()->getContentSize();
    auto center = getPosition();
    auto pos = other->getPosition();
    Vec2 p1, p2;
    if(vertical){
        p1 = Vec2(center.x - interval, 0);
        p2 = Vec2(center.x + interval, frameSize.height);
    }else{
        p1 = Vec2(0, center.y - interval);
        p2 = Vec2(frameSize.height, center.y + interval);
    }
    return p1.x <= pos.x && pos.x <= p2.x &&
           p1.y <= pos.y && pos.y <= p2.y;
}