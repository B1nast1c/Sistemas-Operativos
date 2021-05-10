//Valeria Goyzueta Torres

#include <iostream>
#include <thread>
#include <mutex>
#include <time.h>
#include <unistd.h>

#define MAX 15
#define Pensando 1
#define Esperando 2
#define Comiendo 3
int comida, consumido=0, nfil; //Variable consumida total
using namespace std;
int Estado[MAX];


class Palillo{
  public:
    mutex mu; //mutex a los recursos
    Palillo(){};
};

Palillo Vajilla[MAX]; //Arreglo de palillos 

struct Filosofo{
  int id=0, energia, right, left, plato;
  Filosofo(): plato(50), energia(50), left(id), right((id+1)%nfil){}
};

void verificar(Filosofo &f1){
  if(Estado[f1.id]==Esperando and Estado[f1.left]!=Comiendo and Estado[f1.right]!=Comiendo and f1.plato>0){
    Estado[f1.id]=Comiendo;

    cout<<"El filosofo "<<f1.id<<" agarra los palitos"<<endl;
  }
}

void Agarrar(Filosofo &f1){
    Estado[f1.id]=Esperando; //Esta hambriento y quierer el palillo
    verificar(f1);
}

void Devolver(Filosofo &f1){
  if(Estado[f1.id]==Comiendo){
    cout<<"El filosofo "<<f1.id<<" devuelve los palitos"<<endl;
    Estado[f1.id]=Pensando;
   
  }
}

void Comer(Filosofo &f1){
  if(Estado[f1.id]==Comiendo){
    int come = rand() % 5 + 1;

    lock(Vajilla[f1.left].mu, Vajilla[f1.right].mu); //Bloqueo a los recursos del arreglo de los tenedores

    lock_guard<mutex> left_lock(Vajilla[f1.left].mu,adopt_lock); //bloqueo al recurso izquierdo
    lock_guard<mutex> right_lock(Vajilla[f1.right].mu,adopt_lock); //bloqueo al recurso derecho 

    cout<<"Filosofo "<<f1.id<<" come "<<come<<" bocados"<<endl;
    f1.energia+=come*5;
    consumido+=come;
    f1.plato-=come*2;
    this_thread::sleep_for(come*1100ms);
  }
  
}

void Pensar(Filosofo &f1){ //Solamente pensamiento de los filósofos
    Estado[f1.id]=Pensando;
    int piensa = rand() % 3 + 1;
    cout<<"Filosofo "<<f1.id<<" piensa "<<endl;

    if(f1.energia>50){
      f1.energia=50;
    }

    f1.energia-=piensa;
    sleep(piensa); //Reduccion de energia al pensar
}

void Cenar(Filosofo &f1, Palillo &pi, Palillo &pd){
  while(1){
    if(f1.energia<0){ 
      cout<<"El filosofo ha muerto "<<endl;
      return; 
    }
    if(f1.plato<=0){
      cout<<"Pensando hasta el final... "<<endl;
      this_thread::sleep_for(1000ms);
      return; 
    }
    Pensar(f1); //Funciones en orden 
    Agarrar(f1);
    Comer(f1);
    Devolver(f1);
  }
}

void cena(){
  int num;
  cout<<"Cuantos filosofos desea: ";
  cin>>num;
  cout<<"Los filosofos se están sentando "<<endl;
  comida=num*50; //Controla el ciclo while
  nfil=num;
  thread Mesa[num];
  Filosofo Filosofos[num];

  for(int i=0; i<num; i++){
    srand(time(NULL));
    Filosofos[i].id=i;
    Mesa[i]=thread(Cenar, ref(Filosofos[i]), ref(Vajilla[Filosofos[i].left]), ref(Vajilla[Filosofos[i].right]));
  }
  for(int i; i<num; i++){
    Mesa[i].join();
  }
}

int main() {
  cena();
  cout<<"LA CENA HA FINALIZADO"<<endl;
  cout<<"Stan Itzy"<<endl;
}
