#include <iostream>
#include <vector>
#include <string>

#include "Categorie.h"

Categorie::Categorie(Categorie const * const parente) :
	m_nom{""},
	m_parent{parente}
{
}


std::string Categorie::getNom() const
{
	return m_nom;
}

void Categorie::setNom(const std::string& nom)
{
	m_nom = nom;
}

Categorie const * const Categorie::getCategorieParente() const
{
	return m_parent;
}

void Categorie::ajouterNote(const Note& note)
{
	m_notes.push_back(note);
}

std::ostream& operator<<(std::ostream& os, const Categorie& c)
{
	os << c.m_nom << "\n";
	for (const Note& n : c.m_notes) {
		os << n << "\n";
	}
	return os;
}
