#include <iostream>
#include <fstream>
using namespace std;
template <typename Tip>
void selection_sort(Tip *niz, int vel){
    for(int i=0; i<vel; i++){
        int min=i;
        Tip tmp;
        for(int j=i+1; j<vel; j++){
            if(niz[j]<niz[min])  min=j;
        }
            
        tmp=niz[i];
        niz[i]=niz[min];
        niz[min]=tmp;
    }
}

template <typename Tip>
void bubble_sort(Tip *niz, int vel){
    for(int i=vel-1; i>=1; i--){
        for(int j=1; j<=i; j++){
            if(niz[j-1]>niz[j]){
                Tip x=niz[j-1];
                niz[j-1]=niz[j];
                niz[j]=x;
            }
        }
    }
}



template <typename Tip>
void subquick_sort(Tip *niz, int first, int last){
    int p=(first+last)/2;
    Tip pivot=niz[p]; //srednji element je nas pivot
    int  i=first,j=last;
    while(j>=i){
        while(niz[i]<pivot)
          i++;
         while(niz[j]>pivot)
            j--;
      if(j>=i){
          Tip tmp;
          tmp=niz[i];
          niz[i]=niz[j];
          niz[j]=tmp;
          i++;
          j--;
      }
    }
    
    if(first<j)
        subquick_sort(niz,first,j); //rekurzija
    if(i<last)
        subquick_sort(niz,i,last);
}

template <typename Tip>
 void quick_sort(Tip *niz, int vel){
    return subquick_sort(niz,0,vel-1);
 }

template <typename Tip>
void merge(Tip *niz,int prvi,int zadnji, int srednji){
    int i,j,k;
    Tip *pom = new Tip [zadnji-prvi+1];
    i=prvi;
    j=srednji+1;
    k=0;
      while(i<=srednji && j<=zadnji ){
          if(niz[i]<niz[j]){
              pom[k]=niz[i];
              k++;
              i++;
          }
          else{
              pom[k]=niz[j];
              k++;
              j++;
          }
      }
      while(i<=srednji){ //posto sam stavila da je i=srednji on nikako nece uci u petlju ako ne stavim <=
          pom[k]=niz[i];
          k++;
          i++;
      }
      while(j<=zadnji){
         pom[k]=niz[j];
         k++;
         j++;
      }
      for(int i=prvi; i<=zadnji; i++){
          niz[i]=pom[i-prvi];
      }
     delete [] pom;
}

template <typename Tip>
void sub_merge_sort(Tip *niz, int prvi, int zadnji){
    if(prvi<zadnji){
        int srednji=(prvi+zadnji)/2;
        int s=srednji+1;
        sub_merge_sort(niz,prvi,srednji);
        sub_merge_sort(niz,s,zadnji);
        merge(niz,prvi,zadnji,srednji);
    }
}   
template <typename Tip>
void merge_sort(Tip *niz, int vel){
    return sub_merge_sort(niz,0,vel-1);
}
void ucitaj(string filename, int *&niz, int vel){
    std::ifstream dat;
    dat.open(filename);
    char c=dat.get();  int i=0;
    while((c=dat.get()) != EOF) // da se svaki put znak moze uporedjivat sa krajem fajla
    vel++;
    niz=new int[vel];
    char element=dat.get();
    while((element=dat.get()) != EOF && i<vel){
        niz[i]=element;
        i++;
    }
    dat.close();
}

void generisi(string filename, int vel){
    std::ofstream izlaz;
    izlaz.open(filename);
    for(int i=0; i<vel; i++){
        izlaz<<rand() % 100<<" ";
    }
    izlaz.close();
}

void pomocna(string filename, int *&niz, int vel){
    ucitaj(filename,niz,vel);
    int odgovor;
    std::cout<<"Koji algoritam sortiranja zelite: 1 - Selection sort, 2 - Bubble sort, 3 - Qiuck Sort 4 - Merge Sort: ";
    std::cin>> odgovor;
    if(odgovor==1){
        clock_t t1=clock();
        selection_sort(niz,vel);
        clock_t t2=clock();
        std::cout<<"Vrijeme izvrsavanja algoritma selection sort je: "<<t2-t1<<std::endl;
        bool sortiran=true;
        for(int i=0; i<vel-1; i++){
            if(niz[i+1] < niz[i]){
                sortiran=false;
                break;
            }
        }
        if(sortiran) std::cout<<"Niz je sortiran\n";
        else std::cout<<"Niz nije sortiran\n";
        generisi("izlazna.txt",vel);
    }
    else if(odgovor==2){
        clock_t t1=clock();
        bubble_sort(niz,vel);
        clock_t t2= clock();
        std::cout<<"Vrijeme izvrsavanja algoritma bubble sort je: "<<t2-t1<<std::endl;
        bool sortiran=true;
        for(int i=0; i<vel-1; i++){
            if(niz[i+1]< niz[i]){
                sortiran=false;
                break;
            }
        }
        if(sortiran) std::cout<<"Niz je sortiran.\n";
        else std::cout<<"Niz nije sortiran.\n";
        generisi("izlazna.txt",vel);
    }
    
    else if(odgovor==3){
        clock_t t1=clock();
        quick_sort(niz,vel);
        clock_t t2=clock();
        std::cout<<"Vrijeme izvrsavanja algoritma quick_sort je: "<<t2-t1<<std::endl;
        bool sortiran=true;
        for(int i=0; i<vel-1; i++){
            if(niz[i+1]<niz[i]){
                sortiran=false;
                break;
            }
        }
        if(sortiran) std::cout<<"Niz je sortiran\n";
        else std::cout<<"Niz nije sortiran\n";
        generisi("izlazna.txt",vel);
    }
    else if(odgovor==4){
        clock_t t1=clock();
        merge_sort(niz,vel);
        clock_t t2=clock();
        std::cout<<"Vrijeme izvrsavanja algoritma merge sort je: "<<t2-t1<<std::endl;
        bool sortiran=true;;
        for(int i=0; i<vel; i++){
            if(niz[i+1]<niz[i]){
                sortiran=false;
                break;
            }
        }
        if(sortiran) std::cout<<"Niz je sortiran.\n";
        else std::cout<<"Niz nije sortiran.\n";
        generisi("izlazna.txt",vel);
    }

}


int main() {

    int *niz;
    int vel=50;
    generisi("pomocna.txt",vel);
    ucitaj("pomocna.txt",niz,vel);
    pomocna("pomocna.txt", niz,vel);
    
    
}
