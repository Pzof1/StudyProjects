#ifndef LABWORK3_PZOF1_LIBRARIES_PARSER_PARSER_H
#define LABWORK3_PZOF1_LIBRARIES_PARSER_PARSER_H

#include <cinttypes>
#include <fstream>
#include <cstring>
#include <iostream>
#include <filesystem>

struct ProgramParameters {
  char* input_path;
  char* output_path = "";
  uint64_t max_iterations;
  bool max_iterations_flag = false;
  uint64_t freq;
  bool freq_flag = false;
};

static const char* st_input = "--input=";
static const char* st_output = "--output=";
static const char* st_freq = "--freq=";
static const char* st_max_iter = "--max=";

void InputError();

void ParseArguments(char *argv[], int argc, ProgramParameters& Arguments);

#endif