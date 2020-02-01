#include <iostream>
#include <vector>
#include <string>
using namespace std;

/*******************************************
 * Completez le programme a partir d'ici.
 *******************************************/
class Auteur {
private:
    string nom;
    bool prix;
public:
    Auteur(string nom, bool prix = false) : nom(nom), prix(prix) {}
    Auteur(Auteur const &obj) = delete;
    string getNom() const { return nom;}
    bool getPrix() const { return prix;}
};

class Oeuvre{
private:
    string titre;
    const Auteur &auteur;
    string langue;    // éventuellement const string langue
public:
    Oeuvre(string titre,  Auteur const &auteur, string langue);
    ~Oeuvre();
    string getTitre() const { return titre; }
    Auteur const & getAuteur() const { return auteur; }
    string getLangue() const { return langue; }
    void affiche() const;
};

class Exemplaire{
private:
    const Oeuvre &oeuvre;
public:
    Exemplaire(Oeuvre const &ov);
    Exemplaire(Exemplaire const &obj);
    ~Exemplaire();
    Oeuvre const & getOeuvre() const{ return oeuvre;}
    void affiche() const;
};

class Bibliotheque{
private:
    string nom;
    vector<Exemplaire  *> Ex;
public:
    Bibliotheque(string nom);
    ~Bibliotheque();
    string getNom() const { return nom; }
    void stocker(Oeuvre &ex, unsigned int n=1);
    void lister_exemplaires(string langue) const;
    void lister_exemplaires() const;
    void afficher_auteurs(bool prix=false) const;
    int compter_exemplaires(Oeuvre &oeuvre);
};

void Oeuvre::affiche() const {
    cout << titre << ", " << auteur.getNom() << ", en " << langue << endl;
}

Oeuvre::~Oeuvre() {
    cout << "L'oeuvre \"" << titre << ", " << auteur.getNom() << ", en " << langue;
    cout << "\" n'est plus disponible." << endl;
}

Oeuvre::Oeuvre(string titre, Auteur const &auteur, string langue)
        : titre(titre), auteur(auteur), langue(langue) {}


Exemplaire::Exemplaire(Oeuvre const &ov) : oeuvre(ov)
{
    cout << "Nouvel exemplaire de : " << ov.getTitre() << ", " << ov.getAuteur().getNom();
    cout << ", en " << ov.getLangue() << endl;
}

Exemplaire::Exemplaire(Exemplaire const &obj) : oeuvre(obj.getOeuvre()){
    cout << "Copie d'un exemplaire de : " << obj.getOeuvre().getTitre() << ", ";
    cout << obj.getOeuvre().getAuteur().getNom();
    cout << ", en " << obj.getOeuvre().getLangue() << endl;
}

Exemplaire::~Exemplaire() {
    cout << "Un exemplaire de \"" << getOeuvre().getTitre() << ", " << getOeuvre().getAuteur().getNom();
    cout << ", en " << getOeuvre().getLangue() << "\" a été jeté !" << endl;
}

void Exemplaire::affiche() const{
    cout << "Exemplaire de : " << getOeuvre().getTitre() << ", " << getOeuvre().getAuteur().getNom();
    cout << ", en " << getOeuvre().getLangue() << endl;
}


Bibliotheque::Bibliotheque(string nom) : nom(nom) {
    cout << "La bibliothèque " << nom << " est ouverte !" << endl;
}

Bibliotheque::~Bibliotheque() {
    cout << "La bibliothèque " << nom << " ferme ses portes," << endl;
    cout << "et détruit ses exemplaires :" << endl;
    for (auto ex : Ex) delete ex;
}

void Bibliotheque::stocker(Oeuvre &ex, unsigned int n) {
    for (int i = 0; i < n; ++i) {
        Ex.push_back(new Exemplaire(ex));
    }
}

void Bibliotheque::lister_exemplaires() const {
    for (auto ex : Ex) ex->affiche();
}

void Bibliotheque::afficher_auteurs(bool prix) const {
    if (prix) {
    for (auto ex : Ex){
        if (ex->getOeuvre().getAuteur().getPrix())
        cout << ex->getOeuvre().getAuteur().getNom() << endl;
    }
    }
    else {
        for (auto ex : Ex){
                cout << ex->getOeuvre().getAuteur().getNom() << endl;
        }
    }
}

int Bibliotheque::compter_exemplaires(Oeuvre &oeuvre) {
    int compteur(0);
    for (auto ex : Ex) {
        if (oeuvre.getTitre() == ex->getOeuvre().getTitre()) compteur++;
    }
    return compteur;
}

void Bibliotheque::lister_exemplaires(string langue) const {
    for (auto ex : Ex) {
        if (ex->getOeuvre().getLangue() == langue) ex->affiche();
    }
}

/*******************************************
 * Ne rien modifier apres cette ligne.
 *******************************************/

int main()
{
    Auteur a1("Victor Hugo"),
            a2("Alexandre Dumas"),
            a3("Raymond Queneau", true);

    Oeuvre o1("Les Misérables"           , a1, "français" ),
            o2("L'Homme qui rit"          , a1, "français" ),
            o3("Le Comte de Monte-Cristo" , a2, "français" ),
            o4("Zazie dans le métro"      , a3, "français" ),
            o5("The Count of Monte-Cristo", a2, "anglais" );

    Bibliotheque biblio("municipale");
    biblio.stocker(o1, 2);
    biblio.stocker(o2);
    biblio.stocker(o3, 3);
    biblio.stocker(o4);
    biblio.stocker(o5);

    cout << "La bibliothèque " << biblio.getNom()
         << " offre les exemplaires suivants :" << endl;
    biblio.lister_exemplaires();

    const string langue("anglais");
    cout << " Les exemplaires en "<< langue << " sont :" << endl;
    biblio.lister_exemplaires(langue);

    cout << " Les auteurs à succès sont :" << endl;
    biblio.afficher_auteurs(true);

    cout << " Il y a " << biblio.compter_exemplaires(o3) << " exemplaires de "
         << o3.getTitre() << endl;

    return 0;
}
