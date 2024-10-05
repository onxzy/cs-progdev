#ifndef EMAIL_H
#define EMAIL_H

#include "PieceJointe.h"

class Email : public PieceJointe {
	private:
		std::string sujet;
		std::string destinataire;
		std::string texte;

	public:
		Email(const std::string& titre, const std::string& destinataire, const std::string& texte);
		std::string getTitre() const override;
		const std::string& getDestinataire() const;
		const std::string& getTexte() const;
};

#endif
