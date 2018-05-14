#include "base64.h"

Base64::Base64() {

}

const char Base64::encodeList[64] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z',
                                'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z',
                                '0','1','2','3','4','5','6','7','8','9','+','/'};

const std::string Base64::encodeTable = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

const char Base64::decodeList[128] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
                                      -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
                                      -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 62, -1, -1, -1, 63,
                                      52, 53, 54, 55, 56, 57, 58, 59, 60, 61, -1, -1, -1, -2, -1, -1,
                                      -1, 0,  1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13, 14,
                                      15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, -1, -1, -1, -1, -1,
                                      -1, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40,
                                      41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, -1, -1, -1, -1, -1 };

std::string Base64::encode(std::string str) {
    unsigned char *current = (unsigned char *)str.c_str();
    return encode(current, str.size());
}

std::string Base64::encode(const char *str, int length) {
    unsigned char *current = (unsigned char *)str;
    return encode(current, length);
}

std::string Base64::encode(const unsigned char *str, int length) {
    std::string output;
    int index = 0;
    while (index + 3 <= length) {
        output += encodeTable[str[index] >> 2];
        output += encodeTable[((str[index] & 0x03) << 4) + (str[index + 1] >> 4)];
        output += encodeTable[((str[index + 1] & 0x0f) << 2) + (str[index + 2] >> 6)];
        output += encodeTable[str[index + 2] & 0x3f];
        index += 3;
    }
    if (length % 3 == 1) {
        output += encodeTable[str[index] >> 2];
        output += encodeTable[(str[index] & 0x03) << 4];
        output += "==";
    }
    if (length % 3 == 2) {
        output += encodeTable[str[index] >> 2];
        output += encodeTable[((str[index] & 0x03) << 4) + (str[index + 1] >> 4)];
        output += encodeTable[(str[index + 1] & 0x0f) << 2];
        output += "=";
    }
    return output;
}

std::string Base64::decode(std::string str) {
    return decode(str.c_str(), str.size());
}

std::string Base64::decode(const unsigned char *str, int length) {
    return decode((char *)str, length);
}

std::string Base64::decode(const char *str, int length) {
    std::string output;
    int index = 0;
    while (index + 4 < length) {
        auto c1 = decodeList[(int)str[index]];
        auto c2 = decodeList[(int)str[index + 1]];
        auto c3 = decodeList[(int)str[index + 2]];
        auto c4 = decodeList[(int)str[index + 3]];
        if (c1 < 0 || c2 < 0 || c3 < 0 || c4 < 0)
            return std::string();
        output += (c1 << 2) + (c2 >> 4);
        output += (c2 << 4) + ((c3 & 0x3c) >> 2);
        output += (c3 << 6) + c4;
        index += 4;
    }

    auto c1 = decodeList[(int)str[index]];
    auto c2 = decodeList[(int)str[index + 1]];
    auto c3 = decodeList[(int)str[index + 2]];
    auto c4 = decodeList[(int)str[index + 3]];
    if (c1 < 0 || c2 < 0 || c3 == -1 || c4 == -1)
        return std::string();
    output += (c1 << 2) + (c2 >> 4);
    if (c3 != -2) {
        output += (c2 << 4) + ((c3 & 0x3c) >> 2);
        if (c4 != -2)
            output += (c3 << 6) + c4;
    }
    return output;
}

std::string Base64::encode_old(std::string str)
{
    std::string output;
    std::vector<int> binaryStream;
    //all characters in binary stream
    for (unsigned i = 0; i < str.size(); i++) {
        unsigned char tempChar = str[i];
        for (int j = 7, bit = 1; j >= 0; j--)
            binaryStream.push_back(bit & (tempChar >> j));
    }
    //add zeros
    int zeroToAppend = binaryStream.size() % 6 == 0 ? 0 : 6 - binaryStream.size() % 6;
    for (int i = 0; i < zeroToAppend; i++)
        binaryStream.push_back(0);
    //convert to base64
    for (unsigned i = 0; i < binaryStream.size() / 6; i++) {
        int num = 0;
        for (int j = 0; j < 6; j++)
            num |= binaryStream[i * 6 + j] << (5 - j);
        output.push_back(encodeTable[num]);
    }
    //add =
    if (str.size() % 3 == 1)
        output += "==";
    if (str.size() % 3 == 2)
        output += "=";
    return output;
}