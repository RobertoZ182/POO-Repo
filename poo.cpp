#include <iostream>
#include <string>
using namespace std;

class Meniu
{
public:
    string denumire;
    float pret;
    int nrIngrediente;
    static int totalProduse;
    const string tip;
    string *ingrediente;

    Meniu() : tip("Necunoscut") {
        denumire = "Necunoscut";
        pret = 0;
        nrIngrediente = 0;
        ingrediente = nullptr;
        totalProduse++;
    }

   
    Meniu(string den, float p) : tip("Standard") {
        denumire = den;
        pret = p;
        nrIngrediente = 2;
        ingrediente = new string[nrIngrediente];
        ingrediente[0] = "Apa";
        ingrediente[1] = "Sare";
        totalProduse++;
    }

  
    Meniu(string den, float p, string tipM, int n) : tip(tipM) {
        denumire = den;
        pret = p;
        nrIngrediente = n;
        ingrediente = new string[n];
        for (int i = 0; i < n; i++)
            ingrediente[i] = "Ingredient " + to_string(i + 1);
        totalProduse++;
    }
    static float calculeazaReducere(float pret, int procent)
    {
        return pret - (pret * procent / 100.0f);
    }

    void afisare()
    {
        cout << "Meniu: " << denumire << " | Pret: " << pret << " lei | Tip: " << tip << endl;
        if (ingrediente != nullptr)
        {
            cout << "Ingrediente: ";
            for (int i = 0; i < nrIngrediente; i++)
                cout << ingrediente[i] << " ";
            cout << endl;
        }
        cout << endl;
    }

    ~Meniu()
    {
        delete[] ingrediente;
    }
};

int Meniu::totalProduse = 0;

class Chelner
{
public:
    string nume;
    int varsta;
    int nrMese;
    static int totalChelneri;
    const int codID;
    string *mese;

    Chelner() : codID(0) {
        nume = "Anonim";
        varsta = 0;
        nrMese = 0;
        mese = nullptr;
        totalChelneri++;
    }

    
    Chelner(string n, int v) : codID(100) {
        nume = n;
        varsta = v;
        nrMese = 2;
        mese = new string[nrMese];
        mese[0] = "Masa 1";
        mese[1] = "Masa 2";
        totalChelneri++;
    }

    
    Chelner(string n, int v, int cod, int nr) : codID(cod) {
        nume = n;
        varsta = v;
        nrMese = nr;
        mese = new string[nr];
        for (int i = 0; i < nr; i++)
            mese[i] = "Masa " + to_string(i + 1);
        totalChelneri++;
    }
    static float calculeazaBacsis(float totalVanzari, float procent)
    {
        return totalVanzari * procent / 100.0f;
    }

    void afisare()
    {
        cout << "Chelner: " << nume << " (" << varsta << " ani)"
             << " | Cod ID: " << codID << endl;
        if (mese != nullptr)
        {
            cout << "Mese servite: ";
            for (int i = 0; i < nrMese; i++)
                cout << mese[i] << " ";
            cout << endl;
        }
        cout << endl;
    }

    ~Chelner()
    {
        delete[] mese;
    }
};
int Chelner::totalChelneri = 0;

class Comanda
{
public:
    int nrComanda;
    float valoareTotala;
    int nrProduse;
    static int totalComenzi;
    const string dataComenzii;
    string *produse;


        Comanda() : dataComenzii("N/A") {
        nrComanda = 0;
        valoareTotala = 0;
        nrProduse = 0;
        produse = nullptr;
        totalComenzi++;
    }

   
    Comanda(int nr, float val) : dataComenzii("24/10/2025") {
        nrComanda = nr;
        valoareTotala = val;
        nrProduse = 2;
        produse = new string[nrProduse];
        produse[0] = "Apa plata";
        produse[1] = "Pizza";
        totalComenzi++;
    }


    Comanda(int nr, float val, string data, int n) : dataComenzii(data) {
        nrComanda = nr;
        valoareTotala = val;
        nrProduse = n;
        produse = new string[n];
        for (int i = 0; i < n; i++)
            produse[i] = "Produs " + to_string(i + 1);
        totalComenzi++;
    }

    static float adaugaTVA(float valoare, float tva)
    {
        return valoare + valoare * tva / 100.0f;
    }

    void afisare()
    {
        cout << "Comanda #" << nrComanda << " | Data: " << dataComenzii
             << " | Valoare: " << valoareTotala << " lei" << endl;
        if (produse != nullptr)
        {
            cout << "Produse: ";
            for (int i = 0; i < nrProduse; i++)
                cout << produse[i] << " ";
            cout << endl;
        }
        cout << endl;
    }

    ~Comanda()
    {
        delete[] produse;
    }
};
int Comanda::totalComenzi = 0;

int main()
{
    cout << "=== Domeniu: RESTAURANT (Roberto Zatreanu) ===\n\n";

   
    Meniu m1;
    Meniu m2("Pizza Margherita", 28.5);
    Meniu m3("Paste Carbonara", 35.0, "Fel principal", 3);

    m1.afisare();
    m2.afisare();
    m3.afisare();

    cout << "Total produse in meniu: " << Meniu::totalProduse << endl;
    cout << "Pret redus Pizza: " << Meniu::calculeazaReducere(m2.pret, 10) << " lei\n\n";


   
    Chelner c1;
    Chelner c2("Ion Popescu", 25);
    Chelner c3("Maria Ionescu", 30, 202, 4);

    c1.afisare();
    c2.afisare();
    c3.afisare();

    cout << "Total chelneri: " << Chelner::totalChelneri << endl;
    cout << "Bacsis pentru vanzari 1000 lei la 5%: " 
         << Chelner::calculeazaBacsis(1000, 5) << " lei\n\n";


   
    Comanda o1;
    Comanda o2(1, 85.0);
    Comanda o3(2, 120.5, "24/10/2025", 3);

    o1.afisare();
    o2.afisare();
    o3.afisare();

    cout << "Total comenzi: " << Comanda::totalComenzi << endl;
    cout << "Valoare comanda cu TVA 9%: " 
         << Comanda::adaugaTVA(o3.valoareTotala, 9) << " lei\n";

    return 0;
}
