// ProjetMain.cpp : Définit le point d'entrée pour l'application console.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <map>
#include <algorithm>
#include <iterator>
#include "Decomposition.h"
#include "Generator.h"

using namespace std;


int main()
{
	// Déclaration des données

	map<string, vector<string>> *dico;
	map<string, string> *dicoFin;
	vector<vector<string>> listeFin;
	vector<vector<string>> listeDemarrage;
	vector<string> phraseFinale;
	string monchemin;
	string leTweet;
	string recommencer="OUI";
	dico = new map<string, vector<string>>;
	dicoFin = new map<string, string>;
		
	// Lancement du code 
	cout <<"Bonjour, indiquez moi le chemin de votre fichier" <<endl;
	getline(cin, monchemin);
	Generator chemin(monchemin);
	cout << "Generation du dictionnaire, veuillez patienter" << endl;
	chemin.initialisationDonnee(*dico, *dicoFin, listeDemarrage);
	//	monchemin = "C:/Users/Perrine Le Chanu/Documents/ENSAE/C++/Projet/trump.txt";

	// Vérification de la véracité du chemin
	while (listeDemarrage.empty())
	{
		cout << "Attention votre chemin est faux, pouvez vous me donner un autre chemin." << endl;
		getline(cin, monchemin);
		Generator chemin(monchemin);
		cout << "Generation du dictionnaire, veuillez patienter" << endl;
		chemin.initialisationDonnee(*dico, *dicoFin, listeDemarrage);
	}
	cout << "Le dictionnaire est cree, le tweet va etre genere." << endl;;

	// Génération des tweets, jusqu'à ce que l'utilisateur souhaite arrêter.
	while (recommencer == "OUI")
	{
		
		chemin.generePhrase(phraseFinale,*dico,*dicoFin, listeDemarrage);
		chemin.phraseFinale(phraseFinale, leTweet);
		cout << endl;
		cout << "Attention !! Nouveau tweet de Trump !" << endl;
		cout << endl;
		cout << leTweet << endl;
		cout << endl;
		phraseFinale.clear();
		leTweet.clear();

		cout << "Voulez-vous recommencer ? " << endl;
		cout << "Inscrire 'OUI' ou 'NON' " << endl;
		getline(cin, recommencer);

		// Vérification du choix de l'utilisateur
		while(recommencer.compare("OUI")==1 && recommencer.compare("NON")==1) {
			cout << "Je n'ai pas compris, voulez-vous recommencer ? " << endl;
			cout << "Inscrire 'OUI' ou 'NON' " << endl;
			getline(cin, recommencer);
		}
	}
	
	// Fin du programme
	cout << "A bientot !" << endl;
	getchar();
	getchar();
	return 0;
}




