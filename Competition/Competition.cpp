#include <iostream>
#include "Application.h"

/// <summary>
/// PROGRAMME PRINCIPAL
/// </summary>
/// <returns></returns>
int main()
{
	Application App;

	//  Initialisation pour le g�n�rateur de nombres al�atoires
	srand((unsigned int)std::time(0));

	//  Initialisation et lancement de l'application
	App.InitialiserCompetition();
	App.Run();
}
