#ifndef PONG_CONSTANTS_H_
#define PONG_CONSTANTS_H_

#include <string>

const int kScreenWidth      = 1600;
const int kScreenHeight     = 900;

const int kDirectionLeft = -1;
const int kDirectionRight = 1;

const int kBorderSpace     = 50;
const int kBorderWidth     = kScreenWidth - (kBorderSpace * 2);
const int kBorderHeight    = kScreenHeight - (kBorderSpace * 2);
const int kBorderThickness = 10;

const int kTableX      = kBorderSpace + kBorderThickness;
const int kTableY      = kBorderSpace + kBorderThickness;
const int kTableWidth  = kBorderWidth - (kBorderThickness * 2);
const int kTableHeight = kBorderHeight - (kBorderThickness * 2);

/* Strings */
const std::string kWindowName = "Pong";
const std::string kLogFilename = "pong.log";

const int kRedMask   = 0xff000000;
const int kGreenMask = 0x00ff0000;
const int kBlueMask  = 0x0000ff00;
const int kAlphaMask = 0x000000ff;

#endif
