#ifndef PIECEJOINTE_H
#define PIECEJOINTE_H

#include <string>

class PieceJointe {
  private:

  public:
    virtual ~PieceJointe();
    virtual std::string getTitre() const = 0;
};


#endif