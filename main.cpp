#include <cstdio>
#include "Element.hpp"
#include "Graphe.hpp"

#include <iostream>
#include <string>
using namespace std;

int main()
{

    std::string addr;
    addr = "C:/Users/aDMiN/Documents/TP9 LIFAP6/test.txt";
    Graphe test(3,3);

    Sommet depart(0,0,0,'g');
    Sommet finale(67,2,2,'b');

    test.remplirGraphe(addr);
    cout<<" entre dans la recherche"<<endl;
    test.recherche(depart,finale);
    cout<< "sors de la recherche"<<endl;
    test.affichage();
    /*
    test.accesAltitude(1,1);
    résultat = test.distance(0,0,'N');
    cout << " le résultat est : "<<résultat <<endl;
    */



    return 0;
}

