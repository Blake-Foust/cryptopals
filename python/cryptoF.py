import binascii
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

class  CryptoF:

    def hex2b64(self,hex):
        return codecs.encode(codecs.decode(hex,'hex'), 'base64').decode()

    def xor2Hex(self,hex1,hex2):
        result = int(hex1,16) ^ int(hex2,16)
        return f'{result:x}'

    def byteXorHex(self, hex):
        shcore = 0
        schbuffer = ''
        fscore = 0
        score = 0
        number = 0
        sbuffer = ''
        result = ''

        
        for i in range(0,256):
            for j in range(0,len(hex),2):
                x = int(hex[j:j+2],16)
                xor = x ^ i
                sbuffer += chr(xor)

            for k in range(len(sbuffer)):
                if sbuffer[k] in letter_frequency:
                    score += letter_frequency[sbuffer[k]]

            if score > fscore:
                fscore = score
                result = sbuffer

            score = 0
            sbuffer = ""
        
        #if score > shcore:
        #    schoree = score
        #    schbuffer = result

        return result