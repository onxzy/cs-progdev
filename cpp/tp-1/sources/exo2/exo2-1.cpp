#include <iostream>
#include <fstream>

#include "Biscuit.h"
#include "BiscuitFourre.h"

int main()
{
	std::cout << "Affichage 1 : Biscuit b à la fraise, diamètre 10cm" << std::endl;
	Biscuit b{"fraise", 10};
	std::cout << b.donnerDescriptionVirtual() << "\n" << std::endl;

	std::cout << "Affichage 2 : Biscuit fourré b2 vanille/chocolat, diamètre 16cm" << std::endl;
	BiscuitFourre b2{"vanille", "chocolat", 16};
	std::cout << b2.donnerDescriptionVirtual() << "\n" << std::endl;

	std::cout << "Affichage 3 : Biscuit fourré b3 framboise/pistache, diamètre 28cm" << std::endl;
	BiscuitFourre b3{"framboise", "pistache", 28};
	std::cout << b3.donnerDescriptionNonVirtual() << "\n"
		  << b3.donnerDescriptionVirtual() << "\n"
		  << std::endl;

	std::cout << "Affichage 4 : Biscuit référence sur b3" << std::endl;
	Biscuit& ref_b = b3;
	std::cout << ref_b.donnerDescriptionNonVirtual() << "\n"
		  << ref_b.donnerDescriptionVirtual() << "\n"
		  << std::endl;

	std::cout << "Affichage 5 : Biscuit pointeur sur b3" << std::endl;
	Biscuit* ptr_b = &b3;
	std::cout << ptr_b->donnerDescriptionNonVirtual() << "\n"
		  << ptr_b->donnerDescriptionVirtual() << "\n"
		  << std::endl;

	std::cout << "Affichage 6 : Biscuit b4 initialisé à partir de b3" << std::endl;
	Biscuit b4 = b3;
	std::cout << b4.donnerDescriptionNonVirtual() << "\n"
		  << b4.donnerDescriptionVirtual() << "\n"
		  << std::endl;
}
