##include "api.hpp"

api::api() {
    
}

api::~api() {

}

int api::login(string ip, string username, string userpwd, string &res) {
    LOGIN["username"] = username;
    LOGIN["userpwd"] = userpwd;
    url = HTTPS_URL + ip + LOGIN_URL;
    urlTurnOn = HTTPS_URL + ip + TURNON_URL;
    header = "Content-Type: application/json";
    HttpClient::postData(LOGIN.dump(), url.c_str(), respon, header);
    if (respon.responseString.empty()) {
        return 0;
    } else {
        json res;
        std::cout << respon.responseString << std::endl;
        res = json::parse(respon.responseString);
        token = res["data"]["access_token"];
    }

    urlTurnOff = HTTPS_URL + ip + TURNOFF_URL+ "/";
    //  Person Detection
    urlGetImageid_person = HTTPS_URL + ip + PERSON_DETECTION + token;
    urlCheckEvent_person = HTTPS_URL + ip + GET_PERSONDETECTION;
    //  Face Recognition
    urlGetImageid_Face = HTTPS_URL + ip + FACE_RECOGNITION + token;
    urlCheckEvent_Face = HTTPS_URL + ip + IMAGE_ID_FACE;
    //  Face Mask
    urlGetImageid_FaceMask = HTTPS_URL + ip + FACEMASK + token;
    urlCheckEvent_FaceMask = HTTPS_URL + ip + IMAGE_ID_FACEMASK;

    return 1;
}   

int api::turnOn_person(string type) {
    json zone = json::array();
    TURNON["type"] = "persondetection";
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
    header2 = "Content-Type: application/json";
    urlTurnon_person = urlTurnOn + token;
    HttpClient::postData(TURNON.dump(), urlTurnon_person.c_str(), respon_person, header2);
    if (respon_person.responseString.empty()) {
        std::cout << respon_person.responseCode << std::endl;
    } else {
        json res2;
        std::cout << respon_person.responseString << std::endl;
        res2 = json::parse(respon_person.responseString);
        monitor_uuid_Person = res2["data"]["monitor_uuid"];
    }
}

int api::turnOff_person(string type, HttpSession *session) {
    session = new HttpSession();
    if (session == nullptr) {
        delete session;
    }
    urlTurnOff_person = urlTurnOff + monitor_uuid_Person + ACCESS_TOKEN + token;
    std::cout << "urlTurnOff_person: " << urlTurnOff_person << std::endl;
    session->setUrl(urlTurnOff_person);
    session->setMethod("DELETE");
    if (session->start() == true) {
    std::cout << "DELETED PERSON" << std::endl;
    }
}

void api::GetData_person(string type, HttpSession *session) {
    session = new HttpSession();
    if (session == nullptr) {
        delete session;
    }
    session->setUrl(urlGetImageid_person);
    session->setMethod("GET");
    if (session->start() == true) {
        std::string jNews((const char *)session->getData(), session->getSize());
        json j = json::parse(jNews);
        for (auto i : j["data"]["events"]) {
            std::cout << i << std::endl;
            std::cout << std::endl;
            imageid_person = i["image_id"]; 
            std::cout << "imageid_person: " << imageid_person << std::endl;
            urlGetEvent_person = urlCheckEvent_person + imageid_person + ACCESS_TOKEN + token;
            std::string res_person = "Success Person Detection";
            std::string type_person = "PersonDetection.txt";
            std::string failed_person = "Failed to Detect AI Face";
            std::ofstream out_person(type_person, ios::out | ios::app);
            session->setUrl(urlGetEvent_person);
            session->setMethod("GET");
            if (session->start() == true) {
                std::cout << "urlGetEvent_person: " << urlGetEvent_person << std::endl;
                out_person << res_person << std::endl;
                out_person << urlGetEvent_person << std::endl;
            } else {
                out_person << failed_person << std::endl;
            }
        }
    }
}

int api::turnOn_face(std::string type) {
    TURNON["type"] = "facerecognition";
    tags["group_id"] = 1;
    TURNON["tags"] = tags;
    params["width"] = 1280;
    params["height"] = 720;
    json zones = json::array();
    params["zones"] = zones;
    TURNON["params"] = params;
    extras["enable_embeddings"] = false;
    profile_feature["profile_size"] = 160;
    profile_feature["threshold_recognize"] = 0.74;
    extras["profile_feature"] = profile_feature;
    server["use"] = false;
    server["url_data"] = "http://10.2.64.100/api/monitor";
    server["url_media"] = "http://10.2.64.100/api/monitor";
    notify_server["use"] = true;
    notify_server["sleep"] = 300000;
    server["notify_server"] = notify_server;
    server["backup"] = true;
    server["access_token"] = token;
    extras["server"] = server;
    extras["alarm_output"] = false;
    extras["event_type"] = 12;
    extras["base64"] = false;
    extras["cam_id"] = 1;
    TURNON["extras"] = extras;
    TURNON["enable"] = true;
    TURNON["record"] = false;
    TURNON["sleep"] = 300000;
    json schedule_time = json::array();
    TURNON["schedule_time"] = schedule_time;

    std::string jNews_face = TURNON.dump(4);
    std::cout << jNews_face << std::endl;
    header_face = "Content-Type: application/json";
    urlTurnOn_face = urlTurnOn + token;
    std::cout << "urlTurnon_person: " << urlTurnon_person << std::endl;
    HttpClient::postData(TURNON.dump(), urlTurnOn_face.c_str(), respon_face, header_face);
    if (respon_face.responseString.empty()) {
        std::cout << respon_face.responseCode << std::endl;
    } else {
        json res2;
        std::cout << respon_face.responseString << std::endl;
        res2 = json::parse(respon_face.responseString);
        monitor_uuid_Face = res2["data"]["monitor_uuid"];
        std::cout << "monitor_uuid_Face: " << monitor_uuid_Face << std::endl;
    }
}

void api::GetData_face(std::string type, HttpSession *session_face) {
    session_face = new HttpSession();
    if (session_face == nullptr) {
        delete session_face;
    }
    session_face->setUrl(urlGetImageid_Face);
    session_face->setMethod("GET");
    if (session_face->start() == true) {
        std::string jNews_face((const char *)session_face->getData(), session_face->getSize());
        json j = json::parse(jNews_face);
        for (auto i : j["data"]["events"]) {
            imageid_Face = i["image_id"];
            urlGetEvent_Face = urlCheckEvent_Face + imageid_Face + ACCESS_TOKEN + token;
            std::string res_face = "Success Face Detection";
            std::string type_face = "FaceRecognition.txt";
            std::string failed_face = "Failed to Detect AI Face";
            std::ofstream out_face(type_face, ios::out | ios::app);
            session_face->setUrl(urlGetEvent_Face);
            session_face->setMethod("GET");
            if (session_face->start() == true) {
                std::cout << "urlGetEvent_Face: " << urlGetEvent_Face << std::endl;
                out_face << res_face << std::endl;
                out_face << urlGetEvent_Face << std::endl;
            } else {
                
            }
        }
    }

}

int api::turnOff_face(std::string type, HttpSession *session_face) {
    session_face = new HttpSession();
    if (session_face == nullptr) {
        delete session_face;
    }
    urlTurnOff_Face = urlTurnOff + monitor_uuid_Face + ACCESS_TOKEN + token;
    std::cout << "urlTurnOff_person: " << urlTurnOff_person << std::endl;
    session_face->setUrl(urlTurnOff_Face);
    session_face->setMethod("DELETE");
    if (session_face->start() == true) {
    std::cout << "DELETED FACE" << std::endl;
    }
}

int api::turnOn_faceMask(std::string type) {
    TURNON["type"] = "facemask";
    tags["group_id"] = 1;
    TURNON["tags"] = tags;
    params["width"] = 1280;
    params["height"] = 720;
    json zones = json::array();
    params["zones"] = zones;
    TURNON["params"] = params;
    server["use"] = true;
    server["url_data"] = "http://10.2.64.100/api/monitor";
    server["url_media"] = "http://10.2.64.100/api/monitor";
    notify_server["use"] = true;
    notify_server["sleep"] = 300000;
    server["notify_server"] = notify_server;
    server["backup"] = true;
    server["access_token"] = token;
    extras["server"] = server;
    extras["alarm_output"] = false;
    extras["event_type"] = 12;
    extras["base64"] = false;
    extras["cam_id"] = 1;
    TURNON["extras"] = extras;
    TURNON["enable"] = true;
    TURNON["record"] = false;
    TURNON["sleep"] = 300000;
    json schedule_time = json::array();
    TURNON["schedule_time"] = schedule_time;

    std::string jNews_faceMask = TURNON.dump(4);
    std::cout << jNews_faceMask << std::endl;
    header_faceMask = "Content-Type: application/json";
    urlTurnOn_faceMask = urlTurnOn + token;
    std::cout << "urlTurnon_person: " << urlTurnOn_faceMask << std::endl;
    HttpClient::postData(TURNON.dump(), urlTurnOn_faceMask.c_str(), respon_faceMask, header_faceMask);
    if (respon_faceMask.responseString.empty()) {
        std::cout << respon_faceMask.responseCode << std::endl;
    } else {
        json res2;
        std::cout << respon_faceMask.responseString << std::endl;
        res2 = json::parse(respon_faceMask.responseString);
        monitor_uuid_FaceMask = res2["data"]["monitor_uuid"];
        std::cout << "monitor_uuid_FaceMask: " << monitor_uuid_FaceMask << std::endl;
    }
}

void api::GetData_faceMask(std::string type, HttpSession *session_faceMask) {
    session_faceMask = new HttpSession();
    if (session_faceMask == nullptr) {
        delete session_faceMask;
    }
    session_faceMask->setUrl(urlGetImageid_FaceMask);
    session_faceMask->setMethod("GET");
    if (session_faceMask->start() == true) {
        std::string jNews_faceMask((const char *)session_faceMask->getData(), session_faceMask->getSize());
        json j = json::parse(jNews_faceMask);
        for (auto i : j["data"]["events"]) {
            imageid_FaceMask = i["image_id"];
            urlGetEvent_FaceMask = urlCheckEvent_FaceMask + imageid_FaceMask + ACCESS_TOKEN + token;
            std::string res_faceMask = "Success Face Mask Detection";
            std::string type_faceMask = "FaceMask.txt";
            std::string failed_faceMask = "Failed to Detect AI Face";
            std::ofstream out_faceMask(type_faceMask, ios::out | ios::app);
            session_faceMask->setUrl(urlGetEvent_FaceMask);
            session_faceMask->setMethod("GET");
            if (session_faceMask->start() == true) {
                std::cout << "urlGetEvent_Face: " << urlGetEvent_FaceMask << std::endl;
                out_faceMask << res_faceMask << std::endl;
                out_faceMask << urlGetEvent_FaceMask << std::endl;
            } else {
                
            }
        }
    }
}

int api::turnOff_faceMask(std::string type, HttpSession *session_faceMask) {
    session_faceMask = new HttpSession();
    if (session_faceMask == nullptr) {
        delete session_faceMask;
    }
    urlTurnOff_FaceMask = urlTurnOff + monitor_uuid_FaceMask + ACCESS_TOKEN + token;
    std::cout << "urlTurnOff_person: " << urlTurnOff_FaceMask << std::endl;
    session_faceMask->setUrl(urlTurnOff_FaceMask);
    session_faceMask->setMethod("DELETE");
    if (session_faceMask->start() == true) {
    std::cout << "DELETED FACE MASK" << std::endl;
    }
}
