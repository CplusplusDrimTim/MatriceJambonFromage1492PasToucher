#pragma once
#include "Cexception.h"
#include <string.h>
#include <iostream>
#include <fstream>
using namespace std;


#ifndef CMATRICE_H
#define CMATRICE_H

#define ERREUR_INDICE_INCORRECT 100
#define ERREUR_DIMENSIONS_INCORRECTES 101
#define ERREUR_DIVISION_PAR_ZERO 102
#define ERREUR_OUVERTURE_FICHIER 103
#define ERREUR_FORMAT_FICHIER 104


/************************************
Template de manipulation de matrices

Auteurs	: Aurèle LUCIANI - Benjamin POUVREAU
Version	: 1.0	04/2017
*************************************/
template <class MType> class Cmatrice
{
private:
	unsigned int uiMATnombreLignes;
	unsigned int uiMATnombreColonnes;
	MType ** ppMTPMATmatrice;

public:
	//Constructeurs et destructeur
	Cmatrice();
	Cmatrice(unsigned int uiNombreLignes, unsigned int uiNombreColonnes, MType ** ppMTPtableau);
	Cmatrice(unsigned int uiNombreLignes, unsigned int uiNombreColonnes);
	Cmatrice(Cmatrice<MType> & MATparam);
	~Cmatrice(void);

	//Accesseurs
	unsigned int MATgetNbrLignes() const
		{ return uiMATnombreLignes; }
	unsigned int MATgetNbrColonnes() const
		{ return uiMATnombreColonnes; }

	MType MATgetElement(unsigned int uiIndiceLigne, unsigned int uiIndiceColonne) const;
	void MATsetElement(unsigned int uiIndiceLigne, unsigned int uiIndiceColonne, MType MTPelement);

	//Méthode
	Cmatrice<MType> MATtransposer();

	//Surcharges d'opérateurs
	template <class ConstantType> Cmatrice<MType> operator*(ConstantType CTPconstante);
	template <class ConstantType> Cmatrice<MType> operator/(ConstantType CTPconstante);

	Cmatrice<MType> operator+(Cmatrice<MType> MATparam);
	Cmatrice<MType> operator-(Cmatrice<MType> MATparam);
	Cmatrice<MType> operator*(Cmatrice<MType> MATparam);
	Cmatrice<MType> & operator=(Cmatrice<MType> MATparam);

	
};

//Surcharges d'opérateurs
template <class MType, class ConstantType> Cmatrice<MType> operator*(ConstantType CTPconstante,Cmatrice<MType> MATparam);
template <class MType> ostream & operator<<(ostream& os, Cmatrice<MType> MATparam);

//Parser
Cmatrice<double> lireMatrice(const char * nomFichier);

#include "Cmatrice.cpp"

#endif //CMATRICE_H
