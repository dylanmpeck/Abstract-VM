/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <dpeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/17 18:53:06 by dpeck             #+#    #+#             */
/*   Updated: 2019/05/22 16:02:21 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IOperand.hpp"
#include "AVM.hpp"
#include <sys/stat.h>

int main(int argc, char **argv)
{
    if (argc > 2)
        std::cout << "usage: avm [input_file]" << std::endl;
    else if (argc == 1)
    {
        AVM avm;
        avm.runStdin();
    }
    else if (argc == 2)
    {
        AVM avm;
        struct stat st;
        lstat(argv[1], &st);
        if (S_ISDIR(st.st_mode))
            std::cout << "usage: avm [input_file]" << std::endl;
        else
            avm.runFile(argv[1]);   
    }
    return (0);
}