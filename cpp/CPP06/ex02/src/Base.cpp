/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Base.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 14:44:14 by seb               #+#    #+#             */
/*   Updated: 2024/07/20 13:54:30 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Base.hpp"
#include "BaseA.hpp"
#include "BaseB.hpp"
#include "BaseC.hpp"

#include<cstdlib>

Base::~Base()
{
}

Base    *generate(void)
{
    srand((unsigned) time(NULL));
	int tmp = rand() % 3;
    char c;
    c = 'A' + tmp;
    std::cout << "Random generate a Base" << c << std::endl;
    if (tmp == 0)
        return new BaseA();
    if (tmp == 1)
        return new BaseB();
    if (tmp == 2)
        return new BaseC();
    return (NULL);
}

void identify(Base* p)
{
    BaseA* BaseAPtr = dynamic_cast<BaseA*>(p);
    BaseB* BaseBPtr = dynamic_cast<BaseB*>(p);
    BaseC* BaseCPtr = dynamic_cast<BaseC*>(p);
    if (BaseAPtr )
    {
        std::cout << "Base est de type A" << std::endl;
        return ;
    }
    else if (BaseBPtr )
    {
        std::cout << "Base est de type B" << std::endl;
        return ;
    }
    else if (BaseCPtr)
    {
        std::cout << "Base est de type C" << std::endl;
        return ;
    }
    else 
    {
        std::cout << "Base est de type base" << std::endl;
    }
}

void identify(Base &p)
{
    try
    {
        BaseA &BaseAPtr = dynamic_cast<BaseA &>(p);
        (void)BaseAPtr;
        std::cout << "Base est de type A" << std::endl;
    }
    catch (const std::exception& e)
    {
        try
        {
            BaseB &BaseBPtr = dynamic_cast<BaseB &>(p);
            (void)BaseBPtr;

            std::cout << "Base est de type B" << std::endl;
        }
        catch (const std::exception& e)
        {
            try 
            {
                BaseC &BaseCPtr = dynamic_cast<BaseC &>(p);
                (void)BaseCPtr;
                std::cout << "Base est de type C" << std::endl;
            }
            catch (const std::exception& e)
            {
                std::cout << "Base est de type base" << std::endl;
            }
        }
    }
}
