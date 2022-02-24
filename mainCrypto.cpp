/*
 * Author - Matthew Foust
 * mainCrypto.cpp
 */

#include <iostream>
#include <string>
#include "base64_C.hpp"
#include "crypto_Functions.hpp"
#include "AES_C.hpp"
#include "AES_128_ECB.hpp"

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
/*	std::string plainText = "5412321231311213C2C2C2C2C2C2C2C2";
	std::string userKey = "C2C2C2C2C2C2C2C2C2C2C2C2C2C2C2C2";
	// std::string plainText = "C2";
	// std::string userKey = "";
	AES_C a(userKey, plainText);
	a.PracticeRun();	
*/

	std::string key = "YELLOW SUBMARINE";
	AES_128_ECB d;

	std::ifstream myfile;
	myfile.open("7.txt");



	d.DECRYPT(key, myfile);



	return 0;	
}
