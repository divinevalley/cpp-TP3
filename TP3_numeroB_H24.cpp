/*
 TP3
 Numero B
 Deanna Wung
 
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

#include <iostream> // entree-sortie standard
#include <iomanip>  // formatage (presentation)
#include <string>   // chaine de caracteres
#include <fstream>
#include <stdlib.h>
#include <string.h>

using namespace std; // librairie standard

class Personne
{
  private :
    char   sexe;
    int    numero;
    double taille, poids;
    string nomPre;

  public :
    Personne(char sexe, int numero, double taille, double poids, string nomPre);
    Personne();
    
    // surcharge operateur affichage <<
    friend ostream& operator << (ostream& sortie, const Personne& unePers);

    string getNomPre() ;
    char getSexe()
    {
        return sexe;
    }
    
    double getTaille()
    {
        return taille;
    }
    
    double getPoids()
    {
        return poids;
    }
    void afficher();
                  
};

struct Element {
    Personne pers;
    Element * suivant;
};

ostream& operator << (ostream& sortie, const Personne& unePers){
    sortie.setf(ios::fixed);
    sortie.setf(ios::showpoint);
    
    sortie << setw(25) << unePers.nomPre
            << setw(10) << (unePers.sexe == 'F' ? "feminin":"masculin")
           << setw(8) << unePers.numero
           << setw(8) << setprecision(2) << unePers.taille
           << setw(8) << setprecision(1) << unePers.poids << endl;
    
    return sortie;
    
}

typedef Element * Pointeur;

// Partie implementation
Personne::Personne(char sexe, int numero, double taille, double poids,
                      string nomPre)
{
    this->sexe = sexe;
    this->numero = numero;
    this->taille = taille;
    this->poids = poids;
    this->nomPre = nomPre;
}

Personne::Personne()
{
}

string Personne::getNomPre()
{
    return nomPre;
}

void Personne::afficher()
{
        cout.setf(ios::showpoint);
        cout.setf(ios :: fixed);
        
        cout   << setw(30) << nomPre
               << setw(6)  << numero
               << setw(8) << setprecision(2) << taille
               << setw(6) << setprecision(1) << poids
               << setw(10) << ( sexe == 'F' ? "feminin":"masculin")
               << endl;
}

// lire le fichier .txt et construire la liste de Personne
void lireRemplir(const char nomALire[], Pointeur& liste, Pointeur & dernier)
   {
    char   sexe;
    int    numero;
    double taille, poids;
    string nom;
    string prenom;
    
    liste = NULL;
    
      ifstream  aLire (nomALire, ios::in); // localiser et ouvrir pour la lecture
    
    while (aLire >> nom >> prenom >> sexe >> taille >> poids >> numero) {
        //construire une personne
        Personne unePers(sexe, numero, taille, poids, nom + " " + prenom);
        
        // Preparer nouvel element
        Pointeur tempo = new Element;
        tempo->pers = unePers;
        tempo->suivant = NULL;
        
        // mettre nouvel element sur la liste
        if(liste == NULL)
            liste = dernier = tempo;
        else{
            dernier->suivant = tempo;
            dernier = tempo;
        }
    }
    
       aLire.close();
   }
       
// afficher contenu de la liste, comptet et afficher aussi le nb d'elements
void afficher(Pointeur liste)
{
    cout << "-----CONTENU DE LA LISTE:-----\n";
    int n = 0 ;

    while(liste){
        cout << setw(2) << n++ << ") " << liste->pers;
        liste = liste->suivant;
    }
    
    cout << "===> Il y a " << n << " personnes dans la liste\n" << endl;
}

// afficher les N premieres personnes de la liste
void afficherN(Pointeur liste, int n){
    cout << "Affichage des " << n << " premieres personnes:\n";
    int compt = 0;
    while (liste && compt < n) {
        cout << setw(2) << compt++ << ") " << liste->pers;
        liste=liste->suivant;
    }
    cout << "\n";
}

// chercher la/les personne(s) de la liste ayant un certain nom. il faut mettre le nom en MAJUSCULES
void afficherNom(Pointeur liste, string nom){
    cout << "les personnes avec le nom " << nom << " :\n";
    int n = 0;
    while (liste) {
        if (liste->pers.getNomPre() == nom)
            cout << setw(2) << n << ") " << liste->pers;
        n++;
        liste=liste->suivant;
    }
    cout << "\n";
}

/* chercher un element Personne de la liste ayant un certain nom, renvoie par reference les pointeurs sur l'element d'avant et l'element recherche */
void chercher(Pointeur liste, string nomAChercher, Pointeur & avant, Pointeur & cestLui){
    avant = NULL; // initialiser, avant premier element, c'est null
    cestLui = liste; // initialiser au premier element
    
    // tant que liste non null et qu'on n'a pas trouve le nom
    while(cestLui && cestLui->pers.getNomPre() != nomAChercher){
        // avant prendre la place de cestlui
        avant = cestLui;
        
        // cestLui s'avance
        cestLui = cestLui->suivant;
    }
}

// chercher et supprimer un element Personne de la liste ayant un certain nom
void supprimer(Pointeur & liste, string nom){
    Pointeur avant = NULL;
    Pointeur cestLui;
    chercher(liste, nom, avant, cestLui);
    
    if(cestLui) // si trouve, cestlui ne sera pas null
    {
        if (avant) // si element d'avant non null
            avant->suivant = cestLui->suivant; // pointer vers element d'apres
        else // sinon, veut dire que cestlui est le premier element.
            liste = liste->suivant; // dans ce cas, on va juste maj la liste (pointeur) vers elem suivant
        
        delete cestLui; // liberer espace memoire
        cout << "suppression OK\n";
    }
    else
        cout << "introuvable\n";
    
    // si liste est vide
    if (liste == NULL) cout << "liste est vide\n";
}
   
int main() {

    cout.setf(ios::showpoint);
    cout.setf(ios::fixed);
    Pointeur liste, dernier;
        
    cout << "a-b) Lire fichier, creer liste chainee, compter et afficher le nb de personnes:\n";
    lireRemplir("met_h24.txt", liste, dernier);
    afficher(liste);
        
    cout << "c) Afficher les 9 premieres personnes\n";
    afficherN(liste, 9);

    cout << "d) Afficher toutes les personnes nommees, Robitaille Suzanne, de la liste.\n";
    afficherNom(liste, "ROBITAILLE SUZANNE");
        
    cout << "e) Supprimer la personne, Michaud Normand, puis reafficher les 7 premieres personnes de la liste.\n";
    supprimer(liste, "MICHAUD NORMAND");
    afficherN(liste, 7);
    
    cout << "(extra:) pour montrer que la suppression a bien reussi: \n";
    afficher(liste);
        
    return 0;
        
}

/*
 Execution:
 
 a-b) Lire fichier, creer liste chainee, compter et afficher le nb de personnes:

 -----CONTENU DE LA LISTE:-----
  0)               ROY CHANTAL   feminin    2754    1.75    57.9
  1)         MOLAISON CLAUDINE   feminin    1848    1.57    62.2
  2)       ROBITAILLE CHANTALE   feminin    2007    1.79    72.3
  3)         BEDARD MARC-ANDRE  masculin    2636    1.43    55.5
  4)           MONAST STEPHANE  masculin    1750    1.65    61.7
  5)              JALBERT LYNE   feminin    2168    1.63    52.6
  6)            DUBE FRANCOISE   feminin    4612    1.68    67.5
  7)        ROBITAILLE SUZANNE   feminin    2325    1.72    75.4
  8)            LEMELIN SOPHIE   feminin    7777    1.88    57.8
  9)              LABELLE LISE   feminin    1512    1.79    68.0
 10)          CHOQUETTE HELENE   feminin    2340    1.71    60.8
 11)        ROBITAILLE SUZANNE   feminin    8007    1.82    76.1
 12)           MICHAUD NORMAND  masculin    3428    1.73   103.7
 13)             RICHER AGATHE   feminin    3563    1.65    53.1
 14)          BEGIN MARIE-LUCE   feminin    4101    1.62    49.0
 15)        ROBITAILLE SUZANNE   feminin    7654    1.63    75.1
 16)              COUTU PIERRE  masculin    4008    1.72    62.1
 17)          TREMBLAY SUZANNE   feminin    4371    1.48    61.5
 18)        BERGEVIN GUILLAUME  masculin    2277    1.84    86.4
 19)            DUMITRU PIERRE  masculin    3629    1.82    99.4
 20)          ROBITAILLE LUCIE   feminin    6002    1.78    85.1
 21)              FILLION ERIC  masculin    2630    1.78    75.7
 22)           DESMARAIS DENIS  masculin    3215    1.79    58.7
 23)             TREMBLAY MARC  masculin    3529    1.79    64.9
 24)          TREMBLAY SYLVAIN  masculin    1538    1.83    86.2
 25)        ROBITAILLE SUZANNE   feminin    4119    1.68    60.2
 ===> Il y a 26 personnes dans la liste

 c) Afficher les 9 premieres personnes
 Affichage des 9 premieres personnes:
  0)               ROY CHANTAL   feminin    2754    1.75    57.9
  1)         MOLAISON CLAUDINE   feminin    1848    1.57    62.2
  2)       ROBITAILLE CHANTALE   feminin    2007    1.79    72.3
  3)         BEDARD MARC-ANDRE  masculin    2636    1.43    55.5
  4)           MONAST STEPHANE  masculin    1750    1.65    61.7
  5)              JALBERT LYNE   feminin    2168    1.63    52.6
  6)            DUBE FRANCOISE   feminin    4612    1.68    67.5
  7)        ROBITAILLE SUZANNE   feminin    2325    1.72    75.4
  8)            LEMELIN SOPHIE   feminin    7777    1.88    57.8

 d) Afficher toutes les personnes nommees, Robitaille Suzanne, de la liste.
 les personnes avec le nom ROBITAILLE SUZANNE :
  7)        ROBITAILLE SUZANNE   feminin    2325    1.72    75.4
 11)        ROBITAILLE SUZANNE   feminin    8007    1.82    76.1
 15)        ROBITAILLE SUZANNE   feminin    7654    1.63    75.1
 25)        ROBITAILLE SUZANNE   feminin    4119    1.68    60.2

 e) Supprimer la personne, Michaud Normand, puis reafficher les 7 premieres personnes de la liste.
 suppression OK
 Affichage des 7 premieres personnes:
  0)               ROY CHANTAL   feminin    2754    1.75    57.9
  1)         MOLAISON CLAUDINE   feminin    1848    1.57    62.2
  2)       ROBITAILLE CHANTALE   feminin    2007    1.79    72.3
  3)         BEDARD MARC-ANDRE  masculin    2636    1.43    55.5
  4)           MONAST STEPHANE  masculin    1750    1.65    61.7
  5)              JALBERT LYNE   feminin    2168    1.63    52.6
  6)            DUBE FRANCOISE   feminin    4612    1.68    67.5

 (extra:) pour montrer que la suppression a bien reussi:
 -----CONTENU DE LA LISTE:-----
  0)               ROY CHANTAL   feminin    2754    1.75    57.9
  1)         MOLAISON CLAUDINE   feminin    1848    1.57    62.2
  2)       ROBITAILLE CHANTALE   feminin    2007    1.79    72.3
  3)         BEDARD MARC-ANDRE  masculin    2636    1.43    55.5
  4)           MONAST STEPHANE  masculin    1750    1.65    61.7
  5)              JALBERT LYNE   feminin    2168    1.63    52.6
  6)            DUBE FRANCOISE   feminin    4612    1.68    67.5
  7)        ROBITAILLE SUZANNE   feminin    2325    1.72    75.4
  8)            LEMELIN SOPHIE   feminin    7777    1.88    57.8
  9)              LABELLE LISE   feminin    1512    1.79    68.0
 10)          CHOQUETTE HELENE   feminin    2340    1.71    60.8
 11)        ROBITAILLE SUZANNE   feminin    8007    1.82    76.1
 12)             RICHER AGATHE   feminin    3563    1.65    53.1
 13)          BEGIN MARIE-LUCE   feminin    4101    1.62    49.0
 14)        ROBITAILLE SUZANNE   feminin    7654    1.63    75.1
 15)              COUTU PIERRE  masculin    4008    1.72    62.1
 16)          TREMBLAY SUZANNE   feminin    4371    1.48    61.5
 17)        BERGEVIN GUILLAUME  masculin    2277    1.84    86.4
 18)            DUMITRU PIERRE  masculin    3629    1.82    99.4
 19)          ROBITAILLE LUCIE   feminin    6002    1.78    85.1
 20)              FILLION ERIC  masculin    2630    1.78    75.7
 21)           DESMARAIS DENIS  masculin    3215    1.79    58.7
 22)             TREMBLAY MARC  masculin    3529    1.79    64.9
 23)          TREMBLAY SYLVAIN  masculin    1538    1.83    86.2
 24)        ROBITAILLE SUZANNE   feminin    4119    1.68    60.2
 ===> Il y a 25 personnes dans la liste

 Program ended with exit code: 0
 
 
 */
