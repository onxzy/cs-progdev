#include <iostream>
#include <fstream>

#include "Biscuit.h"
#include "BiscuitFourre.h"

Biscuit& reference()
{
	std::cout << "Instanciation du Biscuit fourré b3 framboise/pistache, diamètre 1cm" << std::endl;
	BiscuitFourre b3{"framboise", "pistache", 1};

	std::cout << "Création de la référence sur le biscuit fourré b3" << std::endl;
	Biscuit& ref_b = b3;

	return ref_b;
}

int main()
{
	std::cout << "Affichage : Biscuit référence sur b3" << std::endl;
	Biscuit& ref = reference();
	std::cout << ref.donnerDescriptionNonVirtual() << "\n"
		  << ref.donnerDescriptionVirtual() << "\n"
		  << std::endl;
}
