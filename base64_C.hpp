#ifndef Base64_C_H
#define Base64_C_H
#include <cstdint>
#include <string>

class Base64_C
{
private:
	uint8_t HFC = 252;
	uint8_t H30 = 48;
	uint8_t H0F = 15;
	uint8_t HFF = 255;
	uint8_t H0C = 12;
	uint8_t HF0 = 240;
	uint8_t H3F = 63;
	
	inline static const std::string BASE64CHAR = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

	//Private Variables
	std::string base64String, userPrivateInput, padding, decryptedString, dB64;
	uint8_t numberOfIterations = 0;
	uint8_t b64SLength = 0;
	
	void b64_padding(auto& inputLength);
	void b64_enc_algorithm();
	void b64_decrypt(std::string& cryptedText); 
public:
	Base64_C(std::string& userInput);
	//Think of some Overloaded Constructors that might be useful.

	void b64_encode(std::string& userPrivateData);  
//	~Base64_C();



};

#endif
