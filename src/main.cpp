#include "udp-chat.h"
#include <vector>
#include <string>

int main() {
    udp_chat();

    std::vector<std::string> vec;
    vec.push_back("test_package");

    udp_chat_print_vector(vec);
}
