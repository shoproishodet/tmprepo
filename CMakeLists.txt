cmake_minimum_required(VERSION 3.17)

set(PROJECT_NAME DiagnosticM)

project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 20)

find_package(Boost 1.81 REQUIRED)

include_directories(
        ${Boost_INCLUDE_DIR}
        )

link_directories(
        ${Boost_LIBRARY_DIR}
        )

add_executable(${PROJECT_NAME}_CLIENT
        StartClient.cpp
        Client/Client.cpp
        Client/Client.h
        )

add_executable(${PROJECT_NAME}_SERVER
        StartServer.cpp
        Server/Server.cpp
        Server/Server.h
        )

target_link_libraries(${PROJECT_NAME}_CLIENT
        ${Boost_LIBRARIES}
        )

target_link_libraries(${PROJECT_NAME}_SERVER
        ${Boost_LIBRARIES}
        )

if(WIN32)
    target_link_libraries(${PROJECT_NAME}_CLIENT
            ws2_32
            )
    target_link_libraries(${PROJECT_NAME}_SERVER
            ws2_32
            )
endif()
