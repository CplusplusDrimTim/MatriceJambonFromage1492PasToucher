char * positionnerCurseur(char* pcTempString);

/*****************************************************************************************************************************
******************************************************************************************************************************
		Définition des méthodes de Cmatrice
******************************************************************************************************************************
******************************************************************************************************************************/


/************************************
	Constructeur par défaut
*************************************
Entrée		: Rien
Nécessité	: Néant
Sortie		: Rien
Entraîne	: (L'objet en cours est initialisé)
*************************************/
template <class MType>
Cmatrice<MType>::Cmatrice()
{
	uiMATnombreLignes = 0;
	uiMATnombreColonnes = 0;
	ppMTPMATmatrice = NULL;
}


/************************************
	Constructeur de confort 1
*************************************
Entrée		: Nombre de lignes de la matrice,
				Nombre de colonnes de la matrice,
				Tableau d'éléments pour initialiser la matrice
Nécessité	: (Les dimensions passées en paramètre correspondent aux dimensions du tableau)
			ET (Une surcharge de l'opérateur '=' est définie pour MType [MType = MType])
Sortie		: Rien
Entraîne	: (L'objet en cours est initialisé à partir des dimensions et du tableau passé en paramètre)
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

	//Initialisation de la matrice
	for (unsigned int uiBoucleLignes = 0; uiBoucleLignes < uiMATnombreLignes; uiBoucleLignes++)
		for (unsigned int uiBoucleColonnes = 0; uiBoucleColonnes < uiMATnombreColonnes; uiBoucleColonnes++)
			ppMTPMATmatrice[uiBoucleLignes][uiBoucleColonnes] = ppMTPtableau[uiBoucleLignes][uiBoucleColonnes];
}


/************************************
	Constructeur de confort 2
*************************************
Entrée		: Nombre de lignes de la matrice,
				Nombre de colonnes de la matrice
Nécessité	: Rien
Sortie		: Rien
Entraîne	: (L'objet en cours est initialisés en tant que matrice de dimensions spécifiées par l'utilisateur)
Warning		: Les valeurs MType de la matrice ne sons pat initialisées
*************************************/
template <class MType>
Cmatrice<MType>::Cmatrice(unsigned int uiNombreLignes, unsigned int uiNombreColonnes)
{
	uiMATnombreLignes = uiNombreLignes;
	uiMATnombreColonnes = uiNombreColonnes;

	ppMTPMATmatrice = new MType*[uiMATnombreLignes];
	for (unsigned int uiBoucle = 0; uiBoucle < uiMATnombreLignes; uiBoucle++)
		ppMTPMATmatrice[uiBoucle] = new MType[uiMATnombreColonnes];
}


/************************************
	Constructeur de recopie
*************************************
Entrée		: Objet Cmatrice à recopier
Nécessité	: (Une surcharge de l'opérateur '=' est définie pour MType [MType = MType])
Sortie		: Rien
Entraîne	: (L'objet en cours est initialisé)
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
		//Allocation tableau 2D
		ppMTPMATmatrice = new MType*[uiMATnombreLignes];
		for (unsigned int uiBoucle = 0; uiBoucle < uiMATnombreLignes; uiBoucle++)
			ppMTPMATmatrice[uiBoucle] = new MType[uiMATnombreColonnes];

		//Initialisaton matrice
		for (unsigned int uiBoucleLignes = 0; uiBoucleLignes < uiMATnombreLignes; uiBoucleLignes++)
			for (unsigned int uiBoucleColonnes = 0; uiBoucleColonnes < uiMATnombreColonnes; uiBoucleColonnes++)
				ppMTPMATmatrice[uiBoucleLignes][uiBoucleColonnes] = MATparam.ppMTPMATmatrice[uiBoucleLignes][uiBoucleColonnes];
	}
}


/************************************
	Destructeur
*************************************
Entrée		: Rien
Nécessité	: Néant
Sortie		: Rien
Entraîne	: (L'objet en cours est détruit)
			ET (La mémoire allouée à l'objet en cours est libérée)
*************************************/
template <class MType>
Cmatrice<MType>::~Cmatrice()
{
	for (unsigned int uiBoucleLignes = 0; uiBoucleLignes < uiMATnombreLignes; uiBoucleLignes++)
		delete [] ppMTPMATmatrice[uiBoucleLignes];
	delete [] ppMTPMATmatrice;
}


/************************************
	Lecteur d'élément de matrice
*************************************
Entrée		: Indice de ligne de l'élément,
				Indice de colonne de l'élément
Nécessité	: Néant
Sortie		: L'élément de la matrice correspondant aux indices spécifiés
Entraîne	: (L'élément souhaité est retourné)
			OU (Une exception est levée en cas d'indice(s) incorrect(s))
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
	Modificateur d'élément de matrice
*************************************
Entrée		: Indice de ligne de l'élément à modifier,
				Indice de colonne de l'élément à modifier,
				Nouvelle valeur de l'élément
Nécessité	: (Une surcharge de l'opérateur '=' est définie pour MType [MType = MType])
Sortie		: Rien
Entraîne	: (L'élément souhaité est modifié avec la nouvelle valeur)
			OU (Une exception est levée en cas d'indice(s) incorrect(s))
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
Entrée		: Rien
Nécessité	: (Une surcharge de l'opérateur '=' est définie pour MType [MType = MType])
Sortie		: Nouvelle Cmatrice<MType>, transposée de la Cmatrice courante
Entraîne	: (L'objet en sortie est créé et initialisé par transposition de l'objet courant)
*************************************/
template <class MType>
Cmatrice<MType> Cmatrice<MType>::MATtransposer()
{
	//Tableau 2D temporaire pour stocker les éléments transposés
	MType ** ppMTPelementsTransposes;

	if (uiMATnombreLignes > 0 && uiMATnombreColonnes > 0)
	{
		//Allocation du tableau 2D utilisé pour initialisé la future matrice
		ppMTPelementsTransposes = new MType*[uiMATnombreColonnes];
		for (unsigned int uiBoucle = 0; uiBoucle < uiMATnombreColonnes; uiBoucle++)
			ppMTPelementsTransposes[uiBoucle] = new MType[uiMATnombreLignes];

		//Transposition des éléments de la matrice courante dans le tableau 2D
		for (unsigned int uiBoucleLignes = 0; uiBoucleLignes < uiMATnombreColonnes; uiBoucleLignes++)
			for (unsigned int uiBoucleColonnes = 0; uiBoucleColonnes < uiMATnombreLignes; uiBoucleColonnes++)
				ppMTPelementsTransposes[uiBoucleLignes][uiBoucleColonnes] = ppMTPMATmatrice[uiBoucleColonnes][uiBoucleLignes];

		//Initialisation de la nouvelle matrice, avec indices inversés et en utilisant le tableau 2D
		Cmatrice<MType> MATmatriceTransposee(uiMATnombreColonnes, uiMATnombreLignes, ppMTPelementsTransposes);
		
		//Désallocation du tableau 2D temporaire
		for (unsigned int uiBoucleLignes = 0; uiBoucleLignes < uiMATnombreColonnes; uiBoucleLignes++)
			delete [] ppMTPelementsTransposes[uiBoucleLignes];
		delete [] ppMTPelementsTransposes;

		return MATmatriceTransposee;
	}
	else
	{
		/*Si la matrice courante est vide (Au moins un indice nul), 
		 *on renvoie une matrice vide avec des indices nuls via le constructeur par défaut*/
		Cmatrice<MType> MATmatriceTransposee;
		return MATmatriceTransposee; 
	}
}


/************************************
	Produit d'une matrice et d'une constante
*************************************
Entrée		: Matrice d'éléments MType à multiplier à la constante ConstantType
Nécessité	: (Une surcharge de l'opérateur '*' est définie pour ConstantType et MType [MType = MType * ConstantType])
			ET (Une surcharge de l'opérateur '=' est définie pour MType [MType = MType])
			ET (MType et ConstantType doivent supporter l'initialisation suivante : MType MTPexemple = 0 et ConstantType CTPexemple = 0)
Sortie		: Nouvelle Cmatrice<MType>, produit d'une matrice et d'une constante
Entraîne	: (L'objet en sortie est créé et initialisé par produit d'un objet Cmatrice<MType> à une constante ConstantType)
*************************************/
template <class MType>
template <class ConstantType>
Cmatrice<MType> Cmatrice<MType>::operator*(ConstantType CTPconstante)
{
	Cmatrice<MType> MATresultat(uiMATnombreLignes, uiMATnombreColonnes);
	for(unsigned int uicptl = 0; uicptl<uiMATnombreLignes; uicptl++)
		for(unsigned int uicptc = 0; uicptc<uiMATnombreColonnes; uicptc++)
			MATresultat.ppMTPMATmatrice[uicptl][uicptc] = ppMTPMATmatrice[uicptl][uicptc] * CTPconstante;
	
	return MATresultat;
}


/************************************
	Division d'une matrice par une constante
*************************************
Entrée		: Matrice d'éléments MType à diviser par une constante ConstantType
Nécessité	: (Une surcharge de l'opérateur '/' est définie pour ConstantType et MType [MType = MType / ConstantType])
			ET (Une surcharge de l'opérateur '=' est définie pour MType [MType = MType])
			ET (MType et ConstantType doivent supporter l'initialisation suivante : MType MTPexemple = 0 et ConstantType CSTexemple = 0)
Sortie		: Nouvelle Cmatrice<MType>, division d'une matrice par une constante
Entraîne	: (L'objet en sortie est créé et initialisé par produit s"un objet Cmatrice<MType>)
*************************************/
template <class MType>
template <class ConstantType>
Cmatrice<MType> Cmatrice<MType>::operator/(ConstantType CTPconstante)
{
	if (CTPconstante==0)
	{
		Cexception EXCobjet(ERREUR_DIVISION_PAR_ZERO , "Erreur division par zero : La constante ne doit pas etre nulle");
		throw EXCobjet;
	}
	Cmatrice<MType> MATresultat(uiMATnombreLignes, uiMATnombreColonnes);
	for(unsigned int uicptl = 0; uicptl<uiMATnombreLignes; uicptl++)
		for(unsigned int uicptc = 0; uicptc<uiMATnombreColonnes; uicptc++)
			MATresultat.ppMTPMATmatrice[uicptl][uicptc]= ppMTPMATmatrice[uicptl][uicptc] / CTPconstante;

	return MATresultat;
}


/************************************
	Addition de matrices
*************************************
Entrée		: Matrice d'éléments MType à additioner à la matrice courante
Nécessité	: (Les deux matrices sont de même type / classe MType)
			ET (Une surcharge de l'opérateur '=' est définie pour MType [MType = MType])
			ET (Une surcharge de l'opérateur '+' est définie pour MType [MType = MType + MType])
Sortie		: Nouvelle Cmatrice<MType>, addition des deux matrices
Entraîne	: (L'objet en sortie est créé et initialisé par addition des deux objets Cmatrice<MType>)
			OU (Une exception est levée si les deux matrices ne sont pas de mêmes dimensions)
*************************************/
template <class MType>
Cmatrice<MType> Cmatrice<MType>::operator+(Cmatrice<MType> MATparam)
{
	if (uiMATnombreLignes != MATparam.uiMATnombreLignes || uiMATnombreColonnes != MATparam.uiMATnombreColonnes)
	{
		Cexception EXCobjet(ERREUR_DIMENSIONS_INCORRECTES, "Erreur addition de matrices : Dimensions incompatibles");
		throw EXCobjet;
	}
	else
	{
		//Allocation tableau temporaire 2 dimensions
		MType ** ppMTPresultat = new MType*[uiMATnombreLignes];
		for (unsigned int uiBoucle = 0; uiBoucle < uiMATnombreLignes; uiBoucle++)
			ppMTPresultat[uiBoucle] = new MType[uiMATnombreColonnes];

		//Addition et affectation dans le tableau temporaire
		for (unsigned int uiBoucleLignes = 0; uiBoucleLignes < uiMATnombreLignes; uiBoucleLignes++)
			for (unsigned int uiBoucleColonnes = 0; uiBoucleColonnes < uiMATnombreColonnes; uiBoucleColonnes++)
				ppMTPresultat[uiBoucleLignes][uiBoucleColonnes] = ppMTPMATmatrice[uiBoucleLignes][uiBoucleColonnes] 
																	+ MATparam.ppMTPMATmatrice[uiBoucleLignes][uiBoucleColonnes];
		
		Cmatrice<MType> MATresultat(uiMATnombreLignes, uiMATnombreColonnes, ppMTPresultat);

		//Désallocation du tableau 2D temporaire
		for (unsigned int uiBoucleLignes = 0; uiBoucleLignes < uiMATnombreLignes; uiBoucleLignes++)
			delete [] ppMTPresultat[uiBoucleLignes];
		delete [] ppMTPresultat;

		return MATresultat;		
	}
}


/************************************
	Soustraction de matrices
*************************************
Entrée		: Matrice d'éléments MType à soustraire à la matrice courante
Nécessité	: (Les deux matrices sont de même type / classe MType)
			ET (Une surcharge de l'opérateur '=' est définie pour MType [MType = MType])
			ET (Une surcharge de l'opérateur '-' est définie pour MType [MType = MType - MType])
Sortie		: Nouvelle Cmatrice<MType>, soustraction des deux matrices
Entraîne	: (L'objet en sortie est créé et initialisé par soustraction de l'objet en paramètre à l'ojet courant)
			OU (Une exception est levée si les deux matrices ne sont pas de mêmes dimensions)
*************************************/
template <class MType>
Cmatrice<MType> Cmatrice<MType>::operator-(Cmatrice<MType> MATparam)
{
	if (uiMATnombreLignes != MATparam.uiMATnombreLignes || uiMATnombreColonnes != MATparam.uiMATnombreColonnes)
	{
		Cexception EXCobjet(ERREUR_DIMENSIONS_INCORRECTES, "Erreur soustraction de matrices : Dimensions incompatibles");
		throw EXCobjet;
	}
	else
	{
		//Allocation tableau temporaire 2 dimensions
		MType ** ppMTPresultat = new MType*[uiMATnombreLignes];
		for (unsigned int uiBoucle = 0; uiBoucle < uiMATnombreLignes; uiBoucle++)
			ppMTPresultat[uiBoucle] = new MType[uiMATnombreColonnes];

		//Soustraction et affectation dans le tableau temporaire
		for (unsigned int uiBoucleLignes = 0; uiBoucleLignes < uiMATnombreLignes; uiBoucleLignes++)
			for (unsigned int uiBoucleColonnes = 0; uiBoucleColonnes < uiMATnombreColonnes; uiBoucleColonnes++)
				ppMTPresultat[uiBoucleLignes][uiBoucleColonnes] = ppMTPMATmatrice[uiBoucleLignes][uiBoucleColonnes] 
																	- MATparam.ppMTPMATmatrice[uiBoucleLignes][uiBoucleColonnes];
		
		Cmatrice<MType> MATresultat(uiMATnombreLignes, uiMATnombreColonnes, ppMTPresultat);

		//Désallocation du tableau 2D temporaire
		for (unsigned int uiBoucleLignes = 0; uiBoucleLignes < uiMATnombreLignes; uiBoucleLignes++)
			delete [] ppMTPresultat[uiBoucleLignes];
		delete [] ppMTPresultat;

		return MATresultat;			
	}
}


/************************************
	Produit de matrices
*************************************
Entrée		: Matrice d'éléments MType à multiplier à la matrice courante
Nécessité	: (Les deux matrices sont de même type / classe MType)
			ET (Une surcharge de l'opérateur '=' est définie pour MType [MType = MType])
			ET (Une surcharge de l'opérateur '*' est définie pour MType [MType = MType * MType])
			ET (Une surcharge de l'opérateur '+' est définie pour MType [MType = MType + MType])
			ET (MType doit supporter l'initialisation suivante : MType MTPexemple = 0)
Sortie		: Nouvelle Cmatrice<MType>, produit des deux matrices
Entraîne	: (L'objet en sortie est créé et initialisé par produit des deux objets Cmatrice<MType>)
			OU (Une exception est levée si les deux matrices ont des dimensions incompatibles)
*************************************/
template <class MType>
Cmatrice<MType> Cmatrice<MType>::operator*(Cmatrice<MType> MATparam)
{	
	if (uiMATnombreColonnes != MATparam.uiMATnombreLignes)
	{
		Cexception EXCobjet(ERREUR_DIMENSIONS_INCORRECTES, "Erreur produit de matrices : Dimensions incompatibles");
		throw EXCobjet;
	}
	else
	{
		//Allocation tableau temporaire 2 dimensions
		MType ** ppMTPresultat = new MType*[uiMATnombreLignes];
		for (unsigned int uiBoucle = 0; uiBoucle < uiMATnombreLignes; uiBoucle++)
			ppMTPresultat[uiBoucle] = new MType[MATparam.uiMATnombreColonnes];

		//Produit et affectation dans le tableau temporaire
		for (unsigned int uiBoucleLignes = 0; uiBoucleLignes < uiMATnombreLignes; uiBoucleLignes++)
		{
			for (unsigned int uiBoucleColonnes = 0; uiBoucleColonnes < MATparam.uiMATnombreColonnes; uiBoucleColonnes++)
			{
				MType MTPresultatElement = 0;
				for (unsigned int uiBoucleAddition = 0; uiBoucleAddition < uiMATnombreColonnes; uiBoucleAddition++)
					MTPresultatElement = MTPresultatElement + ppMTPMATmatrice[uiBoucleLignes][uiBoucleAddition]
												* MATparam.ppMTPMATmatrice[uiBoucleAddition][uiBoucleColonnes];

				ppMTPresultat[uiBoucleLignes][uiBoucleColonnes] = MTPresultatElement;
			}
		}

		Cmatrice<MType> MATresultat(uiMATnombreLignes, MATparam.uiMATnombreColonnes, ppMTPresultat);

		//Désallocation du tableau 2D temporaire
		for (unsigned int uiBoucleLignes = 0; uiBoucleLignes < uiMATnombreLignes; uiBoucleLignes++)
			delete [] ppMTPresultat[uiBoucleLignes];
		delete [] ppMTPresultat;

		return MATresultat;	
	}
}


/************************************
	Surcharge de l'opérateur d'affectation
*************************************
Entrée		: L'objet Cmatrice<MType> à copier
Nécessité	: (Les deux matrices sont de même type / classe MType)
			ET (Une surcharge de l'opérateur '=' est définie pour MType [MType = MType])
Sortie		: L'objet à modifier, modifié par copie de l'objet d'entrée
Entraîne	: (L'objet en cours est modifié par copie du contenu du paramètre)
*************************************/
template <class MType>
Cmatrice<MType> & Cmatrice<MType>::operator=(Cmatrice<MType> MATparam)
{
	//Désallocation de la précédente matrice de l'objet en cours
	for (unsigned int uiBoucleLignes = 0; uiBoucleLignes < uiMATnombreLignes; uiBoucleLignes++)
		delete [] ppMTPMATmatrice[uiBoucleLignes];
	delete [] ppMTPMATmatrice;

	//Définition des nouvelles dimensions
	uiMATnombreLignes = MATparam.uiMATnombreLignes;
	uiMATnombreColonnes = MATparam.uiMATnombreColonnes;

	//Allocation de la nouvelle matrice et recopie des valeurs
	if (MATparam.ppMTPMATmatrice == NULL)
		ppMTPMATmatrice = NULL;
	else
	{
		ppMTPMATmatrice = new MType*[uiMATnombreLignes];
		for (unsigned int uiBoucleLignes = 0; uiBoucleLignes < uiMATnombreLignes; uiBoucleLignes++)
			ppMTPMATmatrice[uiBoucleLignes] = new MType[uiMATnombreColonnes];

		for (unsigned int uiBoucleLignes = 0; uiBoucleLignes < uiMATnombreLignes; uiBoucleLignes++)
			for (unsigned int uiBoucleColonnes = 0; uiBoucleColonnes < uiMATnombreColonnes; uiBoucleColonnes++)
				ppMTPMATmatrice[uiBoucleLignes][uiBoucleColonnes] = MATparam.ppMTPMATmatrice[uiBoucleLignes][uiBoucleColonnes];
	}

	return *this;
}




/*****************************************************************************************************************************
******************************************************************************************************************************
		Définition des fonctions extérieures à Cmatrice
******************************************************************************************************************************
******************************************************************************************************************************/


/************************************
	Produit d'une constante et d'une matrice
*************************************
Entrée		: Constante ConstantType de la multiplication,
				Matrice d'éléments MType à multiplier à la constante
Nécessité	: (Une surcharge de l'opérateur '*' est définie pour MType et ConstantType [MType = ConstantType * MType])
			ET (Une surcharge de l'opérateur '=' est définie pour MType [MType = MType])
			ET (MType et ConstantType doivent supporter l'initialisation suivante : MType MTPexemple = 0 et ConstantType CTPexemple = 0)
Sortie		: Nouvelle Cmatrice<MType>, produit d'une constante et d'une matrice
Entraîne	: (L'objet en sortie est créé et initialisé par produit d'une constante ConstantType à un objet Cmatrice<MType>)
*************************************/
template <class MType, class ConstantType> 
Cmatrice<MType> operator*(ConstantType CTPconstante, Cmatrice<MType> MATparam)
{
	Cmatrice<MType> MATresultat(MATparam.MATgetNbrLignes(), MATparam.MATgetNbrColonnes());
	for(unsigned int uicptl = 0; uicptl < MATparam.MATgetNbrLignes(); uicptl++)
		for(unsigned int uicptc = 0; uicptc < MATparam.MATgetNbrColonnes(); uicptc++)
			MATresultat.MATsetElement(uicptl, uicptc, MATparam.MATgetElement(uicptl, uicptc) * CTPconstante);

	return MATresultat;
}


/************************************
	Surcharge opérateur de sortie standard 
*************************************
Entrée		: Référence sur le flux de sortie
				Matrice d'éléments MType à afficher sur la sortie standard
Nécessité	: (Une surcharge de l'opérateur '<<' est définie pour MType [cout << MType])
Sortie		: Référence sur le flux de sortie représentant la matrice
Entraîne	: (Une représentation de la matrice est affichée sur la sortie standard)
*************************************/
template <class MType> 
ostream & operator<<(ostream& os, Cmatrice<MType> MATparam)
{
	os << endl;
	for (unsigned int uiBoucleLignes = 0; uiBoucleLignes < MATparam.MATgetNbrLignes(); uiBoucleLignes++)
	{
		for (unsigned int uiBoucleColonnes = 0; uiBoucleColonnes < MATparam.MATgetNbrColonnes(); uiBoucleColonnes++)
			os << MATparam.MATgetElement(uiBoucleLignes, uiBoucleColonnes) << "\t";
		os << endl;
	}
	return os;
}


/************************************
	Positionneur de curseur pour lecture
*************************************
Entrée		: Chaîne de caractères temporaire à parcourir
Nécessité	: Néant
Sortie		: Pointeur sur le char à lire
Entraîne	: (Le pointeur est retourné)
			OU (Une exception est levée en cas de format incorrect)
*************************************/
char * positionnerCurseur(char* pcTempString)
{
	char * pcBeginCursor;

	pcBeginCursor = strchr(pcTempString, '=');
	if (pcBeginCursor == NULL)
	{
		Cexception EXCobjet(ERREUR_FORMAT_FICHIER, "Erreur format fichier : Format non conforme");
		throw EXCobjet;
	}
	pcBeginCursor++;
	while ((*pcBeginCursor == ' ' || *pcBeginCursor == '\t') && *pcBeginCursor != '\0')
		pcBeginCursor++;

	if (*pcBeginCursor == '\0')
	{
		Cexception EXCobjet(ERREUR_FORMAT_FICHIER, "Erreur format fichier : Format non conforme");
		throw EXCobjet;
	}

	return pcBeginCursor;
}


/************************************
	Parser
*************************************
Entrée		: Nom du fichier à lire
Nécessité	: (Le fichier respecte le format spécifié)
			ET (Une surcharge de l'opérateur '=' est définie pour MType [MType = MType])
Sortie		: Cmatrice<double> initialisée à partir du fichier
Entraîne	: (Une Cmatrice<double> est initialisée)
			OU (Une exception est levée en cas d'échec d'ouverture)
			OU (Une exception est levée en cas de format incorrect)
			OU (Une exception est levée en cas de type différent de double)
Indication	: Les espaces et tabulations sont pris en charge par le parser.
Warning		: Si les éléments de la matrices ne sont pas saisis correctement (nbColonnes éléments par ligne, nbLignes d'éléments),
				la matrice sera initialisée avec les n premiers double rencontrés. Le reste de la matrice sera initialisé avec des
				valeurs non prédictibles.
*************************************/
Cmatrice<double> lireMatrice(const char * nomFichier)
{
	char pcTempString[255];
	char * pcBeginCursor;
	char * pcEndPointeur;	//Pour le strtol
	unsigned int uiNbrLignes = 0;
	unsigned int uiNbrColonnes = 0;
	double ** ppdElementsMatrice;


	//ouverture du fichier en lecture
	ifstream flux(nomFichier, ios::out);
	
	//Si l'ouverture a échouée
	if (flux.fail())
	{
		Cexception EXCobjet(ERREUR_OUVERTURE_FICHIER, "Erreur ouverture fichier : Fichier introuvable");
		throw EXCobjet;
	}
	
	//==============================================
	//Lecture de la 1ère ligne
	//==============================================
	flux.getline(pcTempString, 255);
	
	//Echec de lecture ou dépassement du buffer
	if (flux.fail())
	{
		Cexception EXCobjet(ERREUR_FORMAT_FICHIER, "Erreur format fichier : Format non conforme");
		throw EXCobjet;
	}

	pcBeginCursor = positionnerCurseur(pcTempString);

	//"double" contient6 caractères => on ne compare que les 6 1ers char
	//Si le type "double" n'est pas spécifié, erreur.
	if (_strnicmp(pcBeginCursor, "double", 6) != 0)
	{
		Cexception EXCobjet(ERREUR_FORMAT_FICHIER, "Erreur format fichier : Type \"double\" attendu");
		throw EXCobjet;
	}

	pcBeginCursor = NULL;

	//==============================================
	//Ligne suivante
	//==============================================
	flux.getline(pcTempString, 255);

	//Echec de lecture ou dépassement du buffer
	if (flux.fail())
	{
		Cexception EXCobjet(ERREUR_FORMAT_FICHIER, "Erreur format fichier : Format non conforme");
		throw EXCobjet;
	}

	pcBeginCursor = positionnerCurseur(pcTempString);

	uiNbrLignes = (int) strtol(pcBeginCursor, &pcEndPointeur, 0);	//Si pas de valeur valide, dimension considérée nulle.

	//==============================================
	//Ligne suivante
	//==============================================
	flux.getline(pcTempString, 255);

	//Echec de lecture ou dépassement du buffer
	if (flux.fail())
	{
		Cexception EXCobjet(ERREUR_FORMAT_FICHIER, "Erreur format fichier : Format non conforme");
		throw EXCobjet;
	}

	pcBeginCursor = positionnerCurseur(pcTempString);

	uiNbrColonnes = (int) strtol(pcBeginCursor, &pcEndPointeur, 0);	//Si pas de valeur valide, dimension considérée nulle.

	//==============================================
	//Initialisation matrice
	//==============================================

	//Si une des dimension est nulle, on retourne une matrice initialisée par le constructeur par défaut
	if (uiNbrLignes == 0 || uiNbrColonnes == 0)
	{
		Cmatrice<double> MATmatrice;
		return MATmatrice;
	}

	//Lecture d'une ligne "dans le vide" pour positionner le curseur
	flux.getline(pcTempString, 255);

	//Allocation tableau 2D temporaire pour construire la matrice
	ppdElementsMatrice = new double*[uiNbrLignes];
	for (unsigned int uiBoucle = 0; uiBoucle < uiNbrLignes; uiBoucle++)
		ppdElementsMatrice[uiBoucle] = new double[uiNbrColonnes];

	//Initialisation de la matrice
	for (unsigned int uiBoucleLignes = 0; uiBoucleLignes < uiNbrLignes; uiBoucleLignes++)
		for (unsigned int uiBoucleColonnes = 0; uiBoucleColonnes < uiNbrColonnes; uiBoucleColonnes++)
			flux >> ppdElementsMatrice[uiBoucleLignes][uiBoucleColonnes];

	flux.close();

	Cmatrice<double> MATmatrice(uiNbrLignes, uiNbrColonnes, ppdElementsMatrice);

	//Désallocation du tableau 2D temporaire
	for (unsigned int uiBoucleLignes = 0; uiBoucleLignes < uiNbrLignes; uiBoucleLignes++)
		delete [] ppdElementsMatrice[uiBoucleLignes];
	delete [] ppdElementsMatrice;

	return MATmatrice;
}
