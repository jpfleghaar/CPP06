/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpflegha <jpflegha@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/14 14:50:02 by Jpflegha          #+#    #+#             */
/*   Updated: 2026/06/14 15:25:59 by Jpflegha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Base.hpp"
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"
#include <iostream>
#include <cstdlib>   // rand, srand
#include <ctime>     // time
#include <exception> // std::exception (NOT <typeinfo>, which is forbidden)

Base *generrateClass()
{
    switch(std::rand() % 3)
    {
        case 0:
            return(new A());
        case 1:
            return(new B());
        default:
            return(new C());
    }
}

void identify(Base *p)
{
    if(dynamic_cast<A *>(p))
        std::cout << "A is our object";
    else if(dynamic_cast<B *>(p))
        std::cout << "B is our object";
    else if(dynamic_cast<C *>(p))
        std::cout << "C is our object";
    else
        std::cout << "it is not A,B or C";
}

void identify(Base &p)
{
    try
    {
        std::cout << "first try ... ";
        (void)dynamic_cast<A &>(p);
        std::cout << "A is the reference" << std::endl;
        return;
    }
    catch(std::exception &) {}

    try
    {
        std::cout << "second try ... ";
        (void)dynamic_cast<B &>(p);
        std::cout << "B is the reference" << std::endl;
        return;
    }
    catch(std::exception &) {}

    try
    {        
        std::cout << "thirt try ... ";
        (void)dynamic_cast<C &>(p);
        std::cout << "C is the reference" << std::endl;
        return;
    }
    catch(std::exception &) {}

    std::cout << "it is not A,B or C" << std::endl;
}

int main()
{
    std::srand(static_cast<unsigned int>(std::time(NULL)));

    for(int i = 0; i < 6; i++)
    {
        Base *p = generrateClass();

        std::cout << "object: " << i << " by pointer: ";
        identify(p);

        std::cout << " by reference: ";
        identify(*p);

        delete p;
    }
    return(0);
}