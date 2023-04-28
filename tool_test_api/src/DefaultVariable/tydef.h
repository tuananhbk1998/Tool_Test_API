//
//  tydef.h
//  AiCAM
//
//  Created by Nguyen Xuan Truong on 10/11/2022.
//  Copyright © 2022 Nguyen Xuan Truong. All rights reserved.
//

#ifndef __TYPEDEF_H__
#define __TYPEDEF_H__

#include <iostream>
#include <string>
#include <curl/curl.h>
#include "../Json/json.hpp"
#include <vector>
#include <pthread.h>
#include <fstream>
#include <ctime>
#include <sys/stat.h>
#include <iomanip>
#include <memory>
#include <map>
#include <algorithm> 
#include <functional>
#include <queue>
#include <mutex>
#include <unistd.h>
#include <cstdlib>
#include <unistd.h>
#include <sstream>

using json = nlohmann::json;

// define type in all class
typedef std::string STRING;
typedef void VOID;
typedef void* PVOID;
typedef int INT;
typedef bool BOOLEAN;
typedef size_t SIZE_T;
typedef uint8_t* PUINT8;
typedef struct curl_slist* PCURLLIST;
typedef CURL* PCURL;
typedef struct curl_httppost* PHTTPPOST;
typedef std::vector<std::string> VECTOR_STR;
typedef json JSON;
typedef const char* PCHAR;
typedef std::vector<std::vector<int>> VECTOR_POINT;

#endif // __TYPEDEF_H__