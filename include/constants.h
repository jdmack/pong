#ifndef PONG_CONSTANTS_H_
#define PONG_CONSTANTS_H_

#include <string>

const int kScreenWidth      = 1600;
const int kScreenHeight     = 900;

/* Strings */
const std::string kWindowName = "Pong";
const std::string kLogFilename = "pong.log";

const int kRedMask   = 0xff000000;
const int kGreenMask = 0x00ff0000;
const int kBlueMask  = 0x0000ff00;
const int kAlphaMask = 0x000000ff;

#endif
