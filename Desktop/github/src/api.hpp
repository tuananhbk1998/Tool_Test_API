/**
* @Copyright (C) 2022, AI View. All rights reserved.
* @Module: Tool_testAPI
* @Author: AnhMTc
* @Created: 30/12/2022
* @Description: Manage post event AI to server
*/
#ifndef api_hpp
#define api_hpp
#include <string>
#include <vector>
#include <chrono>
#include "json.hpp"
#include "HttpClient/HttpClient.hpp"
#include "HttpSession/HttpSession.hpp"
#include "DefaultVariable/define.h"
#include "DefaultVariable/tydef.h"
using namespace std;
using namespace nlohmann;

class api {
    public:
        api();
        ~api();

        //  General
        int login(std::string ip, std::string username, std::string userpwd, std::string &res);

        //  Person Detection
        int turnOn_person(std::string type);
        void GetData_person(std::string type, HttpSession *session);
        int turnOff_person(std::string type, HttpSession *session);

        //  Face Recognition
        int turnOn_face(std::string type);
        void GetData_face(std::string type, HttpSession *session_face);
        int turnOff_face(std::string type, HttpSession *session_face);

        // Face Mask 
        int turnOn_faceMask(std::string type);
        void GetData_faceMask(std::string type, HttpSession *session_faceMask);
        int turnOff_faceMask(std::string type, HttpSession *session_faceMask);

    private:
        // HttpSession *session;
        json LOGIN, TURNON;
        HttpResponse respon, respon_person;
        std::string url, urlTurnOn, urlTurnon_person, urlTurnOff, urlTurnOff_person, urlGetImageid_person, urlCheckEvent_person, urlGetEvent_person;
        std::string header, header2;
        json tags,params, extras;
        json profile_feature, server, notify_server;
        std::string monitor_uuid_Person, imageid_person;
        bool enable = true;
        bool record = false;
        uint8_t sleep;
        json schedule_time;

    private:
        HttpResponse respon_face;
        std::string urlTurnOn_face, urlGetImageid_Face, urlCheckEvent_Face, urlGetEvent_Face, urlTurnOff_Face;
        std::string header_face;
        std::string token, monitor_uuid_Face, imageid_Face;

    private:
        HttpResponse respon_faceMask;
        std::string urlTurnOn_faceMask, urlGetImageid_FaceMask, urlCheckEvent_FaceMask, urlGetEvent_FaceMask, urlTurnOff_FaceMask;
        std::string header_faceMask;
        std::string monitor_uuid_FaceMask, imageid_FaceMask;

};

#endif 

