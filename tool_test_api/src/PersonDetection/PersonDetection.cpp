#include "PersonDetection.hpp"
using namespace std;


PersonDetection::PersonDetection() {

}

PersonDetection::~PersonDetection() {

}

void PersonDetection::Login() {    
    std::cin >> ip;
    urlLogin = HTTPS_URL + ip + LOGIN_URL;
    std::cout << "username" << std::endl;
    std::cin >> username;
    std::cout << "userpwd" << std::endl;
    std::cin >> userpwd;
    LOGIN["username"] = username;
    LOGIN["userpwd"] = userpwd;
    header = "Content-Type: application/json";
    HttpClient::postData(LOGIN.dump(), urlLogin.c_str(), respon, header);
    if (respon.responseString.empty()) {
        std::cout << respon.responseCode << std::endl;
    } else {
        json res;
        std::cout << respon.responseString << std::endl;
        res = json::parse(respon.responseString);
        token = res["data"]["access_token"];
        std::cout << token << std::endl;
    }
}

void PersonDetection::TurnOn() {
    header2 = "Content-Type: application/json";
    urlTurnon = HTTPS_URL + ip + TURNON_URL + token;
    TURNON["type"] = type;
    json zone = json::array();
    params["width"] = 1280;
    params["height"] = 720;
    params["zones"] = zone;
    params["allowed_amount"] = 3;
    params["repeated_time"] = 5;
    TURNON["params"] = params;
    tags["group_id"] = 1;
    TURNON["tags"] = tags;
    extras["server"]["use"] = false;
    extras["server"]["url_data"] = "http://192.168.1.200/api/monitor";
    extras["server"]["url_media"] = "http://192.168.1.200/api/monitor";
    extras["server"]["notify_server"]["use"] = true;
    extras["server"]["notify_server"]["sleep"] = 300000;
    extras["server"]["backup"] = true;
    extras["server"]["access_token"] = token;
    extras["alarm_output"] = false;
    extras["event_type"] = "12";
    extras["base64"] = false;
    extras["cam_id"] = 1;
    TURNON["extras"] = extras;
    TURNON["enable"] = enable;
    TURNON["record"] = record;
    TURNON["sleep"] = 300000;
    json schedule = json::array();
    TURNON["schedule_time"] = schedule;
    HttpClient::postData(TURNON.dump(), urlTurnon.c_str(), respon2, header2);
    std::cout << TURNON.dump(4) << std::endl;
    if (respon2.responseString.empty()) {
        std::cout << respon2.responseCode << std::endl;
    } else {
        json res2;
        std::cout << respon2.responseString << std::endl;
        res2 = json::parse(respon2.responseString);
        monitor_uuid = res2["data"]["monitor_uuid"];
        std::cout << monitor_uuid << std::endl;
    }
}

void PersonDetection::GetData(HttpSession *session) {
    url_ImageID = HTTPS_URL + ip + PERSON_DETECTION + token;
    session->setUrl(url_ImageID);
    session->setMethod("GET");
    if (session->start() == true) {
        std::string jNews((const char *)session->getData(), session->getSize());
        json j = json::parse(jNews);
        for (auto i : j["data"]["events"]) {
            std::cout << i << std::endl;
            std::cout << std::endl;
            image_id = i["image_id"]; 
            std::cout << image_id << std::endl;
            url_GetData = HTTPS_URL + ip + GET_PERSONDETECTION + image_id + ACCESS_TOKEN + token;
            session->setUrl(url_GetData);
            session->setMethod("GET");
            if (session->start() == true) {
                std::cout << url_GetData << std::endl;
            }
        }
    }
}

