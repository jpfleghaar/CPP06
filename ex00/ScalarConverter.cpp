/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpflegha <jpflegha@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/10 15:36:33 by Jpflegha          #+#    #+#             */
/*   Updated: 2026/06/10 16:17:11 by Jpflegha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScalarConverter.hpp"
#include <iostream>
#include <string>
#include <cstdlib> // strtol, strtod
#include <climits> // INT_MAX, INT_MIN
#include <cctype>  // isdigit, isprint
#include <cmath>   // floor
#include <sstream>

ScalarConverter::ScalarConverter() {}
ScalarConverter::ScalarConverter(const ScalarConverter &) {}
ScalarConverter &ScalarConverter::operator=(const ScalarConverter &) { return *this; }
ScalarConverter::~ScalarConverter() {}

//check if string is just 1 char and not a digit
static bool isCharLiteral(const std::string &str)
{
    return(str.length() == 1 && !std::isdigit(static_cast<unsigned char>(str[0])));
}

static bool parseNumber(const std::string &str, double &out)
{
	if (str.empty())
		return(false);
	const char *start = str.c_str();
	char *end = NULL;
	double value = std::strtod(start, &end);
	if (end == start)
		return false;
	if (*end == '\0' || (*end == 'f' && *(end + 1) == '\0'))
	{
		out = value;
		return true;
	}
	return(false);
}

static void printResults(double value, bool nanFlag, bool posInf, bool negInf)
{
    bool spacial = (nanFlag || posInf || negInf);

    // Print CHAR
    std::cout <<  "char: ";
    if(spacial || value < static_cast<double>(INT_MIN) || value > static_cast<double>(INT_MAX))
        std::cout << "impossible";
    else
    {
        int c = static_cast<int>(value);
		if(c < 0 || c > 127)
            std::cout << "impossible";
        else if(!std::isprint(c))
            std::cout << "Non displayable";
        else
            std::cout << "'" << static_cast<char>(c) << "'";
    }
    std::cout << "\n";

    // Print INT
    std::cout << "int: ";
    if(spacial || value < static_cast<double>(INT_MIN) || value > static_cast<double>(INT_MAX))
        std::cout << "impossible";
    else
        std::cout << static_cast<int>(value);
    std::cout << "\n";

    // Print FLOAT
    std::cout << "float: ";
    if(nanFlag)
        std::cout << "nanf";
    else if(posInf)
        std::cout << "+inff";
    else if(negInf)
    	std::cout << "-inff";
	else
    {
        float f = static_cast<float>(value);
        std::ostringstream oss;
        oss << f;
        std::string text = oss.str();
		// Only add .0 if the text is a plain whole number — not if it already has a dot, an e (scientific notation), or is inf/nan.
        if(text.find('.') == std::string::npos && text.find('e') == std::string::npos
            && text.find("inf") == std::string::npos && text.find("nan") == std::string::npos)
            text += ".0";
        std::cout << text << "f";
    }
    std::cout << "\n";

    // Print DOUBLE
    std::cout << "double: ";
    if(nanFlag)
        std::cout << "nan";
    else if(posInf)
        std::cout << "+inf";
    else if(negInf)
        std::cout << "-inf";
    else
    {
        std::ostringstream oss;
        oss << value;
        std::string text = oss.str();
		// Only add .0 if the text is a plain whole number — not if it already has a dot, an e (scientific notation), or is inf/nan.
    	if(text.find('.') == std::string::npos && text.find('e') == std::string::npos
            && text.find("inf") == std::string::npos && text.find("nan") == std::string::npos)
            text += ".0";
        std::cout << text;
    }
    std::cout << "\n";
}

void ScalarConverter::convert(const std::string &literal)
{
	double d = 0.0;
	bool nanFlag = false;
	bool posInf = false;
	bool negInf = false;

	if (isCharLiteral(literal))
		d = static_cast<double>(literal[0]);
	else if (literal == "nan" || literal == "nanf")
		nanFlag = true;
	else if (literal == "+inf" || literal == "+inff")
		posInf = true;
	else if (literal == "-inf" || literal == "-inff")
		negInf = true;
	else if (!parseNumber(literal, d))
	{
		std::cout << "char: impossible" << std::endl;
		std::cout << "int: impossible" << std::endl;
		std::cout << "float: impossible" << std::endl;
		std::cout << "double: impossible" << std::endl;
		return;
	}

	printResults(d, nanFlag, posInf, negInf);
}