#pragma once
#include "stdafx.h"
#include "Decomposition.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <map>

class Generator : public Decomposition
// signifie : créer une classe Generator qui hérite de la classe Decomposition
{
	/*
	Cette classe hérite de la classe décomposition. 
	Après décomposition du corpus de texte en élément distinct, dictionnaire, listes d'initialisation et liste de fin, cette classe permettra la génération d'un nouveau corpus de texte.
	Ici génération d'un tweet. Contrainte sur la taille du texte.
	*/

public :

	Generator(std::string chemin);

	void initialisationDonnee(std::map<std::string, std::vector<std::string>> &dico, std::map<std::string, 
		std::string> &dicoFin,	std::vector<std::vector<std::string>>& listeDemarrage);								// Initialisation des données permettant de créer le corpus de texte.							

	void initialisationPhrase(std::vector<std::vector<std::string>> &listeDemarrage, std::string &clef, int &taille,
		std::vector<std::string> &phraseFinale, int & alea);														// Fonction permettant d'initialiser une phrase

	void tirageDico(std::string clef, std::map<std::string, std::vector<std::string>> &dico, std::string &sortie);	// Via une clef, et par la méthode de Markov, récupérer un mot associé à la clef. Fonction ulilisée pour générer une phrase cohérente.

	void finPhrase(std::vector<std::string> &phraseFinale, std::string clef, std::map<std::string,
		std::vector<std::string>> & dico, std::map<std::string, std::string> & dicoFin);							// Permet de finir une phrase. (En cas de contrainte sur la longueur de la phrase)

	void generePhrase(std::vector<std::string> &phraseFinale, std::map<std::string, std::vector<std::string>> &dico, 
		std::map<std::string, std::string> &dicoFin, std::vector<std::vector<std::string>> &listeDemarrage);		// Génération d'une phrase (tweet) syntaxiquement correcte.
	
	void phraseFinale(std::vector<std::string> &phraseFinale, std::string &leTweet);								// Construction de la phrase pour ensuite l'afficher.

protected:
	// élément protégé ne devant être modifié.
	std::string m_chemin;																							// Chemin où se situe le corpus de texte initial
};

