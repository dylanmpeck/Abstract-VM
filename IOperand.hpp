/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IOperand.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <dpeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/17 14:58:56 by dpeck             #+#    #+#             */
/*   Updated: 2019/05/17 19:05:21 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IOPERAND_HPP
#define IOPERAND_HPP

#include <string>

enum eOperandType {Int8, Int16, Int32, Float, Double};

class IOperand {

public:
    virtual int getPrecision(void) const = 0; // Precision of the type of the instance
    virtual eOperandType getType(void) const = 0; // Type of the instance

    virtual IOperand const * operator+( IOperand const & rhs ) const = 0; // Sum
    virtual IOperand const * operator-( IOperand const & rhs) const = 0; // Difference
    virtual IOperand const * operator*( IOperand const & rhs) const = 0; // Product
    virtual IOperand const * operator/( IOperand const & rhs) const = 0; // Quotient
    virtual IOperand const * operator%( IOperand const & rhs) const = 0; // Modulo

    virtual std::string const & toString( void ) const = 0; // String representation of instance

    virtual ~IOperand( void ) {}
};

#endif