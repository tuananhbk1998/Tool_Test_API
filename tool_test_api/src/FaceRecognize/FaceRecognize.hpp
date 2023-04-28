/**
* @Copyright (C) 2022, AI View. All rights reserved.
* @Module: TestAPI_FaceRecognize
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

class FaceRecognition {
    public:
        FaceRecognition();
        ~FaceRecognition();

        void Login();
        void getEvent(HttpSession *session);

    private:
        std::string ip, username, userpwd;
        std::string urlLogin, urlGetData, urlGetImage;
        std::string header;
        HttpResponse respon, respon2;
        std::string token, image_id;
        json LOGIN;
        
};