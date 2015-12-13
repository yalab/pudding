//
//  StageData.cpp
//  pudding
//
//  Created by Atsushi Yoshida on 2015/12/10.
//
//

#include "StageData.h"

std::vector<const StageData> stagesData = {
    //                                                      rate             |    clear
    // bubbleCount, minSpeed, maxSpeed, turnLimit, white, red, blue, yellow, |  white, red, blue, yellow, combo
    {           20,       2,       5,        30, {  10,  10,   10,     10}, {     0,   0,    0,      0,    10}},
    {           25,       5,      10,        20, {  10,  10,   10,     10}, {     0,   0,    0,      0,    10}},
    {            4,       2,       5,        10, {  10,  10,   10,     10}, {     0,   0,    0,      0,     3}}

};

const char* kplayableStageNo = "playableStageNo";