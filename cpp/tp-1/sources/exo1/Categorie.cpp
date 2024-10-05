#include <string>

#include "Categorie.h"

Categorie::Categorie() {}

Categorie::Categorie(const std::string& nom, Categorie * const categorieParente) 
  : nom(nom), categorieParente(categorieParente) {
  Categorie();
}

void Categorie::setNom(const std::string& nom) {
  this->nom = nom;
}

std::string Categorie::getNom() const {
  return this->nom;
}

Categorie& Categorie::getCategorieParente() const {
  return *this->categorieParente;
}

void Categorie::ajouterNote(const Note& note) {
  if (this->notes.size() >= Categorie::MAX_NOTES)
    throw new TooManyNotes();
  this->notes.push_back(note);
}
void Categorie::retirerNote(int i) {
  this->notes.erase(this->notes.begin() + i);
}
void Categorie::viderNotes() {
  this->notes.clear();
}
// Note& Categorie::getNote(int i) {
//   return this->notes.at(i);
// }
std::vector<Note>::iterator Categorie::begin() {
  return this->notes.begin();
}

std::vector<Note>::iterator Categorie::end() {
  return this->notes.end();
}
std::vector<Note>::const_iterator Categorie::begin() const {
  return this->notes.cbegin();
}

std::vector<Note>::const_iterator Categorie::end() const {
  return this->notes.cend();
}

std::ostream& operator<<(std::ostream& os, const Categorie& categorie) {
  os << categorie.getNom() << std::endl;
  for (auto it = categorie.begin(); it == categorie.end(); it++) {
    os << *it << std::endl;
  }
  // for (const Note& note: categorie) {
  //   os << note << std::endl;
  // }
  return os;
}
