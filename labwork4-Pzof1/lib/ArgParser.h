#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#include <unordered_map>
#include <cstring>
#include <sstream>
#pragma once

namespace ArgumentParser {

struct ArgumentParams{
  std::string long_name_;
  char short_name_;
  bool has_short_name_ = false;
  std::string description_;

  uint32_t min_count_ = 1;
  bool is_multi_value_ = false;
  bool is_positional = false;
  bool has_default_value_ = false;
  bool is_store_value_ = false;

  bool parsed = false;
};

class Argument {
 public:
  Argument() = default;
  virtual ~Argument() = default;

  ArgumentParams& GetParams();
  virtual std::string GetDefaultValue() const = 0;
  virtual std::string GetType() const = 0;
  virtual uint32_t GetStoreSize() const = 0;

  virtual void AddValue(const std::string& value) = 0;

 protected:
  ArgumentParams params_;
};

class IntArgument : public Argument {
 public:
  IntArgument(const std::string& long_name, const std::string& description = "");
  IntArgument(char short_name, const std::string& long_name, const std::string& description = "");

  std::string GetDefaultValue() const;
  int GetIntValue(uint32_t index = 0) const;
  std::string GetType() const;
  uint32_t GetStoreSize() const;

  IntArgument& Default(int default_value);
  IntArgument& MultiValue(uint32_t min_count = 1);
  IntArgument& Positional();
  IntArgument& StoreValue(int& store);
  IntArgument& StoreValues(std::vector<int>& store);

  void AddValue(const std::string& value) override;
 private:
  int default_value_;
  int* value_storage_;
  std::vector<int>* values_storage_;
};

class StringArgument : public Argument {
 public:
  StringArgument(const std::string& long_name, const std::string& description = "");
  StringArgument(char short_name, const std::string& long_name, const std::string& description = "");

  std::string GetDefaultValue() const;
  std::string GetStringValue(uint32_t index = 0) const;
  std::string GetType() const;
  uint32_t GetStoreSize() const;

  StringArgument& Default(const std::string& default_value);
  StringArgument& MultiValue(uint32_t min_count = 1);
  StringArgument& Positional();
  StringArgument& StoreValue(std::string& store);
  StringArgument& StoreValues(std::vector<std::string>& store);

  void AddValue(const std::string& value) override;
 private:
  std::string default_value_;
  std::string* value_storage_;
  std::vector<std::string>* values_storage_;
};

class BoolArgument : public Argument {
 public:
  BoolArgument(const std::string& long_name, const std::string& description = "");
  BoolArgument(char short_name, const std::string& long_name, const std::string& description = "");

  std::string GetDefaultValue() const;
  bool GetBoolValue(uint32_t index = 0) const;
  std::string GetType() const;
  uint32_t GetStoreSize() const;

  BoolArgument& Default(bool default_value);
  BoolArgument& MultiValue(uint32_t min_count = 1);
  BoolArgument& Positional();
  BoolArgument& StoreValue(bool& store);
  BoolArgument& StoreValues(std::vector<bool>& store);

  void AddValue(const std::string& value) override;
 private:
  bool default_value_;
  bool* value_storage_;
  std::vector<bool>* values_storage_;
};

class ArgParser {
 public:
  ArgParser(const std::string& parser_name);

  StringArgument& AddStringArgument(char short_name, const std::string& long_name, const std::string& description = "");
  StringArgument& AddStringArgument(const std::string& long_name, const std::string& description = "");
  IntArgument& AddIntArgument(char short_name, const std::string& long_name, const std::string& description = "");
  IntArgument& AddIntArgument(const std::string& long_name, const std::string& description = "");
  BoolArgument& AddFlag(char short_name, const std::string& long_name, const std::string& description = "");
  BoolArgument& AddFlag(const std::string& long_name, const std::string& description = "");

  std::string GetStringValue(const std::string& name, uint32_t index = 0)  const;
  int GetIntValue(const std::string& name, uint32_t index = 0) const;
  bool GetFlag(const std::string& name, uint32_t index = 0) const;

  void SetIndexPositional();
  Argument* GetLongArgument(const std::string& long_name);
  Argument* GetShortArgument(char short_name);
  bool CheckMinCountAndDefaultValue();
  void GetPositional(const std::vector<std::string>& args);

  void AddHelp(char short_name = 'h', const std::string& long_name = "help", const std::string& description = "No Help");
  void GetHelpDescription();
  std::string HelpDescription();
  bool Help() const;

  bool ParseShortArgument(const std::string& str_to_parse);
  bool ParseLongArgument(const std::string& str_to_parse);
  bool Parse(std::vector<std::string> args);
  bool Parse(int argc, char* argv[]);
 private:
  std::string help_description_ = "";
  std::string help_long_name_ = "help";
  char help_short_name_ = 'h';
  bool help_parsed = false;

  uint32_t parsed_count = 0;
  uint32_t index_positional = -1;

  std::string parser_name_;
  std::vector<Argument*> arguments_;
  std::unordered_map<std::string, size_t> arguments_map_long;
  std::unordered_map<char, size_t> arguments_map_short;
};
}