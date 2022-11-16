/*
 * Author - Matthew Foust
 * mainCrypto.cpp
 *
 *
 * ./Cryptogram #set #challenge
 */

#include <iostream>
#include <fstream>
#include <string>
#include "base64_C.hpp"
#include "crypto_Functions.hpp"
#include "AES_C.hpp"
#include "AES_128_ECB.hpp"

std::string s1c1 = "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d";
std::string s1c21 = "1c0111001f010100061a024b53535009181c";
std::string s1c22 = "686974207468652062756c6c277320657965";
std::string s1c3 = "1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736";
std::string s1c5 = "Burning 'em, if you ain't quick and nimble I go crazy when I hear a cymbal";

int main(int argc, char* argv[])
{
		
	Crypto_Functions cp;	
	int set = atoi(argv[1]);
    int challenge =  atoi(argv[2]);

	switch(set){
		case 1:
			{
				Base64_C b64(s1c1);
				break;
			}
		case 2:
			{
				std::cout << cp.xorHexS(s1c21,s1c22) << std::endl;
				break;
			}
		case 3:
			{
				cp.decrypt_SBXC(s1c3);
				break;
			}
		case 4:
			{
				std::string fline;
				std::ifstream file4;
				file4.open("4.txt",std::ios::in);
				while(std::getline(file4, fline))
				{
					cp.decrypt_SBXC(fline);
				}
				break;
			}
		case 5:
			{
				cp.repeat_XOR(s1c5);
				break;
			}
		default:
			{
				std::cout << "Didnt' work \n";
				break;
			}
	}


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

/*	std::string key = "YELLOW SUBMARINE";
	AES_128_ECB d;

	std::ifstream myfile;
	myfile.open("7.txt");



	d.DECRYPT(key, myfile);
*/


	return 0;	
}
