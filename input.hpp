#pragma once
#include <exception>
#include <iostream>
#include <stdexcept>
#include <string>
inline bool ask(std::string question) {
  std::cout << question << "\n[Y/n]\n>";
  std::string res = "";
askAgian:
  std::cin.clear();
  std::getline(std::cin, res);
  if (std::cin.eof()) {
    exit(0);
  }
  if (res.empty()) {
    return true;
  }
  switch (res.at(0)) {
  case 'y':
  case 'Y':
    return true;
    break;
  case 'n':
  case 'N':
    return false;
    break;
  default:
    res = "";
    std::cout << "unknown answer; try agian\n[Y/n]\n>";
    goto askAgian;
    break;
  }
}
inline int askInt(std::string question) {
  ask:
  std::cout << question << "\n>";
  std::string res = "";
  std::cin.clear();
  std::getline(std::cin, res);
  try {
  return std::stoi(res);
  } catch (std::invalid_argument e) {
    std::cout << "invalid arugment"<< e.what() << "\n";
    goto ask;
  }
}