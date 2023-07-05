#include "number.h"
#include <vector>
#include <iostream>
#include <string>
#include <cmath>

const int kElementNine = 1000000000;

int len_num(int i) {
    if (i == 0) {
        return 1;
    } // тк при входе нуля количество элементов не подсчитывается
    int sum = 0;
    while (i) {
        i = i / 10;
        sum++;
    }

    return sum;
} //подсчет количества цифр в элементе массива

uint2022_t from_uint(uint32_t i) {
    uint2022_t answer;
    answer.number[uint2022_t::SIZE - 1] = i % kElementNine;
    answer.number[uint2022_t::SIZE - 2] = i / kElementNine;
    answer.amount = len_num(i);

    return answer;
} // преобразование из инта в юинт_2022

uint2022_t from_string(const char* buff) {
    uint2022_t answer;
    int i = 0;
    while (isdigit(buff[i])) {
        ++i;
    }
    //подсчет количества введенных цифр
    answer.amount = i;
    int num = 0;
    int digit_nine = 0;
    int finish = answer.SIZE - 1;
    for (int j = answer.amount - 1; j >= 0; j--) {
        int digit = (buff[j]) - '0'; //перевод из чара в инт спомощью аски кода 48 == 0
        digit_nine = digit_nine + digit * pow(10, num); // оформление элемента вектора (9 цифр в элементе)
        num++;
        if (num >= 9) {
            answer.number[finish] = digit_nine; //запись цифр в элемент массива
            digit_nine = 0;
            num = 0;
            finish--;
        }

    }

    answer.number[finish] = digit_nine; //дозаписываем оставщиеся цифры

    return answer;
}

uint2022_t operator+(const uint2022_t& lhs, const uint2022_t& rhs) {
    uint2022_t answer;
    int sum = 0;
    for (int i = answer.SIZE - 1; i > 0; i--) {
        sum = sum + lhs.number[i] + rhs.number[i];
        answer.number[i] = sum % kElementNine;
        sum = sum / kElementNine;
    }

    return answer;
}

uint2022_t operator-(const uint2022_t& lhs, const uint2022_t& rhs) {
    uint2022_t answer;
    int mod = 0;
    for (int i = answer.SIZE - 1; i > 0; i--) {
        int digit_lhs = lhs.number[i];
        int digit_rhs = rhs.number[i];
        for (int j = 0; j < 9; j++) {
            mod += 10 + (digit_lhs % 10) - (digit_rhs % 10);
            digit_lhs = digit_lhs / 10;
            digit_rhs = digit_rhs / 10;
            answer.number[i] += (mod % 10) * pow(10, j);
            if (mod < 10) mod = -1;
            else mod = 0;
        }

    }

    return answer;
}

uint2022_t operator*(const uint2022_t& lhs, const uint2022_t& rhs) {
    uint2022_t answer;
    for (int i = 0; i <= answer.SIZE - 1; i++) {
        for (int j = 0; j <= answer.SIZE - 1; j++) {
            long long bigger = answer.number[abs((answer.SIZE - 1) - (i + j))]
                    + (long long) lhs.number[answer.SIZE - 1 - i]
                            * (long long) rhs.number[answer.SIZE - 1 - j]
                    + bigger;
            answer.number[abs((answer.SIZE - 1) - (i + j))] = bigger % kElementNine;
            bigger = bigger / kElementNine;
        }

    }

    return answer;
}

uint2022_t operator/(const uint2022_t& lhs, const uint2022_t& rhs) {

    return uint2022_t();
}

bool operator==(const uint2022_t& lhs, const uint2022_t& rhs) {
    uint2022_t answer;

    for (int i = 0; i < answer.SIZE; i++) {
        if (lhs.number[i] != rhs.number[i]) {

            return false;
        }

    }

    return true;
}

bool operator!=(const uint2022_t& lhs, const uint2022_t& rhs) {
    for (int i = 0; i < uint2022_t::SIZE; i++) {
        if (lhs.number[i] != rhs.number[i]) {

            return true;
        }

    }

    return false;
}

std::ostream& operator<<(std::ostream& stream, const uint2022_t& value) {
    bool flag = false;
    bool flag_two = true;
    for (int i = 0; i < uint2022_t::SIZE; i++) {
        if (value.number[i] != 0) {
            flag = true;
        }

        if (len_num(value.number[i]) == 0 && flag) {
            stream << 000000000;
        }

        if (len_num(value.number[i]) != 9 && flag && !flag_two) {
            for (int j = 0; j < 9 - len_num(value.number[i]); j++) {
                stream << 0;
            }

        }

        stream << value.number[i];
        flag_two = false;
    }

    bool flag_null = false;
    for (int i = 0; i < uint2022_t::SIZE; i++) {
        if (value.number[i] != 0) {
            flag_null = true;
        }

    }

    if (!flag_null) {
        stream << 0;
    }

    return stream;
}
