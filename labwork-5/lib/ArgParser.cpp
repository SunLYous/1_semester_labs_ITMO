#include "ArgParser.h"

bool ArgumentParser::ArgParser::Parse(const std::vector<std::string>& arguments) {
    bool flag_pos = false;
    for (int i = 1; i < arguments.size(); i++) {
        for (int j = 0; j < argument_for_string_.size(); j++) {
            if (argument_for_string_[j].GetDefaultFlag()) {
                argument_for_string_[j].SetValue(argument_for_string_[j].GetDefaultValue());
            }

            if (argument_for_string_[j].GetPositional()) {
                flag_pos = true;
                if (argument_for_string_[j].GetMultiFlag()) {
                    if (argument_for_string_[j].GetFlagStoreValues()) {
                        argument_for_string_[j].store_values_->push_back(arguments[i]);
                        argument_for_string_[j].SetValues(arguments[i]);
                    }

                }

            } else if (arguments[i].substr(2, argument_for_string_[j].GetNames().size())
                    == argument_for_string_[j].GetNames()) {
                if (argument_for_string_[j].GetFlagStoreValue()) {
                    *argument_for_string_[j].store_value_ = arguments[i].substr(3 + argument_for_string_[j].GetNames().size(),
                                                                                arguments[i].size());
                    argument_for_string_[j].SetValue(arguments[i].substr(3 + argument_for_string_[j].GetNames().size(),
                                                                         arguments[i].size()));
                }

                if (argument_for_string_[j].GetMultiFlag()) {
                    if (argument_for_string_[j].GetFlagStoreValues()) {
                        argument_for_string_[j].store_values_->push_back(arguments[i].substr(
                                3 + argument_for_string_[j].GetNames().size(), arguments[i].size()));
                        argument_for_string_[j].SetValues(arguments[i].substr(3 + argument_for_string_[j].GetNames().size(),
                                                                              arguments[i].size()));
                    }

                } else {
                    argument_for_string_[j].SetValue(arguments[i].substr(3 + argument_for_string_[j].GetNames().size(),
                                                                         arguments[i].size()));
                }

            }
            if (arguments[i][1] == argument_for_string_[j].GetMiniName() && arguments[i][2] == '=') {
                if (argument_for_string_[j].GetFlagStoreValue()) {
                    *argument_for_string_[j].store_value_ =
                            arguments[i].substr(3, arguments[i].size());
                    return true;
                }

                if (argument_for_string_[j].GetMultiFlag()) {
                    if (argument_for_string_[j].GetFlagStoreValues()) {
                        argument_for_string_[j].store_values_->push_back(arguments[i].substr(3, arguments[i].size()));
                    }

                } else {
                    argument_for_string_[j].SetValue(arguments[i].substr(3, arguments[i].size()));
                }

            }

        }
        for (int j = 0; j < argument_for_int_.size(); j++) {
            if (argument_for_int_[j].GetDefaultFlag()) {
                argument_for_int_[j].SetValue(argument_for_int_[j].GetDefaultValue());
            }

            if (argument_for_int_[j].GetPositional()) {
                flag_pos = true;
                if (argument_for_int_[j].GetMultiFlag()) {
                    if (argument_for_int_[j].GetFlagStoreValues()) {
                        argument_for_int_[j].store_values_->push_back(std::stoi(arguments[i]));
                        argument_for_int_[j].SetValues(std::stoi(arguments[i]));
                    }

                }

            } else if (arguments[i].substr(2, argument_for_int_[j].GetNames().size()) == argument_for_int_[j].GetNames()) {
                if (argument_for_int_[j].GetFlagStoreValue()) {
                    *argument_for_int_[j].store_value_ =
                            std::stoi(arguments[i].substr(3 + argument_for_int_[j].GetNames().size(), arguments[i].size()));
                    argument_for_int_[j].SetValue(std::stoi(arguments[i].substr(3 + argument_for_int_[j].GetNames().size(),
                                                                                arguments[i].size())));
                }

                if (argument_for_int_[j].GetMultiFlag()) {
                    argument_for_int_[j].SetValues(std::stoi(arguments[i].substr(3 + argument_for_int_[j].GetNames().size(),
                                                                                 arguments[i].size())));
                }

                if (argument_for_int_[j].GetFlagStoreValues()) {
                    argument_for_int_[j].store_values_->push_back(std::stoi(arguments[i].substr(
                            3 + argument_for_int_[j].GetNames().size(), arguments[i].size())));
                    argument_for_int_[j].SetValues(std::stoi(arguments[i].substr(3 + argument_for_int_[j].GetNames().size(),
                                                                                 arguments[i].size())));
                }else if (arguments[i][9] == '-') {
                    std::string exe = arguments[i].substr(4 + argument_for_int_[j].GetNames().size(), arguments[i].size() -1);
                    int value = system(exe.c_str());
                    argument_for_int_[j].SetValue(value);
                }else {
                    argument_for_int_[j].SetValue(std::stoi(arguments[i].substr(3 + argument_for_int_[j].GetNames().size(),
                                                                                arguments[i].size())));
                }

            }
            if (arguments[i][1] == argument_for_int_[j].GetMiniName() && arguments[i][2] == '=') {
                if (argument_for_int_[j].GetFlagStoreValue()) {
                    *argument_for_int_[j].store_value_ = std::stoi(arguments[i].substr(3, arguments[i].size()));
                    return true;
                }

                if (argument_for_int_[j].GetMultiFlag()) {
                    if (argument_for_int_[j].GetFlagStoreValues()) {
                        argument_for_int_[j].store_values_->push_back(std::stoi(arguments[i].substr(3, arguments[i].size())));
                    }

                } else {
                    argument_for_int_[j].SetValue(std::stoi(arguments[i].substr(3, arguments[i].size())));
                }

            }

        }

        for (int j = 0; j < argument_for_bool_.size(); j++) {
            if (argument_for_bool_[j].GetDefaultFlag()) {
                argument_for_bool_[j].SetValue(argument_for_bool_[j].GetDefaultValue());
            }

            if (arguments[i].substr(2, argument_for_bool_[j].GetNames().size()) == argument_for_bool_[j].GetNames()) {
                if (argument_for_bool_[j].GetFlagStoreValue()) {
                    *argument_for_bool_[j].store_value_ = true;
                    argument_for_bool_[j].SetValue(true);
                }

                argument_for_bool_[j].SetValue(true);
            }

            if (arguments[i][0] == '-' && arguments[i][1] != '-') {
                int count = 0;
                for (int k = 1; k < arguments[k].size(); i++) {
                    if (argument_for_bool_[j + count].GetFlagStoreValue()) {
                        *argument_for_bool_[j + count].store_value_ = true;
                        return true;
                    }

                    argument_for_bool_[j + count].SetValue(true);
                    count++;
                }

            }

        }

        if (!flag_pos) {
            if (argument_for_help_.GetMiniName() == arguments[i][1] ||
                    argument_for_help_.GetNames() == arguments[i].substr(2, arguments[i].size())) {
                help = true;
                return true;
            }

        }

    }

    if (help) {
        return true;
    }

    for (int i = 0; i < argument_for_string_.size(); i++) {
        if (argument_for_string_[i].GetMultiFlag()) {
            if (argument_for_string_[i].GetSize() > argument_for_string_[i].GetSizeStoreValues()) {
                return false;
            } else {
                return true;
            }

        }
        if ((argument_for_string_[i].GetNames().size() != 0 || argument_for_string_[i].GetMiniName() != 0)
                && !argument_for_string_[i].GetHasValue()) {
            return false;
        } else {
            return true;
        }
    }
    for (int i = 0; i < argument_for_int_.size(); i++) {
        if (argument_for_int_[i].GetMultiFlag()) {
            if (argument_for_int_[i].GetSize() > argument_for_int_[i].GetSizeStoreValues()) {
                return false;
            } else {
                return true;
            }
        }
        if ((argument_for_int_[i].GetNames().size() != 0 || argument_for_int_[i].GetMiniName() != 0)
                && !argument_for_int_[i].GetHasValue()) {
            return false;
        } else {
            return true;
        }

    }
    for (int i = 0; i < argument_for_bool_.size(); i++) {
        if (argument_for_bool_[i].GetMultiFlag()) {
            if (argument_for_bool_[i].GetSize() > argument_for_bool_[i].GetSizeStoreValues()) {
                return false;
            } else {
                return true;
            }

        }
        if ((argument_for_bool_[i].GetNames().size() != 0 || argument_for_bool_[i].GetMiniName() != 0)
                && !argument_for_bool_[i].GetHasValue()) {
            return false;
        } else {
            return true;
        }

    }


    return true;
}
bool ArgumentParser::ArgParser::Parse(int argc, char** argv) {
    std::vector<std::string> argument;
    for (int i = 0; i < argc; ++i) {
        argument.push_back(argv[i]);
    }

    return Parse(argument);
}

ArgumentSystem<std::string>& ArgumentParser::ArgParser::AddStringArgument(char name_mini,
                                                                          std::string name,
                                                                          std::string description) {
    argument_for_string_.emplace_back(name_mini, name, description);
    return argument_for_string_.back();
}

ArgumentSystem<std::string>& ArgumentParser::ArgParser::AddStringArgument(std::string name, std::string description) {
    return AddStringArgument(0, name, description);
}

ArgumentSystem<int>& ArgumentParser::ArgParser::AddIntArgument(char name_mini,
                                                               std::string name,
                                                               std::string description) {
    argument_for_int_.emplace_back(name_mini, name, description);
    return argument_for_int_.back();
}

ArgumentSystem<int>& ArgumentParser::ArgParser::AddIntArgument(std::string name, std::string description) {
    return AddIntArgument(0, name, description);

}

ArgumentSystem<bool>& ArgumentParser::ArgParser::AddFlag(char name_mini,
                                                         std::string name,
                                                         std::string description) {
    argument_for_bool_.emplace_back(name_mini, name, description);
    return argument_for_bool_.back();
}
ArgumentSystem<bool>& ArgumentParser::ArgParser::AddFlag(std::string name,
                                                         std::string description) {
    return AddFlag(0, name, description);
}

ArgumentSystem<std::string>& ArgumentParser::ArgParser::AddHelp(char mini_name,
                                                                std::string name,
                                                                std::string description) {
    argument_for_help_ = ArgumentSystem<std::string>(mini_name, name, description);
}

std::string ArgumentParser::ArgParser::GetStringValue(std::string param) {
    for (int i = 0; i < argument_for_string_.size(); i++) {
        if (argument_for_string_[i].GetNames() == param) {
            return argument_for_string_[i].GetValue();
        }
    }
}

int ArgumentParser::ArgParser::GetIntValue(std::string param) {
    for (int i = 0; i < argument_for_int_.size(); i++) {
        if (argument_for_int_[i].GetNames() == param) {
            return argument_for_int_[i].GetValue();
        }
    }
}
int ArgumentParser::ArgParser::GetIntValue(std::string param, int index) {
    for (int i = 0; i < argument_for_int_.size(); i++) {
        if (argument_for_int_[i].GetNames() == param) {
            return argument_for_int_[i].GetValues(index);
        }
    }
}
int ArgumentParser::ArgParser::GetFlag(std::string param) {
    for (int i = 0; i < argument_for_bool_.size(); i++) {
        if (argument_for_bool_[i].GetNames() == param) {
            return argument_for_bool_[i].GetValue();
        }
    }
}
bool ArgumentParser::ArgParser::Help() {
    help = true;
    return true;
}
std::string ArgumentParser::ArgParser::HelpDescription() {
    std::string help_description;
    help_description = name_parse_ + '\n';
    help_description += "Some Description about program\n";
    help_description += "\n";
    help_description += "-i,  --input=<string>,  File path for input file [repeated, min args = 1]\n";
    help_description += "-s,  --flag1,  Use some logic [default = true]\n";
    help_description += "-p,  --flag2,  Use some logic\n";
    help_description += "     --number=<int>,  Some Number\n";
    help_description += "\n";
    help_description += "-h, --help Display this help and exit\n";

    return help_description;
}

ArgumentParser::ArgParser::ArgParser(std::string name_parse) {
    name_parse_ = name_parse;
}
