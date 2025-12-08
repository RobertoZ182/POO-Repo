#include <iostream>
#include <string>
#include <vector>
#include <fstream>

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

    virtual ~Meniu()
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
        Meniu rezultat(*this); 
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

    virtual void afisare() const
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
       
    void scrieInFisierText(ofstream &out) const;
    static Meniu citesteDinFisierText(ifstream &in);

    void scrieInFisierBinar(ofstream &out) const;
    static Meniu citesteDinFisierBinar(ifstream &in);

    static int getTotalProduse() { return totalProduse; }

    friend void aplicaReducere(Meniu &m, int procent);

    friend istream &operator>>(istream &in, Meniu &m);
    friend ostream &operator<<(ostream &out, const Meniu &m);

    void Meniu::scrieInFisierText(ofstream &out) const
{
    // format simplu, pe mai multe linii
    out << denumire << '\n';
    out << pret << '\n';
    out << tip << '\n';
    out << nrIngrediente << '\n';
    for (int i = 0; i < nrIngrediente; ++i)
        out << ingrediente[i] << '\n';
}

Meniu Meniu::citesteDinFisierText(ifstream &in)
{
    string den, tipM, linie;
    float p;
    int nIng;

    if (!getline(in, den))
        return Meniu(); // EOF sau eroare

    if (!getline(in, linie))
        return Meniu();
    p = stof(linie);

    if (!getline(in, tipM))
        return Meniu();

    if (!getline(in, linie))
        return Meniu();
    nIng = stoi(linie);

    vector<string> ing;
    for (int i = 0; i < nIng; ++i)
    {
        string s;
        if (!getline(in, s))
            s = "";
        ing.push_back(s);
    }

    Meniu m(den, p, tipM, nIng);
    m.setIngredienteFromVector(ing);
    return m;
}

void Meniu::scrieInFisierBinar(ofstream &out) const
{
    size_t len;

    // denumire
    len = denumire.size();
    out.write(reinterpret_cast<const char*>(&len), sizeof(len));
    out.write(denumire.c_str(), len);

    // pret
    out.write(reinterpret_cast<const char*>(&pret), sizeof(pret));

    // tip
    string tipLocal = tip;
    len = tipLocal.size();
    out.write(reinterpret_cast<const char*>(&len), sizeof(len));
    out.write(tipLocal.c_str(), len);

    // nrIngrediente
    out.write(reinterpret_cast<const char*>(&nrIngrediente), sizeof(nrIngrediente));

    // ingrediente
    for (int i = 0; i < nrIngrediente; ++i)
    {
        len = ingrediente[i].size();
        out.write(reinterpret_cast<const char*>(&len), sizeof(len));
        out.write(ingrediente[i].c_str(), len);
    }
}

Meniu Meniu::citesteDinFisierBinar(ifstream &in)
{
    size_t len;
    string den, tipM;
    float p;
    int nIng;

    if (!in.read(reinterpret_cast<char*>(&len), sizeof(len)))
        return Meniu();
    den.resize(len);
    in.read(&den[0], len);

    in.read(reinterpret_cast<char*>(&p), sizeof(p));

    in.read(reinterpret_cast<char*>(&len), sizeof(len));
    tipM.resize(len);
    in.read(&tipM[0], len);

    in.read(reinterpret_cast<char*>(&nIng), sizeof(nIng));

    vector<string> ing;
    for (int i = 0; i < nIng; ++i)
    {
        in.read(reinterpret_cast<char*>(&len), sizeof(len));
        string s;
        s.resize(len);
        in.read(&s[0], len);
        ing.push_back(s);
    }

    Meniu m(den, p, tipM, nIng);
    m.setIngredienteFromVector(ing);
    return m;
}

};

int Meniu::totalProduse = 0;

istream &operator>>(istream &in, Meniu &m)
{
    cout << "Denumire meniu: ";
    in >> ws;
    getline(in, m.denumire);

    cout << "Pret: ";
    in >> m.pret;

    cout << "Numar ingrediente: ";
    in >> m.nrIngrediente;

    delete[] m.ingrediente;
    if (m.nrIngrediente > 0)
    {
        m.ingrediente = new string[m.nrIngrediente];
        in >> ws;
        for (int i = 0; i < m.nrIngrediente; ++i)
        {
            cout << "Ingredient " << i + 1 << ": ";
            getline(in, m.ingrediente[i]);
        }
    }
    else
    {
        m.ingrediente = nullptr;
    }
    return in;
}

ostream &operator<<(ostream &out, const Meniu &m)
{
    out << "Meniu: " << m.denumire << " | Pret: " << m.pret
        << " lei | Tip: " << m.tip << "\n";
    if (m.ingrediente != nullptr && m.nrIngrediente > 0)
    {
        out << "Ingrediente: ";
        for (int i = 0; i < m.nrIngrediente; ++i)
            out << m.ingrediente[i] << " ";
        out << "\n";
    }
    return out;
}
class MeniuBauturi : public Meniu
{
private:
    bool alcoolic;
    float volumMl;
    string categorie;   

public:
    MeniuBauturi()
        : Meniu("Bautura necunoscuta", 0.0f, "Bautura", 0),
          alcoolic(false), volumMl(0.0f), categorie("Necunoscuta")
    {
    }

    MeniuBauturi(const string &den, float pret,
                 bool alc, float volum, const string &cat)
        : Meniu(den, pret, "Bautura", 0),
          alcoolic(alc), volumMl(volum), categorie(cat)
    {
    }

    
    bool getAlcoolic() const { return alcoolic; }
    float getVolumMl() const { return volumMl; }
    string getCategorie() const { return categorie; }

    
    void setAlcoolic(bool a) { alcoolic = a; }
    void setVolumMl(float v) { volumMl = v; }
    void setCategorie(const string &c) { categorie = c; }

    void descriereScurta() const
    {
        cout << "Bautura " << getDenumire()
             << " (" << volumMl << " ml, "
             << (alcoolic ? "alcoolica" : "nealcoolica")
             << ", " << categorie << ")\n";
    }

    void afisare() const override
    {
        Meniu::afisare();
        cout << "Detalii bautura: "
             << (alcoolic ? "alcoolica" : "nealcoolica")
             << ", volum: " << volumMl << " ml"
             << ", categorie: " << categorie << "\n\n";
    }
};

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

    virtual ~Chelner()
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

    virtual void afisare() const
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

    
    friend istream &operator>>(istream &in, Chelner &c);
    friend ostream &operator<<(ostream &out, const Chelner &c);
};

int Chelner::totalChelneri = 0;

istream &operator>>(istream &in, Chelner &c)
{
    cout << "Nume chelner: ";
    in >> ws;
    getline(in, c.nume);

    cout << "Varsta: ";
    in >> c.varsta;

    cout << "Numar mese: ";
    in >> c.nrMese;

    delete[] c.mese;
    if (c.nrMese > 0)
    {
        c.mese = new string[c.nrMese];
        in >> ws;
        for (int i = 0; i < c.nrMese; ++i)
        {
            cout << "Denumire masa " << i + 1 << ": ";
            getline(in, c.mese[i]);
        }
    }
    else
    {
        c.mese = nullptr;
    }

    return in;
}

ostream &operator<<(ostream &out, const Chelner &c)
{
    out << "Chelner: " << c.nume << " (" << c.varsta << " ani)"
        << " | Cod ID: " << c.codID << "\n";
    if (c.mese != nullptr && c.nrMese > 0)
    {
        out << "Mese servite: ";
        for (int i = 0; i < c.nrMese; ++i)
            out << c.mese[i] << " ";
        out << "\n";
    }
    return out;
}
class ChelnerSef : public Chelner
{
private:
    int nrSubordonati;
    float bonusFix;
    string zona;   

public:
    ChelnerSef()
        : Chelner("Sef necunoscut", 0, 999, 0),
          nrSubordonati(0), bonusFix(0.0f), zona("N/A")
    {
    }

    ChelnerSef(const string &n, int v, int cod, int nrMese,
               int nrSub, float bonus, const string &z)
        : Chelner(n, v, cod, nrMese),
          nrSubordonati(nrSub), bonusFix(bonus), zona(z)
    {
    }

    int getNrSubordonati() const { return nrSubordonati; }
    float getBonusFix() const { return bonusFix; }
    string getZona() const { return zona; }

    void setNrSubordonati(int nr) { nrSubordonati = nr; }
    void setBonusFix(float b) { bonusFix = b; }
    void setZona(const string &z) { zona = z; }

    float calculeazaVenitTotal(float salariuBaza) const
    {
        return salariuBaza + bonusFix;
    }

    void afisare() const override
    {
        Chelner::afisare();
        cout << "   (Sef de sala) Subordonati: " << nrSubordonati
             << " | Bonus fix: " << bonusFix
             << " lei | Zona: " << zona << "\n\n";
    }
};

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

        
    void scrieInFisierText(ofstream &out) const;
    static Comanda citesteDinFisierText(ifstream &in);

    void scrieInFisierBinar(ofstream &out) const;
    static Comanda citesteDinFisierBinar(ifstream &in);


    static int getTotalComenzi() { return totalComenzi; }

    friend void aplicaTVAlaComanda(Comanda &c, float tva);

    friend istream &operator>>(istream &in, Comanda &c);
    friend ostream &operator<<(ostream &out, const Comanda &c);

    void Comanda::scrieInFisierText(ofstream &out) const
{
    out << nrComanda << '\n';
    out << valoareTotala << '\n';
    out << dataComenzii << '\n';
    out << nrProduse << '\n';
    for (int i = 0; i < nrProduse; ++i)
        out << produse[i] << '\n';
}

Comanda Comanda::citesteDinFisierText(ifstream &in)
{
    string linie, data;
    int nr, nProd;
    float val;

    if (!getline(in, linie))
        return Comanda();
    nr = stoi(linie);

    if (!getline(in, linie))
        return Comanda();
    val = stof(linie);

    if (!getline(in, data))
        return Comanda();

    if (!getline(in, linie))
        return Comanda();
    nProd = stoi(linie);

    vector<string> prod;
    for (int i = 0; i < nProd; ++i)
    {
        string s;
        if (!getline(in, s))
            s = "";
        prod.push_back(s);
    }

    Comanda c(nr, val, data, nProd);
    c.setProduseFromVector(prod);
    return c;
}

void Comanda::scrieInFisierBinar(ofstream &out) const
{
    size_t len;

    // nrComanda
    out.write(reinterpret_cast<const char*>(&nrComanda), sizeof(nrComanda));

    // valoareTotala
    out.write(reinterpret_cast<const char*>(&valoareTotala), sizeof(valoareTotala));

    // dataComenzii
    len = dataComenzii.size();
    out.write(reinterpret_cast<const char*>(&len), sizeof(len));
    out.write(dataComenzii.c_str(), len);

    // nrProduse
    out.write(reinterpret_cast<const char*>(&nrProduse), sizeof(nrProduse));

    // produse
    for (int i = 0; i < nrProduse; ++i)
    {
        len = produse[i].size();
        out.write(reinterpret_cast<const char*>(&len), sizeof(len));
        out.write(produse[i].c_str(), len);
    }
}

Comanda Comanda::citesteDinFisierBinar(ifstream &in)
{
    size_t len;
    int nr, nProd;
    float val;
    string data;

    if (!in.read(reinterpret_cast<char*>(&nr), sizeof(nr)))
        return Comanda();

    in.read(reinterpret_cast<char*>(&val), sizeof(val));

    in.read(reinterpret_cast<char*>(&len), sizeof(len));
    data.resize(len);
    in.read(&data[0], len);

    in.read(reinterpret_cast<char*>(&nProd), sizeof(nProd));

    vector<string> prod;
    for (int i = 0; i < nProd; ++i)
    {
        in.read(reinterpret_cast<char*>(&len), sizeof(len));
        string s;
        s.resize(len);
        in.read(&s[0], len);
        prod.push_back(s);
    }

    Comanda c(nr, val, data, nProd);
    c.setProduseFromVector(prod);
    return c;
}

};

int Comanda::totalComenzi = 0;

istream &operator>>(istream &in, Comanda &c)
{
    cout << "Numar comanda: ";
    in >> c.nrComanda;

    cout << "Valoare totala: ";
    in >> c.valoareTotala;

    cout << "Numar produse: ";
    in >> c.nrProduse;

    delete[] c.produse;
    if (c.nrProduse > 0)
    {
        c.produse = new string[c.nrProduse];
        in >> ws;
        for (int i = 0; i < c.nrProduse; ++i)
        {
            cout << "Produs " << i + 1 << ": ";
            getline(in, c.produse[i]);
        }
    }
    else
    {
        c.produse = nullptr;
    }

    return in;
}

ostream &operator<<(ostream &out, const Comanda &c)
{
    out << "Comanda #" << c.nrComanda << " | Data: " << c.dataComenzii
        << " | Valoare: " << c.valoareTotala << " lei\n";
    if (c.produse != nullptr && c.nrProduse > 0)
    {
        out << "Produse: ";
        for (int i = 0; i < c.nrProduse; ++i)
            out << c.produse[i] << " ";
        out << "\n";
    }
    return out;
}

void aplicaReducere(Meniu &m, int procent)
{
    m.pret = Meniu::calculeazaReducere(m.pret, procent);
}

void aplicaTVAlaComanda(Comanda &c, float tva)
{
    c.valoareTotala = Comanda::adaugaTVA(c.valoareTotala, tva);
}

class Masa
{
private:
    int nrMasa;
    int nrLocuri;
    Chelner chelner;     
    int nrComenzi;
    Comanda *comenzi;     
    static int totalMese;

public:
   
    Masa() : nrMasa(0), nrLocuri(0), chelner(), nrComenzi(0), comenzi(nullptr)
    {
        totalMese++;
    }


    Masa(int nr, int locuri, const Chelner &ch)
        : nrMasa(nr), nrLocuri(locuri), chelner(ch), nrComenzi(0), comenzi(nullptr)
    {
        totalMese++;
    }

   
    Masa(int nr, int locuri, const Chelner &ch, int nCom, const Comanda *vComenzi = nullptr)
        : nrMasa(nr), nrLocuri(locuri), chelner(ch), nrComenzi(nCom)
    {
        if (nrComenzi > 0)
        {
            comenzi = new Comanda[nrComenzi];
            if (vComenzi != nullptr)
            {
                for (int i = 0; i < nrComenzi; ++i)
                    comenzi[i] = vComenzi[i];
            }
            else
            {
                
                for (int i = 0; i < nrComenzi; ++i)
                    comenzi[i] = Comanda(i + 1, 0.0f);
            }
        }
        else
        {
            comenzi = nullptr;
        }
        totalMese++;
    }

    Masa(const Masa &other)
        : nrMasa(other.nrMasa), nrLocuri(other.nrLocuri),
          chelner(other.chelner), nrComenzi(other.nrComenzi)
    {
        if (nrComenzi > 0)
        {
            comenzi = new Comanda[nrComenzi];
            for (int i = 0; i < nrComenzi; ++i)
                comenzi[i] = other.comenzi[i];
        }
        else
        {
            comenzi = nullptr;
        }
        totalMese++;
    }

    ~Masa()
    {
        delete[] comenzi;
    }

   
    Masa &operator=(const Masa &other)
    {
        if (this != &other)
        {
            nrMasa = other.nrMasa;
            nrLocuri = other.nrLocuri;
            chelner = other.chelner;

            delete[] comenzi;
            nrComenzi = other.nrComenzi;
            if (nrComenzi > 0)
            {
                comenzi = new Comanda[nrComenzi];
                for (int i = 0; i < nrComenzi; ++i)
                    comenzi[i] = other.comenzi[i];
            }
            else
            {
                comenzi = nullptr;
            }
        }
        return *this;
    }

   
    Masa &operator+=(const Comanda &c)
    {
        Comanda *nou = new Comanda[nrComenzi + 1];
        for (int i = 0; i < nrComenzi; ++i)
            nou[i] = comenzi[i];
        nou[nrComenzi] = c;

        delete[] comenzi;
        comenzi = nou;
        nrComenzi++;
        return *this;
    }

    bool operator<(const Masa &other) const
    {
        return nrLocuri < other.nrLocuri;
    }

   
    Comanda operator[](int index) const
    {
        if (index < 0 || index >= nrComenzi || comenzi == nullptr)
        {
          
            return Comanda();
        }
        return comenzi[index];
    }

    int getNrMasa() const { return nrMasa; }
    int getNrLocuri() const { return nrLocuri; }
    int getNrComenzi() const { return nrComenzi; }
    Chelner getChelner() const { return chelner; }

    vector<Comanda> getComenzi() const
    {
        vector<Comanda> v;
        for (int i = 0; i < nrComenzi; ++i)
            v.push_back(comenzi[i]);
        return v;
    }

    // === SETERI ===
    void setNrMasa(int nr) { nrMasa = nr; }
    void setNrLocuri(int loc) { nrLocuri = loc; }
    void setChelner(const Chelner &ch) { chelner = ch; }

    void setComenziFromVector(const vector<Comanda> &v)
    {
        delete[] comenzi;
        nrComenzi = static_cast<int>(v.size());
        if (nrComenzi > 0)
        {
            comenzi = new Comanda[nrComenzi];
            for (int i = 0; i < nrComenzi; ++i)
                comenzi[i] = v[i];
        }
        else
        {
            comenzi = nullptr;
        }
    }

    float calculeazaTotalMasa() const
    {
        float s = 0.0f;
        for (int i = 0; i < nrComenzi; ++i)
            s += comenzi[i].getValoareTotala();
        return s;
    }

 
    void afisare() const
    {
        cout << "Masa #" << nrMasa << " | Locuri: " << nrLocuri << endl;
        cout << "Chelner asignat:\n";
        chelner.afisare();
        cout << "Numar comenzi: " << nrComenzi
             << " | Total masa: " << calculeazaTotalMasa() << " lei\n";
        if (comenzi != nullptr && nrComenzi > 0)
        {
            cout << "Comenzi pe masa:\n";
            for (int i = 0; i < nrComenzi; ++i)
            {
                cout << " - Comanda [" << i << "]:\n";
                cout << comenzi[i];
            }
        }
        cout << endl;
    }

    static int getTotalMese() { return totalMese; }

   
    friend istream &operator>>(istream &in, Masa &m);
    friend ostream &operator<<(ostream &out, const Masa &m);
};

int Masa::totalMese = 0;

istream &operator>>(istream &in, Masa &m)
{
    cout << "Numar masa: ";
    in >> m.nrMasa;

    cout << "Numar locuri: ";
    in >> m.nrLocuri;

    cout << "\n--- Date chelner pentru aceasta masa ---\n";
    in >> m.chelner;

    cout << "Numar comenzi pe aceasta masa: ";
    in >> m.nrComenzi;

    delete[] m.comenzi;
    if (m.nrComenzi > 0)
    {
        m.comenzi = new Comanda[m.nrComenzi];
        for (int i = 0; i < m.nrComenzi; ++i)
        {
            cout << "\nComanda " << i + 1 << " pentru masa:\n";
            in >> m.comenzi[i];
        }
    }
    else
    {
        m.comenzi = nullptr;
    }

    return in;
}

ostream &operator<<(ostream &out, const Masa &m)
{
    out << "Masa #" << m.nrMasa << " | Locuri: " << m.nrLocuri << "\n";
    out << "Chelner asignat:\n";
    out << m.chelner;
    out << "Numar comenzi: " << m.nrComenzi
        << " | Total masa: " << m.calculeazaTotalMasa() << " lei\n";
    if (m.comenzi != nullptr && m.nrComenzi > 0)
    {
        out << "Comenzi pe masa:\n";
        for (int i = 0; i < m.nrComenzi; ++i)
        {
            out << "   Comanda [" << i << "]:\n";
            out << m.comenzi[i];
        }
    }
    out << "\n";
    return out;
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
        cout << "\n=== Testare clasa Masa (FAZA 5) ===\n";

    Masa masa1;                      
    Masa masa2(10, 4, c2);           

    masa2 += o2;
    masa2 += o3;

    cout << "Masa2 (dupa 2 comenzi adaugate):\n";
    cout << masa2 << "\n";

    
    Comanda prima = masa2[0];
    cout << "Prima comanda de pe masa2 are valoarea: "
         << prima.getValoareTotala() << " lei\n";

    Masa masa3(11, 6, c3);
    cout << "Comparatie (masa2 < masa3 dupa nrLocuri): "
         << (masa2 < masa3 ? "DA" : "NU") << "\n";

    cout << "Total mese create: " << Masa::getTotalMese() << "\n\n";

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

    cout << "\n=== Sfarsit testare initiala ===\n\n";

    cout << "=== Citire vectori de obiecte de la tastatura ===\n\n";

    int nM, nC, nO;

    cout << "Numar obiecte Meniu: ";
    cin >> nM;
    vector<Meniu> vM(nM);
    for (int i = 0; i < nM; ++i)
    {
        cout << "\n--- Meniu " << i + 1 << " ---\n";
        cin >> vM[i];
    }

    cout << "\nMeniuri citite:\n";
    for (int i = 0; i < nM; ++i)
    {
        cout << "Meniu [" << i << "]:\n";
        cout << vM[i] << "\n";
    }

    cout << "\nNumar obiecte Chelner: ";
    cin >> nC;
    vector<Chelner> vC(nC);
    for (int i = 0; i < nC; ++i)
    {
        cout << "\n--- Chelner " << i + 1 << " ---\n";
        cin >> vC[i];
    }

    cout << "\nChelneri cititi:\n";
    for (int i = 0; i < nC; ++i)
    {
        cout << "Chelner [" << i << "]:\n";
        cout << vC[i] << "\n";
    }

    cout << "\nNumar obiecte Comanda: ";
    cin >> nO;
    vector<Comanda> vO(nO);
    for (int i = 0; i < nO; ++i)
    {
        cout << "\n--- Comanda " << i + 1 << " ---\n";
        cin >> vO[i];
    }

    cout << "\nComenzi citite:\n";
    for (int i = 0; i < nO; ++i)
    {
        cout << "Comanda [" << i << "]:\n";
        cout << vO[i] << "\n";
    }

    cout << "\n=== Matrice de obiecte de tip Comanda ===\n";

    int L, C;
    cout << "Numar linii matrice: ";
    cin >> L;
    cout << "Numar coloane matrice: ";
    cin >> C;

    Comanda **mat = new Comanda *[L];
    for (int i = 0; i < L; ++i)
        mat[i] = new Comanda[C];

    cout << "\n--- Citire elemente matrice ---\n";
    for (int i = 0; i < L; ++i)
    {
        for (int j = 0; j < C; ++j)
        {
            cout << "\nComanda de pe pozitia [" << i << "][" << j << "]:\n";
            cin >> mat[i][j];
        }
    }

    cout << "\n--- Afisare matrice comenzi ---\n";
    for (int i = 0; i < L; ++i)
    {
        for (int j = 0; j < C; ++j)
        {
            cout << "Comanda [" << i << "][" << j << "]:\n";
            cout << mat[i][j] << "\n";
        }
    }

   
    for (int i = 0; i < L; ++i)
        delete[] mat[i];
    delete[] mat;

        cout << "\n=== Testare clase derivate (MeniuBauturi, ChelnerSef) ===\n";

    MeniuBauturi b1;
    MeniuBauturi b2("Coca-Cola", 8.5f, false, 500.0f, "Racoritoare");
    MeniuBauturi b3("Vin rosu house", 15.0f, true, 150.0f, "Vin");

    cout << "Afisare bauturi (obiecte derivate direct):\n";
    b1.afisare();
    b2.afisare();
    b3.afisare();

    b2.descriereScurta();
    b3.descriereScurta();
    cout << "\n";

    ChelnerSef sef1;
    ChelnerSef sef2("Gheorghe Pop", 40, 301, 5, 3, 500.0f, "Terasa");

    cout << "Afisare chelneri sefi (obiecte derivate direct):\n";
    sef1.afisare();
    sef2.afisare();

    cout << "Venit total sef2 la salariu baza 3000: "
         << sef2.calculeazaVenitTotal(3000.0f) << " lei\n\n";

    cout << "--- Upcasting ---\n";

    Meniu *pMeniuBautura = &b2;
    Chelner *pChelnerSef = &sef2;

    cout << "Afisare prin pointer Meniu* care pointeaza la MeniuBauturi:\n";
    pMeniuBautura->afisare();   

    cout << "Afisare prin pointer Chelner* care pointeaza la ChelnerSef:\n";
    pChelnerSef->afisare();     

    cout << "Pret bautura (accesat prin pointer la baza): "
         << pMeniuBautura->getPret() << " lei\n";
    cout << "Nume chelner sef (accesat prin pointer la baza): "
         << pChelnerSef->getNume() << "\n\n";

             cout << "\n=== Testare fisiere text si binare (Meniu, Comanda) ===\n";

    // --- FISIERE TEXT ---
    {
        ofstream fout("meniu_comanda.txt");
        if (fout)
        {
            m2.scrieInFisierText(fout);
            m3.scrieInFisierText(fout);
            o2.scrieInFisierText(fout);
            o3.scrieInFisierText(fout);
        }
        fout.close();

        ifstream fin("meniu_comanda.txt");
        if (fin)
        {
            cout << "\nCitire din fisier text:\n";
            Meniu fm1 = Meniu::citesteDinFisierText(fin);
            Meniu fm2 = Meniu::citesteDinFisierText(fin);
            Comanda fc1 = Comanda::citesteDinFisierText(fin);
            Comanda fc2 = Comanda::citesteDinFisierText(fin);

            cout << "Meniu din fisier 1:\n"; fm1.afisare();
            cout << "Meniu din fisier 2:\n"; fm2.afisare();
            cout << "Comanda din fisier 1:\n"; fc1.afisare();
            cout << "Comanda din fisier 2:\n"; fc2.afisare();
        }
    }

    // --- FISIERE BINARE ---
    {
        ofstream foutb("meniu_comanda.bin", ios::binary);
        if (foutb)
        {
            m2.scrieInFisierBinar(foutb);
            m3.scrieInFisierBinar(foutb);
            o2.scrieInFisierBinar(foutb);
            o3.scrieInFisierBinar(foutb);
        }
        foutb.close();

        ifstream finb("meniu_comanda.bin", ios::binary);
        if (finb)
        {
            cout << "\nCitire din fisier binar:\n";
            Meniu bm1 = Meniu::citesteDinFisierBinar(finb);
            Meniu bm2 = Meniu::citesteDinFisierBinar(finb);
            Comanda bc1 = Comanda::citesteDinFisierBinar(finb);
            Comanda bc2 = Comanda::citesteDinFisierBinar(finb);

            cout << "Meniu binar 1:\n"; bm1.afisare();
            cout << "Meniu binar 2:\n"; bm2.afisare();
            cout << "Comanda binar 1:\n"; bc1.afisare();
            cout << "Comanda binar 2:\n"; bc2.afisare();
        }
    }

    cout << "\n=== Sfarsit testare completa ===\n";
    return 0;
}
