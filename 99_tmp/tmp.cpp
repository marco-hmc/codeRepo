#include <codecvt>
#include <iostream>
#include <locale>
#include <string>

bool isCharSingleByte(const char* input, int offset) {
    return (input[offset] & 0x80) == 0;
}

bool isIncrementSymbol(const char* input, int offset) {
    std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> converter;
    std::u32string utf32 =
        converter.from_bytes(input + offset, input + offset + 4);
    return utf32[0] == U'\u2206';
}

int main() {
    const char* input = u8"a∆!";
    int cnt = 0;
    while (input[cnt]) {
        if (isCharSingleByte(input, cnt)) {
            std::cout << input[cnt] << " is a single-byte character."
                      << std::endl;
            cnt++;
        } else {
            if (isIncrementSymbol(input, cnt)) {
                std::cout << "Found increment symbol ∆ at offset " << cnt << "."
                          << std::endl;
            } else {
                std::cout << "Found multi-byte character at offset " << cnt
                          << "." << std::endl;
            }
            cnt +=
                3;  // Move to the next character (assuming 3-byte UTF-8 character)
        }
    }
    return 0;
}