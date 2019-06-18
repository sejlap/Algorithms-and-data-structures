#include <iostream>
#include <utility>
#include <vector>
#include <string>

template <typename TipKljuca, typename TipVrijednosti>
class Mapa{
public:
    Mapa(){};
    virtual ~Mapa() {};
    virtual int brojElemenata() const=0;
    virtual TipVrijednosti operator[](const TipKljuca &kljuc)const=0;
    virtual TipVrijednosti &operator[](const TipKljuca &kljuc)=0;
    virtual void obrisi()=0;
    virtual void obrisi(const TipKljuca &kljuc)=0;
};

template <typename TipKljuca, typename TipVrijednosti>
class NizMapa : public Mapa<TipKljuca,TipVrijednosti> {
int duzina;
int kapacitet;
std::pair<TipKljuca, TipVrijednosti> **nizMapa;

public:
    NizMapa(){
        duzina=0;
        kapacitet=10000;
        nizMapa = new std::pair<TipKljuca,TipVrijednosti> *[kapacitet] {};
     
    }
    ~NizMapa(){
        for(int i=0; i<duzina; i++)
        delete nizMapa[i];
        delete [] nizMapa;
    }
    NizMapa(const NizMapa &n) : duzina(n.duzina), kapacitet(n.kapacitet),nizMapa(nullptr){
      nizMapa= new std::pair<TipKljuca, TipVrijednosti> *[kapacitet];
      try{
          for(int i=0; i<duzina; i++)
              nizMapa[i]= new std::pair<TipKljuca,TipVrijednosti> (*n.nizMapa[i]);
      }
      catch(...){
          for(int i=0; i<duzina; i++)
          delete nizMapa[i];
          delete []nizMapa;
      }
      
    }
    NizMapa &operator=(const NizMapa &n){
        if(&n==this) return *this;
        for(int i=0; i<duzina; i++) delete nizMapa[i];
        delete []nizMapa;
        duzina=n.duzina;
        kapacitet=n.kapacitet;
        nizMapa=nullptr;
        nizMapa= new std::pair<TipKljuca, TipVrijednosti> *[kapacitet]{};
        try{
            for(int i=0; i<duzina; i++)
                nizMapa[i]= new std::pair<TipKljuca,TipVrijednosti> (*n.nizMapa[i]);
        }
        catch(...){
            for(int i=0; i<duzina; i++)
            delete nizMapa[i];
            delete []nizMapa;
        }
        return *this;
    }
    int brojElemenata() const { return duzina; }
    TipVrijednosti operator[](const TipKljuca &kljuc)const {
        int ima=0, noviindeks=0;
        for(int i=0; i<duzina; i++){
            if(nizMapa[i]->first==kljuc){
                ima=1;
                noviindeks=i;
                break;
            }
            else ima=0;
        }
        if(ima) return nizMapa[noviindeks]->second;
        else return TipVrijednosti();
    }
    TipVrijednosti &operator[](const TipKljuca &kljuc){
        int ima=0,noviindeks=0;
        for(int i=0; i<duzina; i++){
            if(nizMapa[i]->first==kljuc){
                ima=1;
                noviindeks=i;
                break;
            }
            else ima=0;
        }
        if(ima)  return nizMapa[noviindeks]->second;
        else {
            int i=0;
            while( nizMapa[i]!=nullptr && i<kapacitet) i++;
            nizMapa[i] = new std::pair<TipKljuca, TipVrijednosti>;
            nizMapa[i]->first=kljuc;
            duzina++;
            return nizMapa[i]->second;
            }
    }
    void obrisi(){
        for(int i=0; i<duzina; i++){
             delete nizMapa[i];
             nizMapa[i]=nullptr;
        }
        duzina=0;
    }
    
    void obrisi(const TipKljuca &kljuc){
        int ima=0,indeks=0;
        for(int i=0; i<duzina; i++){
            if(nizMapa[i]!=nullptr && nizMapa[i]->first==kljuc){
                ima=1;
                indeks=i;
            }
        }
        if(ima){
            delete nizMapa[indeks];
            nizMapa[indeks]=nullptr;
            for(int k=indeks; k<duzina; k++)
            nizMapa[k]=nizMapa[k+1];
            duzina--;
        }
    }
};

void putovanja(){
    NizMapa<std::string,int> cjenovnik;
    cjenovnik["Bec"] = 289;
    cjenovnik["Istanbul"] = 589;
    cjenovnik["Amsterdam"] = 259;
    std::cout<<"\nFunkcija putovanja";
    std::cout<<"\nBroje elemenata mape je: "<<cjenovnik.brojElemenata();
    cjenovnik.obrisi();
    std::cout<<"\nObrisali smo sve elemente i sada je broj elemenata mape: "<<cjenovnik.brojElemenata();
}

void pjevaci(){
    NizMapa<char,std::vector<std::string>> pjevaci;
    std::vector<std::string> pop;
    std::vector<std::string> folk;
    std::vector<std::string> rok;
    pop.push_back("Zdravko Colic");
    pop.push_back("Dino Merlin");
    
    folk.push_back("Halid Beslic");
    folk.push_back("Hanka Paldum");
    
    rok.push_back("Mladen Vojicic Tifa");
    rok.push_back("Alen Islamovic");
    
    pjevaci['P']= pop;
    pjevaci['F'] = folk;
    pjevaci['R'] = rok;
    std::cout<<"\n\nFunkcija pjevaci";
    std::cout<<"\nBroj elemenata mape pjevaci je: "<<pjevaci.brojElemenata();
    pjevaci.obrisi('F');
    std::cout<<"\nBroj elemenata mape pjevaci je sada "<<pjevaci.brojElemenata();
    
}

void predmeti(){
    NizMapa<std::string,int> predmeti;
    predmeti["OBP"]= 7;
    predmeti["DM"]= 8;
    std::cout<<"\n\nFunkcija predmeti";
    std::cout<<"\nBroj elemenata u mapi je: "<<predmeti.brojElemenata();
    predmeti.obrisi("DM");
    std::cout<<"\nObrisali smo jedan element, sada u mapi ima  "<<predmeti.brojElemenata()<<" element.";
    predmeti.obrisi();
    std::cout<<"\nA sada je: "<<predmeti.brojElemenata();
}
void profesori(){
    NizMapa<std::string, std::string> profesori;
    profesori["ASP"]= "Haris Šupić";
    profesori["LD"] = "Novica Nosovic";
    std::cout<<"\n\nFunkcija profesori";
    std::cout<<"\nBroje elemenata mape profesori je: "<<profesori.brojElemenata();
    profesori.obrisi("LD");
    std::cout<<"\nObrisali smo LD sada je broj elemenata mape profesori: "<<profesori.brojElemenata();
    profesori.obrisi();
    std::cout<<"\nSada je broj elemenata mape: "<<profesori.brojElemenata();
}

void brojevi(){
    NizMapa<int,int> brojevi;
    brojevi[15] = 25;
    brojevi[35] = 45;
    brojevi[12] = 18;
    std::cout<<"\n\nFunkcija brojevi ";
    std::cout<<"\nBroj elemenata mape brojevi je:  "<<brojevi.brojElemenata();
    brojevi.obrisi(35);
    std::cout<<"\nObrisali smo jedan element sada je broj elemenata mape brojevi: "<<brojevi.brojElemenata();
    brojevi.obrisi();
    std::cout<<"\nNakon brisanja mapa brojevi ima "<<brojevi.brojElemenata()<< "elemenata.";
}
int main() {
    
        putovanja();
        pjevaci();
        predmeti();
        profesori();
        brojevi();

    return 0;
}
