cmake_minimum_required(VERSION 3.15)
project(udp-chat CXX)



add_executable(udp-chat src/udp-chat.cpp src/main.cpp)



install(TARGETS udp-chat DESTINATION "."
        RUNTIME DESTINATION bin
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        )
