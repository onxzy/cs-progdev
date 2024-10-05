#ifndef BISCUIT_H
#define BISCUIT_H

#include <string>

/**
 * Représente un biscuit, une pâtisserie simple et savoureuse à partager
 *
 * Attention, cette classe ne gère que les biscuits ronds.
 */
class Biscuit {
protected:
	/**
	 * Le parfum du biscuit (fraise, pistache, chocolat, etc.)
	 */
	std::string m_gout;

	/**
	 * Le diamètre du biscuit
	 */
	int m_diametre;

public:
	/**
	 * Constructeur de base
	 *
	 * @param gout Le parfum du biscuit
	 * @param diametre La taille du biscuit
	 */
	Biscuit(const std::string& gout, int diametre);

	/**
	 * Constructeur de copie du biscuit
	 *
	 * On utilise l'implémentation par défaut, qui recopie chaque argument.
	 * Notez qu'on doit obligatoirement mettre cette déclaration même si on
	 * utilise l'implémentation par défaut car la présence d'un autre
	 * constructeur supprime les constructeurs qui seraient générés
	 * automatiquement autrement.
	 *
	 * @param biscuit Le biscuit à recopier
	 */
	Biscuit(const Biscuit& biscuit) = default;

	/**
	 * Destructeur du biscuit
	 *
	 * On définit explicitement le destructeur afin de le rendre virtual,
	 * ce qui est nécessaire pour pouvoir en hériter en toute sécurité (du
	 * point de vue de la libération de la mémoire à la destruction).
	 */
	virtual ~Biscuit() = default;

	/**
	 * Affiche une description alléchante mais générique du biscuit
	 *
	 * @return la description textuelle du biscuit
	 */
	std::string donnerDescriptionNonVirtual() const;

	/**
	 * Affiche une description personnalisable (dans les classes-filles) du
	 * biscuit
	 *
	 * @return la description textuelle personnalisée du biscuit
	 */
	virtual std::string donnerDescriptionVirtual() const;
};

#endif
