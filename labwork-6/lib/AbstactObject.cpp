#include "AbstactObject.h"
namespace omfl {
    bool AbstractObject::IsInt() {
        if (type == "int") {
            return true;
        }

        return false;
    }
    bool AbstractObject::IsFloat() {
        if (type == "float") {
            return true;
        }

        return false;
    }
    bool AbstractObject::IsString() {
        if (type == "string") {
            return true;
        }

        return false;
    }
    bool AbstractObject::IsBool() {
        if (type == "bool") {
            return true;
        }

        return false;
    }
    bool AbstractObject::IsArray() {
        if (type == "array") {
            return true;
        }

        return false;
    }
    AbstractObject& AbstractObject::Get(std::string key) {
        SectionObject* tmp = dynamic_cast<SectionObject*>(this);
        return tmp->Get(key);
    }

    std::string StringObject::AsString() { return value_; }
    std::string StringObject::AsStringOrDefault(std::string def) {
        if (IsString()) {
            return value_;
        }
        return AbstractObject::AsStringOrDefault(def);
    };
    int IntObject::AsInt() { return value_; }
    int IntObject::AsIntOrDefault(int def) {
        if (IsInt()) {
            return AsInt();
        }
        return AbstractObject::AsIntOrDefault(def);
    };
    float FloatObject::AsFloat() { return value_; }
    float FloatObject::AsFloatOrDefault(float def) {
        if (IsFloat()) {
            return AsFloat();
        }
        return AbstractObject::AsFloatOrDefault(def);
    };
    bool BoolObject::AsBool() { return value_; }
    bool BoolObject::AsBoolOrDefault(bool def) {
        if (IsBool()) {
            return AsBool();
        }
        return AbstractObject::AsBoolOrDefault(def);
    };

    AbstractObject& ArrayObject::operator[](int index) {
        if (index < 0 || index >= value_.size()) {
            AbstractObject* tmp = new ArrayObject;
            return *tmp;
        }
        return *value_[index];
    }

    AbstractObject& SectionObject::Get(std::string key) const {
        std::string name_section;
        std::string name_section_next;
        if (key.find(".") != std::string::npos) {
            name_section = key.substr(0, key.find("."));
            name_section_next = key.substr(key.find(".") + 1, key.size());
            for (int i = 0; i < value_.size(); i++) {
                if (value_[i]->key_ == name_section) {
                    return value_[i]->Get(name_section_next);
                }
            }
        } else {
            name_section_next = key_;
            for (int i = 0; i < value_.size(); i++) {
                if (value_[i]->key_ == key) {
                    return *value_[i];
                }
            }
        }
    }

}