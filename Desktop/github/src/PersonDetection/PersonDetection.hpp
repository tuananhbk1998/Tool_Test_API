/**
* @Copyright (C) 2022, AI View. All rights reserved.
* @Module: TestAPI_PersonDetection
* @Author: AnhMTc
* @Created: 30/12/2022
* @Description: Manage post event AI to server
*/

#include <iostream>
#include <fstream>
#include <ctime>
#include <string>
#include "json.hpp"
#include "HttpSession.hpp"
#include "HttpClient.hpp"
#include "tydef.h"
#include "define.h"
#include "curl/curl.h"

class PersonDetection {
    public:
        PersonDetection();
        ~PersonDetection();
        void Login();
        void TurnOn();
        void GetData(HttpSession *session);

    private:
        CURL *curl;
        std::string urlLogin, urlTurnon, url_ImageID, url_GetData;
        std::string ip, username, userpwd;
        json LOGIN, TURNON, GET_IMAGE;
        std::string header, header2;
        std::vector<std::string> header3;
        HttpResponse respon, respon2, respon3;
        std::string token, monitor_uuid, image_id;
        

        std::string type = "persondetection";
        json tags;
        json params;
        json extras;
        bool enable = true;
        bool record = false;
        uint64_t sleep;
        json schedule_time;
};