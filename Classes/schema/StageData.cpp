//
//  StageData.cpp
//  pudding
//
//  Created by Atsushi Yoshida on 2015/12/10.
//
//

#include "StageData.h"

std::vector<const StageData> stagesData = {
    //                rate             |    clear
    //   no, white, red, blue, yellow, |  white, red, blue, yellow, combo
    {     1, {  10,  10,   10,     10}, {     0,   0,    0,      0,    10}}
};
