#include <string>

#include "Biscuit.h"

/**
 * Représente un biscuit fourré, un biscuit particulier coupé en deux dans son
 * épaisseur et garni d'une mousse, une crème, etc.
 */
class BiscuitFourre : public Biscuit {
protected:
	/**
	 * Le parfum du fourrage
	 */
	std::string m_fourrage;

public:
	/**
	 * Constructeur de BiscuitFourre
	 *
	 * @param gout le goût du biscuit
	 * @param fourrage le goût du fourrage
	 * @param diametre le diamètre du biscuit
	 */
	BiscuitFourre(const std::string& gout, const std::string& fourrage, int diametre);

	/**
	 * Constructeur par recopie
	 *
	 * @param autreBiscuit le biscuit à copier
	 */
	BiscuitFourre(const BiscuitFourre& autreBiscuit) = default;

	/**
	 * Destructeur
	 */
	virtual ~BiscuitFourre() = default;

	/**
	 * Redéfinition de l'affichage générique du biscuit
	 *
	 * @return Représentation textuelle du biscuit
	 */
	std::string donnerDescriptionNonVirtual() const;

	/**
	 * Redéfinition de l'affichage personnalisé du biscuit
	 *
	 * @return Représentation textuelle du biscuit
	 */
	std::string donnerDescriptionVirtual() const override;
};
