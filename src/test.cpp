#include "imap_control.h"
#include <iostream>

int main(int argc, char* argv[])
{
  ImapControl robot;
  robot.auth("page@gmail.com","password_user");
  std::vector<std::string> result = robot.list_all();
  robot.view_msg((char *)result[2].c_str());


}
