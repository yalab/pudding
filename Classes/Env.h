#ifndef __mermaid__Env_h
#define __mermaid__Env_h

#include <string>
#include <unordered_map>

#ifdef __APPLE__
#include "TargetConditionals.h"
#endif


#if TARGET_IPHONE_SIMULATOR
// SIMULATOR
static const std::string API_URL = "http://localhost:3000";
#elif COCOS2D_DEBUG
//DEBUG
static const std::string API_URL = "https://omermaid-stg.herokuapp.com";
#else
//RELEASE
static const std::string API_URL = "https://omermaid.herokuapp.com";
#endif

static const std::string GAME_ID = "mermaid";

static const std::unordered_map<int, const std::string> SKU = {{120, "com.oke_ya.mermaid.charge1"}};


#endif //__mermaid__Env_h
