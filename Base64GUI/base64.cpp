#include "base64.h"

using namespace std;



Base64::Base64()
{

}


bool Base64::encode(std::string filepath)
{
    ifstream file(filepath, ios::binary);
    //ofstream result(_savePath + ".b64", ios::out | ios::trunc);
    ofstream result(filepath.substr (0 , filepath.find_last_of('.')) + ".b64", ios::binary);

    char readChar = 0;
    int charCount = 0;
    bool readStatus = true;
    std::array<char , 3> readCharStr;



    while(readStatus)
    {
        //spr czy mozesz czytac
        if(!file.get(readChar)){
            readStatus = false;
            //break;
        }
        //dodaj oryginalne znaki do buffora
        if(readStatus){
            readCharStr[charCount] = readChar;
            charCount++;
        }
        //kiedy zczytałes 3 litery to zakoduj
        if(charCount == 3)
        {
            charCount = 0;
            std::array<char , 4> char4;
            //zakodowanie
            char4[0] = (readCharStr[0] & 0xfc) >> 2;
            char4[1] = ((readCharStr[0] & 0x03) << 4) + ((readCharStr[1] & 0xf0) >> 4);
            char4[2] = ((readCharStr[1] & 0x0f) << 2) + ((readCharStr[2] & 0xc0) >> 6);
            char4[3] = readCharStr[2] & 0x3f;
            //zapisanie
            for(const auto c : char4){
                result << _base64Chars[c];
            }
        }
        //jezeli plik sie skonczyl i zostaly mniej niz 3 litery to zakoduj to co masz i dodaj =
        if(charCount != 3 && charCount > 0 && readStatus == false)
        {
            int i = charCount;
            std::array<char , 4> char4;
            for(int j = i; j < 3; j++)
                readCharStr[j] = '\0';

            char4[0] = (readCharStr[0] & 0xfc) >> 2;
            char4[1] = ((readCharStr[0] & 0x03) << 4) + ((readCharStr[1] & 0xf0) >> 4);
            char4[2] = ((readCharStr[1] & 0x0f) << 2) + ((readCharStr[2] & 0xc0) >> 6);
            char4[3] = readCharStr[2] & 0x3f;

            for (int j = 0; (j < i + 1); j++)
                result << _base64Chars[char4[j]];
            //dodaj = tyle razy ile brakujacych liter
            while((i++ < 3))
                result << '=';
        }

    }

    file.close();
    result.close();
}

void Base64::decode(std::string filepath , std::string outputformat)
{
    ifstream file(filepath, ios::in);
    ofstream result(filepath.substr (0 , filepath.find_last_of('.')) + "1." + outputformat, ios::binary);

    char readChar = 0;
    int charCount = 0;
    bool readStatus = true;
    std::array<char , 4> readCharStr; //tym razem czytamy po 4 znaki
    int specCharCount = 0;

    while(readStatus)
    {
        //spr czy mozesz czytac
        if(!file.get(readChar)){
            readStatus = false;
            //break;
        }
        if(readChar == '=')
        {
            readStatus = false;
        }

        //dodaj oryginalne znaki do buffora
        if(readStatus){
            readCharStr[charCount] = readChar;
            charCount++;
        }

        if(charCount == 4)
        {
            charCount = 0;
            std::array<char , 3> char3;

            for (int i = 0; i < 4; i++){
                readCharStr[i] = _base64Chars.find(readCharStr[i]); //zamien znaki
            }

            char3[0] = (readCharStr[0] << 2) + ((readCharStr[1] & 0x30) >> 4);
            char3[1] = ((readCharStr[1] & 0xf) << 4) + ((readCharStr[2] & 0x3c) >> 2);
            char3[2] = ((readCharStr[2] & 0x3) << 6) + readCharStr[3];

            for (int i = 0; (i < 3); i++){
                result << char3[i];
            }
        }

        if(charCount != 4 && charCount > 0 && readStatus == false)
        {
            std::array<char , 3> char3;
            int i = charCount;
            for (int j = i; j <4; j++){
                readCharStr[j] = 0;
            }

            for (int j = 0; j <4; j++){
                readCharStr[j] = _base64Chars.find(readCharStr[j]);

            }

            char3[0] = (readCharStr[0] << 2) + ((readCharStr[1] & 0x30) >> 4);
            char3[1] = ((readCharStr[1] & 0xf) << 4) + ((readCharStr[2] & 0x3c) >> 2);
            char3[2] = ((readCharStr[2] & 0x3) << 6) + readCharStr[3];

            for (int j = 0; (j < i); j++){
                result << char3[j];
            }

            charCount = 0;
        }
    }

    file.close();
    result.close();
}



