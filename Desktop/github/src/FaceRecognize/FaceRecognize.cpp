#include "FaceRecognize.hpp"
using namespace std;

FaceRecognition::FaceRecognition() {

}

FaceRecognition::~FaceRecognition() {

}

void FaceRecognition::Login() {
    ip = "172.16.1.98";
    urlLogin = HTTPS_URL + ip + LOGIN_URL;
    username = "admin";
    userpwd = "Bkav@2020";
    LOGIN["username"] = username;
    LOGIN["userpwd"] = userpwd;
    header = "Content-Type: application/json";
    HttpClient::postData(LOGIN.dump(), urlLogin.c_str(), respon, header);
    std::cout << urlLogin << std::endl;
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

void FaceRecognition::getEvent(HttpSession *session) {
    ip = "172.16.1.98";
    urlGetData = HTTPS_URL + ip + FACE_RECOGNITION + token;
    session->setUrl(urlGetData);
    session->setMethod("GET");
    if (session->start() == true) {
        std::string jNews((const char *)session->getData(), session->getSize());
        json res = json::parse(jNews);
        for (auto i : res["data"]["events"]) {
            std::cout << i << std::endl;
            image_id = i["image_id"];
            std::cout << image_id << std::endl;
            urlGetImage = HTTPS_URL + ip + IMAGE_ID_FACE + image_id + ACCESS_TOKEN + token;
            session->setUrl(urlGetImage);
            session->setMethod("GET");
            if (session->start() == true) {
                std::cout << urlGetImage << std::endl;
            }
        }
    }
}