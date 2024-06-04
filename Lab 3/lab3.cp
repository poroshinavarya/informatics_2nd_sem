#include <iostream>
#include <cmath>
#include <limits>
#include <string>
#include <ctime>
using namespace std;

int num = 0; //изначальный размер массива
double Check_input(double var);
int Check_input(int var);
class Wheel{
    double cur_mileage;
       int status;
public:
    int check_status(double mileage, double speed);
    Wheel(){status=0;cur_mileage=0;};
    double def_wheel(double mileage, double speed){
        cur_mileage=mileage;
        status=check_status(mileage, speed);
        return cur_mileage;
    }
    virtual void output();
    int get_status() {return status;}
};
class Engine{
protected:
    double engIntake; //потребление двигателя l/km
    double engPow; //мощность двигателя HP horsepower
public:
 inline double calc_Intake() {return fabs(pow(engPow, 1 / 3) + sqrt(engPow) - 6.25);}
 Engine(){engIntake=0;engPow=0;};
 void def_engine(double power);
 virtual void output();
};
class Fuel_system{
    protected:
        double cur_fuel; //текущий обЪём топлива литры l;
public:
  double TankVolume; //обЪём бака литры l
  void calc_cur_fuel(double engIntake,double mileage,double Cnt_refueling);//расчёт текущего обЪёма топлива
  Fuel_system(){TankVolume=0;cur_fuel=0;};
 void def_fuel_system(double volume, double engIntake, double mileage );
 virtual void output();
};
class Vehicle: public Engine, public Fuel_system{
private:
    int WheelCnt;
    double speed;
  int damaged_wheels=0;
  double mileage;
  double Cnt_refueling;//количество заправок
  double Time;//время в пути
public:
      Wheel* ptr_wheel;
    string name;

  Vehicle(string NameCar, int wheels){
    mileage = damaged_wheels =0;
    set_name(NameCar);
    set_WheelCnt(wheels);
    ptr_wheel= new Wheel[wheels];
    for (int i = 0; i < wheels; i++) {
        ptr_wheel[i] = Wheel();
    }
    def_fuel_system(0, engIntake, mileage);
    def_engine(0);
    calc_speed();
  }
  Vehicle(){
    name="Vehicle is added";
    Time=mileage=Cnt_refueling=damaged_wheels=0;
    ptr_wheel=0;
  }
  ~Vehicle(){
    cout << "Deletion of " << name << endl;
  }

  void set_name(string NameCar){name = NameCar;}
  void set_WheelCnt(int wheels){WheelCnt = wheels;}
  void set_mileage(double tracklength) { mileage=tracklength; }
  void output();
  inline double calc_Time(double routelength) {
    return (routelength / speed);
  };
   void calc_speed();
  double calc_refuel(double raceLength){
    double Refuel = (raceLength * (engIntake / 100)) / TankVolume;
  if (Refuel > 1)
    this->Cnt_refueling= ceil(Refuel);
  else
    this->Cnt_refueling= floor(Refuel);
    }
    void time_show();
    double get_Time(){return Time;};
    double get_Cnt_refueling(){return Cnt_refueling;};
    int get_WheelCnt() { return WheelCnt; }
    double get_speed(){return speed;};
    void number_of_damaged_wheels();
    friend Vehicle *Results(int num);
    friend void outputResults(Vehicle *&pVehicles, int num);
  friend ostream &operator<<(ostream &stream, const Vehicle &obj){
    return stream << "Number of wheels: " << obj.WheelCnt << ";\n"
    << "Damaged wheels: " << obj.damaged_wheels << ";\n"
    << "Speed: " << obj.speed << " km/h;\n"
    << "Mileage: " << obj.mileage << " km;\n"
    <<"fuel volume: "<<obj.TankVolume<<"l;\n"
    <<"current fuel: "<<obj.cur_fuel<<"l\n"
    <<"engine power: "<<obj.engPow<<" HP;\n"
    <<"engine intake: "<<obj.engIntake<<" l/100km;\n"<<endl;
    }
};


int menu(int &cur) {
  cout << "\nChoose action:\n";
  cout << "0 - exit\n";
  cout << "1 - to add new Vehicle\n";
  cout << "2 - output information about Vehicle\n";
  cout << "3 - to enter length of the track\n";
  cout << "4 - route calculation\n";
  if (cur == 1)
    cout << "5 - results of last race\n";
  int choice = 0;
  choice = Check_input(choice);
  if (choice == 4) {
    cur = 1;
  }
  return choice;
}

void clean(int var=1) {
  for (int i = 0; i < 3; i = i + 1) {
    cout << endl;
  }
}

void newCar(Vehicle *&pVehicles, int &num, const Vehicle &cars){
  Vehicle *temp;
  if (pVehicles != nullptr) {
    temp = new Vehicle[num + 1];
    for (int i = 0; i < num; i++) {
      temp[i] = pVehicles[i];
    }
    delete[] pVehicles;
  }
  else{
    temp = new Vehicle[1];
  }
  temp[num] = cars;
  pVehicles = temp;
  num++;
}

Vehicle *Results(Vehicle *&pVehicles, int num){
  Vehicle *results = new Vehicle[num];
  Vehicle *cur_copy = new Vehicle[1];
  for (int i = 0; i < num; i++) {
    results[i] = pVehicles[i];
  }
  for (int i = 0; i < num; i++) {
    for (int j = 0; j < num; j++) {
      if ((results[i].get_Time() - results[j].get_Time() < 0)&&(results[i].get_Cnt_refueling() - results[i].get_Cnt_refueling() <= 0)) {
        cur_copy[0] = results[i];
        results[i] = results[j];
        results[j] = cur_copy[0];
      }
    }
  }
  delete[] cur_copy;
  return results;
}

void outputResults(Vehicle *&pVehicles, int num) {
  Vehicle *results = Results(pVehicles, num);
  for (int i = 0; i < num; i++) {
    cout << results[i].name << endl;
    results[i].time_show();
    cout << "Refuel times: " << int(results[i].Cnt_refueling) << endl;
  }
  delete[] results;
}

double Check_input(double var) {
  cin >> var;
  if (cin.fail() || var <= 0) {
    while (!(cin >> var) || var <= 0) {
      cout << "error, try again\n";
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
  }
  return var;
}

int Check_input(int var) {
  cin >> var;
  if (cin.fail() || var < 0) {
    while (!(cin >> var) || var < 0) {
      cout << "error, try again\n";
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
  }
  return var;
}
int Wheel :: check_status(double mileage, double speed)
{
  int ratio = (1/(mileage*sqrt(speed)));
  if(ratio>=0.5){
    return 0;
  }
  else
  {
    return 1;
  }
}

void Wheel ::output() {
  if (status == 1) {
    cout << "damaged" << endl;
  } else {
    cout << "not damaged" << endl;
  }
}
void Engine ::output() {
  cout << "engine power: " << engPow << " HP;" << endl;
  cout << "engine intake: " << engIntake << " l/100km;" << endl;
}

void Engine::def_engine(double power) {
  cout << "engine power (HP): ";
  power = Check_input(power);
  engPow = power;
  engIntake = calc_Intake();
}

void Fuel_system ::calc_cur_fuel(double engIntake, double mileage,double Cnt_refueling) { //расчёт текущего обЪёма топлива
  if (Cnt_refueling == 0) {
    cur_fuel=double(TankVolume - ((engIntake / 100) * mileage));
  } else {
    cur_fuel=(((Cnt_refueling)*TankVolume) - ((engIntake / 100) * mileage));
  }
}

void Fuel_system ::def_fuel_system(double volume, double engIntake,double mileage) {
  cout << "fuel volume: ";
  volume = Check_input(volume);
  TankVolume = volume;
  cur_fuel = volume;
}
void Fuel_system ::output() {
  cout << "fuel volume: " << TankVolume << "l" << endl;
  cout << "current fuel: " << cur_fuel << "l" << endl;
}

void Vehicle::output() {
  cout << "\nNumber of wheels: " << WheelCnt << ";\n"
       << "Damaged wheels: " << damaged_wheels << ";\n"
       << "speed: " << speed << " km/h;\n"
       << "mileage: " << mileage << " km;" << endl;
  Engine::output();
  Fuel_system::output();
}

void Vehicle ::time_show(){
  double t = this->Time;
  int hours = int(t);
  double cur_time = (t - hours) * 60;
  int minutes = int(cur_time);
  int seconds = int((cur_time - minutes) * 60);
  cout << "TIME: " << hours << ":" << minutes << ":" << seconds << endl;
}

void Vehicle ::calc_speed(){
  if (damaged_wheels == 0){
speed= double(fabs(sqrt(engPow) * (70.0 / double(WheelCnt) - 2.5) * (cur_fuel / 100.0)));
 }
    else{
        speed = (fabs(sqrt(engPow) * (70.0 / double(WheelCnt) - 2.5) * (cur_fuel / 100.0))/(pow(2., double(damaged_wheels))));
    }
  }


void Vehicle ::number_of_damaged_wheels(){
  int count = 0;
  for (int i = 0; i < WheelCnt; i++) {
    if (ptr_wheel[i].get_status() == 1){
      count++;
    }
  }
  damaged_wheels = count;
}


int main(){
  clean();
  Vehicle *pVehicles = nullptr;
  double trackLength = 0;
  int flag = 1;
  int cur = 0;
  while (flag == 1){
    int choice = 10;
    choice = menu(cur);
    if ((choice > 5) || (choice < 0)){
      cout << "\nerror, try another number!\n";
    }
    switch (choice){
    case 0:{
      cout << "Are you sure you want to exit?\n1 - yes\n0 - no, go back\n";
      int exit = 2;
      exit = Check_input(exit);
      if (exit == 1){
        flag = 0;
        break;
      }
      else{
        clean();
      }
      break;}
      delete[] pVehicles;
      for (int i = 0; i < num; i++) {
          delete[] pVehicles[i].ptr_wheel;
      }
      break;
    case 1:{
      clean();
      string NameCar = "";
       cout << "\nName of the car: ";
      cin >> NameCar;
      int WheelCnt = 0;
      cout << "Number of wheels: ";
      WheelCnt = Check_input(WheelCnt);
      while ((WheelCnt< 2) || (WheelCnt == 5) || (WheelCnt == 7)){
        cout << "Uncorrect number of wheels! try again:" << endl;
        WheelCnt = Check_input(WheelCnt);
      }
      Vehicle cars(NameCar, WheelCnt);
      clean();
      newCar(pVehicles, num, cars);
      cur = 0;
      break;
    }
    case 2:{
      clean();
      for (int i = 0; i < num; i++) {
        cout << pVehicles[i].name << endl;
        pVehicles[i].output();
        cout<<"__OR__"<<endl;
        cout<<pVehicles[i];
      }
      break;
    }
    case 3:{
      clean();
      if(cur==0){
            cout<<"Firstly input vehicle!\n";
            break;
          }
      cout << "Enter the length of the track (km): ";
      trackLength = Check_input(trackLength);
      cur = 0;
      break;
    }
    case 4:{
      clean();
      if (trackLength == 0) {
        cout << "You haven't entered the length of the track!\n";
        cur = 0;
        break;
      }
      else{
        for (int i = 0; i < num; i++){
          pVehicles[i].calc_Time(trackLength);
          pVehicles[i].set_mileage(trackLength);
          for (int j = 0; j < pVehicles[i].get_WheelCnt(); j++){
              pVehicles[i].ptr_wheel[j].def_wheel(trackLength, pVehicles[i].get_speed());
            }
          pVehicles[i].number_of_damaged_wheels();
          pVehicles[i].calc_refuel(trackLength);
          pVehicles[i].calc_cur_fuel(pVehicles[i].calc_Intake(), trackLength, pVehicles[i].get_Cnt_refueling());
          pVehicles[i].calc_speed();
        }
            cout << "the calculation has been made\n" << endl;
      }
      break;
    }
    case 5:{
      clean();
      outputResults(pVehicles, num);
      break;}
    default:
      clean();
      break;
    }
  }
  return 0;
}
