/*
#    Copyright (C) 2016 imap_control authors(Antonio Costa, Cooler_),
#    
#    This file is part of spam_detect_PoC
#    
#    libtext_bayes is free software: you can redistribute it and/or modify
#    it under the terms of the GNU Lesser General Public License as published by
#    the Free Software Foundation, either version 3 of the License, or
#    (at your option) any later version.
#
#    libtext_bayes is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#    GNU Lesser General Public License for more details.
#    You should have received a copy of the GNU Lesser General Public License
#    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef _H_IMAP_CONTROL
#define _H_IMAP_CONTROL

#include <stdio.h>
#include <curl/curl.h>
#include <float.h>
#include <math.h>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <set> 
#include <sstream>
#include <fstream>      
#include <cstdlib>
#include <vector>


struct MemoryStruct {
  	char *memory;
  	size_t size;
};

size_t WriteMemoryCallback(void *ptr, size_t size, size_t nmemb, void *data);
 
class ImapControl
{
public:
	ImapControl() {}
	~ImapControl() {}
	void Server(std::string server_in);
	void Auth(std::string login_in, std::string password_in);
	std::vector<std::string> list_all();
	void view_msg(char *uid);
	void remove_msg(char *uid);
private:
	char password[128];
	char login[128];
	char server[128];
	std::vector<std::string> split(const std::string &text, char sep);
};

#endif 
