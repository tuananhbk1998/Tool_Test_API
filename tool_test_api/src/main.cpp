#include <iostream>
#include <fstream>
#include <ctime>
#include <string>
#include "curl/curl.h"
#include "api.hpp"
using namespace std;

int main()
{   
    std::ifstream ifs("/home/anhmtc/Documents/BKAV/tooltestapi/testAPI/temp");
    json jf = json::parse(ifs);
    for (auto i : jf) {
      std::cout << i.dump(4) << std::endl;
      api *test = new api();
      std::string ip = i["ip"];
      std::string username = i["username"];
      std::string userpwd = i["userpwd"];
      //  std::string type = i["type"];
      std::string res;
      int n = 0;
      auto start_AI = std::chrono::high_resolution_clock::now();
      while (n <= 0) {
          if (test->login(ip, username, userpwd, res) == 1) {
              for (auto j : i["type"]) {
                  HttpSession *session;
                  HttpSession *session_face;
                  HttpSession *session_faceMask;
                  api *test_face = new api();
                  api *test_faceMask = new api();
                  if (j == "persondetection") {
                      test->turnOn_person("persondetection");
                      test->GetData_person("persondetection", session);
                  } else if (j == "facerecognition") {
                      if (test_face->login(ip, username, userpwd, res) == 1) {
                          test_face->turnOn_face(j);
                          test_face->GetData_face(j, session_face);
                      } else {
                          std::cout << "Error login for face recognition" << std::endl;
                      }
                  } else if (j == "facemask") {
                      if (test_faceMask->login(ip, username, userpwd, res) == 1) {
                          test_faceMask->turnOn_faceMask(j);
                          test_faceMask->GetData_faceMask(j, session_faceMask);
                      } else {
                          std::cout << "Error login for face mask" << std::endl;
                      }
                  } else {
                      std::cout << "Error can't look forward AI interface" << std::endl;
                  }
                  // sleep(5);
                  for (auto k : i["type"]) {
                      if (k == "persondetection") {
                          test->turnOff_person("persondetection", session);  
                      } else if (k == "facerecognition") {
                          test_face->turnOff_face("facerecognition", session_face);
                      } else if (k == "facemask") {
                          test_faceMask->turnOff_faceMask("facemask", session_faceMask);
                      }
                  }
                }
          } else {
              std::cout << "Error can't login to system" << std::endl;
          }
          auto end_AI = std::chrono::high_resolution_clock::now();
          auto duration_AI = std::chrono::duration_cast<std::chrono::milliseconds>(end_AI - start_AI);
          auto time_excuted = duration_AI.count();
          std::cout << "Time excuted = " << time_excuted << "ms" << std::endl;
          n++;
          std::cout << "Times = " << n << std::endl;
      }
    }
    
  return 0;
}