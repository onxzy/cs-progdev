#include <string>

#include "Biscuit.h"

Biscuit::Biscuit(const std::string& gout, int diametre) :
	m_gout{gout},
	m_diametre{diametre}
{}

std::string Biscuit::donnerDescriptionNonVirtual() const {
	if (m_diametre <= 12)
		return "Petit biscuit au goût " + m_gout;
	else if (m_diametre <= 20)
		return "Biscuit moyen au goût " + m_gout;
	else
		return "Grand biscuit au goût " + m_gout;
}

std::string Biscuit::donnerDescriptionVirtual() const {
	if (m_diametre <= 12)
		return "Petit biscuit au goût " + m_gout;
	else if (m_diametre <= 20)
		return "Biscuit moyen au goût " + m_gout;
	else
		return "Grand biscuit au goût " + m_gout;
}
