#include <string>

#include "BiscuitFourre.h"
#include "Biscuit.h"

BiscuitFourre::BiscuitFourre(const std::string& gout, const std::string& fourrage, int diametre) :
	Biscuit(gout, diametre),
	m_fourrage{fourrage}
{}

std::string BiscuitFourre::donnerDescriptionNonVirtual() const {
	if (m_diametre <= 12)
		return "Petit biscuit " + m_gout + " fourré au goût " + m_fourrage;
	else if (m_diametre <= 20)
		return "Biscuit moyen " + m_gout + " fourré au goût " + m_fourrage;
	else
		return "Grand biscuit " + m_gout + " fourré au goût " + m_fourrage;
}

std::string BiscuitFourre::donnerDescriptionVirtual() const {
	if (m_diametre <= 12)
		return "Petit biscuit " + m_gout + " fourré au goût " + m_fourrage;
	else if (m_diametre <= 20)
		return "Biscuit moyen " + m_gout + " fourré au goût " + m_fourrage;
	else
		return "Grand biscuit " + m_gout + " fourré au goût " + m_fourrage;
}
