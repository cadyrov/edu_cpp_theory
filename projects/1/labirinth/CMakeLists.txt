cmake_minimum_required(VERSION 3.20)

project(labirinth VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

file(GLOB_RECURSE LABIRINTH_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

set(LABIRINTH_CORE_SOURCES ${LABIRINTH_SOURCES})
list(REMOVE_ITEM LABIRINTH_CORE_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp"
)

if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp")
    add_executable(labirinth ${LABIRINTH_SOURCES})
    target_include_directories(labirinth PRIVATE include)

    if(MSVC)
        target_compile_options(labirinth PRIVATE /W4)
    else()
        target_compile_options(labirinth PRIVATE -Wall -Wextra -Wpedantic)
    endif()
endif()

include(CTest)

if(BUILD_TESTING)
    file(GLOB_RECURSE LABIRINTH_TEST_SOURCES CONFIGURE_DEPENDS
        "${CMAKE_CURRENT_SOURCE_DIR}/tests/*.cpp"
    )

    if(LABIRINTH_TEST_SOURCES)
        include(FetchContent)
        FetchContent_Declare(
            googletest
            URL https://github.com/google/googletest/archive/refs/tags/v1.17.0.zip
            DOWNLOAD_EXTRACT_TIMESTAMP TRUE
        )
        FetchContent_MakeAvailable(googletest)

        add_executable(labirinth_tests
            ${LABIRINTH_TEST_SOURCES}
            ${LABIRINTH_CORE_SOURCES}
        )
        target_include_directories(labirinth_tests PRIVATE include)
        target_link_libraries(labirinth_tests PRIVATE GTest::gtest_main)

        if(MSVC)
            target_compile_options(labirinth_tests PRIVATE /W4)
        else()
            target_compile_options(labirinth_tests PRIVATE -Wall -Wextra -Wpedantic)
        endif()

        include(GoogleTest)
        gtest_discover_tests(labirinth_tests)
    endif()
endif()
