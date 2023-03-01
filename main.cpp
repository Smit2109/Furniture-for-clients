#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<vector>
#include<algorithm>
#include<ctime>

using namespace std;

// produse = scaune, dulapuri, canapele,comode;
int produseVandute[4];
int pretProduse[4];
string variable="1";

template <typename T>
bool comparam(T p, T b) { //a - pretul, b - bugetul
    if(p <= b)
        return true;
    else{
        return false;
    }
}

string data();

class Client {
private:
    string nume;
    string prenume;
    string adresa;
    int buget;

public:
    string getNume() { return nume; }

    string getPrenume() { return prenume; }

    string getAdresa() { return adresa; }

    int getBuget() { return buget; }

    //metode de modificare a variabilelor private
    void setNume(string varNume) { nume = varNume; }

    void setPrenume(string varPrenume) { prenume = varPrenume; }

    void setAdresa(string varAdresa) { adresa = varAdresa; }

    void setBuget(int varBuget) { buget = varBuget; }

    void factura(string numePiesa, int cost, string data) {
        string numeFactura = "factura" + nume +".txt";
        ofstream MyFile;
        MyFile.open(numeFactura);
        MyFile << "nume = " << nume << endl;
        MyFile << "prenume = " << prenume << endl;
        MyFile << "adresa = " << adresa << endl;
        MyFile << "numele piesei = " << numePiesa << endl;
        MyFile << "cost = " << cost << endl;
        MyFile << "data = " << data << endl;
    }

    void trimiteNotificare(string produs, int pret) {
        cout << nume << " " << prenume << " was notified of appearance of " << produs << " which is " << pret << endl;
        string dataDeAzi = data();
        int index, i;
        if (comparam(pret, buget)) {
            buget = buget - pret;
            factura(produs, pret, dataDeAzi);
            for(i=0;i<4;i++){
                if(produs == "scaun"){
                    pretProduse[i] = pret;
                    break;
                }
                if(produs == "dulap"){
                    pretProduse[i] = pret;
                    break;
                }
                if(produs == "canapea"){
                    pretProduse[i] = pret;
                    break;
                }
                if(produs == "comoda"){
                    pretProduse[i] = pret;
                    break;
                }

            }
            index = i;
            pretProduse[index] += pret;
            produseVandute[index] ++ ;
        }
    }
};

class Product
{
private:
    string tip;
    double pret;
    vector<class Client *> observers_;
public:

    //Am folosit Observer pentru a notifica toate persoanele care ar fi interesate de aparitia unui nou obiect

    Product(string tip,int pret) : tip(tip), pret(pret) {}

    void attach(class Client *observer)
    {
        observers_.push_back(observer);
    }

    void detach(class Client *observer)
    {
        observers_.erase(remove(observers_.begin(), observers_.end(), observer), observers_.end());
    }

    void notify()
    {
        for (auto observer : observers_)
        {
            observer->trimiteNotificare(tip, pret);
        }
    }

    void produsNou(string tip,double pret)
    {
        pret = pret;
        tip = tip;
        notify();
    }

};

void citire(Client Lista[10]){
    string line, word;
    ifstream MyFile;
    int i = 0, buget;
    MyFile.open("clienti.csv");

    while (getline(MyFile, line)) {

        //convertim stringul in object pentru a putea lua cuvintele pana la virgula
        stringstream my_stream(line);
        //cat timp nu am terminat linia din csv separam cuvintele, adica o sa faca de 3 ori pe fiecare rand
        getline(my_stream, word, ',');
        Lista[i].setNume(word);

        getline(my_stream, word, ',');
        Lista[i].setPrenume(word);

        getline(my_stream, word, ',');
        Lista[i].setAdresa(word);

        getline(my_stream, word, ',');
        buget = stoi(word);
        Lista[i].setBuget(buget);
        //cout << Lista[i].getNume() << " " << Lista[i].getPrenume() << " " << Lista[i].getAdresa() << " " << Lista[i].getBuget() << endl;
        //cout << endl << endl;
        i++;
    }
    MyFile.close();
}

string data(){
    time_t t = time(nullptr); // get current time
    tm tm = *localtime(&t);    // convert to local time

    // format the date and time
    char date[11];
    strftime(date, sizeof(date), "%Y-%m-%d", &tm);
    string current_date(date);
    return current_date;
}

void mobilaLivrata(){
    ofstream MyFile;
    MyFile.open("castig.csv");
    MyFile << ",Scaune" << ",";
    MyFile << "Dulapuri" << ",";
    MyFile << "Canapele" << ",";
    MyFile << "Comode" << "\n";

    MyFile << "Numar" << ",";
    MyFile <<  produseVandute[0] << ",";
    MyFile <<  produseVandute[1] << ",";
    MyFile <<  produseVandute[2] << ",";
    MyFile <<  produseVandute[3] << "\n";

    MyFile << "Castig" << ",";
    MyFile << pretProduse[0] << ",";
    MyFile << pretProduse[1] <<",";
    MyFile << pretProduse[2] << ",";
    MyFile << pretProduse[3] << "\n";
    MyFile.close();

}

//Am folosit abstract factory pentru a crea mai multe produse de acelasi tip dar cu preturi diferite
class AbstractFurnitureFactory {
public:
    virtual Furniture* CreateDulap() = 0;
    virtual Furniture* CreateScaun() = 0;
    virtual Furniture* CreateComoda() = 0;
    virtual Furniture* CreateCanapea() = 0;
};

class ConcreteFurnitureFactory : public AbstractFurnitureFactory {
public:
    Furniture* CreateDulap() {
        return new Dulap;
    }
    Furniture* CreateScaun() {
        return new Scaun;
    }
    Furniture* CreateCanapea() {
        return new Canapea;
    }
    Furniture* CreateComoda() {
        return new Comoda;
    }
};

int main() {
    Client Lista[10];
    cout << "Hello, World!" << endl;
    citire(Lista);

    string obiect;
    int pret, i, j;


    //int produseVandute[4];
   // int pretProduse[4];

    //produse = scaune, dulapuri, canapele,comode;

    for(i = 0; i < 4; i++){
        produseVandute[i] = 0;
        pretProduse[i] = 0;
    }

    cout << "Obicetele sunt:\nscaun, dulap, canapea,comoda\n";
    for(i = 0; i<5; i++){
        cout << "Alegeti obiectul:\n";
        cin >> obiect;
        cout << "Introduceti pretul obiectului:\n";
        cin >> pret;
        for(i=0;i<4;i++){
            if(obiect == "scaun"){
                pretProduse[i] = pret;
                break;
            }
            if(obiect == "dulap"){
                pretProduse[i] = pret;
                break;
            }
            if(obiect == "canapea"){
                pretProduse[i] = pret;
                break;
            }
            if(obiect == "comoda"){
                pretProduse[i] = pret;
                break;
            }

        }
        for(j = 0; j < 8; j++)
        {
            Lista[j].trimiteNotificare(obiect, pret);
        }
    }

    mobilaLivrata();

    //int i = 1;
    //cout << Lista[i].getNume() << " " << Lista[i].getPrenume() << " " << Lista[i].getAdresa() << " " << Lista[i].getBuget() << endl;
    return 0;
}
