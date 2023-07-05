#pragma once

#include "ArgumentSystem.h"

#include<string>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <cstdlib>

namespace ArgumentParser {

    class ArgParser {
    private:
        std::string name_parse_;
        ArgumentSystem<std::string> help_;

        bool help = false;

        std::vector<ArgumentSystem<std::string>> argument_for_string_;
        std::vector<ArgumentSystem<bool>> argument_for_bool_;
        std::vector<ArgumentSystem<int>> argument_for_int_;
        ArgumentSystem<std::string> argument_for_help_;

    public:

        ArgumentSystem<std::string>& AddStringArgument(std::string name, std::string description = "");
        ArgumentSystem<std::string>& AddStringArgument(char mini_name, std::string name, std::string description = "");
        ArgumentSystem<int>& AddIntArgument(std::string name, std::string description = "");
        ArgumentSystem<int>& AddIntArgument(char mini_name, std::string name, std::string description = "");
        ArgumentSystem<bool>& AddFlag(char mini_name, std::string name, std::string description = "");
        ArgumentSystem<bool>& AddFlag(std::string name, std::string description = "");
        std::string HelpDescription();
        ArgumentSystem<std::string>& AddHelp(char mini_name, std::string name, std::string description = "");
        bool Parse(const std::vector<std::string>& arguments);
        bool Help();
        bool Parse(int argc, char** argv);
        std::string GetStringValue(std::string param);
        int GetIntValue(std::string param, int index);
        int GetIntValue(std::string param);
        int GetFlag(std::string param);
        ArgParser(std::string name_parser);
    };

} // namespace ArgumentParser
