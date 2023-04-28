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
#ifndef HTTPMANAGER_H_
#define HTTPMANAGER_H_

#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <netdb.h>
#include <unistd.h>
#include <iostream>
#include "curl/curl.h"
#include <sys/stat.h>
#include <vector>
#include "../Json/json.h"

typedef struct HttpResponse {
    std::string responseString;
    std::string headerString;
    char* url;
    int responseCode;
    double elapsed;
}HttpResponse;

class HttpClient
{
public:

	/**
	 * @brief Get the Instance object
	 *
	 * @return Audio*
	 */
	static HttpClient *GetInstance();

	/**
	 * @brief Get the Json object
	 *
	 * @param url
	 * @param number_timeout
	 * @return std::string
	 */
	std::string GetJson(const char *url, const int &number_timeout = 4L);

	/**
	 * @brief Post news json of event AI for server
	 *
	 * @param news_event
	 * @param url_json
	 * @param number_timeout
	 * @return int. Code state success or faild
	 */
	int PostJson(const std::string &news_event, const char *url_json, const int &number_timeout = 7L);

	void setContent(std::string &curlContent);

	void setHeader(json headers);

	static int postData(std::string data, const char* url, HttpResponse& response, std::string header);

	static int get(const char* url, HttpResponse& response, std::vector<std::string> headers = {});

private:
	/**
	 * @brief Construct a new Http Client object
	 *
	 */
	HttpClient();

	/**
	 * @brief Avoiding implicit generation of the copy constructor.
	 *
	 */
	HttpClient(const HttpClient &) = delete;

	/**
	 * @brief Destroy the Http Client object
	 *
	 */
	~HttpClient();
	std::string curlResponse;
};


#endif //
