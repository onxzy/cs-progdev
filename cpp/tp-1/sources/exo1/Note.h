#ifndef NOTE_H
#define NOTE_H

#include <string>
#include <chrono>
#include <iostream>
#include <vector>

#include "PieceJointe.h"
#include "Photo.h"
#include "Email.h"

class Note {
  private:
    std::string titre;
    std::string contenu;
    std::chrono::system_clock::time_point horodatage;
    std::vector<PieceJointe*> piecesJointes;
    
  public:
    Note();
    Note(const std::string& titre, const std::string& contenu);
    ~Note();

    std::string getTitre() const;
    void setTitre(const std::string& titre);

    std::string getContenu() const;
    void ajouterContenu(const std::string& nouveauContenu);
    void viderContenu();

    void ajouterPieceJointe(PieceJointe* pj);
    void ajouterPhoto(Photo &p);
    void ajouterEmail(Email &e);
    std::vector<PieceJointe*>::const_iterator pjBegin() const;
    std::vector<PieceJointe*>::const_iterator pjEnd() const;

    const std::chrono::system_clock::time_point& getHorodatage() const;
    friend std::ostream& operator<<(std::ostream& os, const Note& note);
};

#endif
