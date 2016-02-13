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
    const int bubbleCount;
    const int minSpeed;
    const int maxSpeed;
    const int turnLimit;
    const int timeLimit;
    const std::array<int, Bubble::TYPE::LAST> rates;
    const std::array<int, Bubble::TYPE::LAST> specials;
    const std::array<int, COUNTER_N> conditions;
} StageData;

extern  const std::vector<const StageData> stagesData;
extern const char* kplayableStageNo;

#endif /* StageData_h */
