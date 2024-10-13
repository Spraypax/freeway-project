#pragma hdrstop
#pragma argsused

#ifdef _WIN32
#include <tchar.h>
#include "CameraHedenNoire.h"
#include "SNClientTCP.h"
#else
  typedef char _TCHAR;
  #define _tmain main
#endif

#include <fstream>
#include <stdio.h>
#include <windows.h>
#include <iostream>
#include "SNImage.h"

	using namespace std;

 int _tmain(int argc, _TCHAR* argv[])
{
	// Tableau contenant les noms des images à traiter
	string nomImage[5] = {"image.jpg"};
	CameraHedenNoire cam;
	const Pixel blanc = {255, 255, 255};
	const Pixel noir = {0, 0, 0};
	const Pixel b = {255, 0, 0};
	const Pixel v = {0, 255, 0};
	const Pixel r = {0, 0, 255};

	cam.PrendrePhoto("image.jpg");
	system(".\\ImageMagick\\magick.exe convert image.jpg -crop 1920x900+0+200 -depth 24 result.bmp");
	SNImage img;
	img.Charger("result.bmp");
	cout<<img.Hauteur()<<" x "<<img.Largeur()<<endl;
	// Chargement de l'image avec la classe SNImage

	//img.Charger("image.bmp");
	// seuillage de l'image
	img.SeuillerNoirBlanc(75);
	// Recherche des coordonnées de la zone supérieure de la plaque
	Coordonnee haut = img.RechercherZone(30, 30, 0);
	// Rotation de l'image de 180 degrés
	img.Tourner180();
	// Recherche des coordonnées de la zone inférieure de la plaque
	Coordonnee bas = img.RechercherZone(30, 30, 0);
	// Rotation de l'image de 180 degrés pour revenir à la position d'origine
	img.Tourner180();
	// Mise à jour des coordonnées pour refléter la position correcte
	bas.ligne = img.Hauteur() - bas.ligne;
	bas.colonne = img.Largeur() - bas.colonne;
	// Calculer la hauteur et la largeur d'une plaque en utilisant les positions des lignes haute et basse
	int hplaq = bas.ligne - haut.ligne;
	int lplaq = 4.2 * hplaq;
	// Dessiner une croix à une position spécifique sur l'image
	img.DessinerCroix(haut.colonne+lplaq,haut.ligne,500,5,0xff);
	// Détourer une partie de l'image, en laissant une marge de 20 colonnes sur la partie droite, en utilisant les coordonnées de la ligne haute et basse ainsi que la largeur calculée de la plaque
	//img.Detourer(bas.colonne+20,img.Largeur()-(haut.colonne+lplaq),haut.ligne+200,img.Hauteur()-bas.ligne+20,0xffffff);
	img.Detourer(300,300,150,150,blanc);


	Coordonnee depart = {0,0};

	Coordonnee c = img.RechercherZoneDiagonale(20, 20, noir );
	cout<< "Haut Gauche : - Ligne : " << c.ligne<<" - Colonne : "<< c.colonne << endl;

	Coordonnee fin_droite = c;
	bool fin_boucle = false;

	// Recherche de la fin de la zone noire à droite en partant de c
	while(!fin_boucle)
	{
		fin_droite.colonne++;
		if(img.image[fin_droite.ligne][fin_droite.colonne].bleu == noir.bleu && img.image[fin_droite.ligne][fin_droite.colonne].vert == noir.vert && img.image[fin_droite.ligne][fin_droite.colonne].rouge == noir.rouge)
		{
			do{
				fin_droite.ligne--;
			}
			while(img.image[fin_droite.ligne][fin_droite.colonne].bleu == noir.bleu && img.image[fin_droite.ligne][fin_droite.colonne].vert == noir.vert && img.image[fin_droite.ligne][fin_droite.colonne].rouge == noir.rouge);
			fin_droite.ligne++;
		}
		else
		{
			fin_droite.ligne++;
			if(img.image[fin_droite.ligne][fin_droite.colonne].bleu == blanc.bleu && img.image[fin_droite.ligne][fin_droite.colonne].vert == blanc.vert && img.image[fin_droite.ligne][fin_droite.colonne].rouge == blanc.rouge)
			{
				fin_boucle = true;
				fin_droite.ligne--;
				fin_droite.colonne--;
			}
		}
	}

	cout<< "Haut Droit : - Ligne : " << fin_droite.ligne<<" - Colonne : "<< fin_droite.colonne << endl;
	// Recherche de la fin de la zone noire en bas en partant du point fin


	Coordonnee fin_droite_colonne = fin_droite;

	bool fin_boucle2 = false;

	while(!fin_boucle2)
	{
		fin_droite_colonne.ligne++;
		if(img.image[fin_droite_colonne.ligne][fin_droite_colonne.colonne].bleu == noir.bleu && img.image[fin_droite_colonne.ligne][fin_droite_colonne.colonne].vert == noir.vert && img.image[fin_droite_colonne.ligne][fin_droite_colonne.colonne].rouge == noir.rouge)
		{
			do{
				fin_droite_colonne.colonne++;
			}
			while(img.image[fin_droite_colonne.ligne][fin_droite_colonne.colonne].bleu == noir.bleu && img.image[fin_droite_colonne.ligne][fin_droite_colonne.colonne].vert == noir.vert && img.image[fin_droite_colonne.ligne][fin_droite_colonne.colonne].rouge == noir.rouge);
			fin_droite_colonne.colonne--;
		}
		else
		{
			fin_droite_colonne.colonne--;
			if(img.image[fin_droite_colonne.ligne][fin_droite_colonne.colonne].bleu == blanc.bleu && img.image[fin_droite_colonne.ligne][fin_droite.colonne].vert == blanc.vert && img.image[fin_droite_colonne.ligne][fin_droite_colonne.colonne].rouge == blanc.rouge)
			{
				fin_boucle2 = true;
				fin_droite_colonne.colonne++;
				fin_droite_colonne.ligne--;
			}
		}
	}

	cout<< "Bas Droit : - Ligne : " << fin_droite_colonne.ligne<<" - Colonne : "<< fin_droite_colonne.colonne << endl;

		Coordonnee fin_gauche_colonne = fin_droite_colonne;
		bool fin_boucle3 = false;

	while(!fin_boucle3)
	{
		fin_gauche_colonne.colonne--;
		if(img.image[fin_gauche_colonne.ligne][fin_gauche_colonne.colonne].bleu == noir.bleu && img.image[fin_gauche_colonne.ligne][fin_gauche_colonne.colonne].vert == noir.vert && img.image[fin_droite.ligne][fin_droite.colonne].rouge == noir.rouge)
		{
			do{
				fin_gauche_colonne.ligne++;
			}
			while(img.image[fin_gauche_colonne.ligne][fin_gauche_colonne.colonne].bleu == noir.bleu && img.image[fin_gauche_colonne.ligne][fin_gauche_colonne.colonne].vert == noir.vert && img.image[fin_gauche_colonne.ligne][fin_gauche_colonne.colonne].rouge == noir.rouge);
			fin_gauche_colonne.ligne--;
		}
		else
		{
			fin_gauche_colonne.ligne--;
			if(img.image[fin_gauche_colonne.ligne][fin_gauche_colonne.colonne].bleu == blanc.bleu && img.image[fin_gauche_colonne.ligne][fin_gauche_colonne.colonne].vert == blanc.vert && img.image[fin_gauche_colonne.ligne][fin_gauche_colonne.colonne].rouge == blanc.rouge)
			{
				fin_boucle3 = true;
				fin_gauche_colonne.ligne++;
				fin_gauche_colonne.colonne--;
			}
		}
	}

	cout<< "Bas Gauche : - Ligne : " << fin_gauche_colonne.ligne<<" - Colonne : "<< fin_gauche_colonne.colonne << endl;

	img.Detourer(c.colonne,1920-fin_droite.colonne,c.ligne,880-fin_droite_colonne.ligne,blanc);


	img.DessinerCroix(c,30,4,b);
	img.DessinerCroix(fin_droite,30,4,v);
	img.DessinerCroix(fin_droite_colonne,30,4,r);
	img.DessinerCroix(fin_gauche_colonne,30,4,r);
	img.Sauvegarder("sortie.bmp");
	system("mspaint sortie.bmp");

//	img.Negatif();
	//system(".\\ImageMagick\\magick.exe convert sortie.bmp result_final.bmp");
	system(".\\Tesseract-OCR\\tesseract.exe sortie.bmp texte -l eng");
//	img.Charger("result_final.bmp");
//	system(".\\Tesseract-OCR\\tesseract.exe result.bmp - --psm 3");
//	system("notepad.exe texte.txt");
	cin.get();
	return 0;
}
