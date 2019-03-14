#include "stdafx.h"
#include "Generator.h"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <map>
#include <cstdlib>
#include <time.h>

using namespace std;

// Déclaration du chemin
Generator::Generator(string chemin): Decomposition(chemin), m_chemin(chemin)
{

}

//Initiatisation des données, via l'appel à la classe déclaration
void Generator::initialisationDonnee(map<string, vector<string>> &dico, map<string, string> &dicoFin, vector<vector<string>> &listeDemarrage) {
	
	Decomposition superListe(m_chemin);
	superListe.dictionnaire(dico, dicoFin, listeDemarrage);

}

/* 
	- Fonction permettant de créer un début de phrase syntaxiquement cohérent. 
	- Liste de démarrage viable via la méthode de Monte Carlo
*/
void Generator::initialisationPhrase(vector<vector<string>> &listeDemarrage, string &clef, int &taille, vector<string> &phraseFinale, int & alea)
{
	int i;

	srand(time(NULL));
	i = rand() % (listeDemarrage.size() -alea - 1) +alea;
	phraseFinale.push_back(listeDemarrage[i][0]);
	phraseFinale.push_back(listeDemarrage[i][1]);
	clef = listeDemarrage[i][0] + " " + listeDemarrage[i][1];
	taille = taille + clef.size() + 1;

}

/*
	- Toujours sous principe de Monte Carlo
	- Le dictionnaire a pour clef une suite de deux mots, et pour lien un vecteur comportant l'ensemble des mots qui les suivent dans le corpus de texte de base.
	- En fonction de la clef, on continue la phrase en allant chercher le mot/ ponctuation suivant dans le dictionnaire.
*/
void Generator::tirageDico(string clef, map<string, vector<string>> &dico, string &sortie)
{
	int alea; 
	std::map<string, vector<string>>::iterator it;
	vector<string> vecSecond;

	it = dico.find(clef);
	if (it != dico.end()) {
			vecSecond= it->second ;
	}
	else {
		/*cerr << "Generator::tirageDico : non-existent Key";
		exit(1);*/
		sortie = " ";
	}

	if (sortie != " ") {
		if (vecSecond.size() == 1) {
			alea = 0;
		}
		else {
			srand(time(NULL));
			alea = rand() % (vecSecond.size() - 1);
		}
		sortie = vecSecond[alea];
	}
}

// Permet de finir une phrase sous contrainte.
void Generator::finPhrase(vector<string> &phraseFinale, string clef, map<string, vector<string>> &dico, map<string, string> &dicoFin)
{

	std::map<string, vector<string>>::iterator it;
	vector<string> vecSecond;
	bool phraseFinie(false);
	string temp;
	std::map<string,string>::iterator position;

	it = dico.find(clef);
	if (it != dico.end()) {
		vecSecond = it->second;

		//Premier cas notre clef nous permet de finir directement la phrase 
		for (int i = 0; i < vecSecond.size(); i++) {
			if (vecSecond[i]=="." || vecSecond[i] == "!" || vecSecond[i] == "?"|| vecSecond[i].find("@")==0 || vecSecond[i].find("#") == 0) {
				phraseFinale.push_back(vecSecond[i]);
				phraseFinie = true;
			}
		}
	}
	
	// Second cas : notre clef doit être modifiée pour trouver la fin de la phrase
	while (phraseFinie!=true) {
		phraseFinale.pop_back();
		temp = phraseFinale[phraseFinale.size() - 1];
		position = dicoFin.find(temp);

		if ( position != dicoFin.end())
		{			
			phraseFinale.push_back(position->second);
			phraseFinie = true;
		}
	}
}

// Génération de l'ensemble de la phrase syntaxiquement correcte.
void Generator::generePhrase(vector<string> &phraseFinale, map<string, vector<string>> &dico, map<string, string> &dicoFin, vector<vector<string>> &listeDemarrage)
{
	int i(0);
	int taille(0);
	string sortie;
	string clef;
	int temp(0);
	int alea(0);

	//Récupération des deux premiers mots pour commencer la phrase
	initialisationPhrase(listeDemarrage, clef, taille, phraseFinale,alea);

	while (taille < 250) // taille tweet 280 caractères.
	{
		tirageDico(clef, dico, sortie);

		if (sortie==" ")
		{
				phraseFinale.push_back("!");
				taille= taille+1 ;
				alea += 33;
				initialisationPhrase(listeDemarrage, clef, taille, phraseFinale, alea);	
		}
		else {
			phraseFinale.push_back(sortie);
			clef.clear();
			clef = phraseFinale[phraseFinale.size() - 2] + " " + phraseFinale[phraseFinale.size() - 1];
			taille = taille + sortie.size() + 1;
		}
		sortie.clear();
	}

	finPhrase(phraseFinale, clef, dico, dicoFin);
}

// Mise en forme sous forme de string pour afficher la phrase créée.
void Generator::phraseFinale(std::vector<std::string> &phraseFinale, std::string &leTweet) {

	int i(0);

	while (i<phraseFinale.size()-1)
	{
		leTweet += phraseFinale[i] + " ";
		i++;
	}
	leTweet += phraseFinale[i] + " ";
}