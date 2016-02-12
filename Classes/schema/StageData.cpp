//
//  StageData.cpp
//  pudding
//
//  Created by Atsushi Yoshida on 2015/12/10.
//
//

#include "StageData.h"

const std::vector<const StageData> stagesData = {
    //                                                       |         rate             | specials                  |   clear
    // bubbleCount, minSpeed, maxSpeed, turnLimit, timeLimit, white, red, blue, yellow, |  wind, fire, ice, thunder |white, red, blue, yellow, combo
    {           20,       2,       5,        30,           0, {  10,  10,   10,     10}, {1,   5,  1,  1}, {     0,   0,    0,      0,    10}},
    {           25,       5,      10,        20,         180, {  10,  10,   10,     10}, {-1,  5, -1,  5}, {     0,   0,    0,      0,    10}},
    {            4,       2,       5,        10,           0, {  10,  10,   10,     10}, { 5,  5,  5,  5}, {     0,   0,    0,      0,     3}}

};

const char* kplayableStageNo = "playableStageNo";