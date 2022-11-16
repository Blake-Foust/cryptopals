/*
 * Crypt Functions Class
 */

#include <unistd.h>
#include <iostream>
#include <exception>
#include <stdlib.h>
#include <sstream>
#include <string>
#include <algorithm>
#include <iterator>
#include <map>
#include <iomanip>
#include <cctype>
#include "crypto_Functions.hpp"

using std::cout;
using std::cin;
using std::endl;

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

void Crypto_Functions::repeat_XOR(std::string& s){
	std::string rString;
	for(int i = 0; i < s.size(); ++i){
		rString += (int)s[i] ^ (int)this->ice[i%3];	
	}

	//std::cout << rString << std::endl;
	dec_to_hex(rString);
	

}

void Crypto_Functions::dec_to_hex(std::string& dec){
	std::stringstream x;
	std::string rx;
	for(int i = 0; i < dec.size(); ++i){
		x << std::hex << (unsigned int)dec[i];
		rx += x.str();
		x.str("");
	}
	cout << rx << endl;
}

void Crypto_Functions::decrypt_SBXC(std::string& hex){
	int score = 0,fscore = 0, hexLength = hex.length();
	std::string abuffer, fString;
	hex_to_CHAR(hex);

	for(size_t i = 0; i < 256; ++i){
		for(size_t j = 0; j < hex.size()/2; ++j){
			abuffer += (int)this->asciiString[j] ^ i;
		}
		for(auto x : abuffer){
			if(this->frequency_Map[x])
				score += this->frequency_Map[x];
				
		}
		if(score > fscore){
			fscore =  score;
			fString = abuffer;
		}
		
		score = 0;
		abuffer.clear();
	}


	if(fscore > this->intbuffer){
		this->intbuffer = fscore;
		this->sbuffer = fString;
		std::cout << "Single Byte Decryption: \n" << this->sbuffer << std::endl;
		std::cout << "Score of Decryption" << this->intbuffer << std::endl;
	}

	this->asciiString.clear();	

	//sleep(1);	
}

bool Crypto_Functions::hex_to_DEC(std::string& hexString){
	this->hexV = {};
	std::string part{};
	unsigned int buffer = 0;
	Hex_Check(hexString);

	for(size_t i = 0; i < hexString.length(); ++i){
		part = hexString.substr(i,2);
		buffer = std::stoull(part, nullptr, 16);
		hexV.push_back(buffer);
	}
	return true;
}

bool Crypto_Functions::hex_to_CHAR(std::string& hexString){
	std::string part;
	char asciiChar;

	for(size_t i = 0; i < hexString.size(); i+=2){
		part = hexString.substr(i,2);
		asciiChar = std::stoull(part, nullptr, 16);
		this->asciiString += asciiChar;
	}
	if(this->asciiString.size() != 0)
		return true;
	else 
		return false;

}


//LOOK AT CCTYPE ISPRINT && ISBLANK FOR MORE INFO 
bool Crypto_Functions::hex_to_ASCII(std::string& hexString)
{
	std::string part;
	char asciiChar;
	for(size_t i = 0; i < hexString.size(); i+=2)
	{
		part = hexString.substr(i,2);
		asciiChar = std::stoul(part, nullptr, 16);
		if(isprint(asciiChar) || isblank(asciiChar))
		{
			this->asciiString += asciiChar;
		}
		else if(isspace(asciiChar))
		{
		}
		else
		{
			return false;
		}
	}
	return true;
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


