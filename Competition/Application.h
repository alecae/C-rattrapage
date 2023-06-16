#pragma once
#include "Menu.h"
#include "Concurrent.h"
#include <list>
#include <deque>
#include <map>
#include <functional>
#include <iterator>

/// <summary>
/// La classe Application est celle qui contient tout le fonctionnement du programme
/// </summary>
class Application
{
private:
	/// <summary>
	/// Le menu de l'application
	/// </summary>
	///
	Menu menu;

	/// <summary>
	/// 
	/// @TODO D�clarer les 3 conteneurs avec les noms et caract�ristiques indiqu�s dans le sujet
	/// 
	/// </summary>
	/// 
	std::deque<int> dossardsPourAffectation;               
	std::list<Concurrent> concurrentsInscrits;            
	std::multimap<int, Concurrent> resultats;


public:
	/// <summary>
	/// Initialiser la comp�tition.
	/// Consiste � saisir le nombre de dossards n�cessaires (= nombre de concurrents)
	/// puis � les cr�er dans le conteneur dossardsPourAffectation.
	/// Entre 2 et 100 dossards.
	/// </summary>
	void InitialiserCompetition() {

		int nombreDossards;
		std::deque<int> dossardsPourAffectation;

		do {
			std::cout << "Entrez le nombre de dossards n�cessaires (entre 2 et 100) : ";
			std::cin >> nombreDossards;
		} while (nombreDossards < 2 || nombreDossards > 100);


		for (int i = 1; i <= nombreDossards; i++) {
			dossardsPourAffectation.push_back(i);
		}



		std::cout << "La comp�tition a �t� initialis�e avec succ�s !" << std::endl;
	};

	/// <summary>
	/// Inscrire un concurent.
	/// Apr�s v�rification qu'il reste un dossard disponible, il faut:
	/// - saisir le nom du concurrent
	/// - retirer 1 dossard au hasard dans le conteneur dossardsPourAffectation
	/// - cr�er le concurrent avec son nom et le dossard
	/// - ajouter le concurrent au conteneur concurentsInscrits
	/// Pas d'inscription possible s'il ne reste plus de dossard disponible.
	/// Le concurrent est affich� ainsi que le nombre de dossards pouvant encore �tre attribu�s.
	/// </summary>
	void InscrireUnConcurrent() {

		if (dossardsPourAffectation.empty()) {
			std::cout << "Plus de dossards disponibles. L'inscription n'est pas possible." << std::endl;
			return;
		}

		std::string nomConcurrent;
		std::list<std::string> concurrentsInscrits;

		// nom du concurrent
		std::cout << "Entrez le nom du concurrent : ";
		std::cin >> nomConcurrent;

		// Retirer dossard au hasard du conteneur dossardsPourAffectation
		std::srand(static_cast<unsigned>(std::time(nullptr)));  // nombres al�atoires
		int randomIndex = std::rand() % dossardsPourAffectation.size();
		auto it = dossardsPourAffectation.begin() + randomIndex;
		int dossard = *it;
		dossardsPourAffectation.erase(it);

		// Cr�ation du concurrent avec son nom et le dossard
		std::string concurrentInscrit = "Nom: " + nomConcurrent + ", Dossard: " + std::to_string(dossard);

		// Ajouter le concurrent au conteneur concurrentsInscrits
		concurrentsInscrits.push_back(concurrentInscrit);

		// Affichage du concurrent inscrit et du nombre de dossards restants
		std::cout << "Concurrent inscrit : " << concurrentInscrit << std::endl;
		std::cout << "Nombre de dossards restants : " << dossardsPourAffectation.size() << std::endl;
	};




	/// <summary>
	/// Affiche la liste des concurrents inscrits par ordre alphab�tique des noms
	/// </summary>
	void AfficherParNom();

	/// <summary>
	/// Affiche la liste des concurrents inscrits par ordre croissant des dossards
	/// </summary>
	void AfficherParDossard();

	/// <summary>
	/// Permet de noter (scorer) tous les concurrents.
	/// - extrait et supprime le premier concurrent du conteneur concurentsInscrits
	/// - lui affecte un score entre 0 et 10 inclus
	/// - ins�re le concurrent not� dans le conteneur resultats, les mieux not�s rang�s en premier
	/// Le score doit servir de cl� pour retrouver tous les concurrents ayant un certain score.
	/// Attention!! On peut avoir plusieurs concurrents avec le m�me score.
	/// </summary>
	void NoterConcurrents();

	/// <summary>
	/// Affiche le score, le dossard et le nom des concurrents not�s.
	/// </summary>
	void AfficherResultats();

	/// <summary>
	/// Boucle d'ex�cution du programme.
	/// </summary>
	void Run();
};

