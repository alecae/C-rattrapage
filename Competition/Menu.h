#pragma once

/// <summary>
/// La classe mod�lisant le menu de l'application de gestion de la comp�tition
/// </summary>
class Menu
{
public:
	/// <summary>
	/// Affiche le menu
	/// </summary>
	void Affiche();

	/// <summary>
	/// Permet � l'utilisateur de choisir un nombre entier compris entre les limites donn�es en param�tres.
	/// Utilis� par exemple pour saisir le n� de la rubrique qu'il choisit.
	/// </summary>
	/// <param name="minNb">La plus petite valeur autoris�e, par d�faut 1</param>
	/// <param name="max">La plus grande valeur autoris�e, par d�faut 6</param>
	/// <returns>Le nombre entier saisi par l'utilisateur</returns>
	int SaisirEntierEntre(int minNb = 1, int max = 6);
};

