#include "Cmatrice.h"

void finProgramme();

void main(int argc, char ** argv )
{
	double dConstante;
	int iBoucle;
	Cmatrice<double> * pMATmatricesChargees;

	cout << endl << " __________________________________________________________" << endl;
	cout << "|                                                          |" << endl;
	cout << "|         LIBRAIRIE DE MANIPULATION DE MATRICES            |" << endl;
	cout << "|                  Programme de test                       |" << endl;
	cout << "|                                                          |" << endl;
	cout << "|     Aurele LUCIANI - Benjamin POUVREAU - Groupe 1        |" << endl;
	cout << "|     Projet C++ Part.1 - DI3 2017 - Polytech Tours        |" << endl;
	cout << "|__________________________________________________________|" << endl << endl << endl;

	//Si aucun argument n'est entré
	if (argc == 1)
	{
		cout << "Veuillez saisir au moins un nom de fichier a exploiter\n\tdans les arguments du programme." << endl;
		finProgramme();
	}

	//Tableau dynamique de Cmatrice<double> qui contiendra les matrices lues
	pMATmatricesChargees = new Cmatrice<double>[argc - 1];


	//Lecture des matrices
	for (iBoucle = 0; iBoucle < argc - 1; iBoucle++)
	{
		try
		{
			pMATmatricesChargees[iBoucle] = lireMatrice(argv[iBoucle + 1]);
			cout << "Matrice " << iBoucle + 1 << " sur " << argc - 1 << " chargee avec succes :" << pMATmatricesChargees[iBoucle] << endl;
		}
		catch (Cexception EXCobjet)
		{
			cout << "Erreur lors de la lecture du fichier \"" << argv[iBoucle + 1] << "\" : " << endl;
			cout << "\tErreur code " << EXCobjet.EXClireValeur() << " : " << EXCobjet.EXClireMessage() << endl;
			delete [] pMATmatricesChargees;
			finProgramme();
		}
	}


	//Saisie de la constante
	cout << "____________________________________________________________" << endl << endl;
	cout << "Saisir une constante de type double => ";
	cin >> dConstante;
	cout << "____________________________________________________________" << endl << endl;


	//Multiplication par la constante
	cout << "Multiplication des matrices par la constante " << dConstante << " :" << endl << endl;
	for (iBoucle = 0; iBoucle < argc - 1; iBoucle++)
	{
		cout << "Matrice " << iBoucle + 1 << " sur " << argc - 1 << " :" << pMATmatricesChargees[iBoucle] * dConstante << endl;
	}
	cout << "____________________________________________________________" << endl << endl;


	//Division par la constante
	cout << "Division des matrices par la constante " << dConstante << " :" << endl << endl;
	for (iBoucle = 0; iBoucle < argc - 1; iBoucle++)
	{
		try
		{
			cout << "Matrice " << iBoucle + 1 << " :" << pMATmatricesChargees[iBoucle] / dConstante << endl;
		}
		catch (Cexception EXCobjet)
		{
			cout << "Erreur lors de la multiplication de la matrice " << iBoucle + 1 << " sur " << argc - 1 << " :" << endl;
			cout << "\tErreur code " << EXCobjet.EXClireValeur() << " : " << EXCobjet.EXClireMessage() << endl << endl;
		}
	}
	cout << "____________________________________________________________" << endl << endl;
	

	//Addition des matrices
	cout << "Addition de toutes les matrices saisies :" << endl << endl;
	try
	{
		Cmatrice<double> MATresultat = pMATmatricesChargees[0];
		for (iBoucle = 1; iBoucle < argc - 1; iBoucle++)
			MATresultat = MATresultat + pMATmatricesChargees[iBoucle];
		cout << "Resutat :" << MATresultat << endl;
	}
	catch (Cexception EXCobjet)
	{
		cout << "Erreur lors de l'addition des matrices :" << endl;
			cout << "\tErreur code " << EXCobjet.EXClireValeur() << " : " << EXCobjet.EXClireMessage() << endl << endl;
	}
	cout << "____________________________________________________________" << endl << endl;

	
	//Opération M1 - M2 + M3 - M4 + ...
	cout << "Operation M1 - M2 + M3 - M4 + ... :" << endl << endl;
	try
	{
		Cmatrice<double> MATresultat = pMATmatricesChargees[0];
		for (iBoucle = 1; iBoucle < argc - 1; iBoucle++)
		{
			if (iBoucle % 2 == 0)
				MATresultat = MATresultat + pMATmatricesChargees[iBoucle];
			else
				MATresultat = MATresultat - pMATmatricesChargees[iBoucle];
		}
		cout << "Resultat :" << MATresultat << endl;
	}
	catch (Cexception EXCobjet)
	{
		cout << "Erreur lors de l'operation :" << endl;
			cout << "\tErreur code " << EXCobjet.EXClireValeur() << " : " << EXCobjet.EXClireMessage() << endl << endl;
	}
	cout << "____________________________________________________________" << endl << endl;


	//Produit de toutes les matrices
	cout << "Produit de toutes les matrices saisies :" << endl << endl;
	try
	{
		Cmatrice<double> MATresultat = pMATmatricesChargees[0];
		for (iBoucle = 1; iBoucle < argc - 1; iBoucle++)
			MATresultat = MATresultat * pMATmatricesChargees[iBoucle];
		cout << "Resutat :" << MATresultat << endl;
	}
	catch (Cexception EXCobjet)
	{
		cout << "Erreur lors du produit des matrices :" << endl;
			cout << "\tErreur code " << EXCobjet.EXClireValeur() << " : " << EXCobjet.EXClireMessage() << endl << endl;
	}

	//Fin du programme
	delete [] pMATmatricesChargees;
	finProgramme();
}


/************************************
	Termine le programme en cours.
*************************************
Entrée		: Rien
Nécessité	: Néant
Sortie		: Rien
Entraîne	: (Le programme se termine avec le code 0)
*************************************/
void finProgramme()
{
	/* Fonction terminant le programme une fois que l'utilisateur appuie sur une touche.
	 * Cela permet à l'utilisateur d'avoir le temps de consulter les résultats.
	 * Cette fonction utilise getchar(), il faut donc vider le buffer d'entrée standard
	 * afin d'éviter que getchar() ne vienne chercher un caractère du buffer au lieu de
	 * permettre à l'utilisateur d'appuyer sur une touche.
	 */
	char cTemp;	//Utilisé pour vider le buffer de cin
	cout << endl << " __________________________________________________________" << endl;
	cout << "|                                                          |" << endl;
	cout << "|    Appuyez sur Entree pour terminer le programme test.   |" << endl;
	cout << "|__________________________________________________________|" << endl;

	//Tant que l'on peut extraire des caractères du buffer
	while (cin.readsome(&cTemp, 1) != 0)
	{}

	getchar();
	exit(0);
}
