add_definitions(-DBOOST_TEST_DYN_LINK)

find_package(Boost COMPONENTS unit_test_framework REQUIRED)
include_directories(${PROJECT_SOURCE_DIR})
file(GLOB sources *.cpp)

foreach(filename ${sources})
    get_filename_component(target_name ${filename} NAME_WE)
    add_executable(${target_name} ${filename})
    target_link_libraries(${target_name} ${Boost_LIBRARIES})
    add_test(${target_name} ${target_name})
endforeach()
