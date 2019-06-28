/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AVM.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <dpeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/19 12:40:53 by dpeck             #+#    #+#             */
/*   Updated: 2019/05/22 16:53:08 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AVM.hpp"

typedef void (AVM::*Instructions)(void);

std::unordered_map<std::string, Instructions> AVM::_instructionMap = AVM::initInstructionMap();

std::unordered_map<std::string, eOperandType> AVM::_enumMap = AVM::initEnumMap();

std::unordered_map<std::string, Instructions> AVM::initInstructionMap()
{
    std::unordered_map<std::string, Instructions> map;
    map["push"] = &AVM::avm_push;
    map["pop"] = &AVM::avm_pop;
    map["dump"] = &AVM::avm_dump;
    map["assert"] = &AVM::avm_assert;
    map["add"] = &AVM::avm_add;
    map["sub"] = &AVM::avm_sub;
    map["mul"] = &AVM::avm_mul;
    map["div"] = &AVM::avm_div;
    map["mod"] = &AVM::avm_mod;
    map["print"] = &AVM::avm_print;
    map["exit"] = &AVM::avm_exit;
    return (map);
}

std::unordered_map<std::string, eOperandType> AVM::initEnumMap()
{
    std::unordered_map<std::string, eOperandType> map;
    map["int8"] = Int8;
    map["int16"] = Int16;
    map["int32"] = Int32;
    map["float"] = Float;
    map["double"] = Double;
    return (map);
}

AVM::AVM() : _operandPtr(nullptr), _stdin(false), _exitFound(false)
{
    this->_instruct = "";
    this->_type = "";
    this->_value = "";
}

AVM::~AVM() 
{
    if (_operandPtr != nullptr)
        delete _operandPtr;

    while (!_operands.empty())
    {
        delete _operands.top();
        _operands.pop();
    }
}

AVM::AVM(AVM const & other)
{
    *this = other;
}

AVM const & AVM::operator=(AVM const & rhs)
{
    if (this != &rhs)
    {
        this->_operands = rhs._operands;
        this->_output = rhs._output;

        if (this->_operandPtr)
            delete this->_operandPtr;
        this->_operandPtr = nullptr;
    }
    return (*this);
}

void AVM::runFile(char *file)
{
    std::filebuf fb;
    if (fb.open(file, std::ios::in))
    {
        std::istream is(&fb);

        try {
            parseFile(is);
            printOutput();
        } catch (AVMException & exception) {
            std::cout << "Error: " << exception.what() << std::endl; // No exit was found
        } catch (std::exception & exception) {
            printErrors();
            if (!_output.empty())
                std::cout << "Clean up errors to display output." << std::endl; // Any error was found in output
        }

        fb.close();
    }
    else
        std::cout << "Error: file is invalid." << std::endl;
}

void AVM::runStdin()
{
    _stdin = true;
    try {
        parseFile(std::cin);
        printOutput();
    } catch (AVMException & e) {
        std::cout << "Error: " << e.what() << std::endl; // No exit was found
    } catch (std::exception & e) {
        printErrors();
        if (!_output.empty())
            std::cout << "Clean up errors to display output." << std::endl; // Any error was found in output
     }
}

void AVM::parseFile(std::istream & file)
{
    std::string line;
    bool error = false;
    int lineNum = 0;

    while (std::getline(file, line))
    {
        lineNum++;
        if (_stdin && line == ";;")
            break;
        if (_stdin && _exitFound == true)
            continue;
        if (line.empty() || line[0] == ';')
            continue;
        try
        {
            getDataFromline(line);
            executeInstructions();
        } catch (AVMException & exception) {
            std::stringstream errorMessage;
            errorMessage << "Error: " << exception.what() << " on line " << lineNum;
            _errors.push(errorMessage.str());
            error = true;
        } catch (std::exception & exception) {
            std::stringstream errorMessage;
            errorMessage << "Error: " << exception.what() << " on line " << lineNum;
            _errors.push(errorMessage.str());
            error = true;
        }
        if (!_stdin && _exitFound == true)
            break;
    }

    if (_exitFound == false)
        throw(NoExitException());
    if (error)
        throw(std::exception());
}

void AVM::getDataFromline(std::string const & line)
{
        _instruct = "";
        _value = "";
        _type = "";
        unsigned long i = 0;

        while (line[i] == ' ' || line[i] == '\t')
            i++;

        if (line[i] == ';')
            return;
        for (; i < line.length(); i++)
        {
            if (line[i] == ' ')
            {
                i++;
                break;
            }
            _instruct.push_back(line[i]);
        }

        if (_instruct == "push" || _instruct == "assert")
        {
            while (line[i] != '(' && line[i] != ' ' && line[i] != '\t')
            {
                _type.push_back(line[i]);
                i++;
            }
            if (line[i] == ' ' || line[i] == '\t')
                throw(LexicalException());
            i++;
            while (line[i] != ')' && line[i] != ' ' && line[i] != '\t')
            {
                _value.push_back(line[i]);
                i++;
            }
            if (line[i] == ' ' || line[i] == '\t')
                throw(LexicalException());
            i++;
        }

        while (line[i] == ' ' || line[i] == '\t')
            i++;
        if (i < line.size() && line[i] == ';')
            return;
        else if (i < line.size())
            throw(LexicalException());
}

void AVM::executeInstructions()
{
    if (_instruct == "push" || _instruct == "assert")
    {
        if (AVM::_enumMap.find(_type) == AVM::_enumMap.end())
            throw(UnknownDataTypeException());
        _operandPtr = factory.createOperand(_enumMap[_type], _value);
    }
    _instructionIt = _instructionMap.find(_instruct);
    if (_instructionIt == _instructionMap.end())
        throw (UnknownInstructionException());
    else
        (this->*(_instructionIt->second))();
}

void AVM::printOutput()
{
    while (!_output.empty())
    {
        std::cout << _output.front() << std::endl;
        _output.pop();
    }
}

void AVM::printErrors()
{
    while (!_errors.empty())
    {
        std::cout << _errors.front() << std::endl;
        _errors.pop();
    }
}

void AVM::avm_push()
{
    if (_operandPtr == nullptr)
        throw (LexicalException());
    _operands.push(_operandPtr);
    _operandPtr = nullptr;
}

void AVM::avm_pop()
{
    if (_operands.empty())
        throw (PopOnEmptyStackException());
    delete _operands.top();
    _operands.pop();
}

void AVM::avm_dump()
{
    std::stack<IOperand const *> copy = this->_operands;
    while (!copy.empty())
    {
        this->_output.push(copy.top()->toString());
        copy.pop();
    }
}

void AVM::avm_assert()
{
    if (_operandPtr == nullptr)
        throw (LexicalException());
    if (_operandPtr->getType() != _operands.top()->getType() || _operandPtr->toString() != _operands.top()->toString())
        throw (BadAssertException());
    delete _operandPtr;
    _operandPtr = nullptr;
    return;
}

void AVM::avm_add()
{
    if (_operands.size() < 2)
        throw (StackSizeTooSmallException());

    IOperand const *a;
    a = _operands.top();

    _operands.pop();
    IOperand const *b;
    b = _operands.top();
    _operands.pop();


    IOperand const *c;
    c = (*a + *b);
    _operands.push(c);
    delete a;
    delete b;
}

void AVM::avm_sub()
{
    if (_operands.size() < 2)
        throw (StackSizeTooSmallException());

    IOperand const *a;
    a = _operands.top();
    _operands.pop();
    IOperand const *b;
    b = _operands.top();
    _operands.pop();

    IOperand const *c;
    c = (*b - *a);
    _operands.push(c);
    delete a;
    delete b;    
}

void AVM::avm_mul()
{
    if (_operands.size() < 2)
        throw (StackSizeTooSmallException());

    IOperand const *a;
    a = _operands.top();
    _operands.pop();
    IOperand const *b;
    b = _operands.top();
    _operands.pop();

    IOperand const *c;
    c = (*a * *b);
    _operands.push(c);
    delete a;
    delete b;    
}

void AVM::avm_div()
{
    if (_operands.size() < 2)
        throw (StackSizeTooSmallException());

    IOperand const *a;
    a = _operands.top();
    _operands.pop();
    IOperand const *b;
    b = _operands.top();
    _operands.pop();

    IOperand const *c;
    c = (*b / *a);
    _operands.push(c);
    delete a;
    delete b;
}

void AVM::avm_mod()
{
    if (_operands.size() < 2)
        throw (StackSizeTooSmallException());

    IOperand const *a;
    a = _operands.top();
    _operands.pop();
    IOperand const *b;
    b = _operands.top();
    _operands.pop();

    IOperand const *c;
    c = (*b % *a);
    _operands.push(c);
    delete a;
    delete b;
}

void AVM::avm_print()
{
    if (_operands.empty())
        throw (StackIsEmptyException());
    if (_operands.top()->getType() != Int8)
        throw (BadAssertException());
    
    char c = std::stoi(_operands.top()->toString());
    std::string output = "";
    output.push_back(c);
    this->_output.push(output);
}

void AVM::avm_exit()
{
    _exitFound = true;
}