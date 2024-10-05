#ifndef CATEGORIE_H
#define CATEGORIE_H

#include <string>
#include <vector>
#include <iostream>
#include <exception>

#include "Note.h"

class TooManyNotes : std::exception {
  public:
    TooManyNotes() {}
    const char* what() const throw() { return "Max Notes exeeded !"; }
};

class Categorie {
  private:
    std::string nom;
    static const int MAX_NOTES = 255;
    Categorie* categorieParente = nullptr;
    std::vector<Note> notes;

  public:
    Categorie();
    Categorie(const std::string& nom, Categorie* const categorieParente = nullptr);

    void setNom(const std::string& nom);
    std::string getNom() const;
    Categorie& getCategorieParente() const;

    void ajouterNote(const Note& note);
    void retirerNote(int i);
    void viderNotes();
    std::vector<Note>::iterator begin();
    std::vector<Note>::iterator end();
    std::vector<Note>::const_iterator begin() const;
    std::vector<Note>::const_iterator end() const;


    friend std::ostream& operator<<(std::ofstream& os, const Categorie& categorie);
};

#endif
