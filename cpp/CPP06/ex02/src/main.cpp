/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 19:30:40 by sbo               #+#    #+#             */
/*   Updated: 2024/07/20 13:57:23 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BaseA.hpp"
#include "BaseB.hpp"
#include "BaseC.hpp"
#include "Base.hpp"
#include "unistd.h"

int main ()
{
    BaseA A;
    BaseB B;
    BaseC C;

    BaseA &refA = A;
    BaseB &refB = B;
    BaseC &refC = C;

    BaseA *ptrA = &A;
    BaseB *ptrB = &B;
    BaseC *ptrC = &C;

    std::cout << "ref" << std::endl;
	std::cout <<"Should be A and identify have\t" ;
    identify(refA);
	std::cout <<"Should be B and identify have\t" ;
    identify(refB);
	std::cout <<"Should be C and identify have\t" ;
    identify(refC);

    std::cout << std::endl << "ptr" << std::endl;
	std::cout <<"Should be A and identify have\t" ;
    identify(ptrA);
	std::cout <<"Should be B and identify have\t" ;
    identify(ptrB);
	std::cout  <<"Should be C and identify have\t" ;
    identify(ptrC);
    
    std::cout  << std::endl << "class" << std::endl;
	std::cout <<"Should be A and identify have\t" ;
    identify(A);
	std::cout  <<"Should be B and identify have\t" ;
    identify(B);
	std::cout  <<"Should be C and identify have\t" ;
    identify(C);
	
    try {
        Base *base;
        base = generate();
	    identify(base);
	    delete base;    
    }
    catch (std::bad_alloc const &e)
    {
        std::cerr << "bad alloc" << std::endl;
    }
}