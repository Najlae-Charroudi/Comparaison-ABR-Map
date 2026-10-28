#include <iostream>
#include <chrono>
#include <map>
#include <cstdlib>
#include <ctime>
using namespace std;

struct Noeud {
    int valeur;
    Noeud* gauche;
    Noeud* droite;
};

Noeud* creerNoeud(int x) {
    Noeud* p = new Noeud;
    p->valeur = x;
    p->gauche = NULL;
    p->droite = NULL;
    return p;
}

Noeud* inserer(Noeud* racine, int x) {
    if (racine == NULL)
        return creerNoeud(x);

    if (x < racine->valeur)
        racine->gauche = inserer(racine->gauche, x);

    else if (x > racine->valeur)
        racine->droite = inserer(racine->droite, x);

    return racine;
}


void afficherArbre(Noeud* racine, int espace = 0) {
    if (racine == NULL)
        return;
    espace = espace + 5;
    afficherArbre(racine->droite, espace);
    cout << endl;
    for (int i = 5; i < espace; i++)
        cout << " ";
    cout << racine->valeur << endl;
    afficherArbre(racine->gauche, espace);
}


void afficherInfixe(Noeud* racine) {
    if (racine != NULL) {
        afficherInfixe(racine->gauche);
        cout << racine->valeur << " ";
        afficherInfixe(racine->droite);
    }
}


bool rechercher(Noeud* racine, int x) {
    if (racine == NULL)
        return false;

    if (x == racine->valeur)
        return true;

    if (x < racine->valeur)
        return rechercher(racine->gauche, x);

    return rechercher(racine->droite, x);
}

///pour trouver le minimum
Noeud* minimum(Noeud* racine) {
    while (racine->gauche != NULL)
        racine = racine->gauche;

    return racine;
}
///pour supprimer avec les 3 cas
Noeud* supprimer(Noeud* racine, int x) {
    if (racine == NULL)
        return NULL;

    if (x < racine->valeur) {
        racine->gauche = supprimer(racine->gauche, x);
    }
    else if (x > racine->valeur) {
        racine->droite = supprimer(racine->droite, x);
    }
    else {
        ///aucun fils
        if (racine->gauche == NULL &&
            racine->droite == NULL) {
            delete racine;
            return NULL;
        }

       ///un seul fils droite
        if (racine->gauche == NULL) {
            Noeud* p = racine->droite;
            delete racine;
            return p;
        }

        ///un seul fils gauche
        if (racine->droite == NULL) {
            Noeud* p = racine->gauche;
            delete racine;
            return p;
        }

        ///deux fils
        Noeud* p = minimum(racine->droite);

        racine->valeur = p->valeur;

        racine->droite =
            supprimer(racine->droite, p->valeur);
    }

    return racine;
}

///////////////////////////////////MAP////////////////////////////////////



// Insertion d'une valeur
void inserer(map<int, int>& m, int x) {
    m.insert({x, x});
}

// Recherche d'une valeur
bool rechercher(map<int, int>& m, int x) {
    return m.find(x) != m.end();
}

// Suppression d'une valeur
void supprimer(map<int, int>& m, int x) {
    m.erase(x);
}

// Affichage des elements
void afficher(map<int, int>& m) {
    for (map<int, int>::iterator it = m.begin();
         it != m.end(); it++) {
        cout << it->first << " ";
    }
    cout << endl;
}


// Calcul du temps d'execution d'une operation
template <typename Fonction>
long long calculerTemps(Fonction operation) {
    auto debut = chrono::high_resolution_clock::now();

    operation();

    auto fin = chrono::high_resolution_clock::now();

    return chrono::duration_cast<chrono::nanoseconds>(
        fin - debut
    ).count();
}




int main() {
    const int N = 80000;

    int* ordonne = new int[N];
    int* aleatoire = new int[N];

    for (int i = 0; i < N; i++) {
        ordonne[i] = i + 1;
        aleatoire[i] = i + 1;
    }


    srand(time(NULL));

    for (int i = N - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = aleatoire[i];
        aleatoire[i] = aleatoire[j];
        aleatoire[j] = temp;
    }

    cout << "Nombre d'elements : " << N << endl;

    auto debut = chrono::high_resolution_clock::now();
    auto fin = chrono::high_resolution_clock::now();

    cout << "\n===== ABR : ORDONNES =====\n";

    Noeud* arbre = NULL;

    debut = chrono::high_resolution_clock::now();

    for (int i = 0; i < N; i++)
        arbre = inserer(arbre, ordonne[i]);

    fin = chrono::high_resolution_clock::now();

    long long tInsABRO =
        chrono::duration_cast<chrono::nanoseconds>(fin - debut).count();

    debut = chrono::high_resolution_clock::now();

    for (int i = 0; i < N; i++)
        rechercher(arbre, ordonne[i]);

    fin = chrono::high_resolution_clock::now();

    long long tRecABRO =
        chrono::duration_cast<chrono::nanoseconds>(fin - debut).count();

    debut = chrono::high_resolution_clock::now();

    for (int i = 0; i < N; i++)
        arbre = supprimer(arbre, ordonne[i]);

    fin = chrono::high_resolution_clock::now();

    long long tSupABRO =
        chrono::duration_cast<chrono::nanoseconds>(fin - debut).count();

    cout << "Insertion  : " << tInsABRO << " ns\n";
    cout << "Recherche  : " << tRecABRO << " ns\n";
    cout << "Suppression: " << tSupABRO << " ns\n";


    cout << "\n===== ABR : ALEATOIRES =====\n";

    arbre = NULL;

    debut = chrono::high_resolution_clock::now();

    for (int i = 0; i < N; i++)
        arbre = inserer(arbre, aleatoire[i]);

    fin = chrono::high_resolution_clock::now();

    long long tInsABRA =
        chrono::duration_cast<chrono::nanoseconds>(fin - debut).count();

    debut = chrono::high_resolution_clock::now();

    for (int i = 0; i < N; i++)
        rechercher(arbre, aleatoire[i]);

    fin = chrono::high_resolution_clock::now();

    long long tRecABRA =
        chrono::duration_cast<chrono::nanoseconds>(fin - debut).count();

    debut = chrono::high_resolution_clock::now();

    for (int i = 0; i < N; i++)
        arbre = supprimer(arbre, aleatoire[i]);

    fin = chrono::high_resolution_clock::now();

    long long tSupABRA =
        chrono::duration_cast<chrono::nanoseconds>(fin - debut).count();

    cout << "Insertion  : " << tInsABRA << " ns\n";
    cout << "Recherche  : " << tRecABRA << " ns\n";
    cout << "Suppression: " << tSupABRA << " ns\n";



    cout << "\n===== MAP : ORDONNES =====\n";

    map<int, int> mapOrdonne;

    debut = chrono::high_resolution_clock::now();

    for (int i = 0; i < N; i++)
        inserer(mapOrdonne, ordonne[i]);

    fin = chrono::high_resolution_clock::now();

    long long tInsMapO =
        chrono::duration_cast<chrono::nanoseconds>(fin - debut).count();

    debut = chrono::high_resolution_clock::now();

    for (int i = 0; i < N; i++)
        rechercher(mapOrdonne, ordonne[i]);

    fin = chrono::high_resolution_clock::now();

    long long tRecMapO =
        chrono::duration_cast<chrono::nanoseconds>(fin - debut).count();

    debut = chrono::high_resolution_clock::now();

    for (int i = 0; i < N; i++)
        supprimer(mapOrdonne, ordonne[i]);

    fin = chrono::high_resolution_clock::now();

    long long tSupMapO =
        chrono::duration_cast<chrono::nanoseconds>(fin - debut).count();

    cout << "Insertion  : " << tInsMapO << " ns\n";
    cout << "Recherche  : " << tRecMapO << " ns\n";
    cout << "Suppression: " << tSupMapO << " ns\n";


    cout << "\n===== MAP : ALEATOIRES =====\n";

    map<int, int> mapAleatoire;

    debut = chrono::high_resolution_clock::now();

    for (int i = 0; i < N; i++)
        inserer(mapAleatoire, aleatoire[i]);

    fin = chrono::high_resolution_clock::now();

    long long tInsMapA =
        chrono::duration_cast<chrono::nanoseconds>(fin - debut).count();

    debut = chrono::high_resolution_clock::now();

    for (int i = 0; i < N; i++)
        rechercher(mapAleatoire, aleatoire[i]);

    fin = chrono::high_resolution_clock::now();

    long long tRecMapA =
        chrono::duration_cast<chrono::nanoseconds>(fin - debut).count();

    debut = chrono::high_resolution_clock::now();

    for (int i = 0; i < N; i++)
        supprimer(mapAleatoire, aleatoire[i]);

    fin = chrono::high_resolution_clock::now();

    long long tSupMapA =
        chrono::duration_cast<chrono::nanoseconds>(fin - debut).count();

    cout << "Insertion  : " << tInsMapA << " ns\n";
    cout << "Recherche  : " << tRecMapA << " ns\n";
    cout << "Suppression: " << tSupMapA << " ns\n";

    delete[] ordonne;
    delete[] aleatoire;

    return 0;
}





