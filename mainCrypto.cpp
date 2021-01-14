/*
 * Author - Matthew Foust
 * mainCrypto.cpp
 */

#include <iostream>
#include <string>
#include "base64_C.hpp"
#include "crypto_Functions.hpp"

int main()
{
	std::cout << "Enter String  " << std::endl;
	std::string userEnters;
	getline(std::cin, userEnters);
	Base64_C b64(userEnters);

	std::string value1 = "1c0111001f010100061a024b53535009181c";
	std::string value2 = "686974207468652062756c6c277320657965";

	Crypto_Functions CF;
	std::cout << "Challenge 2" << std::endl;
	std::cout << CF.xorHexS(value1,value2) << "\n";





	return 0;
}
