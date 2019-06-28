/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Operand.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <dpeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/17 16:42:17 by dpeck             #+#    #+#             */
/*   Updated: 2019/05/21 20:15:47 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPERAND_HPP
#define OPERAND_HPP

#include "IOperand.hpp"
#include "Exceptions.hpp"
#include <iostream>
#include <sstream>
#include <cfenv>

class OperandFactory {

typedef IOperand const * (OperandFactory::*CreateFunctions)(std::string const & value) const;

private:
    IOperand const * createInt8( std::string const & value ) const;
    IOperand const * createInt16( std::string const & value ) const;
    IOperand const * createInt32( std::string const & value ) const;
    IOperand const * createFloat( std::string const & value ) const;
    IOperand const * createDouble( std::string const & value ) const;

    CreateFunctions _createFunctions[5];

public:
    OperandFactory();
    ~OperandFactory();
    OperandFactory(OperandFactory const &);
    OperandFactory const & operator=(OperandFactory const & rhs);

    IOperand const * createOperand( eOperandType type, std::string const & value ) const;
    int checkValidFloat(std::string const & str) const;
    int checkScientificNotation(std::string const & str) const;

};

template <typename T>
class Operand : public IOperand {

private:
    T _value;
    eOperandType _type;
    int _precision;
    OperandFactory factory;
    std::string _strVal;
    
    Operand();

public:
    Operand(T & value, eOperandType type, int precision): _value(value), _type(type), _precision(precision) 
    {
        std::ostringstream ss;
        ss.precision(precision);
        if (_type == Int8)
            ss << std::fixed << static_cast<int>(_value);
        else
            ss << std::fixed << _value;
        this->_strVal = ss.str();
    }

    ~Operand() { return; }
    Operand(Operand const & other) { *this = other; }
    Operand const & operator=(Operand const & rhs)
    {
        if (this != &rhs)
        {
            this->_value = rhs._value;
            this->_type = rhs._type;
            this->_precision = rhs._precision;
            this->factory = rhs.factory;
            this->_strVal = rhs._strVal;
        }
        return (*this);
    }

    virtual int getPrecision(void) const { return this->_precision; }
    virtual eOperandType getType(void) const { return (this->_type); }
    T getValue(void) { return (this->_value); }

    virtual IOperand const * operator+( IOperand const & rhs) const
    {
        eOperandType type = std::max(this->getType(), rhs.getType());

        std::ostringstream ss;
        ss.precision(_precision);
        ss << std::fixed << (std::stod(this->toString()) + std::stod(rhs.toString()));
        return (Operand<T>::factory.createOperand(type, ss.str()));
    }

    virtual IOperand const * operator-( IOperand const & rhs) const
    {
        eOperandType type = std::max(this->getType(), rhs.getType());

        std::ostringstream ss;
        ss.precision(_precision);
        ss << std::fixed << (std::stod(this->toString()) - std::stod(rhs.toString()));
        return (Operand<T>::factory.createOperand(type, ss.str()));
    }

    virtual IOperand const * operator*( IOperand const & rhs) const
    {
        eOperandType type = std::max(this->getType(), rhs.getType());

        std::ostringstream ss;
        ss.precision(_precision);
        ss << std::fixed << (std::stod(this->toString()) * std::stod(rhs.toString()));
        return (Operand<T>::factory.createOperand(type, ss.str()));
    }

    virtual IOperand const * operator/( IOperand const & rhs) const
    {
        eOperandType type = std::max(this->getType(), rhs.getType());

        if (std::stod(rhs.toString()) == 0)
            throw (DivisionByZeroException());

        std::ostringstream ss;
        ss.precision(_precision);
        ss << std::fixed << (std::stod(this->toString()) / std::stod(rhs.toString()));
        return (Operand<T>::factory.createOperand(type, ss.str()));
    }

    //should only work with ints
    virtual IOperand const * operator%( IOperand const & rhs) const
    {
        eOperandType type = std::max(this->getType(), rhs.getType());

        if (type > Int32)
            throw(WrongModTypeException());
        if (std::stod(rhs.toString()) == 0)
            throw (ModuloByZeroException());

        std::ostringstream ss;
        ss.precision(_precision);
        ss << std::fixed << (std::stoi(this->toString()) % std::stoi(rhs.toString()));
        return (Operand<T>::factory.createOperand(type, ss.str()));
    }

    virtual std::string const & toString( void ) const
    {
        return (this->_strVal);
    }
};

#endif