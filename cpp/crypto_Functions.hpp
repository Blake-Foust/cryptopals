#ifndef CRYPTO_FUNCTIONS_H
#define CRYPTO_FUNCTIONS_H
#include <string>
#include <vector>
#include <tuple>
#include <map>

class Crypto_Functions
{
private:
	
	std::string xorReturnString, asciiString;
	std::vector<std::tuple<std::string, double, char>> decryptionScores;
	std::string userValue1, userValue2;
        std::vector<unsigned int> hexV; 
        unsigned int intbuffer = 0;
        std::string sbuffer{};
        std::string ice = "ICE";
public:

	Crypto_Functions();
	Crypto_Functions(std::string& userInput1);
	Crypto_Functions(std::string& userInput1,std::string& userInput2);
	template <typename T1, typename T2>
	bool equal_size(T1 var1, T2 var2);
        bool hex_to_DEC(std::string&);	
	bool hex_to_CHAR(std::string& hexString);
	bool hex_to_ASCII(std::string& hexString);
        std::string xorHexS(std::string& hexString1, std::string& hexString2);
	void Hex_Check(std::string& hexString);
	void decrypt_SBXC(std::string&);
	void repeat_XOR(std::string&);
        void dec_to_hex(std::string&);
        std::map<char, double> frequency_Map{
                {' ', 13.00},
                {'a', 8.56},
                {'b', 2.03},
                {'c', 4.13},
                {'d', 3.13},
                {'e', 11.42},
                {'f', 1.35},
                {'g', 2.30},
                {'h', 2.15},
                {'i', 8.65},
                {'j', 0.20},
                {'k', 0.88},
                {'l', 5.35},
                {'m', 2.70},
                {'n', 7.42},
                {'o', 5.94},
                {'p', 2.77},
                {'q', 0.19},
                {'r', 7.44},
                {'s', 8.15},
                {'t', 6.76},
                {'u', 3.22},
                {'v', 1.09},
                {'w', 0.85},
                {'x', 0.29},
                {'y', 1.65},
                {'z', 0.09},
                {'A', 8.56},
                {'B', 2.03},
                {'C', 4.13},
                {'D', 3.13},
                {'E', 11.42},
                {'F', 1.35},
                {'G', 2.30},
                {'H', 2.15},
                {'I', 8.65},
                {'J', 0.20},
                {'K', 0.88},
                {'L', 5.35},
                {'M', 2.70},
                {'N', 7.42},
                {'O', 5.94},
                {'P', 2.77},
                {'Q', 0.19},
		{'R', 7.44},
                {'S', 8.15},
                {'T', 6.76},
                {'U', 3.22},
                {'V', 1.09},
                {'W', 0.85},
                {'X', 0.29},
                {'Y', 1.65},
                {'Z', 0.09}
        };

};



#endif //CRYPTO_FUNCTIONS_H
