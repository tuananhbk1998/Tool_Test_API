cmake_minimum_required(VERSION 3.0)

# C++ std 14
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_EXE_LINKER_FLAGS "-no-pie")

project(testAPI)

#libCURL
set(curl libcurl.so)
link_directories(${CMAKE_SOURCE_DIR}/curl/lib)
include_directories(${CMAKE_SOURCE_DIR}/curl/include)

include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories(${CMAKE_SOURCE_DIR}/src/HttpSession)
include_directories(${CMAKE_SOURCE_DIR}/src/HttpClient)
include_directories(${CMAKE_SOURCE_DIR}/src/Json)
include_directories(${CMAKE_SOURCE_DIR}/src/DefaultVariable)
#Setup
file(GLOB SOURCES 
src/*.cpp
src/HttpSession/*.cpp
src/HttpClient/*.cpp 
# src/PersonDetection/*.cpp
# src/FaceRecognize/*.cpp
# src/SocialDistancing/*.cpp
# src/FaceMask/*.cpp
# src/FireDetect/*.cpp)
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME}
#    ${CURL_LIBS}
#    ${LIBEVENT_LIBS}
	${curl}
    -lpthread
)

