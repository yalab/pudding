//
//  StageData.h
//  pudding
//
//  Created by Atsushi Yoshida on 2015/12/10.
//
//

#ifndef StageData_h
#define StageData_h

#include <array>
#include "Bubble.h"
#include "StageData.h"

typedef struct StageData{
    const int no;
    std::array<int, Bubble::TYPE::LAST> rates;
    std::array<int, Bubble::TYPE::LAST> conditions;
} StageData;

extern std::vector<const StageData> stagesData;

#endif /* StageData_h */
