#include "code128.hpp"

Code128::Code128()
{

}

Code128::Code128(std::string msg) : str(msg)
{ 
    encodeCode128();
}

inline void Code128::setCode(std::string code) { str = code; }

int Code128::getLength() 
{
    return (str.length() == 0 ? -1 : 2 * img_padding + C128_CHAR_LEN * (str.length() + 2) + C128_STOP_LEN);
}

std::vector<int> Code128::getEncoded()
{
    if(encoded.size() != 0)
    {
        return encoded;
    }

    encodeCode128();

    return encoded;
}

std::vector<int> Code128::toBinary(int n) 
{
    std::vector<int> r;
    while (n != 0) 
    {
        if (n % 2) 
        {
            r.push_back(1);
        } 
        else 
        {
            r.push_back(0);
        }
        n /= 2;
    }
    return r;
}

// std::vector<int> Code128::encodeCode128(const char str_get[]) 
// {
//     std::vector<int> encoded;
//     for (int i = 0; str_get[i] != '\0'; ++i) 
//     {
//         str.push_back(str_get[i]);
//     }

//     for (int i = 0; i < img_padding; i++) 
//     {
//         encoded.push_back(0);
//     }

//     std::vector<int> temp = toBinary(patternBit(136));
//     for (int index = temp.size() - 1; index > -1; --index) 
//     {
//         encoded.push_back(temp[index]);
//     }

//     for (int index = 0; index < str.size(); ++index) 
//     {
//         temp = toBinary(patternBit((int) str[index]));
//         for (int i = temp.size() - 1; i > -1; i--) 
//         {
//             encoded.push_back(temp[i]);
//         }
//     }

//     temp = toBinary(checksumCalc());
//     for (int index = temp.size() - 1; index > -1; --index) 
//     {
//         encoded.push_back(temp[index]);
//     }

//     temp = toBinary(patternBit(138));
//     for (int index = temp.size() - 1; index > -1; --index) 
//     {
//         encoded.push_back(temp[index]);
//     }

//     for (int i = 0; i < img_padding; ++i) 
//     {
//         encoded.push_back(0);
//     }

//     return encoded;
// }

void Code128::encodeCode128() 
{
    //encode padding
    for (int i = 0; i < img_padding; i++) 
    {
        encoded.push_back(0);
    }

    //get start patern bit
    std::vector<int> temp = toBinary(patternBit(136));

    //encode start patern bit
    for (int index = temp.size() - 1; index > -1; --index) 
    {
        encoded.push_back(temp[index]);
    }

    //encode msg
    for (int index = 0; index < str.size(); ++index) 
    {
        temp = toBinary(patternBit((int) str[index]));
        for (int i = temp.size() - 1; i > -1; i--) 
        {
            encoded.push_back(temp[i]);
        }
    }

    //get checksum
    temp = toBinary(checksumCalc());

    //encode checksum
    for (int index = temp.size() - 1; index > -1; --index) 
    {
        encoded.push_back(temp[index]);
    }

    //get stop patern bits
    temp = toBinary(patternBit(138));

    //encode stop patern bits
    for (int index = temp.size() - 1; index > -1; --index) 
    {
        encoded.push_back(temp[index]);
    }

    //encode padding
    for (int i = 0; i < img_padding; ++i) 
    {
        encoded.push_back(0);
    }
}

inline int Code128::patternBit(int _char) { return code128_pattern[_char - 32]; }

int Code128::checksumCalc() 
{
    int checksum = 104;
    for (int i = 0; i < str.length(); ++i) 
    {
        checksum += (str[i] - 32) * (i + 1);
    }

    return patternBit((checksum % 103) + 32);
}

inline void Code128::setImgPadding(int padding) { img_padding = padding; }

void Code128::printEncoded()
{
    std::cout << "padding:\t";
    for(int i = 0; i < img_padding; ++i)
    {
        std::cout << encoded[i] << " ";
    }
    
    std::cout << "\nstart bits:\t";

    for(int i = img_padding; i < img_padding + C128_CHAR_LEN; ++i)
    {
        std::cout << encoded[i] << " ";
    }

    std::cout << "\nmsg:\t\t";

    for(int i = img_padding + C128_CHAR_LEN; i < encoded.size() - C128_CHAR_LEN - C128_STOP_LEN - img_padding; ++i)
    {
        for(int j = 0; j < C128_CHAR_LEN; ++j)
        {
            std::cout << encoded[i + j] << " ";
        }

        i += C128_CHAR_LEN - 1;

        if(i != encoded.size() - C128_CHAR_LEN - C128_STOP_LEN - img_padding - 1)
        {
            std::cout << "\n\t\t";

        }
    }

    std::cout << "\nchecksum:\t";

    for(int i = encoded.size() - C128_CHAR_LEN - C128_STOP_LEN - img_padding; i < encoded.size() - C128_STOP_LEN - img_padding; ++i)
    {
        std::cout << encoded[i] << " ";
    }

    std::cout << "\nstop bits:\t";

    for(int i = encoded.size() - C128_STOP_LEN - img_padding; i < encoded.size()- img_padding; ++i)
    {
        std::cout << encoded[i] << " ";
    }

    std::cout << "\npadding:\t";

    for(int i = encoded.size()- img_padding; i < encoded.size(); ++i)
    {
        std::cout << encoded[i] << " ";
    }

    std::cout << "\n";
}