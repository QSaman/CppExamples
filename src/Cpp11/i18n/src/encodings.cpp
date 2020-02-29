#include <iostream>
#include <string>

int main()
{
    //Character Unicode    UTF-8
    //‪   س       U+0633     D8B3
    //‪   ا       U+0627     D8A7
    //‪   م       U+0645     D985
    //‪   ن       U+0646     D986
    using namespace std;
    string strUTF8_1 {'\xd8', '\xb3', //س
                    '\xd8', '\xa7', //ا
                    '\xd9', '\x85', //م
                    '\xd8', '\xa7', //ا
                    '\xd9', '\x86'  //ن
                   };
    //u8 string literal means that string literal must be encoded into utf-8
    string strUTF8_2 = u8"\xd8\xb3\xd8\xa7\xd9\x85\xd8\xa7\xd9\x86";
    string strUTF8_3 = "\xd8\xb3\xd8\xa7\xd9\x85\xd8\xa7\xd9\x86";
    // \u escape sequence means a unicode code
    string strUTF8_4 = "\u0633\u0627\u0645\u0627\u0646";
    //L string literal means that string literal must be encoded into wide string
    wstring wideStr = L"\u0633\u0627\u0645\u0627\u0646";
    //u string literal means that string literal must be encoded into UTF-16
    u16string u16Str = u"\u0633\u0627\u0645\u0627\u0646";
    //U string literal means that string literal must be encoded into UTF-32
    u32string u32Str = U"\u0633\u0627\u0645\u0627\u0646";
    //u character literal means that character literal is a char16_t
    char16_t ch16_1 = u'س';
    //U character literal means that character literal is a char32_t
    char32_t ch32_1 = U'س';
    //0xd8 is a integer literal
    string strUTF8_5 {(char)0xd8, (char)0xb3,   //س
                      (char)0xd8, (char)0xa7,   //ا
                      (char)0xd9, (char)0x85,   //م
                      (char)0xd8, (char)0xa7,   //ا
                      (char)0xd9, (char)0x86};  //ن

    cout << strUTF8_1 << endl;
    cout << strUTF8_2 << endl;
    cout << strUTF8_3 << endl;
    cout << strUTF8_4 << endl;
    cout << "The output of wide string: ";
    //In Linux wchart_t is 4 bytes and in Windows it's 2 bytes
    for (auto ch : wideStr)
        cout << hex << ch << ' ';
    cout << endl;
    cout << "The output of u16string: ";
    for (char16_t ch : u16Str)
        cout << ch << ' ';
    cout << endl;
    cout << "The output of u32string: ";
    for (char32_t ch : u32Str)
        cout << ch << ' ';
    cout << endl;
    cout << strUTF8_5 << endl;
    cout << ch16_1 << endl;
    cout << ch32_1 << endl;
}
