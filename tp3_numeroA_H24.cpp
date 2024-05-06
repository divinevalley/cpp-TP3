/* Fichier TP3_NumA_H24.cpp
 
 Deanna Wung
 IFT 1166
 H24
 
 A completer pour le numero A du TP #3, Hiver 2024 (10 points)
 
 Taches a faire :
 1. Afficher le tableau des cercles en utilisant, entre
 autres, la surcharge de l'operateur d'affichage <<
 
 2. Permuter ces elements : c[0] et c[4] , c[1] et c[3]
 Reafficher le tableau apres ces deux permutations.
 
 3. Determiner et afficher :
 a) Le cercle ayant le plus petit rayon ;
 b) Le cercle ayant le plus grand rayon.
 En utilisant, entre autres :
 - Une seule fonction template ;
 - La surcharge des operateurs > et <
 
 4. Trier le tableau des cercles par le tri rapide, puis
 reafficher ce tableau apres le tri.
 
 Criteres de correction :
 Tache 1. 2 points
 Tache 2. 2 points
 Tache 3. 3 points
 Tache 4. 3 points
 */

#include <iostream>
#include <iomanip>

using namespace std;

const float PI = 3.14159;
class Cercle
{   private :
    float rayon ; // l'acces au champ rayon est prive
    
    public :
    // un constructeur : conflit entre nom de parametre et nom de champ
    // => on utilise le pointeur this o˘ *this est l'objet courant
    Cercle(float rayon = 5.7)
    {
        this->rayon = rayon ;// c'est meme chose que (*this).rayon;
    }
    
    // fonction membre
    float perimetre()
    {
        return 2 * PI * rayon;
    }
    
    // fonction membre : definition reportee
    float surface();
    
    // afficher un cercle avec un message pertinent
    void afficher(string message = "")
    {
        if(message.length() > 0)
        {
            cout << message << " : " << endl;
            cout << " - rayon                 : " << rayon << endl;
            cout << " - perimetre             : " << perimetre() << endl;
            cout << " - surface               : " << surface() << endl << endl;
        }
        else
            cout << setw(8) << setprecision(1) << rayon
            << setw(10) << setprecision(2) << perimetre()
            << setw(9) << setprecision(2) << surface() << endl;
    }
    
    //surcharger operateur d'affichage:
    friend ostream& operator << (ostream&, Cercle & cercle);
    
    // surcharge operateurs < > =
    bool operator < (Cercle & autre);
    bool operator > (Cercle & autre);
    bool operator <= (Cercle & autre);
    bool operator >= (Cercle & autre);
    bool operator = (Cercle & autre);
    
    float getRayon(); // definition reportee
    void setRayon(float nouvRayon);
};

ostream& operator << (ostream& os, Cercle & cercle){
    os <<  " - rayon : " << cercle.rayon << " - perimetre : " << cercle.perimetre() << " - surface : " << cercle.surface();
    return os;
}

bool Cercle::operator > (Cercle & autre){
    return (this->rayon > autre.rayon);
}

bool Cercle::operator < (Cercle & autre){
    return (this->rayon < autre.rayon);
}

bool Cercle::operator >= (Cercle & autre){
    return (this->rayon >= autre.rayon);
}

bool Cercle::operator <= (Cercle & autre){
    return (this->rayon <= autre.rayon);
}

bool Cercle::operator = (Cercle & autre){
    return (this->rayon = autre.rayon);
}

float Cercle::surface()
{
    return PI * rayon * rayon;
}

float Cercle::getRayon()
{
    return rayon;
}

void Cercle::setRayon(float nouvRayon)
{
    rayon = nouvRayon;
}

// #1. afficher le tableau de Cercles avec operateur <<
void afficherTab(Cercle tab[], int nbElem){
    for (int i = 0; i < nbElem; i++) {
        cout << i << ") " <<  tab[i] << endl;
    }
    cout << endl;
}

// #2. permuter 2 elements
template <class T>
void permuter(T & a, T & b){
    T temp = a;
    a = b;
    b = temp;
}

// #3. fonction template pour trouver l'objet le plus petit et le plus grand
template <class T>
void trouverMiniEtMaxi(T tab[], int nbElem, T & objMini, T & objMaxi){
    T mini = tab[0];
    T maxi = tab[0];
    for (int i=1; i < nbElem; i++) {
        if (tab[i] < mini) { // si plus petit que mini,
            mini = tab[i]; // mettre a jour mini
        }
        if (tab[i]>maxi){ // si plus grand que maxi
            maxi = tab[i]; // m a j maxi
        }
    }
    // renvoyer resultats par ref &
    objMaxi = maxi;
    objMini = mini;
}

template <class T>
int partitionner(T tab[], int debut, int fin){
    int g = debut, d = fin;
    T valPivot = tab[debut];
    
    do {
        while (g <= d && tab[g] <= valPivot) g++;
        while (tab[d]>valPivot) d--;
        if(g<d)
            permuter(tab[g],tab[d]);
        
    } while (g <= d);
    
    permuter(tab[d], tab[debut]);
    return d;
}

template <class T>
void quickSort(T tab[], int gauche, int droite){
    if (droite>gauche){
        int indPivot = partitionner(tab, gauche, droite);
        quickSort(tab, gauche, indPivot-1);
        quickSort(tab, indPivot+1, droite);
    }
}

int main()
{
    
    Cercle c[] = { Cercle(6.2), Cercle(), Cercle(9.3), Cercle (6.9),
        Cercle(4.1), Cercle(12.6), Cercle(8.4) };
    int nbCercle = sizeof(c) / sizeof(Cercle);
    
    cout << "1. Afficher le tableau des cercles, avec surcharge de l'operateur << \n" << endl;
    afficherTab(c, nbCercle);
    
    cout << "2. Permuter c[0] et c[4] , c[1] et c[3]\n" << endl;
    permuter(c[0], c[4]);
    permuter(c[1], c[3]);
    afficherTab(c, nbCercle);
    
    cout << "3. trouver cercle minimal / maximal \n" << endl;
    Cercle mini;
    Cercle maxi;
    trouverMiniEtMaxi(c, nbCercle, mini, maxi);
    cout << "cercle le plus petit:\n" << mini << endl;
    cout << "cercle le plus grand:\n" << maxi << endl;
    cout << endl;
    
    cout << "4. trier par quicksort et reafficher \n" << endl;
    quickSort(c, 0, nbCercle-1);
    afficherTab(c, nbCercle);
    
    return 0;
}



/* Execution :
 
 1. Afficher le tableau des cercles, avec surcharge de l'operateur <<

 0)  - rayon : 6.2 - perimetre : 38.9557 - surface : 120.763
 1)  - rayon : 5.7 - perimetre : 35.8141 - surface : 102.07
 2)  - rayon : 9.3 - perimetre : 58.4336 - surface : 271.716
 3)  - rayon : 6.9 - perimetre : 43.3539 - surface : 149.571
 4)  - rayon : 4.1 - perimetre : 25.761 - surface : 52.8101
 5)  - rayon : 12.6 - perimetre : 79.1681 - surface : 498.759
 6)  - rayon : 8.4 - perimetre : 52.7787 - surface : 221.671

 2. Permuter c[0] et c[4] , c[1] et c[3]

 0)  - rayon : 4.1 - perimetre : 25.761 - surface : 52.8101
 1)  - rayon : 6.9 - perimetre : 43.3539 - surface : 149.571
 2)  - rayon : 9.3 - perimetre : 58.4336 - surface : 271.716
 3)  - rayon : 5.7 - perimetre : 35.8141 - surface : 102.07
 4)  - rayon : 6.2 - perimetre : 38.9557 - surface : 120.763
 5)  - rayon : 12.6 - perimetre : 79.1681 - surface : 498.759
 6)  - rayon : 8.4 - perimetre : 52.7787 - surface : 221.671

 3. trouver cercle minimal / maximal

 cercle le plus petit:
  - rayon : 4.1 - perimetre : 25.761 - surface : 52.8101
 cercle le plus grand:
  - rayon : 12.6 - perimetre : 79.1681 - surface : 498.759

 4. trier par quicksort et reafficher

 0)  - rayon : 4.1 - perimetre : 25.761 - surface : 52.8101
 1)  - rayon : 5.7 - perimetre : 35.8141 - surface : 102.07
 2)  - rayon : 6.2 - perimetre : 38.9557 - surface : 120.763
 3)  - rayon : 6.9 - perimetre : 43.3539 - surface : 149.571
 4)  - rayon : 8.4 - perimetre : 52.7787 - surface : 221.671
 5)  - rayon : 9.3 - perimetre : 58.4336 - surface : 271.716
 6)  - rayon : 12.6 - perimetre : 79.1681 - surface : 498.759

 Program ended with exit code: 0
 
 */
