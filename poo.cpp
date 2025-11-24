#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Meniu;
class Chelner;
class Comanda;

void aplicaReducere(Meniu &m, int procent);
void aplicaTVAlaComanda(Comanda &c, float tva);

class Meniu
{
private:
    string denumire;
    float pret;
    int nrIngrediente;
    static int totalProduse;
    const string tip;
    string *ingrediente;

public:
    Meniu() : tip("Necunoscut"), denumire("Necunoscut"), pret(0.0f), nrIngrediente(0), ingrediente(nullptr)
    {
        totalProduse++;
    }

    Meniu(const string &den, float p) : tip("Standard"), denumire(den), pret(p), nrIngrediente(2)
    {
        ingrediente = new string[nrIngrediente];
        ingrediente[0] = "Apa";
        ingrediente[1] = "Sare";
        totalProduse++;
    }

    Meniu(const string &den, float p, const string &tipM, int n) : tip(tipM), denumire(den), pret(p), nrIngrediente(n)
    {
        if (nrIngrediente > 0)
        {
            ingrediente = new string[nrIngrediente];
            for (int i = 0; i < nrIngrediente; ++i)
                ingrediente[i] = "Ingredient " + to_string(i + 1);
        }
        else
        {
            ingrediente = nullptr;
        }
        totalProduse++;
    }

    Meniu(const Meniu &other) : tip(other.tip), denumire(other.denumire), pret(other.pret), nrIngrediente(other.nrIngrediente)
    {
        if (nrIngrediente > 0)
        {
            ingrediente = new string[nrIngrediente];
            for (int i = 0; i < nrIngrediente; ++i)
                ingrediente[i] = other.ingrediente[i];
        }
        else
        {
            ingrediente = nullptr;
        }
        totalProduse++;
    }

    ~Meniu()
    {
        delete[] ingrediente;
    }

    
    Meniu &operator=(const Meniu &other)
    {
        if (this != &other)
        {
            denumire = other.denumire;
            pret = other.pret;


            delete[] ingrediente;
            nrIngrediente = other.nrIngrediente;
            if (nrIngrediente > 0)
            {
                ingrediente = new string[nrIngrediente];
                for (int i = 0; i < nrIngrediente; ++i)
                    ingrediente[i] = other.ingrediente[i];
            }
            else
            {
                ingrediente = nullptr;
            }
            
        }
        return *this;
    }

    Meniu operator+(const Meniu &other) const
    {
        Meniu rezultat(*this); // copie
        rezultat.denumire = denumire + " & " + other.denumire;
        rezultat.pret = pret + other.pret;

        
        int nouNr = nrIngrediente + other.nrIngrediente;
        delete[] rezultat.ingrediente;
        rezultat.nrIngrediente = nouNr;

        if (nouNr > 0)
        {
            rezultat.ingrediente = new string[nouNr];
            int k = 0;
            for (int i = 0; i < nrIngrediente; ++i)
                rezultat.ingrediente[k++] = ingrediente[i];
            for (int i = 0; i < other.nrIngrediente; ++i)
                rezultat.ingrediente[k++] = other.ingrediente[i];
        }
        else
        {
            rezultat.ingrediente = nullptr;
        }

        return rezultat;
    }

    
    bool operator<(const Meniu &other) const
    {
        return pret < other.pret;
    }

    string operator[](int index) const
    {
        if (index < 0 || index >= nrIngrediente || ingrediente == nullptr)
            return "Index invalid";
        return ingrediente[index];
    }

    

    string getDenumire() const { return denumire; }
    float getPret() const { return pret; }
    int getNrIngrediente() const { return nrIngrediente; }
    string getTip() const { return tip; }
    vector<string> getIngrediente() const
    {
        vector<string> v;
        for (int i = 0; i < nrIngrediente; ++i)
            v.push_back(ingrediente[i]);
        return v;
    }

    void setDenumire(const string &d) { denumire = d; }
    void setPret(float p) { pret = p; }

    void setIngredienteFromVector(const vector<string> &v)
    {
        delete[] ingrediente;
        nrIngrediente = static_cast<int>(v.size());
        if (nrIngrediente > 0)
        {
            ingrediente = new string[nrIngrediente];
            for (int i = 0; i < nrIngrediente; ++i)
                ingrediente[i] = v[i];
        }
        else
        {
            ingrediente = nullptr;
        }
    }

    static float calculeazaReducere(float pret, int procent)
    {
        return pret - (pret * procent / 100.0f);
    }

    void afisare() const
    {
        cout << "Meniu: " << denumire << " | Pret: " << pret << " lei | Tip: " << tip << endl;
        if (ingrediente != nullptr && nrIngrediente > 0)
        {
            cout << "Ingrediente: ";
            for (int i = 0; i < nrIngrediente; i++)
                cout << ingrediente[i] << " ";
            cout << endl;
        }
        cout << endl;
    }

    static int getTotalProduse() { return totalProduse; }

    friend void aplicaReducere(Meniu &m, int procent);
};

int Meniu::totalProduse = 0;

class Chelner
{
private:
    string nume;
    int varsta;
    int nrMese;
    static int totalChelneri;
    const int codID;
    string *mese;

public:
    Chelner() : codID(0), nume("Anonim"), varsta(0), nrMese(0), mese(nullptr)
    {
        totalChelneri++;
    }

    Chelner(const string &n, int v) : codID(100), nume(n), varsta(v), nrMese(2)
    {
        mese = new string[nrMese];
        mese[0] = "Masa 1";
        mese[1] = "Masa 2";
        totalChelneri++;
    }

    Chelner(const string &n, int v, int cod, int nr) : codID(cod), nume(n), varsta(v), nrMese(nr)
    {
        if (nrMese > 0)
        {
            mese = new string[nrMese];
            for (int i = 0; i < nrMese; ++i)
                mese[i] = "Masa " + to_string(i + 1);
        }
        else
        {
            mese = nullptr;
        }
        totalChelneri++;
    }

    Chelner(const Chelner &other) : codID(other.codID), nume(other.nume), varsta(other.varsta), nrMese(other.nrMese)
    {
        if (nrMese > 0)
        {
            mese = new string[nrMese];
            for (int i = 0; i < nrMese; ++i)
                mese[i] = other.mese[i];
        }
        else
        {
            mese = nullptr;
        }
        totalChelneri++;
    }

    ~Chelner()
    {
        delete[] mese;
    }

    
    Chelner &operator=(const Chelner &other)
    {
        if (this != &other)
        {
            nume = other.nume;
            varsta = other.varsta;

            delete[] mese;
            nrMese = other.nrMese;
            if (nrMese > 0)
            {
                mese = new string[nrMese];
                for (int i = 0; i < nrMese; ++i)
                    mese[i] = other.mese[i];
            }
            else
            {
                mese = nullptr;
            }
          
        }
        return *this;
    }

    
    Chelner &operator++()
    {
        nrMese++;
        return *this;
    }


    Chelner &operator+=(int meseNoi)
    {
        if (meseNoi <= 0)
            return *this;

        int nouNr = nrMese + meseNoi;
        string *nou = new string[nouNr];
        int i = 0;
        for (; i < nrMese; ++i)
            nou[i] = (mese != nullptr ? mese[i] : "Masa " + to_string(i + 1));
        for (int j = 0; j < meseNoi; ++j)
            nou[i + j] = "Masa noua " + to_string(j + 1);

        delete[] mese;
        mese = nou;
        nrMese = nouNr;
        return *this;
    }

    
    bool operator<(const Chelner &other) const
    {
        return nrMese < other.nrMese;
    }



    string getNume() const { return nume; }
    int getVarsta() const { return varsta; }
    int getNrMese() const { return nrMese; }
    int getCodID() const { return codID; }
    vector<string> getMese() const
    {
        vector<string> v;
        for (int i = 0; i < nrMese; ++i)
            v.push_back(mese[i]);
        return v;
    }

    void setNume(const string &n) { nume = n; }
    void setVarsta(int v) { varsta = v; }

    void setMeseFromVector(const vector<string> &v)
    {
        delete[] mese;
        nrMese = static_cast<int>(v.size());
        if (nrMese > 0)
        {
            mese = new string[nrMese];
            for (int i = 0; i < nrMese; ++i)
                mese[i] = v[i];
        }
        else
        {
            mese = nullptr;
        }
    }

    static float calculeazaBacsis(float totalVanzari, float procent)
    {
        return totalVanzari * procent / 100.0f;
    }

    void afisare() const
    {
        cout << "Chelner: " << nume << " (" << varsta << " ani)"
             << " | Cod ID: " << codID << endl;
        if (mese != nullptr && nrMese > 0)
        {
            cout << "Mese servite: ";
            for (int i = 0; i < nrMese; i++)
                cout << mese[i] << " ";
            cout << endl;
        }
        cout << endl;
    }

    static int getTotalChelneri() { return totalChelneri; }
};

int Chelner::totalChelneri = 0;

class Comanda
{
private:
    int nrComanda;
    float valoareTotala;
    int nrProduse;
    static int totalComenzi;
    const string dataComenzii;
    string *produse;

public:
    Comanda() : dataComenzii("N/A"), nrComanda(0), valoareTotala(0.0f), nrProduse(0), produse(nullptr)
    {
        totalComenzi++;
    }

    Comanda(int nr, float val) : dataComenzii("24/10/2025"), nrComanda(nr), valoareTotala(val), nrProduse(2)
    {
        produse = new string[nrProduse];
        produse[0] = "Apa plata";
        produse[1] = "Pizza";
        totalComenzi++;
    }

    Comanda(int nr, float val, const string &data, int n) : dataComenzii(data), nrComanda(nr), valoareTotala(val), nrProduse(n)
    {
        if (nrProduse > 0)
        {
            produse = new string[nrProduse];
            for (int i = 0; i < nrProduse; ++i)
                produse[i] = "Produs " + to_string(i + 1);
        }
        else
        {
            produse = nullptr;
        }
        totalComenzi++;
    }

    Comanda(const Comanda &other) : dataComenzii(other.dataComenzii), nrComanda(other.nrComanda),
                                    valoareTotala(other.valoareTotala), nrProduse(other.nrProduse)
    {
        if (nrProduse > 0)
        {
            produse = new string[nrProduse];
            for (int i = 0; i < nrProduse; ++i)
                produse[i] = other.produse[i];
        }
        else
        {
            produse = nullptr;
        }
        totalComenzi++;
    }

    ~Comanda()
    {
        delete[] produse;
    }


    Comanda &operator=(const Comanda &other)
    {
        if (this != &other)
        {
            nrComanda = other.nrComanda;
            valoareTotala = other.valoareTotala;

            delete[] produse;
            nrProduse = other.nrProduse;
            if (nrProduse > 0)
            {
                produse = new string[nrProduse];
                for (int i = 0; i < nrProduse; ++i)
                    produse[i] = other.produse[i];
            }
            else
            {
                produse = nullptr;
            }
        }
        return *this;
    }

    
    Comanda &operator+=(float suma)
    {
        valoareTotala += suma;
        return *this;
    }

    
    Comanda operator+(const Comanda &other) const
    {
        Comanda rezultat(*this); 
        rezultat.valoareTotala = valoareTotala + other.valoareTotala;

        int nouNr = nrProduse + other.nrProduse;
        delete[] rezultat.produse;
        rezultat.nrProduse = nouNr;

        if (nouNr > 0)
        {
            rezultat.produse = new string[nouNr];
            int k = 0;
            for (int i = 0; i < nrProduse; ++i)
                rezultat.produse[k++] = produse[i];
            for (int i = 0; i < other.nrProduse; ++i)
                rezultat.produse[k++] = other.produse[i];
        }
        else
        {
            rezultat.produse = nullptr;
        }

        return rezultat;
    }

    string operator[](int index) const
    {
        if (index < 0 || index >= nrProduse || produse == nullptr)
            return "Index invalid";
        return produse[index];
    }

   

    int getNrComanda() const { return nrComanda; }
    float getValoareTotala() const { return valoareTotala; }
    int getNrProduse() const { return nrProduse; }
    string getDataComenzii() const { return dataComenzii; }
    vector<string> getProduse() const
    {
        vector<string> v;
        for (int i = 0; i < nrProduse; ++i)
            v.push_back(produse[i]);
        return v;
    }

    void setNrComanda(int nr) { nrComanda = nr; }
    void setValoareTotala(float val) { valoareTotala = val; }

    void setProduseFromVector(const vector<string> &v)
    {
        delete[] produse;
        nrProduse = static_cast<int>(v.size());
        if (nrProduse > 0)
        {
            produse = new string[nrProduse];
            for (int i = 0; i < nrProduse; ++i)
                produse[i] = v[i];
        }
        else
        {
            produse = nullptr;
        }
    }

    static float adaugaTVA(float valoare, float tva)
    {
        return valoare + valoare * tva / 100.0f;
    }

    void afisare() const
    {
        cout << "Comanda #" << nrComanda << " | Data: " << dataComenzii
             << " | Valoare: " << valoareTotala << " lei" << endl;
        if (produse != nullptr && nrProduse > 0)
        {
            cout << "Produse: ";
            for (int i = 0; i < nrProduse; i++)
                cout << produse[i] << " ";
            cout << endl;
        }
        cout << endl;
    }

    static int getTotalComenzi() { return totalComenzi; }

    friend void aplicaTVAlaComanda(Comanda &c, float tva);
};

int Comanda::totalComenzi = 0;



void aplicaReducere(Meniu &m, int procent)
{
    m.pret = Meniu::calculeazaReducere(m.pret, procent);
}

void aplicaTVAlaComanda(Comanda &c, float tva)
{
    c.valoareTotala = Comanda::adaugaTVA(c.valoareTotala, tva);
}



int main()
{
    cout << "=== Domeniu: RESTAURANT (Roberto Zatreanu) - Tema modificata ===\n\n";

    Meniu m1;
    Meniu m2("Pizza Margherita", 28.5f);
    Meniu m3("Paste Carbonara", 35.0f, "Fel principal", 3);

    m1.afisare();
    m2.afisare();
    m3.afisare();

    cout << "Total produse in meniu: " << Meniu::getTotalProduse() << endl;

    cout << "Pret Pizza (getter): " << m2.getPret() << " lei\n";
    cout << "Pret redus Pizza (10% calculat static, fara a modifica obiectul): "
         << Meniu::calculeazaReducere(m2.getPret(), 10) << " lei\n\n";

    
    aplicaReducere(m2, 10);
    cout << "Pret Pizza dupa aplicare reducere 10% (aplicata prin functie prietena): "
         << m2.getPret() << " lei\n\n";

    vector<string> noiIngrediente = {"Faina", "Ou", "Parmezan"};
    m3.setIngredienteFromVector(noiIngrediente);
    cout << "Ingrediente Paste Carbonara (dupa set): ";
    for (auto &ing : m3.getIngrediente())
        cout << ing << " ";
    cout << "\n\n";

    Chelner c1;
    Chelner c2("Ion Popescu", 25);
    Chelner c3("Maria Ionescu", 30, 202, 4);

    c1.afisare();
    c2.afisare();
    c3.afisare();

    cout << "Total chelneri: " << Chelner::getTotalChelneri() << endl;
    cout << "Bacsis pentru vanzari 1000 lei la 5%: "
         << Chelner::calculeazaBacsis(1000.0f, 5.0f) << " lei\n\n";

    cout << "Nume c2 (getter): " << c2.getNume() << "\n";
    c2.setNume("Ionel Popescu");
    cout << "Nume c2 dupa set: " << c2.getNume() << "\n\n";

    Comanda o1;
    Comanda o2(1, 85.0f);
    Comanda o3(2, 120.5f, "24/10/2025", 3);

    o1.afisare();
    o2.afisare();
    o3.afisare();

    cout << "Total comenzi: " << Comanda::getTotalComenzi() << endl;
    cout << "Valoare comanda o3 (getter): " << o3.getValoareTotala() << " lei\n";

    
    aplicaTVAlaComanda(o3, 9.0f);
    cout << "Valoare comanda o3 dupa aplicare TVA 9% (functie prietena): "
         << o3.getValoareTotala() << " lei\n\n";

    
    Meniu m2copy = m2;
    cout << "Meniu copiat (m2copy) - afisare (s-a realizat deep copy):\n";
    m2copy.afisare();

    Comanda o3copy = o3;
    cout << "Comanda copiata (o3copy) - afisare:\n";
    o3copy.afisare();

    Chelner c3copy = c3;
    cout << "Chelner copiat (c3copy) - afisare:\n";
    c3copy.afisare();

    m2.setDenumire("Pizza Speciala");
    cout << "Dupa setDenumire(m2): m2.denumire = "
         << m2.getDenumire() << " | m2copy.denumire = "
         << m2copy.getDenumire() << "\n";

    o3.setValoareTotala(300.0f);
    cout << "Dupa setValoareTotala(o3): o3 = " << o3.getValoareTotala()
         << " | o3copy = " << o3copy.getValoareTotala() << "\n\n";

    
    cout << "\n--- Testare operatori Meniu ---\n";
    m1 = m3; 
    cout << "Dupa m1 = m3, m1 devine:\n";
    m1.afisare();

    Meniu combo = m2 + m3; 
    cout << "Meniu combo (m2 + m3):\n";
    combo.afisare();

    cout << "Comparatie pret (m2 < m3): " << (m2 < m3 ? "DA" : "NU") << "\n";

    cout << "Primul ingredient din m3 (operator[]): " << m3[0] << "\n\n";

   
    cout << "--- Testare operatori Chelner ---\n";
    c1 = c2; 
    cout << "Dupa c1 = c2:\n";
    c1.afisare();

    ++c2; 
    cout << "Dupa ++c2 (creste nrMese):\n";
    c2.afisare();

    c2 += 2; 
    cout << "Dupa c2 += 2 (i se mai atribuie 2 mese):\n";
    c2.afisare();

    cout << "Comparatie nrMese (c2 < c3): " << (c2 < c3 ? "DA" : "NU") << "\n\n";

    
    cout << "--- Testare operatori Comanda ---\n";
    o1 = o2; 
    cout << "Dupa o1 = o2:\n";
    o1.afisare();

    o2 += 20.0f;
    cout << "Dupa o2 += 20 (valoare suplimentara):\n";
    o2.afisare();

    Comanda oSum = o2 + o3; 
    cout << "Comanda combinata (o2 + o3):\n";
    oSum.afisare();

    cout << "Primul produs din o3 (operator[]): " << o3[0] << "\n";

    cout << "\n=== Sfarsit testare ===\n";
    return 0;
}

