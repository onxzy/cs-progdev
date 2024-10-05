#ifndef PIECEJOINTE_H
#define PIECEJOINTE_H

class PieceJointe
{
private:

public:
	virtual const std::string& getTitre() const = 0;
	virtual ~PieceJointe() = default;
};

#endif /* PIECEJOINTE_H */
