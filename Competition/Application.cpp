#include <iostream>
#include <Windows.h>
#include "Application.h"
#include "Concurrent.h"

using namespace std;

/// <summary>
/// Retourne un nombre entier g�n�r� au hasard, n,
/// avec deb <= n < fin
/// </summary>
/// <param name="deb"> la valeur minimale de n</param>
/// <param name="fin"> la valeur � laquelle n doit �tre < </param>
/// <returns> n avec deb <= n < fin </returns>
int hasard(int deb, int fin)
{
	int val;
	val = (rand() % fin) + deb;
	return val;
}


/// <summary>
/// Initialiser la comp�tition.
/// Consiste � saisir le nombre de dossards n�cessaires (= nombre de concurrents)
/// puis � les cr�er dans le conteneur dossardsPourAffectation.
/// Entre 2 et 100 dossards.
/// </summary>
void Application::InitialiserCompetition()
{
	cout << "Saisir le nombre de dossards n�cessaires (entre 2 et 100) : " << endl;
	int nombreDossards;
	cin >> nombreDossards;

	if (nombreDossards < 2 || nombreDossards > 100) {
		cout << "Nombre de dossards invalide !" << endl;
		return;
	}

	for (int i = 1; i <= nombreDossards; i++) {
		dossardsPourAffectation.push_back(i);
	}

	cout << "Comp�tition initialis�e avec " << nombreDossards << " dossards." << endl;
}

/// <summary>
/// Inscrire un concurent.
/// Apr�s v�rification qu'il reste un dossard disponible, il faut:
/// - saisir le nom du concurrent
/// - retirer 1 dossard au hasard dans le conteneur dossardsPourAffectation
/// - cr�er le concurrent avec son nom et le dossard
/// - ajouter le concurrent au conteneur concurentsInscrits
/// Pas d'inscription possible s'il ne reste plus de dossard disponible.
/// </summary>
void Application::InscrireUnConcurrent()
{
	if (dossardsPourAffectation.empty()) {
		cout << "Plus de dossards disponibles. L'inscription n'est pas possible." << endl;
		return;
	}

	string nomConcurrent;
	cin.ignore(); 

	cout << "Entrez le nom du concurrent : ";
	getline(cin, nomConcurrent);

	// retirer 1 dossard au hasard dans le conteneur dossardsPourAffectation
	int dossard = dossardsPourAffectation.front();
	dossardsPourAffectation.pop_front();

	// Cr�ation du concurrent avec son nom et le dossard
	Concurrent concurrent(nomConcurrent, dossard);

	// Ajouter le concurrent au conteneur concurrentsInscrits
	concurrentsInscrits.push_back(concurrent);

	cout << "Concurrent inscrit : " << concurrent.GetNom() << " (Dossard : " << concurrent.GetDossard() << ")" << endl;
	cout << "Nombre de dossards restants : " << dossardsPourAffectation.size() << endl;
	
}

/// <summary>
/// Affiche la liste des concurrents inscrits, par ordre alphab�tique des noms
/// </summary>
void Application::AfficherParNom()
{
	if (concurrentsInscrits.empty()) {
		cout << "Aucun concurrent inscrit." << endl;
		return;
	}

	cout << "Liste des concurrents inscrits par ordre alphab�tique des noms :" << endl;

	// Copier les concurrents dans un autres liste pour les trier
	list<Concurrent> concurrentsTries(concurrentsInscrits.begin(), concurrentsInscrits.end());
	concurrentsTries.sort([](const Concurrent& c1, const Concurrent& c2) {
		return c1.GetNom() < c2.GetNom();
		});

	// Affiche les concurrents 
	for (const auto& concurrent : concurrentsTries) {
		cout << "Nom: " << concurrent.GetNom() << ", Dossard: " << concurrent.GetDossard() << endl;
	}
}

/// <summary>
/// Affiche la liste des concurrents inscrits, par ordre croissant des dossards
/// </summary>
void Application::AfficherParDossard()
{
	if (concurrentsInscrits.empty()) {
		cout << "Aucun concurrent inscrit." << endl;
		return;
	}

	cout << "Liste des concurrents inscrits par ordre croissant des dossards :" << endl;

	// Copier les concurrents dans un autres liste pour les trier
	list<Concurrent> concurrentsTries(concurrentsInscrits.begin(), concurrentsInscrits.end());
	concurrentsTries.sort([](const Concurrent& c1, const Concurrent& c2) {
		return c1.GetDossard() < c2.GetDossard();
		});

	// Afficher les concurrents
	for (const auto& concurrent : concurrentsTries) {
		cout << "Dossard: " << concurrent.GetDossard() << ", Nom: " << concurrent.GetNom() << endl;
	}
}

/// <summary>
/// Permet de noter (scorer) tous les concurrents.
/// - extrait et supprime le premier concurrent du conteneur concurentsInscrits
/// - lui affecte un score entre 0 et 10 inclus
/// - ins�re le concurrent not� dans le conteneur resultats, les mieux not�s rang�s en premier
/// Le score doit servir de cl� pour retrouver tous les concurrents ayant un certain score.
/// Attention!! On peut avoir plusieurs concurrents avec le m�me score.
/// </summary>
void Application::NoterConcurrents()
{
	if (concurrentsInscrits.empty()) {
		cout << "Aucun concurrent inscrit." << endl;
		return;
	}

	cout << "Notation des concurrents..." << endl;

	while (!concurrentsInscrits.empty()) {
		Concurrent concurrent = concurrentsInscrits.front();
		concurrentsInscrits.pop_front();

		int score = hasard(0, 11);  

		resultats.insert({ score, concurrent });
	}

	cout << "Tous les concurrents ont �t� not�s." << endl;
}

/// <summary>
/// Affiche le score, le dossard et le nom des concurrents not�s.
/// </summary>
void Application::AfficherResultats()
{
	//@TODO � compl�ter.
}

/// <summary>
/// Boucle d'ex�cution du programme.
/// </summary>
void Application::Run()
{
	bool quit = false;
	int choix = 0;

	do
	{
		//  Affiche le menu et lit le choix de l'utilisateur
		menu.Affiche();
		choix = menu.SaisirEntierEntre(1, 6);

		switch(choix)	//  R�alise l'action choisie par l'utilisateur
		{
		case 1:
			InscrireUnConcurrent();
			break;
		case 2:
			AfficherParNom();
			break;
		case 3:
			AfficherParDossard();
			break;
		case 4:
			NoterConcurrents();
			break;
		case 5:
			AfficherResultats();
			break;
		case 6:
			quit = true;
			break;
		}
	} while (!quit);
}
