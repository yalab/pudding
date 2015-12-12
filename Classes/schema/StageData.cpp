//
//  StageData.cpp
//  pudding
//
//  Created by Atsushi Yoshida on 2015/12/10.
//
//

#include "StageData.h"

std::vector<const StageData> stagesData = {
    //                                    rate             |    clear
    //   no, bubbleCount, minSpeed, maxSpeed, turnLimit, white, red, blue, yellow, |  white, red, blue, yellow, combo
    {     1,          20,       20,       50,        30, {  10,  10,   10,     10}, {     0,   0,    0,      0,    10}},
    {     2,          20,       50,      100,        20, {  10,  10,   10,     10}, {     0,   0,    0,      0,    10}}

};
