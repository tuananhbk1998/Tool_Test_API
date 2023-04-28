#include "Login.hpp"

static std::string access_token;
static std::string monitor_uuid;
static std::string info;
static std::string version;

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}
void Login::LoginTestAPI(){
    CURL *curl;
    CURLcode res;
    std::string readBuffer;
    // CountProcessor input;
    json testAPI;

    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
        testAPI["username"] = "admin";
        testAPI["userpwd"] = "Bkav@2020";
        
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "POST");
        curl_easy_setopt(curl, CURLOPT_URL, "https://10.2.21.219:4004/api/login");
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        //  setContent
        curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
        curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L);
        curl_easy_setopt(curl, CURLOPT_MAXREDIRS, 50L);
        curl_easy_setopt(curl, CURLOPT_TCP_KEEPALIVE, 1L);
        //  setHeader
        struct curl_slist *headers = NULL;
        headers = curl_slist_append(headers, "Content-Type: application/json");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        //  convert json to string to char *
        std::cout << testAPI.dump() << std::endl;
        std::string data = testAPI.dump();
        //  update input
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data.c_str());
        curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, testAPI.dump().size());
        // const char *data = "{\n    \"username\": \"admin\",\n    \"userpwd\": \"Bkav@2020\"\n}";
        // curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data);
        res = curl_easy_perform(curl);
        // std::string data = readBuffer;
        std::cout << readBuffer << std::endl;
    }
    curl_easy_cleanup(curl);
}

void Login::test(char *method, char *url, size_t (*callback)(), void *read_Buffer, struct curl_slist *Headers, char *Data, long Size) {
    CURL *curl;
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);

    if (curl) {
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, &method);
        curl_easy_setopt(curl, CURLOPT_URL, &url);
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, &method);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &callback);
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, &read_Buffer);
        
    }


}

