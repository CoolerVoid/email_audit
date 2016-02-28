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
#include "imap_control.h"
#include <string.h>
#include <vector>

std::vector<std::string> ImapControl::split(const std::string &text, char sep) 
{
 std::vector<std::string> tokens;
 std::size_t start = 0, end = 0;

  	while ((end = text.find(sep, start)) != std::string::npos) 
	{
    		tokens.push_back(text.substr(start, end - start));
    		start = end + 1;
  	}

	tokens.push_back(text.substr(start));

 return tokens;
}

size_t WriteMemoryCallback(void *ptr, size_t size, size_t nmemb, void *data) 
{
	size_t realsize = size * nmemb;
	struct MemoryStruct *mem = (struct MemoryStruct *)data;

	mem->memory = (char *)realloc(mem->memory, mem->size + realsize + 1);

	if( mem->memory ) 
	{
		memcpy(&(mem->memory[mem->size]), ptr, realsize);
		mem->size += realsize;
		mem->memory[mem->size] = 0;
               
	}

	return realsize;
}
      
void ImapControl::Auth(std::string login_in, std::string password_in)
{
	memset(login,0,127);
	strncpy(login,login_in.c_str(),127);

	memset(password,0,127);
	strncpy(password,password_in.c_str(),127);

}


      
void ImapControl::Server(std::string server_in)
{
	memset(server,0,127);
	strncpy(server,server_in.c_str(),127);

}



std::vector<std::string> ImapControl::list_all()
{
  CURL *curl_handle;
  CURLcode res;

  struct MemoryStruct chunk;
 
	chunk.memory =(char *) malloc(1);  
	chunk.size = 0;    

	curl_global_init(CURL_GLOBAL_ALL);
	curl_handle = curl_easy_init();

	char target[256];
	memset(target,0,255);
	strcpy(target,server);
	strcat(target,"/INBOX/");

    	curl_easy_setopt(curl_handle, CURLOPT_USERNAME, login);
    	curl_easy_setopt(curl_handle, CURLOPT_PASSWORD, password);
    	curl_easy_setopt(curl_handle, CURLOPT_URL, target);
   	curl_easy_setopt(curl_handle, CURLOPT_CUSTOMREQUEST, "search all");
	curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
	curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, (void *)&chunk);
 	curl_easy_setopt(curl_handle, CURLOPT_TIMEOUT, 10L); 

#ifdef SKIP_PEER_VERIFICATION
    	curl_easy_setopt(curl_handle, CURLOPT_SSL_VERIFYPEER, 0L);
#endif

#ifdef SKIP_HOSTNAME_VERIFICATION
    	curl_easy_setopt(curl_handle, CURLOPT_SSL_VERIFYHOST, 0L);
#endif

	res = curl_easy_perform(curl_handle);

		if(res != CURLE_OK) 
		{
			fprintf(stderr, "curl_easy_perform() failed: %s\n",
            		curl_easy_strerror(res));
  		} 

  	 std::string tmp(chunk.memory);	
  	 std::vector<std::string> result=split(tmp,' ');

  
   	result.erase(result.begin(), result.begin()+2);


  	curl_easy_cleanup(curl_handle);

	if(chunk.memory!=NULL)
  		free(chunk.memory);

  	curl_global_cleanup();
 		
	return result;
}

void ImapControl::view_msg(char *uid)
{
  CURL *curl_handle;
  CURLcode res;

  struct MemoryStruct chunk;
 
	chunk.memory =(char *) malloc(1);  
	chunk.size = 0;    

	curl_global_init(CURL_GLOBAL_ALL);
	curl_handle = curl_easy_init();

	char path[256];
	memset(path,0,255);
	char target[256];
	memset(target,0,255);
	strcpy(target,server);
	snprintf(path,255,"%s/INBOX/;UID=%s",server,uid);

    	curl_easy_setopt(curl_handle, CURLOPT_USERNAME, login);
    	curl_easy_setopt(curl_handle, CURLOPT_PASSWORD, password);
    	curl_easy_setopt(curl_handle, CURLOPT_URL, path);
	curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
	curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, (void *)&chunk);
 	curl_easy_setopt(curl_handle, CURLOPT_TIMEOUT, 3L); 

#ifdef SKIP_PEER_VERIFICATION
    	curl_easy_setopt(curl_handle, CURLOPT_SSL_VERIFYPEER, 0L);
#endif

#ifdef SKIP_HOSTNAME_VERIFICATION
    	curl_easy_setopt(curl_handle, CURLOPT_SSL_VERIFYHOST, 0L);
#endif
	res = curl_easy_perform(curl_handle);

		if(res != CURLE_OK) 
		{
			fprintf(stderr, "curl_easy_perform() failed: %s\n",
            		curl_easy_strerror(res));
  		} 

  	curl_easy_cleanup(curl_handle);

	if(chunk.memory!=NULL)
  		free(chunk.memory);

  	curl_global_cleanup();
 		
	printf("%s\n",chunk.memory);

}

void ImapControl::remove_msg(char *uid)
{
  CURL *curl_handle;
  CURLcode res;

  struct MemoryStruct chunk;
 
	chunk.memory = (char *)malloc(1);  
	chunk.size = 0;    

	curl_global_init(CURL_GLOBAL_ALL);
	curl_handle = curl_easy_init();
	char cmd[64];
	memset(cmd,0,63);

	char target[256];
	memset(target,0,255);
	strcpy(target,server);
	strcat(target,"/INBOX/");

	snprintf(cmd,63,"STORE %s +Flags \\Deleted",uid);
//imaps://imap.gmail.com:993
    	curl_easy_setopt(curl_handle, CURLOPT_USERNAME, login);
    	curl_easy_setopt(curl_handle, CURLOPT_PASSWORD, password);
    	curl_easy_setopt(curl_handle, CURLOPT_URL, target);
   	curl_easy_setopt(curl_handle, CURLOPT_CUSTOMREQUEST, cmd);
	curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
	curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, (void *)&chunk);
 	curl_easy_setopt(curl_handle, CURLOPT_TIMEOUT, 2L); 
#ifdef SKIP_PEER_VERIFICATION
    	curl_easy_setopt(curl_handle, CURLOPT_SSL_VERIFYPEER, 0L);
#endif

#ifdef SKIP_HOSTNAME_VERIFICATION
    	curl_easy_setopt(curl_handle, CURLOPT_SSL_VERIFYHOST, 0L);
#endif

	res = curl_easy_perform(curl_handle);

 
    	if(res != CURLE_OK)
      		fprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(res));
    	else {

      		curl_easy_setopt(curl_handle, CURLOPT_CUSTOMREQUEST, "EXPUNGE");

      		res = curl_easy_perform(curl_handle);

      		if(res != CURLE_OK)
        		fprintf(stderr, "curl_easy_perform() failed: %s\n",curl_easy_strerror(res));
    	}


	if(chunk.memory!=NULL)
  		free(chunk.memory);

  	curl_global_cleanup();
 		
	printf("%s\n",chunk.memory);
}

