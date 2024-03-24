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
    char name[40];
    double Power;//мощность двигателя
public:
    double speed;
    double fuelCons;//расход топлива

    Vehicle(int countVehicles, Vehicle *pVehicles);
//        name[]="";
//        WheelsCnt=0;
//        Power=0;
//        mileage=0;
//        Volume=0;
//        t=0;
//        speed=0;
//        fuelCons=0;
//    }
    Vehicle();
    ~Vehicle();

    void Speedfunc(int countVehicles, Vehicle *pVehicles);
    void Fuelfunc(int countVehicles, Vehicle *pVehicles);
    void output(int countVehicles, Vehicle *pVehicles);
    void trackTime_refuelings(int routeLength, Vehicle *pVehicles, int countVehicles);
    void Set_name(char nameCar[40]){
        strcpy(name, nameCar);
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





void ignoreLine(){
    cin.clear();
    cin.ignore();
}


Vehicle::Vehicle(int countVehicles,Vehicle* pVehicles){
  for(int i=0; i < countVehicles; i++){
    char name[40];
    int WheelCnt;
    double mileage;
    double Volume;
    double power;
    double t;
    cout << "Введите название ТС: ";
    cin >> name;
    pVehicles[i].Set_name(name);
    cout << "Введите количество колёс: ";
    cin >> WheelCnt;
    while (cin.fail()){
         ignoreLine();
         cout << "Вы ввели символ, введите число" << endl;
         cin >> WheelCnt;
     }
    pVehicles[i].set_WheelCnt(WheelCnt);
    cout << "Введите пробег: ";
    cin >> mileage;
    while (cin.fail()){
       ignoreLine();
       cout << "Вы ввели символ, введите число" << endl;
       cin >> mileage;
    }
    pVehicles[i].set_mileage(mileage);
    cout<<"Введите объём бака: ";
    cin>>Volume;
    while (cin.fail()){
       ignoreLine();
       cout << "Вы ввели символ, введите число" << endl;
       cin >> Volume;
    }
    pVehicles[i].set_Volume(Volume);
    cout<<"Введите мощность двигателя: ";
    cin>>Power;
    while (cin.fail()){
       ignoreLine();
       cout << "Вы ввели символ, введите число" << endl;
       cin >> Power;
    }
    pVehicles[i].set_Power(Power);
    cout<<"Введите время в пути в часах: ";
    cin>>t;
    while (cin.fail()){
       ignoreLine();
       cout << "Вы ввели символ, введите число" << endl;
       cin >> t;
    }
    pVehicles[i].set_Time(t);
    cout<<"\n";
  }
}


void output(int countVehicles, Vehicle *pVehicles){
    for(int i=0;i<countVehicles;i++){
      cout<<"название ТС: "<<pVehicles[i].get_name()<<endl;
      cout<<"количество колёс: "<<pVehicles[i].get_WheelCnt()<<endl;
      cout<<"пробег: "<<pVehicles[i].get_mileage()<<endl;
      cout<<"скорость: "<<pVehicles[i].speed<<endl;
      cout<<"объём бака: "<<pVehicles[i].get_Volume()<<endl;
      cout<<"потребление двигателя: "<<pVehicles[i].fuelCons<<endl;
      cout<<"мощность двигателя: "<<pVehicles[i].get_Power()<<endl;
      cout<<"время в пути: "<<pVehicles[i].get_Time()<<endl;
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
      cout << pVehicles[i].name<<": "<<pVehicles[i].WheelCnt<<" колёс, "<<pVehicles[i].Power<<" лошадиных сил; "<<pVehicles[i].speed<<"км/ч; "<<pVehicles[i].fuelCons<<"l/100км"<<endl;
    }
}
void Vehicle::trackTime_refuelings(int routeLength, Vehicle *pVehicles, int countVehicles){
    double time[countVehicles];
    int num_refuel[countVehicles];
    char name_V[countVehicles][40];
    double refuelings[countVehicles];
    for(int i=0;i<countVehicles;i++){
        refuelings[i]=(((routeLength/100)*pVehicles[i].fuelCons)/pVehicles[i].Volume);
        num_refuel[i]=(int)refuelings[i];
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
                int temp_ref=num_refuel[j];
                num_refuel[j]=num_refuel[j+1];
                num_refuel[j+1]=temp_ref;
                char temp_name[40];
                strcpy(temp_name, name_V[j]);
                strcpy(name_V[j], name_V[j+1]);
                strcpy(name_V[j+1], temp_name);
            }
        if(time[j]==time[j+1]){
          if(num_refuel[j]>num_refuel[j+1]){
            int temp=time[j];
            time[j]=time[j+1];
            time[j+1]=temp;
            int temp_ref=num_refuel[j];
            num_refuel[j]=num_refuel[j+1];
            num_refuel[j+1]=temp_ref;
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
    cout<<"ТС: "<<name_V[i]<<endl;
    cout<<"Время в пути:"<<time[i]<<" часов"<<endl;
    cout<<"Количество заправок: "<<num_refuel[i]<<endl;
    cout<<endl;
  }
}


Vehicle::Vehicle(){
    cout << "ТС создано"<<endl;
}

Vehicle::~Vehicle(){
    cout << "ТС удалён";
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
    cout<<"5-вывод результатов прохождения трассы"<<endl;
    cout<<"6-выход из программы"<<endl;
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

    for(int i=cur-1; i < cur; ++i){
        pVehicles[i].Fuelfunc(countVehicles, pVehicles);
        pVehicles[i].Speedfunc(countVehicles, pVehicles);
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

      break;
    case 4:
      if(routeLength==0){
        cout<<"Введите протяжённость трассы, до определения времени прохождения трассы заданной протяжённости!"<<"\n";
        break;
      }
      new_page();
      pVehicles[0].trackTime_refuelings(routeLength, pVehicles, countVehicles);
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
    Vehicle *pVehicles=new Vehicle[countVehicles];

    int routeLength = 0;
    menu(countVehicles, pVehicles, routeLength);
    delete [] pVehicles;
    return 0;
}
