#include "stdafx.h"
#include "Decomposition.h"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

// Déclatation du chemin
Decomposition::Decomposition( string chemin) : m_chemin(chemin)
{
}

// Ouverture du fichier grâce au chemin indiqué 
bool Decomposition::ouvertureFichier(ifstream &inFile)
{
	//ouverture du fichier contenant l'ensemble des phrases de Trump
	//std::ifstream inFile;
	inFile.open(m_chemin);

	if (!inFile)
	{
		cout << "Decomposition::ouvertureFichier : Unable to open" << endl;
		return false;
	}
	return true;
}

// Cas particulier lors de la décomposition du corpus de texte, afin de ne pas prendre en compte les ponctuations de ces cas comme fin de phrases.
bool Decomposition::mrMrs(std::string word) {
	if (word == "") {
		cerr << "Decomposition::mrMrs : Unable to catch the exception";
		abort();
	}
	if (word == "U.S." || word == "U.S.A." || word == "Mrs." || word == "mrs." || word == "MRS." || word == "Mr." || word == "mr." || word == "MR." || word == "Ms." || word == "ms." || word == "MS.") {
		return true;
	}
	return false;
}

// Liste comprenant l'ensemble des débuts de phrases présent dans le corpus de texte initial.
void Decomposition::f_listeDebut(std::vector<std::vector<std::string>> &listeDemarrage, std::string mot1, std::string mot2 )
{
	vector<string> temp;

	//if (mot1 != "" && mot2 != "") 
	
	if (mot1 == "" || mot2 == "")
	{
		cerr << "Decomposition::f_listeDebut : Unable to add";
		abort();
	}
	else 
	{
		temp.push_back(mot1);
		temp.push_back(mot2);
		listeDemarrage.push_back(temp);
	}
}

// Liste comprenant l'ensemble des fins de phrases présent dans le corpus de texte initial.
void Decomposition::f_dicoFin(map<string, string> &dicoFin, std::string mot1, std::string mot2 )
{
	vector<string> temp;

	if (mot1 == "" || mot2 == "")
	{
		cerr << "Decomposition::f_listeFin : Unable to add";
		abort();
	}
	else
	{
		dicoFin.insert(make_pair(mot1, mot2));
	}
}

// Création du dictionnaire. Clef : deux mots consécutifs dans le corpus, lien : vecteur des mots associés à la clef trouvés dans le corpus de texte initial.
bool Decomposition::dictionnaire(map<string, vector<string>> & dico, map<string, string> &dicoFin, vector<vector<string>> &listeDemarrage)
{
	// Déclaration des variables
	ifstream inFile;
	string word;
	string lettrePrec;
	vector<string> temp;
	vector<string> tempDecoupe;
	bool ponctuation = false;
	bool ouverture;
	string clef;
	vector<string> vecMap;
	std::map<string, vector<string>>::iterator it;

	// Début de la fonction par l'ouverture du fichier initial
	ouverture=ouvertureFichier(inFile);
	if (ouverture)
	{
		int i(-1);
		// découpe mot par mot et insertion dans un tableau
		while (!inFile.eof())
		{
			i++;
			std::ifstream::int_type x;
			x = inFile.get();

			// récupération du mot
			while (x != ' ' && x != std::ifstream::traits_type::eof())
			{
				word += static_cast<char>(x);
				lettrePrec = x;
				x = inFile.get();

				string::size_type pos = 0;
				while ((pos = word.find("\n", pos)) != string::npos)
				{
					word.erase(pos, 2);
				}
			}

			if (word.length() >= 2) {

				// Vérification de la ponctuation
				if (lettrePrec == "." || lettrePrec == "!" || lettrePrec == "?" & !mrMrs(word)) { // Prise en compte des titres
					ponctuation = true;
					word.pop_back();
				}

				//stockage du mot
				temp.push_back(word);
				// Cas du premier élément
				if (temp.size() == 2 && listeDemarrage.size() == 0) {
					f_listeDebut(listeDemarrage, temp[0], temp[1]);
				}

				if (temp.size() == 3 && temp[1] != "" && temp[2] != "")
				{
					//Ligne de 3 mots
					tempDecoupe.push_back(temp[0] + " " + temp[1]);
					tempDecoupe.push_back(temp[2]);
					//Remplissage du dictionnaire

					clef = tempDecoupe[0];

					it = dico.find(clef);
					if (it != dico.end()) {
						vecMap = it->second;
						vecMap.push_back(tempDecoupe[1]);
						it->second = vecMap;
					}
					else
					{
						vecMap.push_back(tempDecoupe[1]);
						dico.insert(make_pair(clef, vecMap));
					}

					vecMap.clear();
					tempDecoupe.clear();

					//Prise en compte de la ponctuation pour remplir la liste f_listeFin et f_listeDebut
					if (temp[0] == "." || temp[0] == "!" || temp[0] == "?")
					{
						f_listeDebut(listeDemarrage, temp[1], temp[2]);
					}
					temp.erase(temp.begin());
				}

				// Cas particulier de la ponctuation 
				if (ponctuation)
				{
					temp.push_back(lettrePrec);
					if (temp.size() == 3)
					{
						//Ligne de 3 mots
						f_dicoFin(dicoFin, temp[1], temp[2]);
						temp.erase(temp.begin());
					}
					ponctuation = false;
				}
				word.clear();
			}
		}

		if (i == -1)
		{
			cout << "Decomposition::decoupage : Unable to decompose" << endl;
			return false;
		}
		else
		{
			return true;
		}

		inFile.close();

	}
	else
	{
		return false;
	}
}
