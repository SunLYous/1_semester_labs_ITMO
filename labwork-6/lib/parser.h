#pragma once

#include "AbstactObject.h"

#include <filesystem>
#include <istream>
#include <string>
#include <fstream>

namespace omfl {

    class Parser {

    public:
        bool valid_ = true;
        bool valid() const;
        void Isvalid(std::vector<std::pair<std::string, std::string>> param);
        std::vector<AbstractObject*> param;
        Parser() = default;
        ~Parser() = default;
        [[nodiscard]] AbstractObject& Get(const std::string& key) const;

    };

    std::vector<std::string> Separation(const std::string& str, char symbol);
    std::vector<std::string> SeparationArray(const std::string& str, char symbol);

//    Parser parse(const std::filesystem::path& path);
    Parser parse(const std::string& str);
    std::string DeleteSpaces(std::string& str);
    std::string DeleteSpace(std::string& str);
    void ParseType(std::vector<AbstractObject*>* arguments, std::vector<std::string>& value);
}// namespace