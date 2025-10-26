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

    return 0;
}
