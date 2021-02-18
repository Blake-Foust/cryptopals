/*
 * Author - Matthew Foust
 * mainCrypto.cpp
 */

#include <iostream>
#include <string>
#include "base64_C.hpp"
#include "crypto_Functions.hpp"
#include "AES_C.hpp"

//Make multiple structs for AES - 128/196/256
/*struct AES_128_ECB{
	const std::bitset<8> v_gf28(0b01100011};
	std::bitset<8> affine_gf28;
};*/

int main()
{
/*	std::cout << "Enter String  " << std::endl;
	std::string userEnters;
	getline(std::cin, userEnters);
	Base64_C b64(userEnters);

	std::string value1 = "1c0111001f010100061a024b53535009181c";
	std::string value2 = "686974207468652062756c6c277320657965";

	Crypto_Functions CF;
	std::cout << "Challenge 2" << std::endl;
	std::cout << CF.xorHexS(value1,value2) << "\n";
*/
	std::string plainText = "54776f204f6e65204e696e652054776f";
	std::string userKey = "5468617473206d79204b756e67204675";
	AES_C a(userKey, plainText);
	a.AES_C_S_BOX();	


	return 0;
}
