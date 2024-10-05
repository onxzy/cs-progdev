#include <iostream> // entrées-sorties
#include <string> // manipulation des chaînes de caractères
#include <chrono> // manipulation des dates et heures
#include <iomanip> // affichage des dates et heures
#include <ctime> // affichage des dates et heures

#include "Note.h" // si vous avez appelé votre fichier différemment, changez cet include !
#include "Categorie.h"
#include "PieceJointe.h"
#include "Email.h"
#include "Photo.h"

/*
 * Cette fonction vous permet d'afficher des dates et heures au format
 * "16/03/2021 09:45:00" en faisant "std::cout << horodatage" où horodatage
 * est du type time_point.
 * Vous n'avez pas besoin de comprendre précisément comment elle fonctionne mais
 * si vous êtes curieux : https://en.cppreference.com/w/cpp/io/manip/put_time.
 *
 * Pour pouvoir utiliser cette fonction, vous aurez sans doute besoin de la
 * déplacer dans votre classe Note.
 */
auto affichageHorodatage(const std::chrono::system_clock::time_point& horodatage) {
	std::time_t t = std::chrono::system_clock::to_time_t(horodatage);
	return std::put_time(std::localtime(&t), "%F %T");
}

int main()
{
	/***** Exemple d'utilisation des dates et heures *****/
	/* Voici comment connaître la date et heure courante.
	 * Le type exact de time_point dépend de votre système d'exploitation et
	 * de la précision de votre horloge. N'oubliez pas que vous pouvez
	 * utiliser auto ou des alias de type, ou encore using namespace, pour
	 * raccourcir un peu la taille des types.
	 */
	std::chrono::system_clock::time_point maintenant = std::chrono::system_clock::now();

	// affichage avec la fonction définie plus haut
	std::cout << affichageHorodatage(maintenant) << std::endl;


	/***** Tests ******/
	/* Les tests ci-dessous vous indiquent ce qui devrait fonctionner, vous
	 * pouvez les décommenter au fur et à mesure. Vous pouvez bien sûr aussi
	 * en ajouter. Notez que l'on utilise #if 0, #endif pour commenter des
	 * portions de tests. Cette manière de faire permet de distinguer les
	 * commentaires "de documentation" des commentaires "de désactivation".
	 * Vous ne pouvez pas imbriquer les commentaires "slash-étoile" les uns
	 * dans les autres, par contre, à l'intérieur de bloc #if, ils ne posent
	 * pas de soucis. */

	// Q2.
	/*
	 * Au début de la question 2, aucun constructeur spécial n'a été
	 * définie, le constructeur par défaut devrait donc être disponible.
	 * Vous devrez changer cette ligne par la suite.
	 */

	Note n1{"Liste de courses"};
	if (n1.getTitre() != std::string("Liste de courses"))
		std::cerr << "Soit setTitre(), soit getTitre() ne fonctionne pas" << std::endl;
	std::cout << n1.getTitre() << std::endl;

	n1.ajouterContenu("Poireaux\n"); // \n : retour à la ligne
	n1.ajouterContenu("Patates\n");
	n1.viderContenu();
	n1.ajouterContenu("Patates\n");
	std::cout << n1.getContenu() << std::endl;
	if (n1.getContenu() != std::string("Patates\n"))
		std::cerr << "ajouterContenu(), viderContenu() ou getContenu() ne fonctionne pas" << std::endl;


	// Q3.
	/*
	 * Vous disposez maintenant d'un constructeur approprié.
	 * Notez au passage comment en C++, on peut facilement découper une
	 * chaîne de caractères en plusieurs portions pour la faire tenir sur
	 * plusieurs lignes : le compilateur rassemble automatiquement les
	 * chaînes juxtaposées (il faut faire attention aux espaces à la fin des
	 * lignes par contre).
	 */
	Note n2{"Journal de bord du capitaine",
		"Starfleet Command nous a ordonné d'explorer les abords de la "
		"zone neutre à la recherche de preuves d'activité de sabotage "
		"organisés par les Romuliens."};
	if (n2.getTitre() != "Journal de bord du capitaine")
		std::cerr << "Le constructeur n'a pas l'air au point" << std::endl;

	// Q4.
	/*
	 * Utilisez l'opérateur d'affichage nouvellement définie. Il doit
	 * permettre une syntaxe pratique comme ci-dessous. Faites bien
	 * attention aux types des arguments et de retour.
	 */
	std::cout << "Note n1\n" << n1 << "\n"
		  << "Note n2\n" << n2 << std::endl;

	// Et la suite ? Les tests vous donneraient un peu trop d'indices
	// concernant les questions où l'on vous demande les types les plus
	// appropriés pour les attributs et méthodes, vous devrez donc vous
	// inspirer des tests ci-dessus pour écrire les vôtres pour les classes
	// Categorie et PieceJointe.
	//

	Categorie c;
	c.setNom("Catégorie 1");
	std::cout << c.getNom() << std::endl;


	Categorie racine;
	racine.setNom("Catégorie racine");

	Categorie fille{&racine};
	fille.setNom("Fille");

	Categorie petiteFille{&fille};
	petiteFille.setNom("Petite-fille");

	std::cout << petiteFille.getCategorieParente()->getNom() << std::endl;

	c.ajouterNote(n1);
	c.ajouterNote(n2);
	std::cout << c << std::endl;


	Email e{"Re: mouvement de Romuliens",
		"<jeanluc.picard@federation.terre>",
		"CLASSIFIED"};
	n2.ajouterPieceJointe(&e);

	std::cout << n2 << std::endl;
}

