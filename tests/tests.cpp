/*
 *
 * This file is part of SimpleCmdParser
 * Copyright (c) https://github.com/tascvh/SimpleCmdParser
 *
 */
#define CATCH_CONFIG_MAIN
#include "../simple_cmd_parser.hpp" // Include the source file or the header file
#include <catch2/catch.hpp>

TEST_CASE("verify override default values", "[sanity]") {
  const char *argv[] = {
      "program_name", "-d", "2.5", "-f", "1.5",
      "-b",           "-i", "8",   "-s", "string_param",
  };

  int argc = sizeof(argv) / sizeof(char *);

  std::string s = "default_string";
  double d = 5.0;
  float f = 3.0;
  bool b = false;
  int i = 5;
  std::optional<int> oi;

  SimpleParser sp(argc, argv);

  sp.read(d, "-d");
  sp.read(i, "-i");
  sp.read(f, "-f");
  sp.read(b, "-b");
  sp.read(s, "-s");
  sp.read(oi, "-i");

  REQUIRE(s == "string_param");
  REQUIRE(d == 2.5);
  REQUIRE(f == 1.5);
  REQUIRE(b == true);
  REQUIRE(i == 8);
  REQUIRE(*oi == 8);
}

TEST_CASE("verify no params supplied use default values", "[sanity]") {
  const char *argv[] = {"program_name"};
  int argc = sizeof(argv) / sizeof(char *);

  std::string s = "default_string";
  double d = 5.0;
  float f = 3.0;
  bool b = false;
  int i = 5;
  std::optional<int> oi;

  SimpleParser sp(argc, argv);

  sp.read(d, "-d");
  sp.read(i, "-i");
  sp.read(f, "-f");
  sp.read(b, "-b");
  sp.read(s, "-s");
  sp.read(oi, "-i");

  REQUIRE(s == "default_string");
  REQUIRE(d == 5.0);
  REQUIRE(f == 3.0);
  REQUIRE(b == false);
  REQUIRE(i == 5);
  REQUIRE(!oi);
}

TEST_CASE("fail parameter type not matching", "[sanity]") {
  const char *argv[] = {"program_name", "-i", "abc"};
  int argc = sizeof(argv) / sizeof(char *);

  try {
    int i = 5;
    SimpleParser sp(argc, argv);
    sp.read(i, "-i");
    REQUIRE(false);
  } catch (std::invalid_argument &e) {
    REQUIRE(true);
  } catch (...) {
    REQUIRE(false);
  }
}

TEST_CASE("fail below valid range", "[sanity]") {
  const char *argv[] = {"program_name", "-i", "-10"};
  int argc = sizeof(argv) / sizeof(char *);

  try {
    int i = 5;
    SimpleParser sp(argc, argv);
    sp.read(i, "-i", "description", {-5, 5});
    REQUIRE(false);
  } catch (std::invalid_argument &e) {
    REQUIRE(true);
  } catch (...) {
    REQUIRE(false);
  }
}

TEST_CASE("fail above valid range", "[sanity]") {

  const char *argv[] = {"program_name", "-i", "2.1"};
  int argc = sizeof(argv) / sizeof(char *);

  try {
    double d = 1.0;
    SimpleParser sp(argc, argv);
    sp.read(d, "-i", "description", {-2, 2});
    REQUIRE(false);
  } catch (std::invalid_argument &e) {
    REQUIRE(true);
  } catch (...) {
    REQUIRE(false);
  }
}
