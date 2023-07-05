#include "parser.h"
namespace omfl {
    AbstractObject& omfl::Parser::Get(const std::string& key) const {
        std::string name_section;
        std::string name_section_next;
        if (key.find(".") != std::string::npos) {
            name_section = key.substr(0, key.find("."));
            name_section_next = key.substr(key.find(".") + 1, key.size());
            for (int i = 0; i < param.size(); i++) {
                if (param[i]->key_ == name_section) {
                    return param[i]->Get(name_section_next);
                }
            }
        } else {
            name_section_next = key;
            for (int i = 0; i < param.size(); i++) {
                if (param[i]->key_ == name_section) {
                    std::string tmp = param[i]->key_;
                    return *param[i];
                }
            }
        }
        for (int i = 0; i < param.size(); i++) {
            if (param[i]->key_ == key) {
                return *param[i];
            }
        }
    }
    bool Parser::valid() const {
        return valid_;
    }

    void Parser::Isvalid(std::vector<std::pair<std::string, std::string>> param) {
        for (int i = 0; i < param.size(); i++) {
            if (param[i].second == ".section") {
                if (param[i].second.size() < 2) {
                    valid_ = false;
                    return;
                }
                if (param[i].first[param[i].first.size() - 2] == '.') {
                    valid_ = false;
                    return;
                }
            }
            if (param[i].first.size() == 0) {
                valid_ = false;
            }
            if (param[i].second.size() == 0) {
                valid_ = false;
            }
            if (param[i].first.find('!') != std::string::npos || param[i].first.find('*') != std::string::npos
                    || param[i].first.find('.') != std::string::npos) {
                valid_ = false;
                return;
            }

            if (param[i].second.size() == 0) {
                valid_ = false;
                return;
            }
            if (param[i].first.size() == 0) {
                valid_ = false;
                return;
            }
            if (param[i].second[0] != '"' && param[i].second[0] != '-' && param[i].second[0] != '+'
                    && !isdigit(param[i].second[0]) && param[i].second != "true" && param[i].second != "false"
                    && param[i].second[0] != '[' && param[i].second != ".section") {
                valid_ = false;
                return;
            }
            if (param[i].second[0] == '[') {
                if (param[i].second[param[i].second.size() - 1] != ']') {
                    valid_ = false;
                    return;
                }
                if (param[i].second.size() < 2) {
                    valid_ = false;
                    return;
                }
            }
            if (param[i].second[param[i].second.size() - 1] == ']') {
                if (param[i].second[0] != '[') {
                    valid_ = false;
                    return;
                }
                if (param[i].second.size() < 2) {
                    valid_ = false;
                    return;
                }
            }
            if (param[i].second[param[i].second.size() - 1] == ']' && param[i].second[0] == '[') {
                int count = 0;
                for (int j = 0; j < param[i].second.size(); j++) {
                    if (param[i].second[j] == '[') {
                        count++;
                    }
                    if (param[i].second[j] == ']') {
                        count--;
                    }

                }
                if (count != 0) {
                    valid_ = false;
                    return;
                }
                if (param[i].second.find(';') != std::string::npos) {
                    valid_ = false;
                    return;
                }
            }
            if (param[i].second[0] == '"' && param[i].second[param[i].second.size() - 1] == '"') {
                std::string tmp = param[i].second.substr(1, param[i].second.size() - 2);
                for (int j = 0; j < tmp.size(); j++) {
                    if (tmp[j] == '"' || tmp[j] == '\\') {
                        valid_ = false;
                        return;
                    }
                }
            }
            if (param[i].second[0] == '\"' && param[i].second.size() == 1) {
                valid_ = false;
                return;
            }
            for (int j = i; j < param.size(); j++) {
                if (param[i].first == param[j].first && i != j && param[i].second != ".section") {
                    valid_ = false;
                    return;
                }
            }
            if ((param[i].second[0] == '.' || param[i].second[param[i].second.size() - 1] == '.')
                    && param[i].second != ".section") {
                valid_ = false;
                return;
            }
            if ((param[i].second[0] == '+' || param[i].second[0] == '-') || std::isdigit(param[i].second[0])) {
                if (param[i].second[0] == '+' || param[i].second[0] == '-') {
                    std::string tmp = param[i].second.substr(1, param[i].second.size());
                    if (tmp.size() == 0) {
                        valid_ = false;
                        return;
                    }
                    if (tmp[tmp.size() - 1] == '.') {
                        valid_ = false;
                        return;
                    }
                    for (int j = 0; j < tmp.size(); j++) {
                        if (!isdigit(tmp[j - 1]) && tmp[j] == '.') {
                            valid_ = false;
                            return;
                        }
                        if (!isdigit(tmp[j]) && tmp[j] != '.') {
                            valid_ = false;
                            return;
                        }
                    }
                } else {
                    std::string tmp = param[i].second;
                    if (tmp.size() == 0) {
                        valid_ = false;
                        return;
                    }
                    if (tmp[tmp.size() - 1] == '.') {
                        valid_ = false;
                        return;
                    }
                    for (int j = 0; j < tmp.size(); j++) {
                        if (!isdigit(tmp[j - 1]) && tmp[j] == '.') {
                            valid_ = false;
                            return;
                        }
                        if (!isdigit(tmp[j]) && tmp[j] != '.') {
                            valid_ = false;
                            return;
                        }
                    }
                }

            }
            if (param[i].second[0] == '\"' && param[i].second[param[i].second.size() - 1] != '\"') {
                valid_ = false;
                return;
            }

            return;

        }

    }
    std::vector<std::string> Separation(const std::string& str, char symbol) {
        std::vector<std::string> arguments;
        std::stringstream s(str);
        std::string argument;
        while (!s.eof()) {
            if (str.find(symbol) != std::string::npos && str[str.size() - 1] == '.') {
                arguments.push_back(str);
                return arguments;
            }
            getline(s, argument, symbol);
            arguments.push_back(argument);
        }

        return arguments;
    }

    std::vector<std::string> SeparationArray(const std::string& str, char symbol) {
        std::vector<std::string> arguments;
        std::vector<std::string> arguments_tmp;
        std::string array;
        std::string delete_array = "";
        std::vector<int> index;
        for (int i = 0; i < str.size(); i++) {
            if (str[i] == '[') {
                index.push_back(i);
            }
            if (str[i] == ']') {
                index.push_back(i);
            }
        }
        if (index.size() != 0) {
            arguments = Separation(str.substr(0, index[0] - 1), ',');
        } else {
            arguments = Separation(str, ',');
        }
        std::vector<std::string> tmp_check;
        for (int i = 0; i < arguments.size(); i++) {
            if (arguments[i].size() != 0) {
                tmp_check.push_back(arguments[i]);
            }
        }
        arguments = tmp_check;
        int k = 1;
        std::string tmp;
        while (k < index.size() && k + 1 < index.size()) {
            for (int i = index[k] + 2; i < index[k + 1] - 2; i++) {
                tmp += str[i];
            }
            arguments_tmp = Separation(tmp, ',');
            for (int i = 0; i < arguments_tmp.size(); i++) {
                if (arguments_tmp[i].size() > 0) {
                    arguments.push_back(arguments_tmp[i]);
                }
            }
            k += 2;
        }
        for (int i = 0; i < index.size(); i += 2) {
            array = str.substr(index[i], index[i + 1] - index[i] + 1);
            arguments.push_back(array);
        }

        return arguments;
    }
    std::string DeleteSymbol(std::string value) {
        if (value.find('#') != std::string::npos) {
            value = value.substr(0, value.find('#'));
            value = DeleteSymbol(value);
            return value;
        }
        return value;
    }

    std::string DeleteSpace(std::string& str) {
        std::string tmp_str;
        if ((str.find('\"') && str[str.find('\"') + 1] < str.size() && str.find('[') == std::string::npos
                && str.find('#') == std::string::npos)) {
            int k = 0;
            while (str != "\"" && k < str.size()) {
                if (str[k] == '\"') {
                    tmp_str += str[k];
                    break;
                }
                if (str[k] != ' ') {
                    tmp_str += str[k];
                }
                k++;
            }
            str = str.substr(k + 1, str.size());
            tmp_str += str.substr(0, str.find('\"') + 1);
            return tmp_str;
        } else {
            for (int i = 0; i < str.size(); i++) {
                if (str[i] != ' ') {
                    tmp_str += str[i];
                }
            }
            tmp_str = DeleteSymbol(tmp_str);
            return tmp_str;
        }
    }
    std::string DeleteSpaces(std::string& str) {

        if (str.find('#') != std::string::npos) {
            if (str.find('#') == 0) {
                return str;
            }
            str = str.substr(0, str.find('#'));
        }
        if (str.size() == 0) {
            return "";
        }
        if (str.find('=') == std::string::npos && str.find('[') == std::string::npos
                && str.find(']') == std::string::npos) {
            if (str.find('{') != std::string::npos) {
                return str;
            }
            return "";
        }
        int i = 0;
        if (str.find('=') != std::string::npos) {
            while (str[i] == ' ') {
                i++;
            }
            str.erase(0, i);
            int j = str.find('=') + 1;
            int count = 0;
            while (str[j] == ' ' && j - 1 > 0) {
                j--;
                count++;
            }
            str.erase(str.find('=') - count, count);
            int k = 0;
            for (int v = str.find('=') + 1; v < str.size(); v++) {
                if (str[v] == ' ') {
                    k++;
                } else {
                    break;
                }
            }
            str.erase(str.find('=') + 1, k);
            int l = str.size() - 1;
            while (str[l] == ' ' && l > 0) {
                l--;
            }
            str.erase(l + 1, str.size() - l);
            return str;
        } else {
            while (str[i] == ' ') {
                i++;
            }
            str.erase(0, i);
            int j = str.size() - 1;
            while (str[j] == ' ' && j > 0) {
                j--;
            }
            str.erase(j + 1, str.size());
            return str;

        }
    }

    void ParseType(std::vector<AbstractObject*>* arguments, std::vector<std::string>& value) {
        for (int j = 0; j < value.size(); j++) {
            if (value[j][0] == '\"' && value[j][value[j].size() - 1] == '\"') {
                value[j] = value[j].substr(1, value[j].size() - 2);
                arguments->push_back(new StringObject(".string", value[j]));
            } else if (value[j] == "true" || value[j] == "false") {
                arguments->push_back(new BoolObject(".bool", value[j] == "true"));
            } else if (value[j].find('.') != std::string::npos && value[j][0] != '[') {
                arguments->push_back(new FloatObject(".float", std::stof(value[j])));
            } else if (value[j][0] == '[' && value[j][value[j].size() - 1] == ']') {
                ArrayObject* array = new ArrayObject(".array");
                arguments->push_back(array);
                std::vector<std::string> array_arguments;
                array_arguments = SeparationArray(value[j].substr(1, value[j].size() - 2), ',');
                for (int i = 0; i < array_arguments.size(); i++) {
                    array_arguments[i] = DeleteSpace(array_arguments[i]);
                }
                ParseType(array->SetArray(), array_arguments);
            } else {
                arguments->push_back(new IntObject(value[j], std::stoi(value[j])));
            }
        }
    }

    Parser parse(const std::string& str) {
        Parser parser;
        std::string key;
        std::string value;
        std::vector<std::string> arguments;
        std::vector<std::pair<std::string, std::string>> map;
        std::vector<SectionObject*> sections;
        SectionObject* section_tmp = nullptr;
        arguments = Separation(str, '\n');
        for (int i = 0; i < arguments.size(); i++) {
            arguments[i] = DeleteSpaces(arguments[i]);
        }
        for (int i = 0; i < arguments.size(); i++) {
            key = "";
            value = "";
            if (arguments[i].find('=') == std::string::npos) {
                if (arguments[i].find('{') != std::string::npos) {
                    parser.valid_ = false;
                }
            }
            if (arguments[i].size() == 0) {
                continue;
            }
            if (arguments[i].find('=') == std::string::npos && arguments[i][0] == '[' &&
                    arguments[i][arguments[i].size() - 1] == ']') {
                arguments[i] = arguments[i].substr(1, arguments[i].size() - 2);
                std::vector<std::string> section_name = Separation(arguments[i], '.');
                for (int k = 0; k < section_name.size(); k++) {
                    section_name[k] = DeleteSpace(section_name[k]);
                    std::string keys = section_name[k];
                    std::string values = ".section";
                    map.push_back(std::make_pair(keys, values));
                }

            } else {
                if (arguments[i].find('=') != std::string::npos) {
                    key = arguments[i].substr(0, arguments[i].find('='));
                    value = arguments[i].substr(arguments[i].find('=') + 1, arguments[i].size());
                }
                if (arguments[i][0] == '#') {
                    if (arguments.size() > 1)
                        parser.valid_ = false;
                }
            }
            if (key.size() != 0 || value.size() != 0) {
                map.push_back(std::make_pair(key, value));
            }
        }

        parser.Isvalid(map);
        if (parser.valid()) {
            for (int i = 0; i < map.size(); i++) {
                if (map[i].second == ".section") {
                    if (sections.size() == 0) {
                        parser.param.push_back(new SectionObject(map[i].first));
                        sections.push_back(dynamic_cast<SectionObject*>(&parser.Get(map[i].first)));
                    } else {
                        for (int j = 0; j < sections.size(); j++) {
                            if (sections[j]->key_ == map[j].first) {
                                section_tmp = sections[j];
                            }
                        }
                        if (section_tmp != nullptr) {
                            if (section_tmp->key_ != map[i].first) {
                                section_tmp->SetSection(map[i].first);
                                sections.push_back(dynamic_cast<SectionObject*>(&section_tmp->Get(map[i].first)));
                            } else {
                                sections.back()->SetSection(map[i].first);
                                sections.push_back(dynamic_cast<SectionObject*>(&parser.Get(map[i].first)));
                            }
                        }
                    }
                } else if (map[i].second[0] == '\"' && map[i].second[map[i].second.size() - 1] == '\"') {
                    if (sections.size() != 0) {
                        map[i].second = map[i].second.substr(1, map[i].second.size() - 2);
                        sections.back()->SetString(map[i].first, map[i].second);
                    } else {
                        map[i].second = map[i].second.substr(1, map[i].second.size() - 2);
                        parser.param.push_back(new StringObject(map[i].first, map[i].second));
                    }
                } else if (map[i].second == "true" || map[i].second == "false") {
                    if (sections.size() != 0) {
                        sections.back()->SetBool(map[i].first, map[i].second == "true");
                    } else {
                        parser.param.push_back(new BoolObject(map[i].first, map[i].second == "true"));
                    }

                } else if (map[i].second.find('.') != std::string::npos && map[i].second[0] != '[') {
                    if (sections.size() != 0) {
                        sections.back()->SetFloat(map[i].first, std::stof(map[i].second));
                    } else {
                        parser.param.push_back(new FloatObject(map[i].first, std::stof(map[i].second)));
                    }
                } else if (map[i].second[0] == '[' && map[i].second[map[i].second.size() - 1] == ']') {
                    if (sections.size() != 0) {
                        sections.back()->SetArray(map[i].first);
                    } else {
                        parser.param.push_back(new ArrayObject(map[i].first));
                    }
                    std::vector<std::string> tmp_array = SeparationArray(map[i].second.substr(1, map[i].second.size() - 2), ',');
                    for (int j = 0; j < tmp_array.size(); ++j) {
                        tmp_array[j] = DeleteSpace(tmp_array[j]);
                    }
                    ParseType(parser.Get(map[i].first).SetArray(), tmp_array);

                } else {
                    if (sections.size() != 0) {
                        sections.back()->SetInt(map[i].first, std::stoi(map[i].second));
                    } else {
                        parser.param.push_back(new IntObject(map[i].first, std::stoi(map[i].second)));
                    }
                }
            }
        }
        return parser;

    }
}