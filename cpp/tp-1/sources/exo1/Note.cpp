#include <string>
#include <chrono>
#include <iostream>
#include <iomanip> // affichage des dates et heures
#include <ctime> // affichage des dates et heures

#include "Note.h"
#include "Photo.h"
#include "Email.h"

Note::Note() : horodatage(std::chrono::system_clock::now()) {}

Note::Note(const std::string& titre, const std::string& contenu)
  : titre(titre), contenu(contenu) {
  Note();
}

std::string Note::getTitre() const {
  return this->titre;
}
void Note::setTitre(const std::string& titre) {
  this->titre = titre;
}

std::string Note::getContenu() const {
  return this->contenu;
}
void Note::ajouterContenu(const std::string& nouveauContenu) {
  // this->contenu.append(nouveauContenu);
  this->contenu += nouveauContenu;
}
void Note::viderContenu() {
  this->contenu.clear();
}

void Note::ajouterPieceJointe(PieceJointe* pj) {
  this->piecesJointes.push_back(pj);
}

void Note::ajouterPhoto(Photo &p) {
  // TODO: why public: PieceJointe in Photo.h
  this->piecesJointes.push_back(new Photo{p});
}
void Note::ajouterEmail(Email &e) {
  this->piecesJointes.push_back(new Email{e});
}

const std::chrono::system_clock::time_point& Note::getHorodatage() const {
  return horodatage;
}

auto affichageHorodatage(const std::chrono::system_clock::time_point& horodatage) {
	std::time_t t = std::chrono::system_clock::to_time_t(horodatage);
	return std::put_time(std::localtime(&t), "%F %T");
}

std::ostream& operator<<(std::ostream& os, const Note& note) {
  return os
    << note.getTitre() << " [" << affichageHorodatage(note.getHorodatage()) << "]" << std::endl 
    << "---------------------" << std::endl 
    << note.getContenu() << std::endl;
}

Note::~Note() {
  for (PieceJointe * const pj: this->piecesJointes) {
    delete pj;
  }
}
