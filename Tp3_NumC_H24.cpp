/*
 
 TP3
 Numero C
 Deanna Wung
 
 Refaites le numéro B en utilisant un conteneur list<Personne>.
 
 On dispose du fichier texte nomme : met_h24.txt qui contient au maximum 30 lignes.
 Chaque ligne contient les informations d’une seule personne dans le systeme metrique :
 Nom et prenom, sexe, taille en metre, poids en kg et son numero.
 
 ROY CHANTAL                           F      1.75           57.9        2754
 MOLAISON CLAUDINE             F      1.57           62.2        1848
 ROBITAILLE CHANTALE         F      1.79           72.3         2007
 BEDARD MARC-ANDRE          M      1.43          55.5         2636
 MONAST STEPHANE                M      1.65          61.7         1750
 Etc.
 
 Le programme Tab_Bis_Pers.cpp permet de lire le fichier met_h24.txt, de memoriser les informations lues dans un tableau des personnes, etc.
 
 ecrivez un programme permettant de realiser les tâches dans l’ordre ci-dessous :
 
 a)    Lire le fichier met_h24.txt, creer une liste chainee programmee, des personnes en utilisant des pointeurs dans l’ordre FIFO. (5 points)
 b)    Compter et afficher le nombre de personnes presentes dans la liste. (2 points)
 c)    Afficher les 9 premieres personnes de la liste. (2 points)
 d)    Afficher toutes les personnes nommees, Robitaille Suzanne, de la liste. (3 points)
 e)    Supprimer la personne, Michaud Normand, puis reafficher les 7 premieres personnes de la liste. (3 points)
 */


#include <iostream> // entree-sortie standard cin, cout
#include <iomanip>  // formatage (presentation)
#include <string>   // chaine de caracteres
#include <fstream>
#include <stdlib.h>
#include <string.h>
#include <list>

using namespace std;

class Personne
{
    private :
    char sexe ;
    float taille, poids ;
    int numero;
    string nomPre;
    
    public :
    Personne(char sexe, int numero, float taille, float poids, string nomPre)
    {
        this->sexe = sexe;
        this->numero = numero;
        this->taille = taille;
        this->poids = poids;
        this->nomPre = nomPre;
        
    }
    
    Personne(string); // pour rechercher a partir d'un nomPre donne
    
    Personne()
    {
    }
    
    // surcharger l'operateur d'affichage :
    friend ostream& operator << (ostream&, const Personne&);
    
    // surcharge operateurs
    bool operator == (const Personne & autre);
    
    char getSexe()
    {
        return sexe;
    }
    
    string getNomPre(){
        return nomPre;
    }
    
};

bool Personne::operator == (const Personne & autre)
{
    return this->nomPre == autre.nomPre;
}

// constructeur pour une Personne avec un nomPre seulement. normaliser nomPre, utile pour la recherche
Personne::Personne(string nom){
    int nbCar = nom.length();
    
    // convertir en majuscules
    for (int i=0; i<nbCar; i++) {
        if(nom[i] >='a' && nom[i]<='z') // si minuscule
            nom[i] += 'A'-'a'; // convertir en ajoutant la difference
    }
    
    // ajouter des blancs a la fin pour normaliser
    for (int i=nbCar; i < 30; i++) {
        nom += " ";
    }
    
    nomPre = nom;
    sexe = ' ';
    taille = 0.0;
    poids = 0.0;
    numero = 0;
}


ostream& operator << (ostream& sortie, const Personne& unePers)
{
    sortie.setf(ios::fixed);
    sortie.setf(ios::showpoint);
    
    sortie << setw(30) << unePers.nomPre
    << setw(10) << (unePers.sexe == 'F' ? "feminin":"masculin")
    << setw(8) << unePers.numero
    << setw(7) << setprecision(2) << unePers.taille
    << setw(8) << setprecision(1) << unePers.poids;
    return sortie;
}

void lireRemplirList(string nomFichier, list<Personne> & liste){
    ifstream  aLire (nomFichier, ios::in); // localiser et ouvrir pour la lecture
    string ligneLue;
    
    while (  getline(aLire, ligneLue, '\n')) // lire jusqua \n la fin de la ligne
    {
          char sexe = ligneLue[30];
          float taille = stof(ligneLue.substr(37,4));  // a partir de la position 37, 4 carac
          float poids  = stof(ligneLue.substr(51,5));    // position 51, extraire 5 carac
          int numero = stoi(ligneLue.substr(64,4));     // transformer en entier
          string nomPre = ligneLue.substr(0, 30); // prendre les 30 premiers carac
                      
          liste.push_back(Personne(sexe, numero, taille, poids, nomPre));
    }

    aLire.close();   // fermer le fichier a lire

}


// afficher contenu d'un conteneur (list) de Personnes
void afficherList(list<Personne> liste){
    cout << "-- Contenu de la liste : -- " << endl;
    int rang = 0;
    
    list<Personne>::iterator il = liste.begin();
    for (il = liste.begin(); il !=liste.end(); il++) {
        cout << setw(2) << rang++ << ") " << *il << "\n";
    }
    cout << "===>Il y a " << liste.size() << " personnes dans la liste.\n" << endl;
}

// afficher N premieres Personnes
void afficherNPremieres(list<Personne> liste, int n){
    cout << "-- " << n << " premieres personnes : -- " << endl;
    
    list<Personne>::iterator il = liste.begin();
    int compt = 0;
    for (il = liste.begin(); compt < n; il++) {
        cout << compt++ << ") " << *il << "\n";
    }
    cout << "\n";
}


// rechercher et afficher la/les personne ayant un certain nom dans la liste
void afficherNom(list<Personne> liste, string nomAChercherAfficher){
    cout << "-- les personnes ayant le nom " << nomAChercherAfficher << " : -- " << endl;
    Personne PersonneAvecNom = Personne(nomAChercherAfficher);
    
    list<Personne>::iterator il = liste.begin();
    
    for (il = liste.begin(); il!=liste.end(); il++) {
        if(*il == PersonneAvecNom) // si on trouve, afficher
            cout << *il << endl;
    }
    
    cout << "\n";
}

// trouver et supprimer la personne de la liste ayant un certain nom
void supprimerNom(list<Personne> & liste, string nomAChercher){
    Personne personneNom = Personne(nomAChercher);
    
    //initialiser iterator et utiliser find() pour placer iterator
    list<Personne>::iterator il;
    il = find(liste.begin(), liste.end(), personneNom);
    
    if(il!=liste.end()) {// si trouve
        liste.erase(il);
        cout << "suppression ok." << endl;
    } else {
        cout << "introuvable." << endl;
    }
}



int main() {
  
    cout << "a-b) Lire fichier, creer liste chainee, compter et afficher le nb de personnes:" << endl;
    // creation conteneur/list
    list<Personne> listePersonnes;
    lireRemplirList("met_h24.txt", listePersonnes);
    afficherList(listePersonnes);
    
    cout << "c) Afficher les 9 premieres personnes" << endl;
    afficherNPremieres(listePersonnes, 9);
    
    cout << "d) Afficher toutes les personnes nommees, Robitaille Suzanne, de la liste." << endl;
    afficherNom(listePersonnes, "ROBITAILLE SUZANNE");
    
    cout << "e) Supprimer la personne, Michaud Normand, puis reafficher les 7 premieres personnes de la liste." << endl;
    supprimerNom(listePersonnes, "MICHAUD NORMAND");
    afficherNPremieres(listePersonnes, 7);
    
    cout << "(extra)... juste pour s'assurer que la suppression a reussi, totalite de la liste: " << endl;
    afficherList(listePersonnes);
    
    return 0;
    
    
}

/*
 Execution:

 a-b) Lire fichier, creer liste chainee, compter et afficher le nb de personnes:

 -- Contenu de la liste : --
  0) ROY CHANTAL                      feminin    2754   1.75    57.9
  1) MOLAISON CLAUDINE                feminin    1848   1.57    62.2
  2) ROBITAILLE CHANTALE              feminin    2007   1.79    72.3
  3) BEDARD MARC-ANDRE               masculin    2636   1.43    55.5
  4) MONAST STEPHANE                 masculin    1750   1.65    61.7
  5) JALBERT LYNE                     feminin    2168   1.63    52.6
  6) DUBE FRANCOISE                   feminin    4612   1.68    67.5
  7) ROBITAILLE SUZANNE               feminin    2325   1.72    75.4
  8) LEMELIN SOPHIE                   feminin    7777   1.88    57.8
  9) LABELLE LISE                     feminin    1512   1.79    68.0
 10) CHOQUETTE HELENE                 feminin    2340   1.71    60.8
 11) ROBITAILLE SUZANNE               feminin    8007   1.82    76.1
 12) MICHAUD NORMAND                 masculin    3428   1.73   103.7
 13) RICHER AGATHE                    feminin    3563   1.65    53.1
 14) BEGIN MARIE-LUCE                 feminin    4101   1.62    49.0
 15) ROBITAILLE SUZANNE               feminin    7654   1.63    75.1
 16) COUTU PIERRE                    masculin    4008   1.72    62.1
 17) TREMBLAY SUZANNE                 feminin    4371   1.48    61.5
 18) BERGEVIN GUILLAUME              masculin    2277   1.84    86.4
 19) DUMITRU PIERRE                  masculin    3629   1.82    99.4
 20) ROBITAILLE LUCIE                 feminin    6002   1.78    85.1
 21) FILLION ERIC                    masculin    2630   1.78    75.7
 22) DESMARAIS DENIS                 masculin    3215   1.79    58.7
 23) TREMBLAY MARC                   masculin    3529   1.79    64.9
 24) TREMBLAY SYLVAIN                masculin    1538   1.83    86.2
 25) ROBITAILLE SUZANNE               feminin    4119   1.68    60.2
 ===>Il y a 26 personnes dans la liste.

 c) Afficher les 9 premieres personnes
 -- 9 premieres personnes : --
 0) ROY CHANTAL                      feminin    2754   1.75    57.9
 1) MOLAISON CLAUDINE                feminin    1848   1.57    62.2
 2) ROBITAILLE CHANTALE              feminin    2007   1.79    72.3
 3) BEDARD MARC-ANDRE               masculin    2636   1.43    55.5
 4) MONAST STEPHANE                 masculin    1750   1.65    61.7
 5) JALBERT LYNE                     feminin    2168   1.63    52.6
 6) DUBE FRANCOISE                   feminin    4612   1.68    67.5
 7) ROBITAILLE SUZANNE               feminin    2325   1.72    75.4
 8) LEMELIN SOPHIE                   feminin    7777   1.88    57.8

 d) Afficher toutes les personnes nommees, Robitaille Suzanne, de la liste.
 -- les personnes ayant le nom ROBITAILLE SUZANNE : --
 ROBITAILLE SUZANNE               feminin    2325   1.72    75.4
 ROBITAILLE SUZANNE               feminin    8007   1.82    76.1
 ROBITAILLE SUZANNE               feminin    7654   1.63    75.1
 ROBITAILLE SUZANNE               feminin    4119   1.68    60.2

 e) Supprimer la personne, Michaud Normand, puis reafficher les 7 premieres personnes de la liste.
 suppression ok.
 -- 7 premieres personnes : --
 0) ROY CHANTAL                      feminin    2754   1.75    57.9
 1) MOLAISON CLAUDINE                feminin    1848   1.57    62.2
 2) ROBITAILLE CHANTALE              feminin    2007   1.79    72.3
 3) BEDARD MARC-ANDRE               masculin    2636   1.43    55.5
 4) MONAST STEPHANE                 masculin    1750   1.65    61.7
 5) JALBERT LYNE                     feminin    2168   1.63    52.6
 6) DUBE FRANCOISE                   feminin    4612   1.68    67.5

 (extra)... juste pour s'assurer que la suppression a reussi, totalite de la liste:
 -- Contenu de la liste : --
  0) ROY CHANTAL                      feminin    2754   1.75    57.9
  1) MOLAISON CLAUDINE                feminin    1848   1.57    62.2
  2) ROBITAILLE CHANTALE              feminin    2007   1.79    72.3
  3) BEDARD MARC-ANDRE               masculin    2636   1.43    55.5
  4) MONAST STEPHANE                 masculin    1750   1.65    61.7
  5) JALBERT LYNE                     feminin    2168   1.63    52.6
  6) DUBE FRANCOISE                   feminin    4612   1.68    67.5
  7) ROBITAILLE SUZANNE               feminin    2325   1.72    75.4
  8) LEMELIN SOPHIE                   feminin    7777   1.88    57.8
  9) LABELLE LISE                     feminin    1512   1.79    68.0
 10) CHOQUETTE HELENE                 feminin    2340   1.71    60.8
 11) ROBITAILLE SUZANNE               feminin    8007   1.82    76.1
 12) RICHER AGATHE                    feminin    3563   1.65    53.1
 13) BEGIN MARIE-LUCE                 feminin    4101   1.62    49.0
 14) ROBITAILLE SUZANNE               feminin    7654   1.63    75.1
 15) COUTU PIERRE                    masculin    4008   1.72    62.1
 16) TREMBLAY SUZANNE                 feminin    4371   1.48    61.5
 17) BERGEVIN GUILLAUME              masculin    2277   1.84    86.4
 18) DUMITRU PIERRE                  masculin    3629   1.82    99.4
 19) ROBITAILLE LUCIE                 feminin    6002   1.78    85.1
 20) FILLION ERIC                    masculin    2630   1.78    75.7
 21) DESMARAIS DENIS                 masculin    3215   1.79    58.7
 22) TREMBLAY MARC                   masculin    3529   1.79    64.9
 23) TREMBLAY SYLVAIN                masculin    1538   1.83    86.2
 24) ROBITAILLE SUZANNE               feminin    4119   1.68    60.2
 ===>Il y a 25 personnes dans la liste.

 Program ended with exit code: 0
 
 */
