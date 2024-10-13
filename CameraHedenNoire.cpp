//---------------------------------------------------------------------------

#pragma hdrstop

#include "CameraHedenNoire.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#include <fstream>
#include <iostream>
#include <stdio.h>
#include "SNClientTCP.h"

CameraHedenNoire::CameraHedenNoire()

{ strcpy(adresseIP,"172.20.10.3");
  port=8899;
}

bool CameraHedenNoire::PrendrePhoto(char* nomFichier)
{	char donnees[1500];
	int nbOctetsLus;
	char trame[1500] ="GET /api/v1/snap.cgi?chn=0 HTTP/1.1\r\nHost: 172.20.10.3:8899\r\nConnection: keep-alive\r\nCache-Control: max-age=0\r\nUpgrade-Insecure-Requests: 1\r\nUser-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/97.0.4692.99 Safari/537.36\r\nAccept: text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.9\r\nAccept-Encoding: gzip, deflate\r\nAccept-Language: fr-FR,fr;q=0.9,en-US;q=0.8,en;q=0.7\r\n\r\n";
	ofstream FichierBrute;
	SNClientTCP monClient;
	monClient.SeConnecterAUnServeur("172.20.10.3",8899);
	monClient.Envoyer(trame,strlen(trame));
	FichierBrute.open("photo.brute",ios_base::binary);

	do{
		nbOctetsLus=monClient.Recevoir(donnees, 1500);
		FichierBrute.write(donnees, nbOctetsLus);
	}
	while (nbOctetsLus>0);
	FichierBrute.close();
	monClient.SeDeconnecter();

   //réécrire-----------------

   ifstream FichierLecture;
   FichierLecture.open("photo.brute",ios_base::binary);
   ofstream FichierEcriture;
   FichierEcriture.open(nomFichier,ios_base::binary);
   unsigned char octetLu;
   bool copie=false;
	do
	{
		octetLu=FichierLecture.get();

	if (octetLu==0xFF) {
		copie=true;
		}

	else;
	if (copie==true){
	FichierEcriture.put(octetLu);
		}
	}

	while(FichierLecture.eof()==0);
	FichierLecture.close();
	FichierEcriture.close();

	return 0;
}
