#include <iostream>
#include <cmath>
#include <string.h>
using namespace std;

class Vehicle{
private:
    int WheelCnt;//количество колёс
    double mileage;//пробег в км/всё время
    double Volume;//объём бака в л
    double t;//время в пути
    string name;
    double Power;//мощность двигателя
    double speed;
    double fuelCons;//расход топлива
public:
    Vehicle(int countVehicles, Vehicle *pVehicles);
    Vehicle();
    ~Vehicle();

    void calc_speed(int countVehicles, Vehicle *pVehicles);
    void calc_fuelCons(int countVehicles, Vehicle *pVehicles);
    //void output(int countVehicles, Vehicle *pVehicles);
   // void trackTime_refuelings(int routeLength, Vehicle *pVehicles, int countVehicles);

    void set_name(string nameCar){name=nameCar;}
    string get_name(){return name;}
    void set_WheelCnt(int Wheel){this->WheelCnt=Wheel;}
    int get_WheelCnt(){return WheelCnt;}
    void set_mileage(double mile){this->mileage=mile;}
    double get_mileage(){return mileage;}
    void set_Volume(double vol){this->Volume=vol;}
    double get_Volume(){return Volume;}
    void set_Power(double power){this->Power=power;}
    double get_Power(){return Power;}
    void set_Time(double time){this->t=time;}
    double get_Time(){return t;}
    double get_fuelCons(){return fuelCons;}
    double get_speed(){return speed;}

    friend void ShowSpeed(int countVehicles, Vehicle *pVehicles,int i){
        cout<<"Speed:";
        cout<<pVehicles[i].speed;
        cout<<"\n";
    }
    friend void Showfuelcons(int countVehicles, Vehicle *pVehicles,int i){
        cout<<"Fuel consumption:";
        cout<<pVehicles[i].fuelCons;
        cout<<"\n";
    }
};


void ignoreLine(){
    cin.clear();
    cin.ignore();
}


Vehicle::Vehicle(int countVehicles,Vehicle* pVehicles){
  for(int i=0; i < countVehicles; i++){
    string name;
    int WheelCnt;
    //double mileage;
    double Volume;
    double power;
   // double t;
   cout<<"ТС № "<<i+1<<endl;
    cout << "Введите название ТС: ";
    cin >> name;
    pVehicles[i].set_name(name);
    cout << "Введите количество колёс: ";
    cin >> WheelCnt;
    while (cin.fail()){
         ignoreLine();
         cout << "Вы ввели символ, введите число" << endl;
         cin >> WheelCnt;
     }
     do{
        if(WheelCnt<=0){
            cout<<"количество колёс должно быть больше 0. Попробуйте ещё раз"<<endl;
            cin>> WheelCnt;
        }
     }while(WheelCnt<=0);
    pVehicles[i].set_WheelCnt(WheelCnt);
//    cout << "Введите пробег: ";
//    cin >> mileage;
//    while (cin.fail()){
//       ignoreLine();
//       cout << "Вы ввели символ, введите число" << endl;
//       cin >> mileage;
//    }
//    pVehicles[i].set_mileage(mileage);
    cout<<"Введите объём бака: ";
    cin>>Volume;
    while (cin.fail()){
       ignoreLine();
       cout << "Вы ввели символ, введите число" << endl;
       cin >> Volume;
    }
     do{
        if(Volume<=0){
            cout<<"объём бака должен быть больше 0. Попробуйте ещё раз"<<endl;
            cin>> Volume;
        }
     }while(Volume<=0);
    pVehicles[i].set_Volume(Volume);
    cout<<"Введите мощность двигателя: ";
    cin>>Power;
    while (cin.fail()){
       ignoreLine();
       cout << "Вы ввели символ, введите число" << endl;
       cin >> Power;
    }
    do{
        if(Power<=0){
            cout<<"мощность двигателя должна быть больше 0. Попробуйте ещё раз"<<endl;
            cin>> Power;
        }
     }while(Power<=0);
    pVehicles[i].set_Power(Power);
//    cout<<"Введите время в пути в часах: ";
//    cin>>t;
//    while (cin.fail()){
//       ignoreLine();
//       cout << "Вы ввели символ, введите число" << endl;
//       cin >> t;
//    }
//    pVehicles[i].set_Time(t);
    cout<<"\n";
    }
}


void output(int countVehicles, Vehicle *pVehicles){
    for(int i=0;i<countVehicles;i++){
      cout<<"название ТС: "<<pVehicles[i].get_name()<<endl;
      cout<<"количество колёс: "<<pVehicles[i].get_WheelCnt()<<endl;
      //cout<<"пробег: "<<pVehicles[i].get_mileage()<<endl;
      cout<<"скорость: "<< pVehicles[i].get_speed() << endl;
      ShowSpeed(countVehicles, pVehicles, i);
      cout<<"объём бака: "<<pVehicles[i].get_Volume()<<endl;
      Showfuelcons(countVehicles, pVehicles, i);
      cout<<"потребление двигателя: "<<pVehicles[i].get_fuelCons()<<endl;
      cout<<"мощность двигателя: "<<pVehicles[i].get_Power()<<endl;
      //cout<<"время в пути: "<<pVehicles[i].get_Time()<<endl;
    }
}


void Vehicle::calc_speed(int countVehicles, Vehicle *pVehicles){
    for(int i=0;i<countVehicles;i++){
        pVehicles[i].speed=fabs(sqrt(pVehicles[i].Power)*((70/pVehicles[i].WheelCnt)-2.5));
    }
}
void Vehicle::calc_fuelCons(int countVehicles, Vehicle *pVehicles){
    for(int i=0;i<countVehicles;i++){
      pVehicles[i].fuelCons=fabs((pow(pVehicles[i].Power,1/3)+sqrt(pVehicles[i].Power))-6.25);
    }
}
//void Vehicle::output(int countVehicles, Vehicle *pVehicles){
//  for(int i=0;i<countVehicles;i++){
//      cout << pVehicles[i].name<<": "<<pVehicles[i].WheelCnt<<" колёс, "<<pVehicles[i].Power<<" лошадиных сил; "<<pVehicles[i].speed<<"км/ч; "<<pVehicles[i].fuelCons<<"l/100км"<<endl;
//    }
//}

int cnt_refueling(int lenght_route, int countVehicles, Vehicle *pVehicles, int i){
      int num_refuelings[countVehicles];
      num_refuelings[i]=(int)(((lenght_route/100)*pVehicles[i].get_fuelCons())/pVehicles[i].get_Volume());
  return num_refuelings[i];
}
void trackResults(int countVehicles, string* name_V, double* time_track, int* num_refuelings){
    cout << "calculation complete!\n";
    for (int i = 0; i < countVehicles; i++) {
        cout << "ТС: " << name_V[i] << endl;
        cout << "Время прохождения трассы:" << (int)time_track[i] << " часов\n";
        cout << (int)((time_track[i] - (int)time_track[i]) * 60) << " мин\n";
        cout << (int)(time_track[i] * 3600 - (int)(time_track[i]) * 3600 - (int)((time_track[i] - (int)time_track[i]) * 60) * 60) << " сек\n";
        cout << "Количество заправок: " << num_refuelings[i] << endl;
        cout << endl;
    }
}


void calc_track(int routeLength, Vehicle *pVehicles, int countVehicles){
    double time[countVehicles];
    int num_refuel[countVehicles];
    string name_V[countVehicles];
    double refuelings[countVehicles];
    for(int i=0;i<countVehicles;i++){
            num_refuel[i] = cnt_refueling(routeLength, countVehicles, pVehicles, i);
//        refuelings[i]=(((routeLength/100)*pVehicles[i].get_fuelCons())/pVehicles[i].get_Volume());
//        num_refuel[i]=(int)refuelings[i];
    }
    for(int i=0;i<countVehicles;i++){
        time[i]=routeLength/pVehicles[i].get_speed();
    }
    for(int i=0;i<countVehicles;++i){
        //strcpy(name_V[i], pVehicles[i].name);
        name_V[i]=pVehicles[i].get_name();
    }
    for(int i=0;i<countVehicles;i++){
        for(int j=0;j<countVehicles-1;++j){
            if(time[j]>time[j+1]){
                double temp=time[j];
                time[j]=time[j+1];
                time[j+1]=temp;
                int temp_ref=num_refuel[j];
                num_refuel[j]=num_refuel[j+1];
                num_refuel[j+1]=temp_ref;
                string temp_name;
                temp_name=name_V[j];
                name_V[j]=name_V[j+1];
                name_V[j+1]=temp_name;
            }
        if(time[j]==time[j+1]){
          if(num_refuel[j]>num_refuel[j+1]){
            double temp=time[j];
            time[j]=time[j+1];
            time[j+1]=temp;
            int temp_ref=num_refuel[j];
            num_refuel[j]=num_refuel[j+1];
            num_refuel[j+1]=temp_ref;
            string temp_name;
            temp_name=name_V[j];
                name_V[j]=name_V[j+1];
                name_V[j+1]=temp_name;
          }
        }
      }
    }
  //cout<<"time and refuelings done"<<endl;
  trackResults(countVehicles, name_V, time, num_refuel);
}


Vehicle::Vehicle(){
    cout << "ТС создано"<<endl;
}
Vehicle::~Vehicle(){
    cout << "ТС удалён"<<endl;
}


void new_page(){
  for(int i=0;i<50;++i){
      cout<<endl;
    }
}


void menu(int countVehicles, Vehicle *pVehicles, int routeLength){
    int exit=0;
    int complete=0;
    int cur=0;

  while(exit == 0){
    cout<<"1-ввести информацию о новых ТС;" << endl;
    cout<<"2-просмотреть информацию о ТС;"<<endl;
    cout<<"3-ввести протяжённость трассы;" << endl;
    cout<<"4-расчет времени прохождения трассы заданной протяженности;"<<endl;
    cout<<"5-выход из программы"<<endl;
    int choice;
    cout << "Выберите действие: "<<endl;
    cin>> choice;
    while (cin.fail()){
        ignoreLine();
        cout << "Вы ввели символ, введите число" << endl;
        cin >> choice;
    }
    switch(choice){
case 1:
    new_page();
    Vehicle(countVehicles, pVehicles);
    for(int i=cur-1; i < cur; i++){
        pVehicles[i].calc_fuelCons(countVehicles, pVehicles);
        pVehicles[i].calc_speed(countVehicles, pVehicles);
    }
    cur++;
    break;
case 2:
    new_page();
      if(cur==0){
        cout<<"введите данные о ТС!\n";
        break;
      }
      output(countVehicles, pVehicles);
      break;
    case 3:
      new_page();
      if(cur==0){
        cout<<"введите данные о ТС!\n";
        break;
      }
      cout<<"Введите протяжённость трассы: ";
      cin >> routeLength;
        while (cin.fail()){
            ignoreLine();
            cout << "Вы ввели символ, введите число" << endl;
            cin >> routeLength;
        }
        do{
            if(routeLength<=0){
                cout<<"протяжённость трассы должна быть больше 0. Попробуйте ещё раз"<<endl;
                cin >> routeLength;
            }
        }while(routeLength<=0);
      break;
    case 4:
      if(routeLength==0){
        cout<<"Введите протяжённость трассы, до определения времени прохождения трассы заданной протяжённости!\n";
        break;
      }
      new_page();
      calc_track(routeLength, pVehicles, countVehicles);
      complete++;
      break;
    case 5:
      new_page();
      cout<<"Вы точно хотите выйти из программы? 1-да 0-нет\n";
      cin >> exit;
        while (cin.fail()){
            ignoreLine();
            cout << "Вы ввели символ, введите число" << endl;
            cin >> exit;
        }
      if(exit==1){
        return;
      }
      break;
    default:
      cout<<"error! try again"<<"\n";
    }
  }
}


int main(){
    setlocale(LC_CTYPE,"");
    int countVehicles;
    cout << "Введите количество ТС: ";
    cin >> countVehicles;
    while (cin.fail()){
        ignoreLine();
        cout << "Вы ввели символ, введите число" << endl;
        cin >> countVehicles;
    }
    do{
      if(countVehicles<=0){
          cout<<"количество ТС должно быть больше 0. Попробуйте ещё раз"<<endl;
          cin >> countVehicles;
      }
    }while(countVehicles<=0);
    Vehicle *pVehicles=new Vehicle[countVehicles];

    int routeLength = 0;
    menu(countVehicles, pVehicles, routeLength);
    delete [] pVehicles;
    return 0;
}
