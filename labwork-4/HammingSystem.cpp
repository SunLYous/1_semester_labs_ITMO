#include "HammingSystem.h"

std::pair<unsigned char, unsigned char> HammingSystem::CodingElement(unsigned char element) {
    std::bitset temporary = std::bitset<8>(element); // превращаем чар в двоичный код
    std::string binary_tmp = temporary.to_string(); // записываем в стринг код чара
    std::string one_part_char;
    std::string two_part_char;
    for (int i = 0; i < 4; ++i) {
        one_part_char += binary_tmp[i];
    }

    for (int i = 4; i < 8; ++i) {
        two_part_char += binary_tmp[i];
    }

    unsigned char one_char = HammingCode(one_part_char);
    unsigned char two_char = HammingCode(two_part_char);
    std::pair<unsigned char, unsigned char> char_symbol;
    char_symbol.first = one_char;
    char_symbol.second = two_char;
    return char_symbol;
}

unsigned char HammingSystem::HammingCode(std::string element) {
    element = "00" + element;
    std::string tmp;
    std::string tmp_two;
    int count = 0;
    for (int i = 0; i < 3; i++) {
        tmp += element[i];
    }

    tmp = tmp + "0";
    for (int i = 3; i < element.size(); i++) {
        tmp_two += element[i];
    }

    element = tmp + tmp_two;
    for (int i = 0; i < element.size(); i += 2) {
        if (element[i] == '1') {
            count++;
        }

    }

    if (count % 2 != 0) {
        tmp = '1';
    } else { tmp = '0'; }
    count = 0;
    for (int i = 1; i < element.size(); i++) {
        if (element[i] == '1') {
            count++;
        }

        if (i % 2 == 0 && i + 2 < element.size()) {
            i += 2;
        }

    }

    if (count % 2 != 0) {
        tmp += '1';
    } else {
        tmp += '0';
    }

    tmp = tmp + element[2];
    count = 0;
    for (int i = 3; i < 7; i++) {
        if (element[i] == '1') {
            count++;
        }

    }

    if (count % 2 != 0) {
        tmp += '1';
    } else {
        tmp += '0';
    }

    for (int i = 4; i < element.size(); i++) {
        tmp += element[i];
    }

    element = tmp;
    unsigned char bit = element[0];
    for (int i = 1; i < element.size(); i++) {
        bit = bit ^ element[i];
    }

    element = element + (char) bit;
    unsigned char symbol = 0;
    for (int k = 0; k < element.size(); ++k) {
        symbol = (symbol << 1) + (element[k] - '0');
    }

    return symbol;
}
std::string HammingSystem::HammingDecoding(unsigned char element) {
    std::bitset temporary = std::bitset<8>(element); // превращаем чар в двоичный код
    std::string binary_tmp = temporary.to_string();
    int count_one = 0;
    bool flag_one = false;
    std::string tmp;
    for (int i = 0; i < binary_tmp.size(); i += 2) {
        if (binary_tmp[i] == '1') {
            count_one++;
        }

    }

    if (count_one % 2 != 0) {
        flag_one = true;
    }

    int count_two = 0;
    bool flag_two = false;
    for (int i = 1; i < 7; i++) {
        if (binary_tmp[i] == '1') {
            count_two++;
        }

        if (i % 2 == 0 && i + 2 < binary_tmp.size()) {
            i += 2;
        }

    }
    if (count_two % 2 != 0) {
        flag_two = true;
    }

    int count_four = 0;
    bool flag_four = false;
    for (int i = 3; i < 7; i++) {
        if (binary_tmp[i] == '1') {
            count_four++;
        }

    }
    if (count_four % 2 != 0) {
        flag_four = true;
    }

    char bit_check = '0';
    bit_check ^= (char) binary_tmp[0];
    for (int i = 1; i < binary_tmp.size(); i++) {
        bit_check = (char) bit_check ^ (char) binary_tmp[i];
    }

    if ((!flag_two && !flag_one && !flag_four && (bit_check == '0' || bit_check == '1'))
            || (flag_two && !flag_one && !flag_four && (bit_check == '0' || bit_check == '1'))
            || (!flag_two && flag_one && !flag_four && (bit_check == '0' || bit_check == '1'))
            || (!flag_two && !flag_one && flag_four && (bit_check == '0' || bit_check == '1'))) {
        tmp = binary_tmp[2];
        for (int i = 4; i < 7; i++) {
            tmp += binary_tmp[i];
        }

        return tmp;
    } else if (bit_check == '1' && (flag_four || flag_one || flag_two)) {
        if (flag_two && flag_four && flag_one) {
            tmp = binary_tmp[2];
            for (int i = 4; i < 6; i++) {
                tmp += binary_tmp[i];
            }

            if (binary_tmp[6] == '0') {
                tmp += "1";
            } else {
                tmp += "0";
            }

            return tmp;
        } else if (flag_four && flag_one) {
            tmp = binary_tmp[2];
            if (binary_tmp[4] == '0') {
                tmp += "1";
            } else {
                tmp += "0";
            }

            for (int i = 5; i < 7; i++) {
                tmp += binary_tmp[i];
            }
            return tmp;
        } else if (flag_four && flag_two) {
            tmp = binary_tmp[2];
            tmp += binary_tmp[4];

            if (binary_tmp[5] == '0') {
                tmp += "1";
            } else {
                tmp += "0";
            }
            tmp += binary_tmp[6];

            return tmp;
        } else if (flag_one && flag_two) {
            if (binary_tmp[2] == '0') {
                tmp += "1";
            } else {
                tmp += "0";
            }

            for (int i = 4; i < 7; i++) {
                tmp += binary_tmp[i];
            }

            return tmp;
        }

    } else if (flag_one || flag_four || flag_two && (count_one + count_four + count_two > 8) && bit_check == '0') {
        std::cerr << "Error" << "\n";
    }

}
