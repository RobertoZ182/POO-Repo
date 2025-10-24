#include <iostream>
#include <string>
using namespace std;

class Meniu {
public:
    string denumire;
    float pret;
    int nrIngrediente;
    static int totalProduse;
    const string tip;  // constant
    string* ingrediente;  // pointer alocat dinamic

};


class Chelner {
public:
    string nume;
    int varsta;
    int nrMese;
    static int totalChelneri;
    const int codID;
    string* mese;

};


class Comanda {
public:
    int nrComanda;
    float valoareTotala;
    int nrProduse;
    static int totalComenzi;
    const string dataComenzii;
    string* produse;

};



int main() {

    return 0;
}
