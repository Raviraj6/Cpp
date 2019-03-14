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
		Ensemble des fonctions pr�sentes dans le cpp et utiles pour d�composer un fichier texte
		- Fonction permettant d'ouvrir un fichier texte
		- Prise en compte des exceptions lors du d�coupage des phrases
		- Fonction cr�ant une liste rassemblant l'ensemble des d�buts de phrases (2 mots) pr�sent dans le corpus de texte analys�
		- Fonction cr�ant une liste rassemblant l'ensemble des fins de phrases (2 mots) pr�sent dans le corpus de texte analys�
		- Formation d'un dictionnaire reprenant le principe de la cha�ne de Markov
		Ces fonctions permettent de d�composer le fichier texte pour pouvoir par la suite construire un nouveau fichier par la m�thode de la cha�ne de Markov
		*/

		Decomposition(std::string chemin);

		bool ouvertureFichier(std::ifstream &inFile);																	//Ouvre le fichier contenant les phrases

		bool mrMrs(std::string word);																					// Prend en compte les exceptions des titres

		void f_listeDebut(std::vector<std::vector<std::string>> &listeDemarrage, std::string mot1, std::string mot2 );  // Cr�ation de la liste nous permettant d'initialiser nos phrases

		void f_dicoFin(std::map<std::string, std::string> &dicoFin, std::string mot1, std::string mot2);				// Cr�ation de la liste nous permettant de finaliser nos phrases
		
		bool dictionnaire(std::map<std::string, std::vector<std::string>> &dico, std::map<std::string,
			std::string> &dicoFin, std::vector<std::vector<std::string>> &listeDemarrage);								// D�coupe le fichier texte en tableau de X lignes, avec pour clef deux mots, et en compl�ment, une liste de mots associ�s � cette clef. 


	protected:
		// �l�ment prot�g�, qui ne doit �tre modifi� !

		std::string m_chemin;																							// Chemin o� se situe le corpus de texte initial
};