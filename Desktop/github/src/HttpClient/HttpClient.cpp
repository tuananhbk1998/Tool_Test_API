/**
* @Copyright (C) 2022, AI View. All rights reserved.
* @Module: HttpClient
* @Author: HieuPV
* @Created: 19/02/2021
* @Modified:
    Name: DangTT
    Date: 19/09/2022
    Change: Name convention
* @Description: Manage post event AI to server
*/

#include "HttpClient.hpp"
#include "HttpSession.hpp"
#include <regex>
// #include <android/log.h>
static CURL *curl;

HttpClient::HttpClient()
{
}

HttpClient::~HttpClient()
{
}

static size_t writeCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

HttpClient *HttpClient::GetInstance()
{
    static HttpClient mInstance;
    return &mInstance;
}

std::string HttpClient::GetJson(const char *url, const int &number_timeout)
{
    std::string response_string;
    std::string header_string;
    curl_global_init(CURL_GLOBAL_DEFAULT);
    auto curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L);
        curl_easy_setopt(curl, CURLOPT_MAXREDIRS, 50L);
        curl_easy_setopt(curl, CURLOPT_TCP_KEEPALIVE, 1L);

        // curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteFunction);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_string);
        curl_easy_setopt(curl, CURLOPT_HEADERDATA, &header_string);

        curl_easy_perform(curl);
        std::cout << response_string << "\n";
        curl_easy_cleanup(curl);
        curl_global_cleanup();
        curl = NULL;
    }
    return response_string;
}

int HttpClient::PostJson(const std::string &news_event, const char *url_json, const int &number_timeout)
{
    int response_code = 0;
    CURLcode ret = CURLE_FAILED_INIT;
    CURL *curl = NULL;
    /*add header*/
    struct curl_slist *headers = NULL;
    headers = curl_slist_append(headers, "Accept: application/json");
    headers = curl_slist_append(headers, "Content-Type: application/json");
    headers = curl_slist_append(headers, "charset: utf-8");
    // headers = curl_slist_append(headers, ("Info: " + g_serialno_camera).c_str());
    // headers = curl_slist_append(headers, ("Version: " + g_version_ota).c_str());

    /*init*/
    curl = curl_easy_init();
    if (curl)
    {
        // DEBUG
        //    curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
        //
        curl_easy_setopt(curl, CURLOPT_URL, url_json);
        curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, news_event.c_str());
        curl_easy_setopt(curl, CURLOPT_USERAGENT, "curl/7.38.0");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_MAXREDIRS, 50L);
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "POST");
        curl_easy_setopt(curl, CURLOPT_TCP_KEEPALIVE, 1L);

        /*Certificate SSL(HTTPs) on Android*/
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);

        /* abort if slower than 30 bytes/sec during 4 seconds */
        // curl_easy_setopt(curl, CURLOPT_LOW_SPEED_TIME, 1L);
        // curl_easy_setopt(curl, CURLOPT_LOW_SPEED_LIMIT, 30L);
        /* TIME OUT*/
        curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, number_timeout);
        curl_easy_setopt(curl, CURLOPT_TIMEOUT, number_timeout);

        ret = curl_easy_perform(curl);
        if (ret != CURLE_OK)
        {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(ret));
        }
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
    }
    curl_easy_cleanup(curl);
    curl_slist_free_all(headers);
    return response_code;
}

void HttpClient::setContent(std::string &curlContent) {
    curlResponse.clear();
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &curlResponse);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, curlContent.c_str());
    curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, curlContent.size());
    curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L);
    curl_easy_setopt(curl, CURLOPT_MAXREDIRS, 50L);
    curl_easy_setopt(curl, CURLOPT_TCP_KEEPALIVE, 1L);
    // curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1);
    // curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
}

void HttpClient::setHeader(json headers) {
    struct curl_slist *headersList = NULL;
    if (headers.is_array())
    {
        for (const std::string header : headers)
        {
            headersList = curl_slist_append(headersList, header.c_str());
        }
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headersList);
    }
}

int HttpClient::postData(std::string data, const char* url, HttpResponse& response, std::string headers) {   
    int curlCode = -1;
    CURL *hnd = curl_easy_init();;
    struct curl_slist *headersList = NULL;
    
    headersList = curl_slist_append(headersList, headers.c_str());
    if (hnd) {
        curl_easy_setopt(hnd, CURLOPT_URL, url);
        curl_easy_setopt(hnd, CURLOPT_POSTFIELDS, data.c_str());
        curl_easy_setopt(hnd, CURLOPT_HTTPHEADER, headersList);
        curl_easy_setopt(hnd, CURLOPT_POST, 1L);
        curl_easy_setopt(hnd, CURLOPT_TCP_KEEPALIVE, 1L);
        curl_easy_setopt(hnd, CURLOPT_TIMEOUT, 20L);

        curl_easy_setopt(hnd, CURLOPT_NOSIGNAL, 1);
        curl_easy_setopt(hnd, CURLOPT_SSL_VERIFYPEER, 0);
        curl_easy_setopt(hnd, CURLOPT_SSL_VERIFYHOST, false);

        response.headerString.clear();
        response.responseString.clear();
        curl_easy_setopt(hnd, CURLOPT_WRITEFUNCTION, writeCallback);
        curl_easy_setopt(hnd, CURLOPT_WRITEDATA, &response.responseString);
        curl_easy_setopt(hnd, CURLOPT_HEADERDATA, &response.headerString);

        curlCode = (int)curl_easy_perform(hnd);
        curl_easy_getinfo(hnd, CURLINFO_RESPONSE_CODE, &response.responseCode);
        curl_easy_getinfo(hnd, CURLINFO_TOTAL_TIME, &response.elapsed);
        curl_easy_getinfo(hnd, CURLINFO_EFFECTIVE_URL, &response.url);
        curl_easy_cleanup(hnd);

    }
    curl_slist_free_all(headersList);
    return curlCode;
}

int HttpClient::get(const char* url, HttpResponse& response, std::vector<std::string> headers) {
    int curlCode = -1;
    CURL *hnd = curl_easy_init();
    struct curl_slist *headersList = NULL;
    for(const std::string index : headers) {
        headersList = curl_slist_append(headersList, index.c_str());
    }
    if (hnd) {
        curl_easy_setopt(hnd, CURLOPT_URL, url);
        curl_easy_setopt(hnd, CURLOPT_HTTPHEADER, headersList);
        // curl_easy_setopt(hnd, CURLOPT_TCP_KEEPALIVE, 1L);
        curl_easy_setopt(hnd, CURLOPT_TIMEOUT, 30L);

        // curl_easy_setopt(hnd, CURLOPT_NOPROGRESS, 1L);
        curl_easy_setopt(hnd, CURLOPT_FOLLOWLOCATION, 1L);

        response.headerString.clear();
        response.responseString.clear();
        curl_easy_setopt(hnd, CURLOPT_WRITEFUNCTION, writeCallback);
        curl_easy_setopt(hnd, CURLOPT_HEADERDATA, &response.headerString);
        curl_easy_setopt(hnd, CURLOPT_WRITEDATA, &response.responseString);
        std::cout << "Test :" << response.responseString << std::endl;

        curlCode = (int)curl_easy_perform(hnd);

        curl_easy_getinfo(hnd, CURLINFO_RESPONSE_CODE, &response.responseCode);
        curl_easy_getinfo(hnd, CURLINFO_TOTAL_TIME, &response.elapsed);
        curl_easy_getinfo(hnd, CURLINFO_EFFECTIVE_URL, &response.url);
        curl_easy_cleanup(hnd);
    }
    curl_slist_free_all(headersList);
    return curlCode;
}