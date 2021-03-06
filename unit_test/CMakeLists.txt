cmake_minimum_required(VERSION 3.10)

# Project settings
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ".")
set(PROJECT_UNIT_TESTS_NAME pvpf_unit_tests)

# Gather the header and source files
file(GLOB UNIT_TESTS_INC_FILES ${PROJECT_SOURCE_DIR}/unit_test/*.hpp)
file(GLOB UNIT_TESTS_SRC_FILES ${PROJECT_SOURCE_DIR}/unit_test/*.cpp)

# Include paths
set(UNIT_TESTS_INCLUDES ${PROJECT_INCLUDE_DIR}
        ${PROJECT_SOURCE_DIR}/src
        ${Boost_INCLUDE_DIR})

# Assign the include directories
include_directories(${UNIT_TESTS_INCLUDES})

# Build unit tests
add_definitions(-DDEV_MODE)
add_definitions(-DBOOST_TEST_DYN_LINK)

add_executable(${PROJECT_UNIT_TESTS_NAME} ${UNIT_TESTS_SRC_FILES} ${INC_FILES} ${SRC_FILES})
target_link_libraries(${PROJECT_UNIT_TESTS_NAME} PRIVATE ${Boost_LIBRARIES} ${OpenCV_LIBS} ${CMAKE_DL_LIBS} -ltbb)

enable_testing()
#add_test(RealTest second_test)
add_test(UNITTEST ${PROJECT_UNIT_TESTS_NAME})

# copy test data
file(GLOB UNIT_TESTS_DATA_FILES ${PROJECT_SOURCE_DIR}/unit_test/test_json/*)
file(COPY ${UNIT_TESTS_DATA_FILES}
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/test_json)

file(GLOB UNIT_TESTS_DYLIB ${PROJECT_SOURCE_DIR}/unit_test/test_dylib/*)
file(COPY ${UNIT_TESTS_DYLIB}
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/test_dylib)

file(GLOB UNIT_TESTS_DYLIB ${PROJECT_SOURCE_DIR}/unit_test/test_images/*)
file(COPY ${UNIT_TESTS_DYLIB}
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/test_images)

file(GLOB UNIT_TESTS_DYLIB ${PROJECT_SOURCE_DIR}/pvpf_algorithm/*)
file(COPY ${UNIT_TESTS_DYLIB}
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/pvpf_algorithm)