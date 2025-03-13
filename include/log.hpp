#pragma once

#include <iostream>
#include <ctime>
#include <sstream>

#define END   "\033[0m"
#define GREY  "\033[1;30m"
#define RED   "\033[1;31m"
#define GREEN "\033[1;32m"
#define BLUE  "\033[1;36m"
#define WHITE "\033[1;37m"

void	logError(const std::string& msg);
void	logPerror(const std::string& msg);
void	log(const std::string& msg) ;
