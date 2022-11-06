import binascii
import random
import os
import ssl
import codecs
import base64
import time

letter_frequency = {'e':11,
                    'a':8.4,
                    'r':7.5,
                    'i':7.5,
                    'o':7.1,
                    't':6.9,
                    'n':6.6,
                    's':5.7,
                    'l':5.4,
                    'c':4.5,
                    'u':3.6,
                    'd':3.3,
                    'p':3.1,
                    'm':3.0,
                    'h':3.0,
                    'g':2.4,
                    'b':2.0,
                    'f':1.8,
                    'y':1.7,
                    'w':1.2,
                    'k':1.1,
                    'v':1.0,
                    'x':0.2,
                    'z':0.2,
                    'j':0.19,
                    'q':0.1}


def xorCipher(hex):
    score = 0 
    number = 0
    result = ""
    #if new number is more than score, score = new number

    for x in range(65,90):
        for n in hex:
            result += str(int(n,16) ^ x)
            result += "1"

        result = f'{int(result):x}'
        #result.encode('ascii','replace')

        ascii_a = binascii.unhexlify(result)
        #ascii_a = codecs.decode(result, 'hex', errors="ignore").decode("ASCII")
        
        for a in ascii_a:            
            if letter_frequency[n]:
                number += letter_frequency[n]
        
        if number > score:
            score = number



def hex2b64(hex):
    return codecs.encode(codecs.decode(hex,'hex'), 'base64').decode()


def xor2hex(hex1,hex2):
    result = int(hex1,16) ^ int(hex2,16)
    return f'{result:x}'

def main():
    hex = "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d"
    s1c1 = hex2b64(hex)
    h1 = '1c0111001f010100061a024b53535009181c'
    h2 = '686974207468652062756c6c277320657965'
    s1c2 = xor2hex(h1,h2)
    print(s1c1)
    print(s1c2)
    xorHexString = '1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736'
    s1c3 = xorCipher(xorHexString)
    print(s1c3)

if __name__ == "__main__":
    main()
