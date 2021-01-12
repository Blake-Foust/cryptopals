/*
 * Author - Matthew Foust
 *
 */

#include <iostream>
#include <string>
#include "base64_C.hpp"
int main()
{
	std::cout << "Enter String  " << std::endl;
	std::string userEnters;
	getline(std::cin, userEnters);
	Base64_C b64(userEnters);
	return 0;
}
