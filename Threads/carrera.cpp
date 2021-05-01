#include <iostream>
#include <thread>
#include <time.h>
using namespace std;
#define METROS 50
int lugar=1, distcaballos=0, ncaballos;

struct Caballos{
    int id;
    int metros;
    Caballos(): metros(0){};
};

void Alinear(Caballos c1){
  while(1){
    if (c1.metros>=METROS){
      if(lugar==1){cout<<"TENEMOS UN GANADOR!"<<endl;}
      cout<<"Caballo "<<c1.id<<" es lugar "<<lugar<<endl;
      lugar++;
      return;
    }
    else{
      int avance = rand() % 20 + 1;
      distcaballos+=avance;
      cout<<"Caballo "<<c1.id<<" ha corrido "<<avance<<" metros!"<<endl;
      int dormir = rand() % 2 + 1;
      cout<<"Caballo "<<c1.id<<" descansa "<<dormir<<" segundos!"<<endl;
      this_thread::sleep_for(dormir*1100ms);
      c1.metros+=avance;
    }
  }
}

void carrera(){
  cout<<"Nro Caballos: ";
  cin>>ncaballos;
  Caballos pista[ncaballos];
  thread caballos[ncaballos];
  cout<<"Alistando caballos..."<<endl;
  cout<<"INICIAMOS CARRERA"<<endl;

  for(int i=0; i<ncaballos;i++){
    srand (time(NULL));
    Caballos c1;
    pista[i]=c1;
    c1.id=i+1;
    caballos[i]=thread(Alinear, c1);
  }
  for(int i=0; i<ncaballos; i++){
    caballos[i].join();
  }

}

int main(void) {
  carrera();
  cout<<"FIN DE LA CARRERA";
  return 0;
}
