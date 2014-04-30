cmake_minimum_required(VERSION 2.8)

project(rabbit)

include_directories(
    ${PROJECT_SOURCE_DIR}
    ${PROJECT_SOURCE_DIR}/thirdparty/rapidjson/include
    ${PROJECT_SOURCE_DIR}/thirdparty/picojson)

include(CTest)
add_subdirectory(test)

