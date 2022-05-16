#include "Element.hpp"
#include "Graphe.hpp"
using namespace std;
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <cstdio>

Sommet::Sommet(Elem Altitude, int I, int J,char c)
{
    altitude=Altitude;
    i=I;
    j=J;
    couleur = c;
    existe = true;

}

Graphe::Graphe(int L, int C)
{

    //vector<Sommet*> tab((l*c),0);
}

void Sommet::afficheSommet() const
{
    cout << altitude <<"--";
    //cout << "ligne " << i << endl;
    //cout << "colonne " << j << endl;
}

void Graphe::affichage() const
{


    for(int i =0; i<l; i++)
    {

        //cout << "nombre est :"<<nb<<endl;
        for(int j=0; j<c; j++)
        {

            if(tab[i*c+j].couleur == 'b')
            {
                std::cout <<"\033[1;"<<7<<"m"<<" Couleur " << tab[i*c+j].altitude << "\033[0m";
            }
            else if(tab[i*c+j].couleur =='g')
            {
                std::cout <<"\033[1;"<<47<<"m"<<" Couleur " << tab[i*c+j].altitude << "\033[0m";
            }
            else if(tab[i*c+j].couleur == 'n')
            {
                std::cout <<"\033[1;"<<90<<"m"<<" Couleur " << tab[i*c+j].altitude << "\033[0m";
            }

        }
        cout<<endl;
        //Et on l'affiche dans la console
        //Ou alors on fait quelque chose avec cette ligne
        //À vous de voir
    }

}

Sommet Graphe::accesSommet(int i, int j)
{
    int indice = (i*c+j);
    if ((tab[indice].existe) == true)
    {
        return tab[indice];
    }
    else
    {
        cout << "le sommet n'existe pas" << endl;
    }
}




bool Graphe::voisin(int i, int j)
{
    int indice = (i*c+j);
    if ((tab[indice].existe) == true)
    {
        return true;
    }
    else
    {
        return false;
    }
}

Elem Graphe::accesAltitude(int i, int j)
{
    int indice = (i*c+j);
    if (tab[indice].existe == true)
    {
        return tab[indice].altitude;
    }
    return 0;
}


double Graphe::distance(int i, int j, char voisin)
{
    int indice = (i*c+j);
    if (tab[indice].existe == true)
    {
        if(voisin=='N')
        {
            int nord = ((i-1) *c+j);
            if(tab[nord].existe == true)
            {
                return sqrt(1+sqrt(accesAltitude(i,j)-accesAltitude((i-1),j)));
            }
        }
        else if(voisin=='S')
        {
            int sud = ((i+1)*c+j);
            if(tab[sud].existe == true)
            {
                return sqrt(1+sqrt(accesAltitude(i,j)-accesAltitude((i+1),j)));
            }
        }
        else if(voisin=='O')
        {
            int est = (i*c+(j+1));
            if(tab[est].existe == true)
            {
                return sqrt(1+sqrt(accesAltitude(i,j)-accesAltitude(i,(j+1))));
            }
        }
        else if(voisin=='E')
        {
            int nord = (i*c+(j-1));
            if(tab[nord].existe == true)
            {
                return sqrt(1+sqrt(accesAltitude(i,j)-accesAltitude(i,(j-1))));
            }
        }
        else
        {
            cout << "entrez N,S,O ou E pour le voisin" << endl;
        }
    }
    else
    {
        return 0;
    }
    return 0;
}



void Graphe::remplirGraphe(string addr)
{
    ifstream fichier(addr);
    int nb_l;
    int nb_c;
    int nb;
    if(fichier)
    {
        //L'ouverture s'est bien passée, on peut donc lire

        string ligne; //Une variable pour stocker les lignes lues
        fichier >> nb_c;
        //  cout << "nb  colonne :"<< nb_c <<endl;
        fichier >> nb_l;
        //  cout << "nb ligne :"<< nb_l <<endl;
        l=nb_l;
        c=nb_c;
        //cout << "nb colonne c'est :"<<nb_c<<endl;
        //cout << "nb ligne c'est :"<<nb_l<<endl;
        getline(fichier, ligne); //Tant qu'on n'est pas à la fin, on lit
        for(int i =0; i<nb_l; i++)
        {
            //cout<<" notre i est :"<<i<<endl;
            //cout << "nombre est :"<<nb<<endl;
            for(int j=0; j<nb_c; j++)
            {
                //cout<<" notre j est :"<<j<<endl;
                fichier >> nb;
                //cout<< "notre nb est :"<<nb<<endl;
                Sommet s(nb,i,j,'b');
                tab.push_back(s);
                s.existe = true;

            }
            //Et on l'affiche dans la console
            //Ou alors on fait quelque chose avec cette ligne
            //À vous de voir
        }

    }
    else
    {
        cout << "ERREUR: Impossible d'ouvrir le fichier en lecture." << endl;
    }
    tab[0].couleur = 'g';
}

double  Sommet::DistanceSommet(Sommet dest)
{
    double D = sqrt(((i - dest.i)*(i - dest.i))
                    + ((j - dest.j)*(j - dest.j)) + ((altitude - dest.altitude)*(altitude-dest.altitude)));
    return D;
}


double  Sommet::Distancevoisin( int desti, int destj, int desta)
{
    double D = sqrt((0.2*(i - desti)*(i - desti))
                    + (0.2*(j - destj)*(j - destj)) + (0.6*(altitude - desta)*(altitude-desta)));
    return D;
}

void Graphe::affiche(prio p)
{
    cout<<"alti : "<<p.altitude<<"distance :"<<p.distance<<" i :"<<p.i<< "  et j :"<<p.j<<endl;
}

void Graphe::recherche(Sommet& initiale, Sommet& finale)
{

    //distance réelle entre un voisin et son sommet
    double distance_nord = initiale.Distancevoisin(initiale.i-1,initiale.j,accesAltitude(initiale.i-1,initiale.j));
    double distance_sud = initiale.Distancevoisin(initiale.i+1,initiale.j,accesAltitude(initiale.i+1,initiale.j));
    double distance_est = initiale.Distancevoisin(initiale.i,initiale.j+1,accesAltitude(initiale.i,initiale.j+1));
    double distance_ouest = initiale.Distancevoisin(initiale.i,initiale.j-1,accesAltitude(initiale.i,initiale.j-1));

    //distance heuristique ( a vole d'oiseau ) entre notre point initiale et le point finale
    double distance_nord_finale = finale.Distancevoisin(initiale.i-1,initiale.j,accesAltitude(initiale.i-1,initiale.j));
    double distance_sud_finale  =finale.Distancevoisin(initiale.i+1,initiale.j,accesAltitude(initiale.i+1,initiale.j));
    double distance_est_finale  =finale.Distancevoisin(initiale.i,initiale.j+1,accesAltitude(initiale.i,initiale.j+1));
    double distance_ouest_finale  =finale.Distancevoisin(initiale.i,initiale.j-1,accesAltitude(initiale.i,initiale.j-1));

    // distance totale = distance entre le sommet et son voisin + distance heuristique

    initiale.cout_heuristique = initiale.DistanceSommet(finale);
    double distance_est_totale = distance_est + distance_est_finale;
    double distance_ouest_totale = distance_ouest + distance_ouest_finale;
    double distance_nord_totale = distance_nord + distance_nord_finale;
    double distance_sud_totale = distance_sud + distance_sud_finale;
    prio pest,pouest,pnord,psud;

    pest.distance = distance_est_totale;
    pest.i = initiale.i;
    pest.j = initiale.j +1;
    pest.altitude = accesAltitude(pest.i,pest.j);

    pouest.distance = distance_ouest_totale;
    pouest.i = initiale.i;
    pouest.j = initiale.j -1;
    pouest.altitude = accesAltitude(pouest.i,pouest.j);

    psud.distance = distance_sud_totale;
    psud.i = initiale.i +1;
    psud.j = initiale.j;
    psud.altitude = accesAltitude(psud.i,psud.j);

    pnord.distance = distance_nord_totale;
    pnord.i = initiale.i - 1;
    pnord.j = initiale.j ;
    pnord.altitude = accesAltitude(pnord.i,pnord.j);

cout<<" !!! test sud distance !!! "<<psud.distance;
cout<<"    ,!!! test est distance !!! "<<pest.distance<<endl;

    if(initiale.couleur != 'n')
    {
        cout<<" pest avant push : "<<pest.distance<< "  psud avant push : "<<psud.distance<<endl;

        if(pest.i >= 0 && pest.j > 0 && pest.i<l && pest.j <c)
        {
            if(voisin(pest.i,pest.j))
            {
                pq.push(pest);
                temp.push(pest);
            }
        }

        if(psud.i >= 0 && psud.j > 0 && psud.i<l && psud.j <c)
        {
            if(voisin(psud.i,psud.j))
            {
                pq.push(psud);
                temp.push(psud);
            }
        }
    }

    initiale.couleur = 'n';

    /*
    if(pnord.i >= 0 && pnord.j > 0 && pnord.i<l && pnord.j <c){
    if(voisinNord(pnord.i,pnord.j)) pq.push(pnord);}

    if(pouest.i >= 0 && pouest.j > 0 && pouest.i<l && pouest.j <c){
    if(voisinOuest(pouest.i,pouest.j)) pq.push(pouest);}

    */

    bool estTrouve= false;
    bool existe = true;
    if(finale.existe == false)
    {
        existe = false;
    }
    if( initiale.DistanceSommet(finale) == 0)
    {
        estTrouve = true;
    }

    if(estTrouve == false )
    {

        affiche(pq.top());
        Sommet init(pq.top().altitude, pq.top().i, pq.top().j, 'g');

        pq.pop();
        affiche(pq.top());

        cout<<"notre Sommet actuel ";
        initiale.afficheSommet();
        cout<<" vers le prochain sommet :";
        init.afficheSommet();
        cout<<endl;


        //if(initiale.couleur == 'n')  meilleur_chemin.push_back(initiale);
        recherche(init,finale);



    }

    while(!meilleur_chemin.empty())
    {
        cout<<"meilleur_chemin"<<endl;
        cout<<"altitude meilleur :"<<meilleur_chemin[0].altitude;
        cout<<" i :"<<meilleur_chemin[0].i;
        cout<<" j :"<<meilleur_chemin[0].j<<endl;
        meilleur_chemin.pop_back();
    }



}



