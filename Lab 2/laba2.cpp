#include <iostream>
#include <math.h>
#include <string.h>
using namespace std;

class Vehicle{
    int WheelCnt;//количество колёс
    double mileage;//пробег в км/всё время
    double Volume;//объём бака в л
    double t;//время в пути
    char name[40];
    double Power;//мощность двигателя
public:
    double speed;
    double fuelCons;//расход топлива

    Vehicle();
    ~Vehicle();

   // void input(int countVehicles, Vehicle *pVehicles);
   void input(int countVehicles, Vehicle *pVehicles){
  for(int i=0;i<countVehicles;i++){
    cout << "Enter the name of the vehicle: ";
    if(!(cin >> pVehicles[i].name[40])){
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
    void Speedfunc(int countVehicles, Vehicle *pVehicles);
    void Fuelfunc(int countVehicles, Vehicle *pVehicles);
    void output(int countVehicles, Vehicle *pVehicles);
    void trackTime_refuelings(int routeLength, Vehicle *pVehicles, int countVehicles);
    void Set_name(char nameCar[40]){
        strcpy(name,nameCar);
    }
    char get_name(){
        for(int i=0;i<40;i++){
            cout<<name[i];
        }
        return 0;
    }
    void set_WheelCnt(int Wheel){
        this->WheelCnt=Wheel;
    }
    int get_WheelCnt(){
        return WheelCnt;
    }
    void set_mileage(double mile){
        this->mileage=mile;
    }
    double get_mileage(){
        return mileage;
    }
    void set_Volume(double vol){
        this->Volume=vol;
    }
    double get_Volume(){
        return Volume;
    }
    void set_Power(double power){
        this->Power=power;
    }
    double get_Power(){
        return Power;
    }
    void set_Time(double time){
        this->t=time;
    }
    double get_Time(){
        return t;
    }
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








void output(int countVehicles, Vehicle *pVehicles){
    for(int i=0;i<countVehicles;i++){
      cout<<"name: "<<pVehicles[i].get_name()<<endl;
      cout<<"count of wheels: "<<pVehicles[i].get_WheelCnt()<<endl;
      cout<<"mileage: "<<pVehicles[i].get_mileage()<<endl;
      cout<<"speed: "<<pVehicles[i].speed<<endl;
      cout<<"volume of tank: "<<pVehicles[i].get_Volume()<<endl;
      cout<<"fuel consumption: "<<pVehicles[i].fuelCons<<endl;
      cout<<"power: "<<pVehicles[i].get_Power()<<endl;
      cout<<"travel time: "<<pVehicles[i].get_Time()<<endl;
    }
}


void Vehicle::Speedfunc(int countVehicles, Vehicle *pVehicles){
    for(int i=0;i<countVehicles;i++){
        pVehicles[i].speed=sqrt(pVehicles[i].Power)*((70/pVehicles[i].WheelCnt)-2.5);
    }
}
void Vehicle::Fuelfunc(int countVehicles, Vehicle *pVehicles){
    for(int i=0;i<countVehicles;i++){
      pVehicles[i].fuelCons=(pow(pVehicles[i].Power,1/3)+sqrt(pVehicles[i].Power))-6.25;
    }
}
void Vehicle::output(int countVehicles, Vehicle *pVehicles){
  for(int i=0;i<countVehicles;i++){
      cout<<pVehicles[i].name<<": "<<pVehicles[i].WheelCnt<<"wheels, "<<pVehicles[i].Power<<"horsepower; "<<pVehicles[i].speed<<"km/h; "<<pVehicles[i].fuelCons<<"l/100km"<<endl;
    }
}
void Vehicle::trackTime_refuelings(int routeLength, Vehicle *pVehicles, int countVehicles){
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
            if(time[j]>time[j+1]){
                double temp=time[j];
                time[j]=time[j+1];
                time[j+1]=temp;
                int temp_ref=num_refuelings[j];
                num_refuelings[j]=num_refuelings[j+1];
                num_refuelings[j+1]=temp_ref;
                char temp_name[40];
                strcpy(temp_name, name_V[j]);
                strcpy(name_V[j], name_V[j+1]);
                strcpy(name_V[j+1], temp_name);
            }
        if(time[j]==time[j+1]){
          if(num_refuelings[j]>num_refuelings[j+1]){
            int temp=time[j];
            time[j]=time[j+1];
            time[j+1]=temp;
            int temp_ref=num_refuelings[j];
            num_refuelings[j]=num_refuelings[j+1];
            num_refuelings[j+1]=temp_ref;
            char temp_name[30];
            strcpy(temp_name,name_V[j]);
            strcpy(name_V[j],name_V[j+1]);
            strcpy(name_V[j+1],temp_name);
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


void menu(int countVehicles, Vehicle *pVehicles, int routeLength){
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
    new_page();
    //input(countVehicles, pVehicles);
    for(int i=cur-1;i<cur;++i){
            pVehicles[i].input(countVehicles, pVehicles);
        pVehicles[i].Fuelfunc(countVehicles, pVehicles);
        pVehicles[i].Speedfunc(countVehicles, pVehicles);
    }
    cur++;
    break;
case 2:
    new_page();
      if(cur==0){
        cout<<"you need to input vehicle!\n";
        break;
      }
      output(countVehicles, pVehicles);
      break;
    case 3:
      new_page();
      if(cur==0){
        cout<<"you need to input vehicle!\n";
        break;
      }
      cout<<"Enter the lenght of the track: ";
      cin>>routeLength;

      break;
    case 4:
      if(routeLength==0){
        cout<<"ENTER LENGHT OF THE TRACK , before determinate track!"<<"\n";
        break;
      }
      new_page();
      pVehicles[0].trackTime_refuelings(routeLength, pVehicles, countVehicles);
      complete++;
      break;

    case 5:
      new_page();
      cout<<"Are you sure to exit? 1-yes 0-no\n";
      cin>>exit;
      if(exit==1){
        return;
      }
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
