
/************************************
	Constructeur par d�faut
*************************************
Entr�e		: Rien
N�cessit�	: N�ant
Sortie		: Rien
Entra�ne	: (L'objet en cours est initialis�)
*************************************/
template <class MType>
Cmatrice<MType>::Cmatrice()
{
	uiMATnombreLignes = 0;
	uiMATnombreColonnes = 0;
	ppMTPMATmatrice = NULL;
}


/************************************
	Constructeur de confort
*************************************
Entr�e		: Nombre de lignes de la matrice,
				Nombre de colonnes de la matrice,
				Tableau d'�l�ments pour initialiser la matrice
N�cessit�	: (Les dimensions pass�es en param�tre correspondent aux dimensions du tableau)
Sortie		: Rien
Entra�ne	: (L'objet en cours est initialis� � partir des dimensions et du tableau pass� en param�tre)
*************************************/
template <class MType>
Cmatrice <MType>::Cmatrice(unsigned int uiNombreLignes, unsigned int uiNombreColonnes, MType ** ppMTPtableau)
{
	uiMATnombreLignes = uiNombreLignes;
	uiMATnombreColonnes = uiNombreColonnes;

	//Allocation tableau 2 dimensions
	ppMTPMATmatrice = new MType*[uiMATnombreLignes];
	for (unsigned int uiBoucle = 0; uiBoucle < uiMATnombreLignes; uiBoucle++)
		ppMTPMATmatrice[uiBoucle] = new MType[uiMATnombreColonnes];

	for (unsigned int uiBoucleLignes = 0; uiBoucleLignes < uiMATnombreLignes; uiBoucleLignes++)
		for (unsigned int uiBoucleColonnes = 0; uiBoucleColonnes < uiMATnombreColonnes; uiBoucleColonnes++)
			ppMTPMATmatrice[uiBoucleLignes][uiBoucleColonnes] = ppMTPtableau[uiBoucleLignes][uiBoucleColonnes];
}

/************************************
	Constructeur de recopie
*************************************
Entr�e		: Objet Cmatrice � recopier
N�cessit�	: N�ant
Sortie		: Rien
Entra�ne	: (L'objet en cours est initialis�)
*************************************/
template <class MType>
Cmatrice<MType>::Cmatrice(Cmatrice<MType> & MATparam)
{
	uiMATnombreLignes = MATparam.uiMATnombreLignes;
	uiMATnombreColonnes = MATparam.uiMATnombreColonnes;

	if (MATparam.ppMTPMATmatrice == NULL)
		ppMTPMATmatrice = NULL;
	else
	{
		ppMTPMATmatrice = new MType*[uiMATnombreLignes];
		for (unsigned int uiBoucle = 0; uiBoucle < uiMATnombreLignes; uiBoucle++)
			ppMTPMATmatrice[uiBoucle] = new MType[uiMATnombreColonnes];

		for (unsigned int uiBoucleLignes = 0; uiBoucleLignes < uiMATnombreLignes; uiBoucleLignes++)
			for (unsigned int uiBoucleColonnes = 0; uiBoucleColonnes < uiMATnombreColonnes; uiBoucleColonnes++)
				ppMTPMATmatrice[uiBoucleLignes][uiBoucleColonnes] = MATparam.ppMTPMATmatrice[uiBoucleLignes][uiBoucleColonnes];
	}
}


/************************************
	Destructeur
*************************************
Entr�e		: Rien
N�cessit�	: N�ant
Sortie		: Rien
Entra�ne	: (L'objet en cours est d�truit)
			ET (La m�moire allou�e � l'objet en cours est lib�r�e)
*************************************/
template <class MType>
Cmatrice<MType>::~Cmatrice()
{
	for (unsigned int uiBoucleLignes = 0; uiBoucleLignes < uiMATnombreLignes; uiBoucleLignes++)
		delete [] ppMTPMATmatrice[uiBoucleLignes];
	delete [] ppMTPMATmatrice;
}


/************************************
	Lecteur d'�l�ment de matrice
*************************************
Entr�e		: Indice de ligne de l'�l�ment,
				Indice de colonne de l'�l�ment
N�cessit�	: N�ant
Sortie		: L'�l�ment de la matrice correspondant aux indices sp�cifi�s
Entra�ne	: (L'�l�ment souhait� est retourn�)
			OU (Une exception est lev�e en cas d'indice(s) incorrect(s))
*************************************/
template <class MType>
MType Cmatrice<MType>::MATgetElement(unsigned int uiIndiceLigne, unsigned int uiIndiceColonne) const
{
	if (uiIndiceLigne >= uiMATnombreLignes || uiIndiceColonne >= uiMATnombreColonnes)
	{
		Cexception EXCobjet(ERREUR_INDICE_INCORRECT , "Erreur lecture element : Indice(s) incorrect(s)");
		throw EXCobjet;
	}
	else
		return ppMTPMATmatrice[uiIndiceLigne][uiIndiceColonne];
}


/************************************
	Modificateur d'�l�ment de matrice
*************************************
Entr�e		: Indice de ligne de l'�l�ment � modifier,
				Indice de colonne de l'�l�ment � modifier,
				Nouvelle valeur de l'�l�ment
N�cessit�	: N�ant
Sortie		: Rien
Entra�ne	: (L'�l�ment souhait� est modifi� avec la nouvelle valeur)
			OU (Une exception est lev�e en cas d'indice(s) incorrect(s))
*************************************/
template <class MType>
void Cmatrice<MType>::MATsetElement(unsigned int uiIndiceLigne, unsigned int uiIndiceColonne, MType MTPelement)
{
	if (uiIndiceLigne >= uiMATnombreLignes || uiIndiceColonne >= uiMATnombreColonnes)
	{
		Cexception EXCobjet(ERREUR_INDICE_INCORRECT , "Erreur modification element : Indice(s) incorrect(s)");
		throw EXCobjet;
	}
	else
		ppMTPMATmatrice[uiIndiceLigne][uiIndiceColonne] = MTPelement;
}


/************************************
	Transposition de matrice
*************************************
Entr�e		: Rien
N�cessit�	: N�ant
Sortie		: Nouvelle Cmatrice, transpos�e de la Cmatrice courante
Entra�ne	: (L'objet en sortie est cr�� et initialis� par transposition de l'objet courant)
*************************************/
template <class MType>
Cmatrice<MType> Cmatrice<MType>::MATtransposer()
{
	//Tableau 2D temporaire pour stocker les �l�ments transpos�s
	MType ** ppMTPelementsTransposes;

	if (uiMATnombreLignes > 0 && uiMATnombreColonnes > 0)
	{
		//Allocation du tableau 2D utilis� pour initialis� la future matrice
		ppMTPelementsTransposes = new MType*[uiMATnombreColonnes];
		for (unsigned int uiBoucle = 0; uiBoucle < uiMATnombreColonnes; uiBoucle++)
			ppMTPelementsTransposes[uiBoucle] = new MType[uiMATnombreLignes];

		//Transposition des �l�ments de la matrice courante dans le tableau 2D
		for (unsigned int uiBoucleLignes = 0; uiBoucleLignes < uiMATnombreColonnes; uiBoucleLignes++)
			for (unsigned int uiBoucleColonnes = 0; uiBoucleColonnes < uiMATnombreLignes; uiBoucleColonnes++)
				ppMTPelementsTransposes[uiBoucleLignes][uiBoucleColonnes] = ppMTPMATmatrice[uiBoucleColonnes][uiBoucleLignes];

		//Initialisation de la nouvelle matrice, avec indices invers�s et en utilisant le tableau 2D
		Cmatrice<MType> MATmatriceTransposee(uiMATnombreColonnes, uiMATnombreLignes, ppMTPelementsTransposes);
		return MATmatriceTransposee;

		//D�sallocation du tableau 2D temporaire
		for (unsigned int uiBoucleLignes = 0; uiBoucleLignes < uiMATnombreColonnes; uiBoucleLignes++)
			delete [] ppMTPelementsTransposes[uiBoucleLignes];
		delete [] ppMTPelementsTransposes;
	}
	else
	{
		/*Si la matrice courante est vide (Au moins un indice nul), 
		 *on renvoie une matrice vide avec des indices nuls via le constructeur par d�faut*/
		Cmatrice<MType> MATmatriceTransposee;
		return MATmatriceTransposee; 
	}
}


/************************************
	Surcharge op�rateur de sortie standard 
*************************************
Entr�e		: R�f�rence sur le flux de sortie
				Matrice d'�l�ments MType � afficher sur la sortie standard
N�cessit�	: Il doit exister une surcharge de l'op�rateur "<<" pour MType
Sortie		: R�f�rence sur le flux de sortie repr�sentant la matrice
Entra�ne	: (Une repr�sentation de la matrice est affich�e sur la sortie standard)
*************************************/
template <class MType> 
ostream & operator<<(ostream& os, Cmatrice<MType> MATparam)
{
	
	for (unsigned int uiBoucleLignes = 0; uiBoucleLignes < MATparam.MATgetNbrLignes(); uiBoucleLignes++)
	{
		for (unsigned int uiBoucleColonnes = 0; uiBoucleColonnes < MATparam.MATgetNbrColonnes(); uiBoucleColonnes++)
			os << MATparam.MATgetElement(uiBoucleLignes, uiBoucleColonnes) << "\t";
		os << endl;
	}
	return os;
}