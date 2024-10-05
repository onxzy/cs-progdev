#ifndef NOTE_H
#define NOTE_H

#include <string>
#include <chrono>
#include <vector>

#include "PieceJointe.h"

class Note
{
private:
	std::string m_titre;
	std::string m_contenu;
	std::chrono::system_clock::time_point m_horodatage;
	std::vector<PieceJointe*> m_piecesjointes;

	auto affichageHorodatage() const;

public:
	Note(const std::string& titre, const std::string& contenu = "");
	const std::chrono::system_clock::time_point& getHorodatage() const;
	std::string getTitre() const;
	void setTitre(const std::string& titre);
	std::string getContenu() const;
	void ajouterContenu(const std::string& texte);
	void viderContenu();
	void ajouterPieceJointe(PieceJointe* pj);

	friend std::ostream& operator<<(std::ostream& os, const Note& n);
};

std::ostream& operator<<(std::ostream& os, const Note& n);

#endif
