#ifndef CATEGORIE_H
#define CATEGORIE_H

#include <string>
#include <vector>
#include <iostream>

#include "Note.h"

class Categorie
{
private:
	std::string m_nom;
	Categorie const * const m_parent;
	std::vector<Note> m_notes;

public:
	Categorie(Categorie const * const parente = nullptr);
	std::string getNom() const;
	void setNom(const std::string& nom);
	Categorie const * const getCategorieParente() const;
	void ajouterNote(const Note& note);

	friend std::ostream& operator<<(std::ostream& os, const Categorie& c);
};

std::ostream& operator<<(std::ostream& os, const Categorie& c);

#endif
