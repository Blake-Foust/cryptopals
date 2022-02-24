#include <iostream>
#include <sstream>
#include <vector>
#include <bitset>
#include <algorithm>
#include <cstddef>
#include <list>
#include <unistd.h>
#include <chrono>
#include <thread>
#include "AES_128_ECB.hpp"

using std::cout;
using std::endl;
using std::cin;



AES_128_ECB::AES_128_ECB(){};
 
void AES_128_ECB::DECRYPT(std::string& key, std::ifstream& inputFile)
{
    auto round = 0;
    KEY_SCHEDULE(key);
    PlainTextToHex(inputFile);
    KeyAddition(round);
};

void AES_128_ECB::KeyAddition(auto& round)
{
    for(auto& x : roundKeys)
    {
        cout << x.first << " " << endl;
        
    }
    std::vector<std::vector<uint8_t>> keyWord = roundKeys.at(round);
    
};

void AES_128_ECB::Byte_Substitution()
{

};

void AES_128_ECB::Diffusion_Layer()
{

};

void AES_128_ECB::PlainTextToHex(std::ifstream& inputFile)
{
//Divide input file by 16 char
    std::string line{};
    int c;
    if(inputFile.is_open())
    {
        while(getline(inputFile,line))
        {
            pText.append(line);
        }
    }
   
    for(unsigned int i = 0; i < pText.length(); i+=16)
    {
        uint8_t pText_Hex_Value{};
        std::string pTextSubstring {};
        uint8_t pTextHexValue{};
        std::string pTextCharSubString{};
        pTextSubstring = pText.substr(i, 16);
        std::stringstream ss;
 //maybe make this a template?
        for(int j = 0; j < 4; ++j)
        {
            std::vector<uint8_t> pTextHexWord{};
            for(int k = j*4; k < j*4+4; ++k)
            {
                ss << std::hex << int(pTextSubstring[k]);
                pTextCharSubString = ss.str();
                //sleep(1);
                pText_Hex_Value = std::stoi(pTextCharSubString,nullptr, 16);
                pTextHexWord.push_back(pText_Hex_Value);
                ss.str("");
            }
            pTextHexWords.push_back(pTextHexWord);
        }   
    }
//-------------------------------


    

};

void AES_128_ECB::InverseMixColumn()
{

};

void AES_128_ECB::KEY_SCHEDULE(const std::string& key)
{
    std::vector<std::vector<uint8_t>> keyHexWords;
    uint8_t key_Hex_Value = 0;
    std::stringstream ss;
    std::string keyCharSubString{""};
    for(int j= 0; j < keyVectorSize; ++j)
    {
        std::vector<uint8_t> keyHexWord{};
        for(int i = j*4; i < j*4+4; ++i)
        {       
            ss << std::hex << int(key[i]);
            keyCharSubString = ss.str();
            key_Hex_Value = std::stoi(keyCharSubString,nullptr, 16);
            keyHexWord.push_back(key_Hex_Value);
            ss.str("");          
        }
        keyHexWords.push_back(keyHexWord);
    }

    unsigned int keyRound = 0;
    while(keyRound != 10)
    {
        roundKeys.insert(std::pair<unsigned int, std::vector<std::vector<uint8_t>>>(keyRound, keyHexWords));
        std::vector<uint8_t> gWord{};
        gWord = G(keyHexWords, keyRound);  
        XorVector(keyHexWords,gWord);   
        ++keyRound;
        cout << "Key Round " << keyRound << endl;
    }
};

std::vector<uint8_t> AES_128_ECB::G(std::vector<std::vector<uint8_t>>& keyHexWords, unsigned int& keyRound)
{
    std::vector<uint8_t> lastWord = keyHexWords[3];
    for(unsigned int i = 0; i <  lastWord.size(); ++i)
        cout << std::hex << static_cast<int>(lastWord[i]) << endl;
    std::rotate(lastWord.begin(),lastWord.begin()+1,lastWord.end());
    lastWord = S_Box(lastWord);
    lastWord[0] ^= round_Constants[keyRound];
    // for(unsigned int i = 0; i < lastWord.size(); ++i)
    //     cout << std::hex << static_cast<int>(lastWord[i]) << endl;
    return lastWord;
};


void AES_128_ECB::XorVector(std::vector<std::vector<uint8_t>>& keyHexWords, std::vector<uint8_t>& gWord)
{

    for(int i = 0; i < 4; ++i)
    {
        keyHexWords[0][i] = keyHexWords[0][i] ^ gWord[i];
    }
    for(int i = 0; i < 4; ++i)
    {
        keyHexWords[1][i] = keyHexWords[1][i] ^ keyHexWords[0][i];
    }
    for(int i = 0; i < 4; ++i)
    {
        keyHexWords[2][i] = keyHexWords[2][i] ^ keyHexWords[1][i];
    }
    for(int i = 0; i < 4; ++i)
    {
        keyHexWords[3][i] = keyHexWords[3][i] ^ keyHexWords[2][i];
    }

};


std::vector<uint8_t> AES_128_ECB::S_Box(std::vector<uint8_t>& lastWord)
{
    uint8_t x = 0, y = 0;
    std::vector<uint8_t> gVector;
       
    for(unsigned int i = 0; i < lastWord.size(); ++i)
    {
        y = (lastWord[i]) & 0x0F;
        x = (lastWord[i] >> 4) & 0x0F;
        gVector.push_back(s_box_vector[x][y]);
    }

    // for(auto& p : gVector)
    //     cout << std::hex << static_cast<int>(p) << std::endl;
    return gVector;

};

// for (unsigned int i = 0; i < keyHexWords.size(); i++) 
// {
//     for (unsigned int j = 0; j < keyHexWords[i].size(); j++)
//     {
//             cout << std::hex << static_cast<int>(keyHexWords[i][j]) << " ";
//     }    
//     cout << endl;
// }