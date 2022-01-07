#ifndef USER_DATA_H
#define USER_DATA_H

#include <iostream>
#include <fstream>
#include <string>
#include <iostream>

bool WriteGroupTitle        (std::string&);
bool WriteId                (std::string&);
bool WriteNickname          (std::string&);

std::string GetGroupTitle   ();
std::string GetId           ();
std::string GetNickname     ();


#endif // USER_DATA_H
