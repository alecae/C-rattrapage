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
	/// @TODO Déclarer les 3 conteneurs avec les noms et caractéristiques indiqués dans le sujet
	/// 
	/// </summary>
	/// 
	std::deque<int> dossardsPourAffectation;               
	std::list<Concurrent> concurrentsInscrits;            
	std::multimap<int, Concurrent> resultats;


public:
	/// <summary>
	/// Initialiser la compétition.
	/// Consiste à saisir le nombre de dossards nécessaires (= nombre de concurrents)
	/// puis à les créer dans le conteneur dossardsPourAffectation.
	/// Entre 2 et 100 dossards.
	/// </summary>
	void InitialiserCompetition() {

		int nombreDossards;
		std::deque<int> dossardsPourAffectation;

		do {
			std::cout << "Entrez le nombre de dossards nécessaires (entre 2 et 100) : ";
			std::cin >> nombreDossards;
		} while (nombreDossards < 2 || nombreDossards > 100);


		for (int i = 1; i <= nombreDossards; i++) {
			dossardsPourAffectation.push_back(i);
		}



		std::cout << "La compétition a été initialisée avec succès !" << std::endl;
	};

	/// <summary>
	/// Inscrire un concurent.
	/// Après vérification qu'il reste un dossard disponible, il faut:
	/// - saisir le nom du concurrent
	/// - retirer 1 dossard au hasard dans le conteneur dossardsPourAffectation
	/// - créer le concurrent avec son nom et le dossard
	/// - ajouter le concurrent au conteneur concurentsInscrits
	/// Pas d'inscription possible s'il ne reste plus de dossard disponible.
	/// Le concurrent est affiché ainsi que le nombre de dossards pouvant encore être attribués.
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
		std::srand(static_cast<unsigned>(std::time(nullptr)));  // nombres aléatoires
		int randomIndex = std::rand() % dossardsPourAffectation.size();
		auto it = dossardsPourAffectation.begin() + randomIndex;
		int dossard = *it;
		dossardsPourAffectation.erase(it);

		// Création du concurrent avec son nom et le dossard
		std::string concurrentInscrit = "Nom: " + nomConcurrent + ", Dossard: " + std::to_string(dossard);

		// Ajouter le concurrent au conteneur concurrentsInscrits
		concurrentsInscrits.push_back(concurrentInscrit);

		// Affichage du concurrent inscrit et du nombre de dossards restants
		std::cout << "Concurrent inscrit : " << concurrentInscrit << std::endl;
		std::cout << "Nombre de dossards restants : " << dossardsPourAffectation.size() << std::endl;
	};




	/// <summary>
	/// Affiche la liste des concurrents inscrits par ordre alphabétique des noms
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
	/// - insère le concurrent noté dans le conteneur resultats, les mieux notés rangés en premier
	/// Le score doit servir de clé pour retrouver tous les concurrents ayant un certain score.
	/// Attention!! On peut avoir plusieurs concurrents avec le même score.
	/// </summary>
	void NoterConcurrents();

	/// <summary>
	/// Affiche le score, le dossard et le nom des concurrents notés.
	/// </summary>
	void AfficherResultats();

	/// <summary>
	/// Boucle d'exécution du programme.
	/// </summary>
	void Run();
};

