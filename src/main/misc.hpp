#pragma once

#include <iostream>
#include <string>
#include <vector>

/// 
/// COLORS
/// 

struct Color
{
    uint8_t r = 0;
    uint8_t g = 0;
    uint8_t b = 0;
    uint8_t a = 255;
};

static const std::vector<Color> Colors = {
    {255, 255,0} ,
    {63,12,12},
    {132,24,28},
    {177,48,38},
    {200,87,77},
    {221,157,151},
    {179,205,224},
    {100,151,177},
    {0,91,150},
    {3,57,108},
    {1,31,75},
    {255,0,0}
};

static Color colorLerp(const Color& col0, const Color& col1, const double& c)
{
    return {
             (uint8_t)(col0.r + (col1.r - col0.r) * c),
             (uint8_t)(col0.g + (col1.g - col0.g) * c),
             (uint8_t)(col0.b + (col1.b - col0.b) * c),
             255
           };
}

static Color linearGradient(const double& c)
{
    double stopLength = 1 / ((double) Colors.size() - 1);
    double ratio = c / stopLength;
    int stopIdx = (int)(c/stopLength);
    double v = (c - stopIdx * stopLength) / stopLength;

    if (stopIdx == Colors.size() - 1)
        return Colors.back();
    else if (stopIdx < Colors.size() - 1)
        return colorLerp(Colors[stopIdx], Colors[stopIdx + 1], v);
    else
        return Color();
}

/// 
/// Conf
/// 
static const std::string confConfiguration = "configuration";
static const std::string confGenomeMutations = "genomeMutations";
static const std::string confInputs = "inputs";
static const std::string confOutputs = "outputs";
static const std::string confName = "name";
static const std::string confMean = "mean";
static const std::string confStd = "std";
static const std::string confSquash = "squash";

/// 
/// Inputs
/// 
static const std::string inHealth = "Health";
static const std::string inHunger = "Hunger";
static const std::string inFoodPositionX = "FoodPositionX";
static const std::string inFoodPositionY = "FoodPositionY";
static const std::string inHorniness = "Horniness";
static const std::string inSize = "Size";
static const std::string inEyeSightRadius = "EyeSightRadius";
static const std::string inEyeSightAngle = "EyeSightAngle";
static const std::string inSpeed = "Speed";
static const std::string inNMutation = "NMutation";
static const std::string inPMutation = "PMutation";
static const std::string inColorR = "ColorR";
static const std::string inColorG = "ColorG";
static const std::string inColorB = "ColorB";

/// 
/// Outputs
/// 
static const std::string outTurnAngle = "TurnAngle";
static const std::string outPositionIncrement = "PositionIncrement";
static const std::string outLayEgg = "LayEgg";
