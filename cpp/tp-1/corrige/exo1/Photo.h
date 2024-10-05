#ifndef PHOTO_H
#define PHOTO_H

#include <string>

#include "PieceJointe.h"

class Photo : public PieceJointe
{
private:
	std::string description;

public:
	Photo(const std::string& description);
	const std::string& getTitre() const;
};

#endif
