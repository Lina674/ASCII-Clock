#include <iostream>
#include <chrono>
#include <map>
#include <vector>
#include <thread>
#include <windows.h>

// \     /
//  \   /
//   \ /

std::map<std::string, std::string> seven_segment = {
    {"0", " _ \n| |\n|_|\n"},
    {"1", "   \n  |\n  |\n"},
    {"2", " _ \n _|\n|_ \n"},
    {"3", " _ \n _|\n _|\n"},
    {"4", "   \n|_|\n  |\n"},
    {"5", " _ \n|_ \n _|\n"},
    {"6", " _ \n|_ \n|_|\n"},
    {"7", "   \n  |\n  |\n"},
    {"8", " _ \n|_|\n|_|\n"},
    {"9", " _ \n|_|\n |\n"},
    {":", "   \n . \n . \n"},
    {" ", "   \n   \n   \n"}
};

std::map<std::string, std::string> seven_segment_eastern_arabic = {
    {"0", " \n . \n \n"},
    {"1", "   \n |\n  |\n"},
    {"2", " _ \n| \n| \n"},
    {"3", " _ \n _|\n _|\n"}, //look up
    {"4", "    _\n |_ \n  |_ \n"},
    {"5", " \n _ \n |_|\n"},
    {"6", " _\n  |\n  |\n"},
    {"7", R"( \     / \n \   / \n \/ \n)"},
    {"8", R"( /\ \n /   \ \n /     \ \n)"},
    {"9", " _ \n|_|\n |\n"},
    {":", "   \n . \n . \n"},
    {" ", "   \n   \n   \n"}
};

std::string get_time() {
    auto now = std::chrono::system_clock::now();
    auto now_c = std::chrono::system_clock::to_time_t(now); //conversion to c format
    std::string time_str = std::ctime(&now_c);
    //std::cout << "Current time: " << time_str; //Current time: Sun Jul 13 17:11:15 2025
    std::string real_time = time_str.substr(11, 8); //start index, length
    //std::cout << real_time << std::endl;
    return real_time;
}

std::vector<std::string> convert_to_ss(std::string time) {
    std::vector<std::string> time_array;
    for (int i = 0; i < time.length(); i++) {
        time_array.push_back(seven_segment_eastern_arabic[std::string(1, time[i])]);
    }
    return time_array;
}

std::string join(std::vector<std::string> vec) {
    std::string lines[3] = {"", "", ""};
    for (int i = 0; i < vec.size(); i++) {
        size_t prev = 0, pos = 0, line_idx = 0;
        while ((pos = vec[i].find('\n', prev)) != std::string::npos) {
            lines[line_idx++] += vec[i].substr(prev, pos - prev);
            prev = pos + 1;
        }
    }
    return lines[0] + "\n" + lines[1] + "\n" + lines[2];;
}

int main() {
    // std::cout << "ASCII Clock" << std::endl;
    // return 0;

    while (true) {
        std::string current_time = get_time();
        std::vector<std::string> time_vector = convert_to_ss(current_time);
        std::cout << join(time_vector) << std::endl;
        //std::this_thread::sleep_for(std::chrono::seconds(1));
        Sleep(1000);
    }
}
