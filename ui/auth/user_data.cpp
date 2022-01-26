#include "user_data.h"

bool WriteId        (std::string& id) {
    std::ofstream output("client_id.txt", std::ios::trunc);

    if (output.is_open()) {
        output << "id: " << id << std::endl;
        output.close();
        return true;
    } else {
        output.close();
        return false;
    }
};


bool WriteNickname  (std::string& nn) {
    std::ofstream output("client_name.txt", std::ios::trunc);

    if (output.is_open()) {
        output << "nickname: " << nn << std::endl;
        output.close();
        return true;
    } else {
        output.close();
        return false;
    }
};

bool WriteGroupTitle  (std::string& nn) {
    std::ofstream output("group_title.txt", std::ios::trunc);

    if (output.is_open()) {
        output << "groupTitle: " << nn << std::endl;
        output.close();
        return true;
    } else {
        output.close();
        return false;
    }
};

bool WriteGroupID  (std::string& nn) {
    std::ofstream output("group_id.txt", std::ios::trunc);

    if (output.is_open()) {
        output << "groupID: " << nn << std::endl;
        output.close();
        return true;
    } else {
        output.close();
        return false;
    }
};


std::string GetId() {
    std::ifstream input("client_id.txt");
    std::string id;
    std::string buf;
    if (input) {
        while(!input.eof()){
            input >> buf;
            if (buf == "id:") {
                input >> id;
                return id;
            };
        }
    } else {
        std::cout << "file is missing!" << std::endl;
    }
    input.close();
    return "null";

};


std::string GetNickname() {
    std::ifstream input("client_name.txt");
    std::string nickname;
    std::string buf;
    if (input) {
        while(!input.eof()){
            input >> buf;
            if (buf == "nickname:") {
                input >> nickname;
                return nickname;
            };
        }
    } else {
        std::cout << "file is missing!" << std::endl;
    }
    input.close();
    return "null";
};

std::string GetGroupTitle() {
    std::ifstream input("group_title.txt");
    std::string gtoupTitle;
    std::string buf;
    if (input) {
        while(!input.eof()){
            input >> buf;
            if (buf == "groupTitle:") {
                input >> gtoupTitle;
                return gtoupTitle;
            };
        }
    } else {
        std::cout << "file is missing!" << std::endl;
    }
    input.close();
    return "null";
};


std::string GetGroupID() {
    std::ifstream input("group_id.txt");
    std::string gtoupTitle;
    std::string buf;
    if (input) {
        while(!input.eof()){
            input >> buf;
            if (buf == "groupID:") {
                input >> gtoupTitle;
                return gtoupTitle;
            };
        }
    } else {
        std::cout << "file is missing!" << std::endl;
    }
    input.close();
    return "null";
};


