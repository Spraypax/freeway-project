//---------------------------------------------------------------------------

#ifndef CameraHedenNoireH
#define CameraHedenNoireH
//---------------------------------------------------------------------------
#include "SNClientTCP.h"

class CameraHedenNoire	{
	private:
	char adresseIP[20];
	unsigned short port;
	char identifiant[30];
	char MotDePasse[30];

	public: CameraHedenNoire();
	bool PrendrePhoto(char* nomFichier);
	void Deplacer(int commande);
};

#endif
