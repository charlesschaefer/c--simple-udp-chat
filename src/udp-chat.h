#pragma once

#include <vector>
#include <string>


#ifdef _WIN32
  #define UDP_CHAT_EXPORT __declspec(dllexport)
#else
  #define UDP_CHAT_EXPORT
#endif

UDP_CHAT_EXPORT void udp_chat();
UDP_CHAT_EXPORT void udp_chat_print_vector(const std::vector<std::string> &strings);
