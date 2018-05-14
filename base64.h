#ifndef BASE64_H
#define BASE64_H

#include <string>
#include <vector>

class Base64
{
public:
    Base64();
    const static char encodeList[64];
    const static std::string encodeTable;
    const static char decodeList[128];
    static std::string encode(std::string str);
    static std::string encode(const char *str, int length);
    static std::string encode(const unsigned char *str, int length);
    static std::string decode(std::string str);
    static std::string decode(const char *str, int length);
    static std::string decode(const unsigned char *str, int length);

    static std::string encode_old(std::string str);


};

#endif // BASE64_H