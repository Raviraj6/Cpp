#pragma once
#include "stdafx.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <map>

class Decomposition
{
	public:
		/*
		Ensemble des fonctions présentes dans le cpp et utiles pour décomposer un fichier texte
		- Fonction permettant d'ouvrir un fichier texte
		- Prise en compte des exceptions lors du découpage des phrases
		- Fonction créant une liste rassemblant l'ensemble des débuts de phrases (2 mots) présent dans le corpus de texte analysé
		- Fonction créant une liste rassemblant l'ensemble des fins de phrases (2 mots) présent dans le corpus de texte analysé
		- Formation d'un dictionnaire reprenant le principe de la chaîne de Markov
		Ces fonctions permettent de décomposer le fichier texte pour pouvoir par la suite construire un nouveau fichier par la méthode de la chaîne de Markov
		*/

		Decomposition(std::string chemin);

		bool ouvertureFichier(std::ifstream &inFile);																	//Ouvre le fichier contenant les phrases

		bool mrMrs(std::string word);																					// Prend en compte les exceptions des titres

		void f_listeDebut(std::vector<std::vector<std::string>> &listeDemarrage, std::string mot1, std::string mot2 );  // Création de la liste nous permettant d'initialiser nos phrases

		void f_dicoFin(std::map<std::string, std::string> &dicoFin, std::string mot1, std::string mot2);				// Création de la liste nous permettant de finaliser nos phrases
		
		bool dictionnaire(std::map<std::string, std::vector<std::string>> &dico, std::map<std::string,
			std::string> &dicoFin, std::vector<std::vector<std::string>> &listeDemarrage);								// Découpe le fichier texte en tableau de X lignes, avec pour clef deux mots, et en complément, une liste de mots associés à cette clef. 


	protected:
		// élément protégé, qui ne doit être modifié !

		std::string m_chemin;																							// Chemin où se situe le corpus de texte initial
};