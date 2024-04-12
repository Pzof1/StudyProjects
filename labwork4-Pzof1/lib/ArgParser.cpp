
#include "ArgParser.h"
using namespace ArgumentParser;

//Argument
ArgumentParams& Argument::GetParams() {
  return params_;
}

//IntArgument
IntArgument::IntArgument(char short_name, const std::string& long_name, const std::string& description)
    : Argument() {
  params_.short_name_ = short_name;
  params_.long_name_ = long_name;
  params_.description_ = description;
  value_storage_ = new int[1];
}

IntArgument::IntArgument(const std::string& long_name, const std::string& description)
    : Argument() {
  params_.long_name_ = long_name;
  params_.description_ = description;
  value_storage_ = new int[1];
}

std::string IntArgument::GetDefaultValue() const {
  std::stringstream ss;
  ss << default_value_;
  return ss.str();
}

IntArgument& IntArgument::Default(int default_value) {
  default_value_ = default_value;
  params_.has_default_value_ = true;
  return *this;
}

int IntArgument::GetIntValue(uint32_t index) const {
  if (!params_.parsed && params_.has_default_value_) {
    return default_value_;
  }
  if (params_.is_multi_value_) {
    if (index < values_storage_->size()) {
      return (*values_storage_)[index];
    } else {
      return 0;
    }
  } else {
    return *value_storage_;
  }
}

IntArgument& IntArgument::MultiValue(uint32_t min_count) {
  params_.is_multi_value_ = true;
  params_.min_count_ = min_count;
  return *this;
}

IntArgument& IntArgument::Positional() {
  params_.is_positional = true;
  return *this;
}

IntArgument& IntArgument::StoreValue(int& store) {
  params_.is_store_value_ = true;
  value_storage_ = &store;
  return *this;
}

IntArgument& IntArgument::StoreValues(std::vector<int>& store) {
  params_.is_store_value_ = true;
  values_storage_ = &store;
  return *this;
}

std::string IntArgument::GetType() const {
  return "int";
}

void IntArgument::AddValue(const std::string& value) {
  if (params_.is_multi_value_) {
    values_storage_->push_back(std::stoi(value));
  } else {
    *value_storage_ = std::stoi(value);
  }
  params_.parsed = true;
}

uint32_t IntArgument::GetStoreSize() const {
  if (params_.is_multi_value_) {
    return values_storage_->size();
  } else {
    return 1;
  }
}
//StringArgument
StringArgument::StringArgument(char short_name, const std::string& long_name, const std::string& description)
    : Argument() {
  params_.short_name_ = short_name;
  params_.long_name_ = long_name;
  params_.description_ = description;
  value_storage_ = new std::string[1];
}

StringArgument::StringArgument(const std::string& long_name, const std::string& description)
    : Argument() {
  params_.long_name_ = long_name;
  params_.description_ = description;
  value_storage_ = new std::string[1];
}

std::string StringArgument::GetDefaultValue() const {
  return default_value_;
}

std::string StringArgument::GetStringValue(uint32_t index) const {
  if (!params_.parsed && params_.has_default_value_) {
    return default_value_;
  }
  if (params_.is_multi_value_) {
    if (index < values_storage_->size()) {
      return (*values_storage_)[index];
    } else {
      return "";
    }
  } else {
    return *value_storage_;
  }
}

StringArgument& StringArgument::Default(const std::string& default_value) {
  params_.has_default_value_ = true;
  default_value_ = default_value;
  return *this;
}

std::string StringArgument::GetType() const {
  return "string";
}

StringArgument& StringArgument::MultiValue(uint32_t min_count) {
  params_.is_multi_value_ = true;
  params_.min_count_ = min_count;
  return *this;
}

StringArgument& StringArgument::Positional() {
  params_.is_positional = true;
  return *this;
}

StringArgument& StringArgument::StoreValue(std::string& store) {
  params_.is_store_value_ = true;
  value_storage_ = &store;
  return *this;
}

StringArgument& StringArgument::StoreValues(std::vector<std::string>& store) {
  params_.is_store_value_ = true;
  values_storage_ = &store;
  return *this;
}

void StringArgument::AddValue(const std::string& value) {
  if (params_.is_multi_value_) {
    values_storage_->push_back(value);
  } else {
    *value_storage_ = value;
  }
  params_.parsed = true;
}

uint32_t StringArgument::GetStoreSize() const {
  if (params_.is_multi_value_) {
    return values_storage_->size();
  } else {
    return 1;
  }
}

//BoolArguments
BoolArgument::BoolArgument(char short_name, const std::string& long_name, const std::string& description)
    : Argument() {
  params_.short_name_ = short_name;
  params_.long_name_ = long_name;
  params_.description_ = description;
  value_storage_ = new bool[1];
}

BoolArgument::BoolArgument(const std::string& long_name, const std::string& description)
    : Argument() {
  params_.long_name_ = long_name;
  params_.description_ = description;
  value_storage_ = new bool[1];
}

std::string BoolArgument::GetDefaultValue() const {
  std::stringstream ss;
  ss << default_value_;
  return ss.str();
}

bool BoolArgument::GetBoolValue(uint32_t index) const {
  if (!params_.parsed && params_.has_default_value_) {
    return default_value_;
  }
  if (params_.is_multi_value_) {
    if (index < values_storage_->size()) {
      return (*values_storage_)[index];
    } else {
      return false;
    }
  } else {
    return *value_storage_;
  }
}

BoolArgument& BoolArgument::Default(bool default_value) {
  default_value_ = default_value;
  params_.has_default_value_ = true;
  return *this;
}

std::string BoolArgument::GetType() const {
  return "bool";
}

BoolArgument& BoolArgument::Positional() {
  params_.is_positional = true;
  return *this;
}

BoolArgument& BoolArgument::StoreValue(bool& store) {
  params_.is_store_value_ = true;
  value_storage_ = &store;
  return *this;
}

BoolArgument& BoolArgument::StoreValues(std::vector<bool>& store) {
  params_.is_store_value_ = true;
  values_storage_ = &store;
  return *this;
}

BoolArgument& BoolArgument::MultiValue(uint32_t min_count) {
  params_.is_multi_value_ = true;
  params_.min_count_ = min_count;
  return *this;
}

void BoolArgument::AddValue(const std::string& value) {
  if (params_.is_multi_value_) {
    values_storage_->push_back(true);
  } else {
    *value_storage_ = true;
  }
  params_.parsed = true;
}

uint32_t BoolArgument::GetStoreSize() const {
  if (params_.is_multi_value_) {
    return values_storage_->size();
  } else {
    return 1;
  }
}

//ArgParser
ArgParser::ArgParser(const std::string& parser_name) {
  parser_name_ = parser_name;
}

int ArgParser::GetIntValue(const std::string& name, uint32_t index) const {
  return dynamic_cast<IntArgument*>(arguments_[arguments_map_long.at(name)])->GetIntValue(index);
}

bool ArgParser::GetFlag(const std::string& name, uint32_t index) const {
  return dynamic_cast<BoolArgument*>(arguments_[arguments_map_long.at(name)])->GetBoolValue(index);
}

std::string ArgParser::GetStringValue(const std::string& name, uint32_t index) const {
  return dynamic_cast<StringArgument*>(arguments_[arguments_map_long.at(name)])->GetStringValue(index);
}

StringArgument& ArgParser::AddStringArgument(char short_name,
                                             const std::string& long_name,
                                             const std::string& description) {
  StringArgument* arg = new StringArgument(short_name, long_name, description);
  arg->GetParams().has_short_name_ = true;
  arguments_.push_back(arg);
  arguments_map_long[long_name] = arguments_.size() - 1;
  arguments_map_short[short_name] = arguments_.size() - 1;
  return *arg;
}

StringArgument& ArgParser::AddStringArgument(const std::string& long_name, const std::string& description) {
  StringArgument* arg = new StringArgument(long_name, description);
  arguments_.push_back(arg);
  arguments_map_long[long_name] = arguments_.size() - 1;
  return *arg;
}

IntArgument& ArgParser::AddIntArgument(char short_name, const std::string& long_name, const std::string& description) {
  IntArgument* arg = new IntArgument(short_name, long_name, description);
  arg->GetParams().has_short_name_ = true;
  arguments_.push_back(arg);
  arguments_map_long[long_name] = arguments_.size() - 1;
  arguments_map_short[short_name] = arguments_.size() - 1;
  return *arg;
}

IntArgument& ArgParser::AddIntArgument(const std::string& long_name, const std::string& description) {
  IntArgument* arg = new IntArgument(long_name, description);
  arguments_.push_back(arg);
  arguments_map_long[long_name] = arguments_.size() - 1;
  return *arg;
}

BoolArgument& ArgParser::AddFlag(char short_name, const std::string& long_name, const std::string& description) {
  BoolArgument* arg = new BoolArgument(short_name, long_name, description);
  arg->GetParams().has_short_name_ = true;
  arguments_.push_back(arg);
  arguments_map_long[long_name] = arguments_.size() - 1;
  arguments_map_short[short_name] = arguments_.size() - 1;
  return *arg;
}

BoolArgument& ArgParser::AddFlag(const std::string& long_name, const std::string& description) {
  BoolArgument* arg = new BoolArgument(long_name, description);
  arguments_.push_back(arg);
  arguments_map_long[long_name] = arguments_.size() - 1;
  return *arg;
}

void ArgParser::AddHelp(char short_name, const std::string& long_name, const std::string& description) {
  help_short_name_ = short_name;
  help_long_name_ = long_name;
  help_description_ += description + "\n";
}

std::string ArgParser::HelpDescription() {
  GetHelpDescription();
  return help_description_;
}

void ArgParser::GetHelpDescription() {

  help_description_ += parser_name_ + "\n";

  for (auto arg : arguments_) {
    std::stringstream ss;
    ArgumentParams params = arg->GetParams();

    if (params.has_short_name_) ss << "-" << params.short_name_ << ", ";

    ss << "--" << params.long_name_ << "=" << arg->GetType() << ", ";
    ss << params.description_ << "[";

    if (params.is_multi_value_) ss << "multivalue min_count = " << params.min_count_;
    if (params.is_positional) ss << " positional";
    if (params.has_default_value_) ss << " default = " << arg->GetDefaultValue();
    if (params.is_store_value_) ss << " storevalue";
    ss << "]\n";
    help_description_ += ss.str();
  }
}

bool ArgParser::Help() const {
  return help_parsed;
}

void ArgParser::SetIndexPositional() {
  for (uint32_t i = 0; i < arguments_.size(); i++) {
    if (arguments_[i]->GetParams().is_positional) {
      index_positional = i;
      break;
    }
  }
}

Argument* ArgParser::GetLongArgument(const std::string& long_name) {
  Argument* arg = arguments_[arguments_map_long.at(long_name)];
  return arg;
}

Argument* ArgParser::GetShortArgument(char short_name) {
  Argument* arg = arguments_[arguments_map_short.at(short_name)];
  return arg;
}

bool ArgParser::ParseLongArgument(const std::string& str_to_parse) {
  std::string long_name = "";
  if (str_to_parse.find("=") == std::string::npos) {
    if (str_to_parse.substr(2) == help_long_name_) {
      help_parsed = true;
      return true;
    }
    long_name = str_to_parse.substr(2);
    Argument* arg = GetLongArgument(long_name);
    if (arg->GetType() == "bool")
      arg->AddValue("true");
  }
  long_name = str_to_parse.substr(2, str_to_parse.find("=") - 2);
  Argument* arg = GetLongArgument(long_name);
  if (arg->GetType() == "bool")
    arg->AddValue("true");
  else
    arg->AddValue(str_to_parse.substr(str_to_parse.find("=") + 1));
  return true;
}

bool ArgParser::ParseShortArgument(const std::string& str_to_parse) {
  if (str_to_parse.find("=") == 2 || str_to_parse.size() == 2) {
    if (str_to_parse[1] == help_short_name_ && str_to_parse.size() == 2) {
      help_parsed = true;
      return true;
    }
    Argument* arg = GetShortArgument(str_to_parse[1]);
    arg->AddValue(str_to_parse.substr(3));
    return true;
  } else {
    for (uint32_t i = 1; i < str_to_parse.size(); i++) {
      Argument* arg = GetShortArgument(str_to_parse[i]);
      if (arg == nullptr)
        return false;
      if (arg->GetType() != "bool") {
        return false;
      }
      arg->AddValue("true");
    }
    return true;
  }
}

bool ArgParser::CheckMinCountAndDefaultValue() {
  for (auto arg : arguments_) {
    ArgumentParams params = arg->GetParams();
    if (!params.parsed && !params.has_default_value_) {
      return false;
    }
    if (params.is_multi_value_ && params.min_count_ > arg->GetStoreSize()) {
      return false;
    }

  }
  return true;
}

void ArgParser::GetPositional(const std::vector<std::string>& args) {
  if (index_positional == -1)
    return;

  Argument* arg = arguments_[index_positional];
  std::string type = arg->GetType();
  for (uint32_t i = 1; i < args.size(); i++) {
    if (!args[i].starts_with("-")) {
      if (type == "int") {
        char* pt_end;
        int value = std::strtol(args[i].c_str(), &pt_end, 10);
        if (pt_end != nullptr) {
          arg->AddValue(std::to_string(value));
          parsed_count++;
        }
      } else if (type == "string") {
        arg->AddValue(args[i]);
        parsed_count++;
      }
    }
  }
}

bool ArgParser::Parse(std::vector<std::string> args) {
  SetIndexPositional();

  for (uint32_t i = 1; i < args.size(); i++) {
    if (args[i].starts_with("--")) {
      if (!ParseLongArgument(args[i]))
        return false;
      //args.erase(args.cbegin() + i);
      parsed_count++;
    } else if (args[i].starts_with("-")) {
      if (!ParseShortArgument(args[i]))
        return false;
      //args.erase(args.cbegin() + i);
      parsed_count++;
    }
    if (help_parsed)
      return true;
  }
  GetPositional(args);

  if (!CheckMinCountAndDefaultValue())
    return false;

  return true;
}

bool ArgParser::Parse(int argc, char* argv[]) {
  std::vector<std::string> args;
  for (size_t i = 0; i < argc; i++) {
    args.push_back(argv[i]);
  }

  return Parse(args);
}

