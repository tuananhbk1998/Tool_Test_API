//
//  define.h
//  SDK
//
//  Created by Nguyen Xuan Truong on 06/02/2023.
//  Copyright © 2023 Nguyen Xuan Truong. All rights reserved.
//

#ifndef __DEFINE_H__
#define __DEFINE_H__

#include "tydef.h"

//define type of HTTP status code
#define HTTP_CODE_500 500
#define HTTP_CODE_400 400
#define HTTP_CODE_200 200
#define HTTP_CONNECT_FAIL 0

//Define the field names of the json message
#define USER_NAME_FIELD_NAME "username"
#define USER_PWD_FIELD_NAME "userpwd"
#define ERROR_CODE_FIELD_NAME "error_code"
#define STATUS_FIELD_NAME "status"
#define DATA_FIELD_NAME "data"
#define ACCESS_TOKEN_FIELD_NAME "access_token"
#define WIDTH_FIELD_NAME "width"
#define HEIGHT_FIELD_NAME "height"
#define ZONES_FIELD_NAME "zones"
#define USE_FIELD_NAME "use"
#define SLEEP_FIELD_NAME "sleep"
#define URL_DATA_FIELD_NAME "url_data"
#define URL_MEDIA_FIELD_NAME "url_media"
#define NOTIFY_SERVER_FIELD_NAME "notify_server"
#define BACKUP_FIELD_NAME "backup"
#define SERVER_FIELD_NAME "server"

//Define the url of the API camera
#define HTTPS_URL "https://"
#define LOGIN_URL ":4004/api/login"
#define TURNON_URL ":4004/api/setup/monitor?access_token="
#define TURNOFF_URL ":4004/api/setup/monitor"
#define PERSON_DETECTION ":4004/api/event/persondetection?from_at=1677181259&to_at=1677646800&count=5&access_token="
#define GET_PERSONDETECTION ":4004/api/event/frame/persondetection/"

#define FACE_RECOGNITION ":4004/api/event/facerecognition?from_at=1675580940&to_at=1678000140&count=5&access_token="
#define IMAGE_ID_FACE ":4004/api/event/frame/facerecognition/"

#define DISTANCING ":4004/api/event/socialdistancing?count=1&access_token="
#define IMAGE_ID_DISTANCING ":4004/api/event/frame/socialdistancing/"

#define FACEMASK ":4004/api/event/facemask?from_at=1675580940&to_at=1678000140&count=5&access_token="
#define IMAGE_ID_FACEMASK ":4004/api/event/frame/facemask/"

#define FIRE_DETECT ":4004/api/event/firedetect?count=1&access_token="
#define IMAGE_ID_FIRE ":4004/api/event/frame/firedetect/"

#define ACCESS_TOKEN "?access_token="



//Default http header
static VECTOR_STR DefaultHeaders = {
    "Content-Type: application/json"
};

//Default of the sleep time
#define DEFAULT_SLEEP_TIME 300000

#endif // __DEFINE