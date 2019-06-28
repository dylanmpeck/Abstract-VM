/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AVM.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <dpeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/19 11:56:29 by dpeck             #+#    #+#             */
/*   Updated: 2019/05/22 16:47:42 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AVM_HPP
#define AVM_HPP

#include "Operand.hpp"
#include <iostream>
#include <istream>
#include <fstream>
#include <stack>
#include <queue>
#include <unordered_map>

class AVM {

typedef void (AVM::*Instructions)(void);

private:
    std::stack<IOperand const *> _operands;
    std::queue<std::string> _output;
    std::queue<std::string> _errors;
    static std::unordered_map<std::string, Instructions> _instructionMap;
    std::unordered_map<std::string, Instructions>::iterator _instructionIt;
    static std::unordered_map<std::string, eOperandType> _enumMap;
    IOperand const * _operandPtr;
    OperandFactory factory;

    std::string _instruct;
    std::string _value;
    std::string _type;

    bool _stdin;
    bool _exitFound;

public:
    AVM();
    ~AVM();
    AVM(AVM const &);
    AVM const & operator=(AVM const &);

    void runFile(char *file);
    void runStdin();

    void parseFile(std::istream & file);
    void getDataFromline(std::string const & line);
    void executeInstructions();
    void printOutput();
    void printErrors();

    static std::unordered_map<std::string, Instructions> initInstructionMap();
    static std::unordered_map<std::string, eOperandType> initEnumMap();

    void avm_push();
    void avm_pop();
    void avm_dump();
    void avm_assert();
    void avm_add();
    void avm_sub();
    void avm_mul();
    void avm_div();
    void avm_mod();
    void avm_print();
    void avm_exit();
};

#endif