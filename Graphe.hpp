#ifndef _GRAPHE
#define _GRAPHE
#include <iostream>
#include <vector>
#include <queue>
#include "Element.hpp"
#include <string>

class Graphe;

class Sommet;

class Sommet
{
public:
    //Constructeur par défaut
    Sommet(Elem Altitude, int I, int J,char c);

    void    afficheSommet() const;
    double  DistanceSommet( Sommet dest);
    double Distancevoisin( int desti, int destj, int desta);

    friend class Graphe;
    Sommet *parent;
    bool pluscourt = false;
    //Données membres
    Elem altitude;
    int i; // ligne du sommet
    int j; // colonne du sommet
    double couttotale;
    double cout_heuristique, cout_parent;
    char couleur;
    bool existe;

};

class Graphe
{
public:

    //Constructeur par défaut
    Graphe(int L, int C);

    //Destructeur
    //~Graphe();
    void recherche(Sommet& initial, Sommet& finale);
    double Distancevoisin( int desti, int destj, int desta);

    //Affectation
    void remplirGraphe(std::string addr);

    //Affichage Graphe
    void affichage() const;

    // Accés aux voisins
    Sommet accesSommet(int i, int j);
    bool voisin(int i, int j);

    //Accés altitude
    Elem accesAltitude(int i, int j);
    //Distance aux voisins
    double distance(int i, int j,char voisin);

    struct prio
    {
        double distance;
        int i;
        int j;
        Elem altitude;
        char couleur = 'b';
    };
    void affiche(prio p);
    struct Custom
    {

        bool operator()(const prio& a, const prio& b)
        {
            return a.distance > b.distance;
        }


    };
    std::priority_queue<prio, std::vector<prio>, Custom> pq;
    std::priority_queue<prio, std::vector<prio>, Custom> temp;

  std::vector<Sommet> tab_test;
int cpt = -1;
    //Données membres
    int l; //Nb de lignes de la grille
    int c; //Nb de colonnes de la grille
    std::vector < Sommet> tab;
    std::vector <Sommet> meilleur_chemin;


};


#endif
