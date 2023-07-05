#ifndef LABWORK5_LIB_ARGUMENTSYSTEM_H_
#define LABWORK5_LIB_ARGUMENTSYSTEM_H_

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

template<typename T>
class ArgumentSystem {
private:
    T value_;
    T default_value_;
    char mini_name_;
    std::string name_;
    std::string description_;

    std::vector<T> values;

    bool flag_store_value_ = false;
    bool flag_store_values_ = false;
    bool default_flag_ = false;
    bool multi_flag_ = false;
    bool positional_ = false;
    bool HasValue_ = false;
    int size_ = 0;

public:
    T* store_value_ = nullptr;
    std::vector<T>* store_values_ = nullptr;

    ArgumentSystem& Positional() {
        positional_ = true;
        return *this;
    }

    void SetValues(T value) {
        values.push_back(value);
    };

    void SetValue(T value) {
        HasValue_ = true;
        value_ = value;
    }

    ArgumentSystem& Default(T value) {
        default_value_ = value;
        value_ = default_value_;
        HasValue_ = true;
        default_flag_ = true;
        return *this;
    };

    ArgumentSystem& StoreValue(T& value) {
        store_value_ = &value;
        flag_store_value_ = true;
        return *this;
    };

    ArgumentSystem& StoreValues(std::vector<T>& value) {
        store_values_ = &value;
        flag_store_values_ = true;
        return *this;
    };

    ArgumentSystem& MultiValue(int min) {
        size_ = min;
        multi_flag_ = true;
        return *this;
    };

    ArgumentSystem& MultiValue() {
        size_ = 0;
        multi_flag_ = true;
        return *this;
    };

    bool GetFlagStoreValues() {
        return flag_store_values_;
    };

    bool GetFlagStoreValue() {
        return flag_store_value_;
    };

    int GetSize() {
        return size_;
    };

    int GetSizeStoreValues() {
        return store_values_->size();
    };

    bool GetHasValue() {
        return HasValue_;
    };

    bool GetDefaultFlag() {
        return default_flag_;
    };

    T GetDefaultValue() {
        return default_value_;
    };

    std::string GetNames() {
        return name_;
    };
    char GetMiniName() {
        return mini_name_;
    };

    T GetValue() {
        return value_;
    }

    bool GetPositional() {
        return positional_;
    }

    bool GetMultiFlag() {
        return multi_flag_;
    };

    T GetValues(int i) {
        return values[i];
    }

    ArgumentSystem(char mini_name, std::string name, std::string description) {
        mini_name_ = mini_name;
        name_ = name;
        description_ = description;
    };

    ArgumentSystem() {
    };
};
#endif //LABWORK5_LIB_ARGUMENTSYSTEM_H_
