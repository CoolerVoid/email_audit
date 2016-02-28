#include "imap_control.h"
#include <iostream>

int main(int argc, char* argv[])
{

  ImapControl imap;
// IMAP server to connect for example "imaps://imap.gmail.com:993" need activte IMAP service at gmail config
  imap.Server("imaps://imap.server.com:993");
//  login and password of e-mail to make connection  
  imap.Auth("email_here@local.com","password_of_email");

// List UIDs of IMAP
  std::vector<std::string> result = imap.list_all();


  imap.view_msg((char *)result[2].c_str());
  printf("%s\n",result[0].c_str());

}
