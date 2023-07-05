#include <iostream>
#include <fstream>
#include <string>


int lines_func(std::string& file) {
    std::ifstream filename(file);
    int line = 0;
    char c;
    while (filename.get(c)) {
        if (c == '\n') {
            ++line;
        }

    }
    std::cout << "lines: " << line << '\n';
}

int bytes_func(std::string& file) {
    std::ifstream filename(file, std::ios::binary | std::ios::ate);
    std::cout << "bytes: " << filename.tellg() << '\n';
}

int words_func(std::string& file) {
    std::ifstream filename(file);
    int sum_words = 0;
    std::string my_word;
    while (filename >> my_word) {
        sum_words++;
    }

    std::cout << "words: " << sum_words << "\n";
}

int stats_func(const std::string& file) {
    std::ifstream filename(file);
    int line = 0;
    char c;
    while (filename.get(c)) {
        if (c == '\n') {
            ++line;
        }
    }
    std::ifstream file_name(file, std::ios::binary | std::ios::ate);
    int bytes = file_name.tellg();
    int stats = bytes / line;
    std::cout << "stats: " << stats << '\n';
}

int main(int argc, char* argv[]) {
    system("chcp 65001");
    bool flag_lines = false;
    bool flag_bytes = false;
    bool flag_words = false;
    bool flag_stats = false;
    for (int i = 0; i < argc; i++) {
        std::string command = argv[i];
        if (command.length() >= 2 && command.length() <= 7) {
            if (command[0] == '-') {
                if (command[1] == '-') {
                    if (command == "--lines") {
                        flag_lines = true;
                    }

                    if (command == "--bytes") {
                        flag_bytes = true;
                    }

                    if (command == "--words") {
                        flag_words = true;
                    }
                    if (command == "--stats") {
                        flag_stats = true;
                    }

                } else {
                    for (int j = 1; j < command.length() && command.length() <= 5; j++) {
                        switch (command[j]) {

                            case 'l':flag_lines = true;
                                break;

                            case 'c': flag_bytes = true;
                                break;

                            case 'w' : flag_words = true;
                                break;

                            case 's': flag_stats = true;
                                break;

                        }

                    }

                }

            }

        }
    }

    for (int i = 1; i < argc; i++) {
        std::string file = argv[i];
        if (file[0] != '-') {

            if (flag_lines) {
                lines_func(file);
            }

            if (flag_bytes) {
                bytes_func(file);
            }

            if (flag_words) {
                words_func(file);
            }
            if (flag_stats) {
                stats_func(file);
            }

            if (!flag_words && !flag_bytes && !flag_lines && !flag_stats && argc == 2) {
                lines_func(file);
                bytes_func(file);
                words_func(file);
                stats_func(file);
            }

        }

    }

    return 0;
}