/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Operand.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <dpeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/19 11:01:07 by dpeck             #+#    #+#             */
/*   Updated: 2019/05/22 15:53:44 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Operand.hpp"

OperandFactory::OperandFactory()
{
    _createFunctions[0] = &OperandFactory::createInt8; 
    _createFunctions[1] = &OperandFactory::createInt16;
    _createFunctions[2] = &OperandFactory::createInt32;
    _createFunctions[3] = &OperandFactory::createFloat; 
    _createFunctions[4] = &OperandFactory::createDouble; 
}

OperandFactory::~OperandFactory() {}

OperandFactory::OperandFactory(OperandFactory const & other)
{
    *this = other;
}

OperandFactory const & OperandFactory::operator=(OperandFactory const & rhs)
{
    static_cast<void>(rhs);
    return (*this);
}

IOperand const * OperandFactory::createOperand(eOperandType type, std::string const & value) const
{
    int idx = type;
    return (this->*(_createFunctions[idx]))(value);
}

IOperand const * OperandFactory::createInt8(std::string const & value) const
{
    try {std::stoi(value);} catch (std::exception & e) {
        throw (OutOfRangeException());
    }
    if (value.compare(std::to_string(std::stoi(value))))
        throw(LexicalException());
    if (std::stod(value) < std::numeric_limits<char>::min() || std::stod(value) > std::numeric_limits<char>::max())
        throw(OutOfRangeException());
    int8_t v = std::stoi(value);
    return (new Operand<int8_t>(v, Int8, 0));
}

IOperand const * OperandFactory::createInt16(std::string const & value) const
{
    try {std::stoi(value);} catch (std::exception & e) {
        throw (OutOfRangeException());
    }
    if (value.compare(std::to_string(std::stoi(value))))
        throw(LexicalException());
    if (std::stod(value) < std::numeric_limits<short>::min() || std::stod(value) > std::numeric_limits<short>::max())
        throw(OutOfRangeException());
    int16_t v = std::stoi(value);
    return (new Operand<int16_t>(v, Int16, 0));
}

IOperand const * OperandFactory::createInt32(std::string const & value) const
{
    try {std::stoi(value);} catch (std::exception & e) {
        throw(OutOfRangeException());
    }
    if (std::stod(value) < std::numeric_limits<int>::min() || std::stod(value) > std::numeric_limits<int>::max())
        throw(OutOfRangeException());
    if (value.compare(std::to_string(std::stoi(value))))
        throw(LexicalException());
    int32_t v = std::stoi(value);
    return (new Operand<int32_t>(v, Int32, 0));
}

IOperand const * OperandFactory::createFloat(std::string const & value) const
{
    int precision = 1;

    try {precision = checkValidFloat(value);} catch (LexicalException & e) {
        try {precision = checkScientificNotation(value);} catch (LexicalException & e) {
            throw (LexicalException());
        }
    }
    try {std::stof(value);} catch (std::exception & e) {
        throw (OutOfRangeException());
    }
    float v = std::stof(value);
    if (precision == 0)
        precision = 1;
    if (precision > 7)
        precision = 7;
    return (new Operand<float>(v, Float, precision));
}

IOperand const * OperandFactory::createDouble(std::string const & value) const
{
    int precision = 1;

    try {precision = checkValidFloat(value);} catch (LexicalException & e) {
        try {precision = checkScientificNotation(value);} catch (LexicalException & e) {
            throw (LexicalException());
        }
    }
    try {std::stod(value);} catch (std::out_of_range & exception) {
        throw(OutOfRangeException());
    }
    double v = std::stod(value);
    if (precision == 0)
        precision = 1;
    if (precision > 15)
        precision = 15;
    return (new Operand<double>(v, Double, precision));
}

int OperandFactory::checkValidFloat(std::string const & str) const
{
    int i = 0;
    int precision = 0;

    if (str[i] == '-' || str[i] == '+')
        i++;
    while (str[i] && str[i] != '.')
    {
        if (str[i] < '0' || str[i] > '9')
            throw(LexicalException());
        i++;
    }
    if (str[i] == '.')
        i++;
    while (str[i])
    {
        if (str[i] < '0' || str[i] > '9')
            throw(LexicalException());
        i++;
        precision++;
    }
    return (precision);
}

int OperandFactory::checkScientificNotation(std::string const & str) const
{
    int i = 0;
    int precision = 0;

    if (str[i] == '-' || str[i] == '+')
        i++;
    while (str[i] && str[i] != 'e' && str[i] != '.')
    {
        if (str[i] < '0' || str[i] > '9')
            throw (LexicalException());
        i++;
    }
    if (str[i] == '.')
    {
        i++;
        while (str[i] && str[i] != 'e')
        {
            if (str[i] < '0' || str[i] > '9')
                throw (LexicalException());
            i++;
        }
    }
    if (str[i] == 'e')
        i++;
    if (str[i] == '-')
    {
        precision = std::stoi(str.substr(i, str.length() - i));
        i++;
    }
    if (str[i] == '+')
        i++;
    while (str[i])
    {
        if (str[i] < '0' || str[i] > '9')
            throw(LexicalException());
        i++;
    }
    return (precision);
}