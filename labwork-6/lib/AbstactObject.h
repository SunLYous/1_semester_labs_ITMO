#ifndef LABWORK_6_SUNLYOUS_LIB_ABSTACTOBJECT_H_
#define LABWORK_6_SUNLYOUS_LIB_ABSTACTOBJECT_H_

#include <iostream>
#include <vector>
#include <string>
namespace omfl {
    class AbstractObject {
    public:
        std::string key_ = "";
        AbstractObject() = default;
        virtual ~AbstractObject() = default;
        std::string type;
        bool IsInt();
        bool IsFloat();
        bool IsString();
        bool IsBool();
        bool IsArray();
        virtual int AsInt() { return 0; };
        virtual float AsFloat() { return 0; };
        virtual std::string AsString() { return ""; };
        virtual bool AsBool() { return false; };
        virtual AbstractObject& operator[](int index) { return *this; };
        virtual int AsIntOrDefault(int def) { return def; };
        virtual float AsFloatOrDefault(float def) { return def; };
        virtual std::string AsStringOrDefault(std::string def) { return def; };
        virtual bool AsBoolOrDefault(bool def) { return def; };
        virtual AbstractObject& AsArray() { return *this; };
        [[nodiscard]] AbstractObject& Get(std::string key);
        virtual void SetString(std::string key, std::string value) {};
        virtual void SetInt(std::string key, int value) {};
        virtual void SetFloat(std::string key, float value) {};
        virtual void SetBool(std::string key, bool value) {};
        virtual void SetArray(std::string key) {};
        virtual std::vector<AbstractObject*>* SetArray() {return nullptr;};
    };

    class IntObject : public AbstractObject {
    private:
        int value_;
    public:
        IntObject(std::string key, int value) {
            key_ = key;
            value_ = value;
            type = "int";
        }
        int AsInt() override;
        int AsIntOrDefault(int def) override;
    };

    class BoolObject : public AbstractObject {
    private:
        bool value_;
    public:
        BoolObject(std::string key, bool value) {
            key_ = key;
            value_ = value;
            type = "bool";
        };

        bool AsBool() override;
        bool AsBoolOrDefault(bool def) override;

    };

    class FloatObject : public AbstractObject {
    private:
        float value_;
    public:
        FloatObject(std::string key, float value) {
            key_ = key;
            value_ = value;
            type = "float";
        };
        float AsFloat() override;
        float AsFloatOrDefault(float def) override;
    };

    class StringObject : public AbstractObject {
    private:
        std::string value_;
    public:
        StringObject(std::string key, std::string value) {
            value_ = value;
            key_ = key;
            type = "string";
        };
        std::string AsString() override;
        std::string AsStringOrDefault(std::string def) override;
    };

    class ArrayObject : public AbstractObject {
    public:
        std::vector<AbstractObject*> value_;
        std::vector<AbstractObject*>* SetArray(){
            return &value_;
        };
        ArrayObject() { type = "none"; };
        ArrayObject(std::string key) {
            key_ = key;
            type = "array";
        };
        ArrayObject(std::string key, std::vector<AbstractObject*> value) {
            key_ = key;
            value_ = value;
            type = "array";
        };
        AbstractObject& operator[](int index) override;
    };
    class SectionObject : public AbstractObject {
    private:
        std::vector<AbstractObject*> value_;
    public:
        AbstractObject& Get(std::string key) const;

        void SetInt(std::string key, int value) {
            value_.push_back(new IntObject(key, value));
        }

        void SetString(std::string key, std::string value) {
            value_.push_back(new StringObject(key, value));
        }

        void SetBool(std::string key, bool value) {
            value_.push_back(new BoolObject(key, value));
        }

        void SetFloat(std::string key, float value) {
            value_.push_back(new FloatObject(key, value));
        }
        void SetArray(std::string key) {
            value_.push_back(new ArrayObject(key));
        }
        void SetSection(std::string key) {
            value_.push_back(new SectionObject(key));

        }
        SectionObject() { type = "section"; };
        SectionObject(std::string key) {
            key_ = key;
            type = "section";
        };
        SectionObject( std::string key, std::vector<AbstractObject*> value) {
            key_ = key;
            value_ = value;
            type = "section";
        };
    };
}
#endif //LABWORK_6_SUNLYOUS_LIB_ABSTACTOBJECT_H_
