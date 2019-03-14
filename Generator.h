#pragma once
#include "stdafx.h"
#include "Decomposition.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <map>

class Generator : public Decomposition
// signifie : cr�er une classe Generator qui h�rite de la classe Decomposition
{
	/*
	Cette classe h�rite de la classe d�composition. 
	Apr�s d�composition du corpus de texte en �l�ment distinct, dictionnaire, listes d'initialisation et liste de fin, cette classe permettra la g�n�ration d'un nouveau corpus de texte.
	Ici g�n�ration d'un tweet. Contrainte sur la taille du texte.
	*/

public :

	Generator(std::string chemin);

	void initialisationDonnee(std::map<std::string, std::vector<std::string>> &dico, std::map<std::string, 
		std::string> &dicoFin,	std::vector<std::vector<std::string>>& listeDemarrage);								// Initialisation des donn�es permettant de cr�er le corpus de texte.							

	void initialisationPhrase(std::vector<std::vector<std::string>> &listeDemarrage, std::string &clef, int &taille,
		std::vector<std::string> &phraseFinale, int & alea);														// Fonction permettant d'initialiser une phrase

	void tirageDico(std::string clef, std::map<std::string, std::vector<std::string>> &dico, std::string &sortie);	// Via une clef, et par la m�thode de Markov, r�cup�rer un mot associ� � la clef. Fonction ulilis�e pour g�n�rer une phrase coh�rente.

	void finPhrase(std::vector<std::string> &phraseFinale, std::string clef, std::map<std::string,
		std::vector<std::string>> & dico, std::map<std::string, std::string> & dicoFin);							// Permet de finir une phrase. (En cas de contrainte sur la longueur de la phrase)

	void generePhrase(std::vector<std::string> &phraseFinale, std::map<std::string, std::vector<std::string>> &dico, 
		std::map<std::string, std::string> &dicoFin, std::vector<std::vector<std::string>> &listeDemarrage);		// G�n�ration d'une phrase (tweet) syntaxiquement correcte.
	
	void phraseFinale(std::vector<std::string> &phraseFinale, std::string &leTweet);								// Construction de la phrase pour ensuite l'afficher.

protected:
	// �l�ment prot�g� ne devant �tre modifi�.
	std::string m_chemin;																							// Chemin o� se situe le corpus de texte initial
};

