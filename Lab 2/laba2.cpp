#include <iostream>
#include <math.h>
#include <string.h>
using namespace std;

class Vehicle{



public:
    int WheelCnt;//количество колёс
    double mileage;//пробег в км/всё время
    double Volume;//объём бака в л
    double speed;
    double Power;//мощность двигателя
    double fuelCons;//расход топлива
    double t;//время в пути
    char name[40];
    //public:
    double Speedfunc(double Power, int cnt);
    double Fuelfunc(double t);
    Vehicle();
    ~Vehicle();
};


Vehicle::Vehicle(){
    cout << "Vehicle is created"<<endl;
//    p = new int;
//    *p = i;
//    cout << p << ": " << *p << endl;
}

Vehicle::~Vehicle(){
    cout << "Vehicle is deleted";
//    delete Vehicle;
}

void input(int countVehicles, Vehicle *pVehicles)
{
  for(int i=0;i<countVehicles;i++)
  {
    cout << "Enter the name of the vehicle: ";
    if(!(cin >> pVehicles[i].name)){
        cout<<"error"<<endl;
        return;
    };
    cout << "Enter the count of wheels: ";
    cin >> pVehicles[i].WheelCnt;
    cout << "Enter the mileage: ";
    cin >> pVehicles[i].mileage;
    cout << "Enter the volume of the tank: ";
    cin >> pVehicles[i].Volume;
    cout << "Enter the power: ";
    cin >> pVehicles[i].Power;
  }
}
void Speedfunc(int countVehicles, Vehicle *pVehicles){
    for(int i=0;i<countVehicles;i++){
        pVehicles[i].speed=sqrt(pVehicles[i].Power)*((70/pVehicles[i].WheelCnt)-2.5);
    }
}
void Fuelfunc(int countVehicles, Vehicle *pVehicles){
    for(int i=0;i<countVehicles;i++){
      pVehicles[i].fuelCons=(pow(pVehicles[i].Power,1/3)+sqrt(pVehicles[i].Power))-6.25;
    }
}
void output(int countVehicles, Vehicle *pVehicles){
  for(int i=0;i<countVehicles;i++){
      cout<<pVehicles[i].name<<": "<<pVehicles[i].WheelCnt<<"wheels, "<<pVehicles[i].Power<<"horsepower; "<<pVehicles[i].speed<<"km/h; "<<pVehicles[i].fuelCons<<"l/100km"<<endl;
    }
}
void trackTime_refuelings(int routeLength, Vehicle *pVehicles, int countVehicles){
    double time[countVehicles];
    int num_refuelings[countVehicles];
    char name_V[countVehicles][40];
    double refuelings[countVehicles];
    for(int i=0;i<countVehicles;i++){
        refuelings[i]=(((routeLength/100)*pVehicles[i].fuelCons)/pVehicles[i].Volume);
        num_refuelings[i]=(int)refuelings[i];
    }
    for(int i=0;i<countVehicles;i++){
        time[i]=routeLength/pVehicles[i].speed;
    }
    for(int i=0;i<countVehicles;++i){
        strcpy(name_V[i], pVehicles[i].name);
    }
    for(int i=0;i<countVehicles;i++){
        for(int j=0;j<countVehicles-1;++j){
//            if(time[j]>time[j+1]){
//                double temp=time[j];
//                time[j]=time[j+1];
//                time[j+1]=temp;
//                int temp_ref=num_refuelings[j];
//                num_refuelings[j]=num_refuelings[j+1];
//                num_refuelings[j+1]=temp_ref;
//                char temp_name[40];
//                strcpy(temp_name, name_V[j]);
//                strcpy(name_V[j], name_V[j+1]);
//                strcpy(name_V[j+1], temp_name);
//            }
        if(time[j]==time[j+1]){
          if(num_refuelings[j]>num_refuelings[j+1]){
            int temp=time[j];
            time[j]=time[j+1];
            time[j+1]=temp;
//            int temp_ref=num_refuelings[j];
//            num_refuelings[j]=num_refuelings[j+1];
//            num_refuelings[j+1]=temp_ref;
//            char temp_name[30];
//            strcpy(temp_name,name_V[j]);
//            strcpy(name_V[j],name_V[j+1]);
//            strcpy(name_V[j+1],temp_name);
          }
        }
      }
    }
  cout<<"time and refuelings done"<<endl;
  for(int i=0;i<countVehicles;i++)
  {
    cout<<"Vehicle: "<<name_V[i]<<endl;
    cout<<"Time of the track:"<<time[i]<<" hours"<<endl;
    cout<<"Count_refuelings: "<<num_refuelings[i]<<endl;
    cout<<endl;
  }
}


void new_page()
{
  for(int i=0;i<100;++i)
    {
      cout<<endl;
    }
}


void menu(int countVehicles, Vehicle *pVehicles,int routeLength){
    int exit=0;
    int complete=0;
    int cur=0;

  while(exit==0){
    cout<<"1-enter new vehicle's information" << endl;
    cout<<"2-see information of the vehicles"<<endl;
    cout<<"3-enter route length" << endl;
    cout<<"4-calculation of time to pass rhe route"<<endl;
    cout<<"5-output of route results"<<endl;
    cout<<"6-exit from programm"<<endl;
    int choice;
    cout << "Enter your choice: "<<endl;
    if(!(cin>> choice)){
        cout << "Error "<<endl;
        return;
    }
    switch(choice){
case 1:
//    cout << "Enter "<<endl;
//    new_page();
//      input(countVehicles, pVehicles);
//      Speedfunc(countVehicles,pVehicles);
//      Fuelfunc(countVehicles, pVehicles);

    break;
case 2:
    break;


default:
    cout << "Error "<<endl;
    break;

    }
  }
}


int main(){
    int countVehicles;
    cout << "Enter count of vehicles: ";
    if(!(cin >> countVehicles)){
        cout <<"error"<< endl;
    }
    Vehicle *pVehicles=new Vehicle[countVehicles];

    int routeLength = 0;
    menu(countVehicles, pVehicles, routeLength);
    delete [] pVehicles;
    return 0;
}
