/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Exceptions.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <dpeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 14:53:02 by dpeck             #+#    #+#             */
/*   Updated: 2019/05/22 16:28:15 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXCEPTIONS_HPP
#define EXCEPTIONS_HPP

#include <exception>
#include <iostream>

class AVMException : public std::exception {

public:
    AVMException();
    ~AVMException() _NOEXCEPT;
    AVMException(AVMException const &);
    AVMException const & operator=(AVMException const &);
};

class LexicalException : public AVMException {

public:
    LexicalException();
    ~LexicalException() _NOEXCEPT;
    LexicalException(LexicalException const &);
    LexicalException const & operator=(LexicalException const &);

    virtual const char * what() const throw();
};

class UnknownInstructionException : public AVMException {

public:
    UnknownInstructionException();
    ~UnknownInstructionException() _NOEXCEPT;
    UnknownInstructionException(UnknownInstructionException const &);
    UnknownInstructionException const & operator=(UnknownInstructionException const &);

    virtual const char * what() const throw();
};


class UnknownDataTypeException : public AVMException {

public:
    UnknownDataTypeException();
    ~UnknownDataTypeException() _NOEXCEPT;
    UnknownDataTypeException(UnknownDataTypeException const &);
    UnknownDataTypeException const & operator=(UnknownDataTypeException const &);

    virtual const char * what() const throw();
};

class OutOfRangeException : public AVMException {

public:
    OutOfRangeException();
    ~OutOfRangeException() _NOEXCEPT;
    OutOfRangeException(OutOfRangeException const &);
    OutOfRangeException const & operator=(OutOfRangeException const &);

    virtual const char * what() const throw();
};

class PopOnEmptyStackException : public AVMException {

public:
    PopOnEmptyStackException();
    ~PopOnEmptyStackException() _NOEXCEPT;
    PopOnEmptyStackException(PopOnEmptyStackException const &);
    PopOnEmptyStackException const & operator=(PopOnEmptyStackException const &);

    virtual const char * what() const throw();
};

class DivisionByZeroException : public AVMException {

public:
    DivisionByZeroException();
    ~DivisionByZeroException() _NOEXCEPT;
    DivisionByZeroException(DivisionByZeroException const &);
    DivisionByZeroException const & operator=(DivisionByZeroException const &);

    virtual const char * what() const throw();
};

class ModuloByZeroException : public AVMException {

public:
    ModuloByZeroException();
    ~ModuloByZeroException() _NOEXCEPT;
    ModuloByZeroException(ModuloByZeroException const &);
    ModuloByZeroException const & operator=(ModuloByZeroException const &);

    virtual const char * what() const throw();
};

class NoExitException : public AVMException {

public:
    NoExitException();
    ~NoExitException() _NOEXCEPT;
    NoExitException(NoExitException const &);
    NoExitException const & operator=(NoExitException const &);

    virtual const char * what() const throw();
};

class BadAssertException : public AVMException {

public:
    BadAssertException();
    ~BadAssertException() _NOEXCEPT;
    BadAssertException(BadAssertException const &);
    BadAssertException const & operator=(BadAssertException const &);

    virtual const char * what() const throw();
};

class StackSizeTooSmallException : public AVMException {

public:
    StackSizeTooSmallException();
    ~StackSizeTooSmallException() _NOEXCEPT;
    StackSizeTooSmallException(StackSizeTooSmallException const &);
    StackSizeTooSmallException const & operator=(StackSizeTooSmallException const &);

    virtual const char * what() const throw();
};

class WrongModTypeException : public AVMException {

public:
    WrongModTypeException();
    ~WrongModTypeException() _NOEXCEPT;
    WrongModTypeException(WrongModTypeException const &);
    WrongModTypeException const & operator=(WrongModTypeException const &);

    virtual const char * what() const throw();
};

class StackIsEmptyException : public AVMException {

public:
    StackIsEmptyException();
    ~StackIsEmptyException() _NOEXCEPT;
    StackIsEmptyException(StackIsEmptyException const &);
    StackIsEmptyException const & operator=(StackIsEmptyException const &);

    virtual const char * what() const throw();
};

#endif