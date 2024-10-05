#include <string>

#include "Photo.h"

Photo::Photo(const std::string& description) :
	description{description}
{
}

const std::string& Photo::getTitre() const
{
	return description;
}
