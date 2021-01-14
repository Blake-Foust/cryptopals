/*
 * Crypt Functions Class
 */

#include <iostream>
#include <stdlib.h>
#include <sstream>
#include <string>
#include <algorithm>
#include <iterator>
#include "crypto_Functions.hpp"

Crypto_Functions::Crypto_Functions(){};

Crypto_Functions::Crypto_Functions(std::string& userInput1)
	: userValue1(userInput1){};

Crypto_Functions::Crypto_Functions(std::string& userInput1, std::string& userInput2)
	: userValue1(userInput1), userValue2(userInput2){};

template<typename T, typename U>
bool Crypto_Functions::equal_size(T var1, U var2)
{
	return (var1.size() == var2.size());
}

std::string Crypto_Functions::xorHexS(std::string& hexString1, std::string& hexString2)
{
	//make this a bool function for a transform?
	auto hex_to_dec=[](char hexChar)
	{
		if(hexChar >= '0' && hexChar <= '9')
			return(hexChar-48);
		else if(hexChar >= 'A' && hexChar <= 'Z')
			return(hexChar - 55);
		else 
			return(hexChar - 87);
	};

	if(!(equal_size(hexString1, hexString2))){
		std::cout << "The hex Strings are not of equal size.\n" << std::endl;
		exit(0);
	}
	std::stringstream xorString;
	xorString.str("");
	for(auto i = 0; i < hexString1.length(); ++i)
	{
		xorString << std::hex << (hex_to_dec(hexString1[i])^hex_to_dec(hexString2[i]));
	}
	return xorString.str();
};

void Crypto_Functions::Hex_Check(std::string& hexString)
{
	try
	{
		
		std::string hexByte;
		std::string buffer;
		for(int i = 0; i < hexString.length(); i+=2)
		{
			hexByte = hexString.substr(i,2);
			buffer = stoi(hexByte,0,16);
		}
	}
	catch(std::invalid_argument& error)
	{
		std::cerr << "Your input contained a non-hex character" << std::endl;
		exit(0);
	}
};

