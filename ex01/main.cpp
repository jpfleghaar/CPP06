/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpflegha <jpflegha@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/11 15:52:48 by Jpflegha          #+#    #+#             */
/*   Updated: 2026/06/11 16:23:35 by Jpflegha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Serializer.hpp"
#include <iostream>

// small helper so we can print an object's fields next to its address
static void printObject(const std::string &label, Data *p)
{
	std::cout << label << " (at " << p << ")\n";
	std::cout << "    id    = " << p->id << "\n";
	std::cout << "    name  = " << p->name << "\n";
	std::cout << "    value = " << p->value << "\n";
}

int main()
{
	// --- 1. make an object and take its address ----------------------
	Data original;
	original.id = 42;
	original.name = "TEST";
	original.value = 3.14;

	Data *ptr = &original;

	std::cout << "=== 1. the object and where it lives ===\n";
	printObject("original", ptr);
	std::cout << "\n";

	// --- 2. serialize: pointer -> integer ----------------------------
	uintptr_t raw = Serializer::serialize(ptr);

	std::cout << "=== 2. serialize: the address becomes a plain number ===\n";
	std::cout << "    pointer (shown in hex) : " << ptr << "\n";
	std::cout << "    serialized in decimal  : " << raw << "\n";
	std::cout << "    serialized in hex      : " << std::hex << raw << std::dec << "\n";
	std::cout << "    -> it is the SAME value, just printed in different bases\n\n";

	// --- 3. deserialize: integer -> pointer --------------------------
	Data *back = Serializer::deserialize(raw);

	std::cout << "=== 3. deserialize: the number becomes a pointer again ===\n";
	std::cout << "    recovered pointer      : " << back << "\n";
	std::cout << "    same address as start? : " << (back == ptr ? "yes" : "no") << "\n\n";

	// --- 4. THE INTERESTING PART -------------------------------------
	std::cout << "=== 4. proof it is the same object, not a copy ===\n";
	back->id = 99;
	back->name = "edited through 'back'";
	std::cout << "    we only touched 'back', now we read 'original':\n";
	printObject("original", &original);
	std::cout << "    -> 'original' changed, so 'back' and '&original' are\n";
	std::cout << "       literally the same object in memory.\n\n";

	// --- 5. works for any number of objects, each keeps its address --
	std::cout << "=== 5. different objects -> different numbers ===\n";
	Data a;
	Data b;
	a.id = 1; a.name = "A"; a.value = 1.0;
	b.id = 2; b.name = "B"; b.value = 2.0;

	uintptr_t ra = Serializer::serialize(&a);
	uintptr_t rb = Serializer::serialize(&b);

	std::cout << "    a serialized : " << ra << "\n";
	std::cout << "    b serialized : " << rb << "\n";
	std::cout << "    deserialize(a)->name = " << Serializer::deserialize(ra)->name << "\n";
	std::cout << "    deserialize(b)->name = " << Serializer::deserialize(rb)->name << "\n";

	return 0;
}