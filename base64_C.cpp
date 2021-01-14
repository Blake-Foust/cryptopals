/*
 * Author - Matthew Foust
 *
 * Notes:
 * Write a template function to check mod2
 * 
 */
#include <bitset>
#include <sstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include "base64_C.hpp"
#include <stdlib.h>
#include "crypto_Functions.hpp"
#include <stdexcept>

Base64_C::Base64_C(std::string& userInput)
	:userPrivateInput(userInput)
{
	Crypto_Functions::Hex_Check(userPrivateInput);
	b64_encode(userPrivateInput);
};


void Base64_C::b64_encode(std::string& userPrivateInput) 
{

	b64SLength = userPrivateInput.length();

	b64_padding(b64SLength);
	b64_enc_algorithm();
       	std::cout << "Encoded To Base 64: " << base64String << "\n";	

	b64_decrypt(base64String);
	std::cout << "Decrtyped to Hex: " << dB64 << "\n";
};

void Base64_C::b64_padding(auto& inputLength)
{

	if(inputLength%3 != 0)
	{
		if(((inputLength+2)%3 != 0))
		{
			numberOfIterations = ((inputLength+4)/6);
			padding = "==";
		}
		else
		{
			numberOfIterations = ((inputLength+2)/6);
			padding = "=";
		}
	}	
	else
		numberOfIterations = (inputLength/6);
};

void Base64_C::b64_enc_algorithm()
{
	uint8_t num = 0;
	std::string subString,bufferString;
	for(auto j = 0; j < numberOfIterations; j++)
	{
		auto pos = j*6;
		//First Character[0,1] of b64
		subString = userPrivateInput.substr(pos,2);
		num = stoi(subString, 0, 16);
		bufferString = static_cast<char>(BASE64CHAR[((num & HFC) >> 2)]);
		base64String.append(bufferString);
		

		//Second Character[2,3] or [1,0] 
		if(userPrivateInput[pos+2])
		{
			subString = userPrivateInput.substr(pos+1,2);
			num = stoi(subString, 0, 16);
			bufferString = static_cast<char>(BASE64CHAR[(num & H30) + (num & H0F)]);
			base64String.append(bufferString);
		}
		else
		{
			subString = userPrivateInput.substr(pos+1,1);
			subString.append("0");
			num = stoi(subString, 0, 16);
			bufferString = static_cast<char>(BASE64CHAR[(num & H30)]);
			base64String.append(bufferString);
		}
		if((pos+3) <= b64SLength)
		{
			//Third Character[3,4]
			if(userPrivateInput[pos+3] && userPrivateInput[pos+4])
			{
				subString = userPrivateInput.substr(pos+3,2);
				num = stoi(subString, 0, 16);
				bufferString = static_cast<char>(BASE64CHAR[((num & HF0) + (num & H0C))>>2]);
				base64String.append(bufferString);
			}
			else if(userPrivateInput[pos+3])
			{
				subString = userPrivateInput.substr(pos+3,1);
				num = stoi(subString, 0, 16);
				bufferString = static_cast<char>(BASE64CHAR[((num & H0F) << 2)]);
				base64String.append(bufferString);
			}

			//Fourth Character[4,5]
			if(userPrivateInput[pos+4])
			{
				subString = userPrivateInput.substr(pos+4,2);
				num = stoi(subString, 0, 16);
				bufferString = static_cast<char>(BASE64CHAR[(num & H30) + (num & H0F)]);
				base64String.append(bufferString);
			}
		}
	}
	base64String.append(padding);

};

void Base64_C::b64_decrypt(std::string& cryptedText)
{
	std::stringstream hexBuffer;
	for(auto i = 0; i < cryptedText.size(); ++i)
	{
		if(cryptedText.at(i) != '=')
		{
			std::bitset<6> bitX6(BASE64CHAR.find(cryptedText[i]));
			decryptedString.append(bitX6.to_string());		
		}
	}

	auto binaryStringSize = (cryptedText.size()%8==0) ? (decryptedString.size()) : (decryptedString.size()-4);

	for(auto j = 0; j < binaryStringSize; j+=8)
	{
		std::bitset<8> bitSetX8(decryptedString.substr(j,8));
		hexBuffer << std::hex << bitSetX8.to_ulong();

		if(hexBuffer.str().size() == 1)
			dB64.append("0" + (hexBuffer.str()));
		else
			dB64.append(hexBuffer.str());
		hexBuffer.str("");
	}
}

//Base64_C::~Base64_C(){};
