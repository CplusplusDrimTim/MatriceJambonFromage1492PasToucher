#include "Cexception.h"


/************************************
	Constructeur par d�faut
*************************************
Entr�e		: Rien
N�cessit�	: N�ant
Sortie		: Rien
Entra�ne	: (L'objet en cours est initialis�)
*************************************/
Cexception::Cexception()
{
	pcEXCMessage = NULL;
}


/************************************
	Constructeur � deux arguments
*************************************
Entr�e		: La valeur de l'erreur et un message d'erreur
N�cessit�	: N�ant
Sortie		: Rien
Entra�ne	: (L'objet en cours est initialis� par copie des param�tres)
*************************************/
Cexception::Cexception(unsigned int Valeur, const char * Message)
{
	uiEXCValeur = Valeur;
	pcEXCMessage = _strdup(Message);
}


/************************************
	Constructeur de recopie
*************************************
Entr�e		: L'objet Cexception � recopier
N�cessit�	: N�ant
Sortie		: Rien
Entra�ne	: (L'objet en cours est initialis� par copie du param�tre)
*************************************/
Cexception::Cexception(Cexception & EXCParam)
{
	uiEXCValeur = EXCParam.uiEXCValeur;
	if (EXCParam.pcEXCMessage != NULL)
		pcEXCMessage = _strdup(EXCParam.pcEXCMessage);
	else
		pcEXCMessage = NULL;
}


/************************************
	Destructeur
*************************************/
Cexception::~Cexception()
{
	if (pcEXCMessage != NULL)
		delete pcEXCMessage;
}


/************************************
	Surcharge de l'op�rateur d'affectation
*************************************
Entr�e		: L'objet Cexception � copier
N�cessit�	: N�ant
Sortie		: L'objet � modifier, modifi� par copie de l'objet d'entr�e
Entra�ne	: (L'objet en cours est modifi� par copie du contenu du param�tre)
*************************************/
Cexception & Cexception::operator=(Cexception EXCParam)
{
	uiEXCValeur = EXCParam.uiEXCValeur;

	if (pcEXCMessage != NULL)
		delete pcEXCMessage;
	if (EXCParam.pcEXCMessage != NULL)
		pcEXCMessage = _strdup(EXCParam.pcEXCMessage);
	else
		pcEXCMessage = NULL;

	return *this; 
}

