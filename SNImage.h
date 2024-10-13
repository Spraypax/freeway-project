#ifndef SNIMAGEH
#define SNIMAGEH
#include <windows.h>
#include <stdio.h>
#include <math.h>
#include <iostream>
#include <fstream>
#include <string>

//VERSION POUR BMP4 Taille entête 0x8A généré par ImageMagic (au lieu de 0x36 généré par paint 24 bits)

using namespace std;

typedef struct {unsigned char bleu;unsigned char vert;unsigned char rouge;} Pixel;
typedef struct {int ligne; int colonne;} Coordonnee;

class SNImage
{   private:
		unsigned long dimensionMax;
		unsigned long tailleFichier,debutImage;
		unsigned long tailleImage,tailleEntete,zero,format,resoLarg,resoHaut;
    	void TracerCercleUnPixel(Coordonnee centre,int rayon,Pixel couleur);
		inline void TracerCercleUnPixel(int centreX,int centreY,int rayon,int couleur){TracerCercleUnPixel(IntVersCoordonnee(centreX,centreY),rayon,IntVersPixel(couleur));}
		void TracerDiagonaleUnPixel(Coordonnee debut,Coordonnee fin, Pixel couleur);
		inline void TracerDiagonaleUnPixel(int debutX,int debutY,int finX,int finY,int couleur){TracerDiagonaleUnPixel(IntVersCoordonnee(debutX,debutY),IntVersCoordonnee(finX,finY),IntVersPixel(couleur));}
		void ChangerCouleurSegment(Coordonnee coord,int taille,int epaisseur,Pixel couleur,char segment);//segment='a' 'b' 'c' 'd' 'e' 'f'
		inline void ChangerCouleurSegment(int x,int y,int taille,int epaisseur,int couleur,char segment){ChangerCouleurSegment(IntVersCoordonnee(x,y),taille,epaisseur,IntVersPixel(couleur),segment);}
		inline Pixel IntVersPixel(int couleur){Pixel p; p.bleu=(couleur>>16)&0xff; p.vert=(couleur>>8)&0xff; p.rouge=couleur&0xff; return p;}
		inline Coordonnee IntVersCoordonnee(int x,int y){Coordonnee c; c.ligne=y; c.colonne=x; return c;}
	protected:
		unsigned short signature;
		unsigned long largeur,hauteur;
		inline int Arrondi(float nb){int intnb=nb; if((nb-intnb)>=0.5) intnb++; return intnb;}
	public:
		Pixel **image;
		SNImage();
		~SNImage();
		inline unsigned short Signature(){return signature;}
		inline unsigned long Largeur(){return largeur;}
		inline unsigned long Hauteur(){return hauteur;}
		inline unsigned long TailleFichier(){return tailleFichier;}
		inline unsigned long DebutImage(){return debutImage;}
		inline unsigned long TailleImage(){return tailleImage;}
		inline unsigned long TailleEntete(){return tailleEntete;}
		inline unsigned long Format(){return format;}
		inline unsigned long ResolutionLargeur(){return resoLarg;}
		inline unsigned long ResolutionHauteur(){return resoHaut;}
		void Charger(string nomFichier);
		void Sauvegarder(string nomFichier);
		void Tourner90Droite();
		void Tourner90Gauche();
		void Tourner180();
		void Negatif();
		void RetournerHorizontal();
		void RetournerVertical();
		void NiveauDeGris();
		void Eclaircir(int niveau);
		void Assombrir(int niveau);
		void SeuillerNoirBlanc(int niveau);
		void Colorier(Coordonnee coord,int l,int h,Pixel couleur);
		inline void Colorier(int x,int y,int l,int h,int couleur){Colorier(IntVersCoordonnee(x,y),l,h,IntVersPixel(couleur));}
		void Detourer(int largeurGauche,int largeurDroite,int largeurHaut,int largeurBas,Pixel couleur);
		inline void Detourer(int largeurGauche,int largeurDroite,int largeurHaut,int largeurBas,int couleur){Detourer(largeurGauche,largeurDroite,largeurHaut,largeurBas,IntVersPixel(couleur));}
		void Recadrer(Coordonnee coord,int l,int h);
		inline void Recadrer(int x,int y,int l,int h){Recadrer(IntVersCoordonnee(x,y),l,h);}
		Coordonnee RechercherZone(int l,int h,Pixel couleur);
		Coordonnee RechercherZoneDiagonale(int l,int h,Pixel couleur);
		inline Coordonnee RechercherZone(int l,int h,int couleur){return RechercherZone(l,h,IntVersPixel(couleur));}
		void DessinerCroix(Coordonnee coord,int taille,int epaisseur,Pixel couleur);
		inline void DessinerCroix(int x,int y,int taille,int epaisseur,int couleur){DessinerCroix(IntVersCoordonnee(x,y),taille,epaisseur,IntVersPixel(couleur));}
		void DessinerCarre(Coordonnee coord,int taille,int epaisseur,Pixel couleur);
		inline void DessinerCarre(int x,int y,int taille,int epaisseur,int couleur){DessinerCarre(IntVersCoordonnee(x,y),taille,epaisseur,IntVersPixel(couleur));}
		void Dessiner7Segments(Coordonnee coord,int taille,int epaisseur,Pixel couleur,string message);
		inline void Dessiner7Segments(int x, int y,int taille,int epaisseur,int couleur,string message){Dessiner7Segments(IntVersCoordonnee(x,y),taille,epaisseur,IntVersPixel(couleur),message);}
		void Dessiner11Segments(Coordonnee coord,int taille,int epaisseur,Pixel couleur,string message);
		inline void Dessiner11Segments(int x, int y,int taille,int epaisseur,int couleur,string message){Dessiner11Segments(IntVersCoordonnee(x,y),taille,epaisseur,IntVersPixel(couleur),message);}
		void TracerDiagonale(Coordonnee debut,Coordonnee fin,int epaisseur,Pixel couleur);
		inline void TracerDiagonale(int debutX,int debutY,int finX,int finY,int epaisseur,int couleur){TracerDiagonale(IntVersCoordonnee(debutX,debutY),IntVersCoordonnee(finX,finY),epaisseur,IntVersPixel(couleur));}
		void TracerCercle(Coordonnee centre,int rayon,int epaisseur,Pixel couleur);
		inline void TracerCercle(int centreX,int centreY,int rayon,int epaisseur,int couleur){TracerCercle(IntVersCoordonnee(centreX,centreY),rayon,epaisseur,IntVersPixel(couleur));}
		void AfficherImageEnCaracteres(int niveau);
		void AfficherImageEnCaracteres4Seuils();
		void AfficherImageEnCaracteres10caracteres(char caracteres[11]);
		//0 pour le noir 10 pour le blanc : "#X*+x-:,. "
		void AfficherTexteAvecImage(string texte, int pourcent);
		void AfficherTexteAvecImageFichier(char nomFichierTxt[20], int pourcent);
		void Histogrammes();  //nécessite histogrammeBleu.bmp histogrammeVert.bmp histogrammeRouge.bmp 256x256pixels
		//void Histogrammes(bool horsZero);  //nécessite histogrammeBleu.bmp histogrammeVert.bmp histogrammeRouge.bmp 256x256pixels
		void DissimulerTexte(char texte[]);
		string ExtraireTexte();
		int SeuillerNoirBlancMoyen();
		bool SeuillagePourcentNoir(int pourcent);// return true si seuillage possible
		void DessinerCroixEtCoordonnees(Coordonnee coord,int tailleCroix,int epCroix,int tailleTexte,int epTexte,Pixel couleur,bool droite);
		inline void DessinerCroixEtCoordonnees(int x,int y,int tailleCroix,int epCroix,int tailleTexte,int epTexte,int couleur,bool droite){DessinerCroixEtCoordonnees(IntVersCoordonnee(x,y),tailleCroix,epCroix,tailleTexte,epTexte,IntVersPixel(couleur),droite);}
		void Dessiner36Segments(Coordonnee coord,int taille,int epaisseur,Pixel couleur,string message);
		inline void Dessiner36Segments(int x,int y,int taille,int epaisseur,int couleur,string message){Dessiner36Segments(IntVersCoordonnee(x,y),taille,epaisseur,IntVersPixel(couleur),message);}
		Coordonnee RechercherZone(int l,int h,int bleu,int vert,int rouge, float pourcentErreur);
		Coordonnee RechercherZoneLaPlusProche(int l,int h,Pixel couleur);
		Coordonnee RechercherZoneLaPlusProche(int l,int h,int bleu,int vert,int rouge, float pourcentErreur);
		Coordonnee RechercherIlot(Coordonnee depart,int largeurContour, Pixel couleurContour, Pixel couleurcentre);

};
#endif



