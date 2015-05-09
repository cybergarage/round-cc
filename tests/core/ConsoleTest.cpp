/******************************************************************
 *
 * Round for C++
 *
 * Copyright (C) Satoshi Konno 2015
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <boost/test/unit_test.hpp>

#include <round/ui/Console.h>

using namespace std;
using namespace Round;

BOOST_AUTO_TEST_SUITE(ui)

BOOST_AUTO_TEST_CASE(ConsoleInput) {
  Console::Input input;
  
  std::string TEST_INPUT_LINE;
  
  TEST_INPUT_LINE = Console::Command::SHELL;
  BOOST_CHECK(input.parse(TEST_INPUT_LINE));
  BOOST_CHECK_EQUAL((input.cmd.compare(Console::Command::SHELL) == 0), true);
  BOOST_CHECK_EQUAL(input.params.size(), 0);

  // Single Space
  
  TEST_INPUT_LINE = Console::Command::SHELL + " ";
  BOOST_CHECK(input.parse(TEST_INPUT_LINE));
  BOOST_CHECK_EQUAL((input.cmd.compare(Console::Command::SHELL) == 0), true);
  BOOST_CHECK_EQUAL(input.params.size(), 0);

  TEST_INPUT_LINE = Console::Command::SHELL + Console::Command::EXIT;
  BOOST_CHECK(input.parse(TEST_INPUT_LINE));
  BOOST_CHECK_EQUAL((input.cmd.compare(Console::Command::SHELL) == 0), false);
  BOOST_CHECK_EQUAL(input.params.size(), 0);

  TEST_INPUT_LINE = Console::Command::SHELL + " " + Console::Command::EXIT;
  BOOST_CHECK(input.parse(TEST_INPUT_LINE));
  BOOST_CHECK_EQUAL((input.cmd.compare(Console::Command::SHELL) == 0), true);
  BOOST_CHECK_EQUAL(input.params.size(), 1);
  BOOST_CHECK_EQUAL((input.params[0].compare(Console::Command::EXIT) == 0), true);

  TEST_INPUT_LINE = Console::Command::SHELL + " " + Console::Command::EXIT + " " + Console::Command::QUIT;
  BOOST_CHECK(input.parse(TEST_INPUT_LINE));
  BOOST_CHECK_EQUAL((input.cmd.compare(Console::Command::SHELL) == 0), true);
  BOOST_CHECK_EQUAL(input.params.size(), 2);
  BOOST_CHECK_EQUAL((input.params[0].compare(Console::Command::EXIT) == 0), true);
  BOOST_CHECK_EQUAL((input.params[1].compare(Console::Command::QUIT) == 0), true);

  // Single Space + LF
  
  TEST_INPUT_LINE = Console::Command::SHELL + " " + "\n";
  BOOST_CHECK(input.parse(TEST_INPUT_LINE));
  BOOST_CHECK_EQUAL((input.cmd.compare(Console::Command::SHELL) == 0), true);
  BOOST_CHECK_EQUAL(input.params.size(), 0);
  
  TEST_INPUT_LINE = Console::Command::SHELL + Console::Command::EXIT + "\n";
  BOOST_CHECK(input.parse(TEST_INPUT_LINE));
  BOOST_CHECK_EQUAL((input.cmd.compare(Console::Command::SHELL) == 0), false);
  BOOST_CHECK_EQUAL(input.params.size(), 0);
  
  TEST_INPUT_LINE = Console::Command::SHELL + " " + Console::Command::EXIT + "\n";
  BOOST_CHECK(input.parse(TEST_INPUT_LINE));
  BOOST_CHECK_EQUAL((input.cmd.compare(Console::Command::SHELL) == 0), true);
  BOOST_CHECK_EQUAL(input.params.size(), 1);
  BOOST_CHECK_EQUAL((input.params[0].compare(Console::Command::EXIT) == 0), true);
  
  TEST_INPUT_LINE = Console::Command::SHELL + " " + Console::Command::EXIT + " " + Console::Command::QUIT + "\n";
  BOOST_CHECK(input.parse(TEST_INPUT_LINE));
  BOOST_CHECK_EQUAL((input.cmd.compare(Console::Command::SHELL) == 0), true);
  BOOST_CHECK_EQUAL(input.params.size(), 2);
  BOOST_CHECK_EQUAL((input.params[0].compare(Console::Command::EXIT) == 0), true);
  BOOST_CHECK_EQUAL((input.params[1].compare(Console::Command::QUIT) == 0), true);
  
  // Double Spaces
  
  TEST_INPUT_LINE = Console::Command::SHELL + "  ";
  BOOST_CHECK(input.parse(TEST_INPUT_LINE));
  BOOST_CHECK_EQUAL((input.cmd.compare(Console::Command::SHELL) == 0), true);
  BOOST_CHECK_EQUAL(input.params.size(), 0);
  
  TEST_INPUT_LINE = Console::Command::SHELL + Console::Command::EXIT;
  BOOST_CHECK(input.parse(TEST_INPUT_LINE));
  BOOST_CHECK_EQUAL((input.cmd.compare(Console::Command::SHELL) == 0), false);
  BOOST_CHECK_EQUAL(input.params.size(), 0);
  
  TEST_INPUT_LINE = Console::Command::SHELL + "  " + Console::Command::EXIT;
  BOOST_CHECK(input.parse(TEST_INPUT_LINE));
  BOOST_CHECK_EQUAL((input.cmd.compare(Console::Command::SHELL) == 0), true);
  BOOST_CHECK_EQUAL(input.params.size(), 1);
  BOOST_CHECK_EQUAL((input.params[0].compare(Console::Command::EXIT) == 0), true);
  
  TEST_INPUT_LINE = Console::Command::SHELL + "  " + Console::Command::EXIT + "  " + Console::Command::QUIT;
  BOOST_CHECK(input.parse(TEST_INPUT_LINE));
  BOOST_CHECK_EQUAL((input.cmd.compare(Console::Command::SHELL) == 0), true);
  BOOST_CHECK_EQUAL(input.params.size(), 2);
  BOOST_CHECK_EQUAL((input.params[0].compare(Console::Command::EXIT) == 0), true);
  BOOST_CHECK_EQUAL((input.params[1].compare(Console::Command::QUIT) == 0), true);
}

BOOST_AUTO_TEST_SUITE_END()

