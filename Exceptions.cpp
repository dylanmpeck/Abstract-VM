/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Exceptions.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <dpeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 15:04:59 by dpeck             #+#    #+#             */
/*   Updated: 2019/05/22 16:58:44 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Exceptions.hpp"

AVMException::AVMException() {}

AVMException::~AVMException() throw() {}

AVMException::AVMException(AVMException const & other)
{
    *this = other;
}

AVMException const & AVMException::operator=(AVMException const & rhs)
{
    static_cast<void>(rhs);
    return (*this);
}

LexicalException::LexicalException() {}

LexicalException::~LexicalException() throw() {}

LexicalException::LexicalException(LexicalException const & other)
{
    *this = other;
}

LexicalException const & LexicalException::operator=(LexicalException const & rhs)
{
    static_cast<void>(rhs);
    return (*this);
}

const char * LexicalException::what() const throw()
{
    return ("Lexical/syntactic exception thrown");
}

UnknownInstructionException::UnknownInstructionException() {}

UnknownInstructionException::~UnknownInstructionException() throw() {}

UnknownInstructionException::UnknownInstructionException(UnknownInstructionException const & other)
{
    *this = other;
}

UnknownInstructionException const & UnknownInstructionException::operator=(UnknownInstructionException const & rhs)
{
    static_cast<void>(rhs);
    return (*this);
}

const char * UnknownInstructionException::what() const throw()
{
    return ("Unknown instruction in file");
}

UnknownDataTypeException::UnknownDataTypeException() {}

UnknownDataTypeException::~UnknownDataTypeException() throw() {}

UnknownDataTypeException::UnknownDataTypeException(UnknownDataTypeException const & other)
{
    *this = other;
}

UnknownDataTypeException const & UnknownDataTypeException::operator=(UnknownDataTypeException const & rhs)
{
    static_cast<void>(rhs);
    return (*this);
}

const char * UnknownDataTypeException::what() const throw()
{
    return ("Unknown data type");
}

OutOfRangeException::OutOfRangeException() {}

OutOfRangeException::~OutOfRangeException() throw() {}

OutOfRangeException::OutOfRangeException(OutOfRangeException const & other)
{
    *this = other;
}

OutOfRangeException const & OutOfRangeException::operator=(OutOfRangeException const & rhs)
{
    static_cast<void>(rhs);
    return (*this);
}

const char * OutOfRangeException::what() const throw()
{
    return ("Value is out of range");
}

PopOnEmptyStackException::PopOnEmptyStackException() {}

PopOnEmptyStackException::~PopOnEmptyStackException() throw() {}

PopOnEmptyStackException::PopOnEmptyStackException(PopOnEmptyStackException const & other)
{
    *this = other;
}

PopOnEmptyStackException const & PopOnEmptyStackException::operator=(PopOnEmptyStackException const & rhs)
{
    static_cast<void>(rhs);
    return (*this);
}

const char * PopOnEmptyStackException::what() const throw()
{
    return ("Pop on empty stack");
}

DivisionByZeroException::DivisionByZeroException() {}

DivisionByZeroException::~DivisionByZeroException() throw() {}

DivisionByZeroException::DivisionByZeroException(DivisionByZeroException const & other)
{
    *this = other;
}

DivisionByZeroException const & DivisionByZeroException::operator=(DivisionByZeroException const & rhs)
{
    static_cast<void>(rhs);
    return (*this);
}

const char * DivisionByZeroException::what() const throw()
{
    return ("Division by zero");
}

ModuloByZeroException::ModuloByZeroException() {}

ModuloByZeroException::~ModuloByZeroException() throw() {}

ModuloByZeroException::ModuloByZeroException(ModuloByZeroException const & other)
{
    *this = other;
}

ModuloByZeroException const & ModuloByZeroException::operator=(ModuloByZeroException const & rhs)
{
    static_cast<void>(rhs);
    return (*this);
}

const char * ModuloByZeroException::what() const throw()
{
    return ("Modulo by zero");
}

NoExitException::NoExitException() {}

NoExitException::~NoExitException() throw() {}

NoExitException::NoExitException(NoExitException const & other)
{
    *this = other;
}

NoExitException const & NoExitException::operator=(NoExitException const & rhs)
{
    static_cast<void>(rhs);
    return (*this);
}

const char * NoExitException::what() const throw()
{
    return ("No exit found");
}

BadAssertException::BadAssertException() {}

BadAssertException::~BadAssertException() throw() {}

BadAssertException::BadAssertException(BadAssertException const & other)
{
    *this = other;
}

BadAssertException const & BadAssertException::operator=(BadAssertException const & rhs)
{
    static_cast<void>(rhs);
    return (*this);
}

const char * BadAssertException::what() const throw()
{
    return ("Assert value not the same");
}

StackSizeTooSmallException::StackSizeTooSmallException() {}

StackSizeTooSmallException::~StackSizeTooSmallException() throw() {}

StackSizeTooSmallException::StackSizeTooSmallException(StackSizeTooSmallException const & other)
{
    *this = other;
}

StackSizeTooSmallException const & StackSizeTooSmallException::operator=(StackSizeTooSmallException const & rhs)
{
    static_cast<void>(rhs);
    return (*this);
}

const char * StackSizeTooSmallException::what() const throw()
{
    return ("Stack size is too small for arithmetic operation");
}

WrongModTypeException::WrongModTypeException() {}

WrongModTypeException::~WrongModTypeException() throw() {}

WrongModTypeException::WrongModTypeException(WrongModTypeException const & other)
{
    *this = other;
}

WrongModTypeException const & WrongModTypeException::operator=(WrongModTypeException const & rhs)
{
    static_cast<void>(rhs);
    return (*this);
}

const char * WrongModTypeException::what() const throw()
{
    return ("Wrong type for modulo (only works with ints)");
}

StackIsEmptyException::StackIsEmptyException() {}

StackIsEmptyException::~StackIsEmptyException() throw() {}

StackIsEmptyException::StackIsEmptyException(StackIsEmptyException const & other)
{
    *this = other;
}

StackIsEmptyException const & StackIsEmptyException::operator=(StackIsEmptyException const & rhs)
{
    static_cast<void>(rhs);
    return (*this);
}

const char * StackIsEmptyException::what() const throw()
{
    return ("Invalid operation on empty stack");
}
