#include <iostream>
#include <cmath>
#include <limits>
#include <string>
using namespace std;

int num = 0; //изначальный размер массива
double Check_input(double var);
int Check_input(int var);

class Vehicle{
private:
    int WheelCnt;
    double Volume;//объём бака в л
    double Power;//мощность двигателя horsepower
    double speed;
    double fuelCons;//расход топлива литров/км
public:
  double mileage;
  double Cnt_refueling;//количество заправок
  string name;
  double Time;//время в пути
  Vehicle(string NameCar, double vol, double power, int wheels) {
    mileage = Time = Cnt_refueling = 0;
    cout << "\nName of the car: ";
    cin>>NameCar;
    set_name(NameCar);
    cout << "Count of wheels: ";
    wheels = Check_input(wheels);
    while ((wheels < 2) || (wheels == 5) || (wheels == 7)) {
      cout << "Uncorrect count of wheels, try again:" << endl;
      wheels = Check_input(wheels);
    }
    set_WheelCnt(wheels);
    cout << "Power of the engine (hp): ";
    power = Check_input(power);
    set_Power(power);
    cout << "Volume (l): ";
    vol = Check_input(vol);
    set_Volume(vol);
    speed = calc_speed();
    fuelCons = calc_fuelCons();
    cout << "\nCar is added!" << endl;
  }
  Vehicle(){
    name="Vehicle is added";
    mileage = Time= Cnt_refueling= 0;
  }
  ~Vehicle(){
    cout << "Deletion of " << name << endl;
  }

  inline double calc_speed(){
    return fabs(sqrt(Power)*((70/double(WheelCnt)) - 2.5));
  }
  inline double calc_fuelCons(){
    return fabs(pow(Power, 1/3) + sqrt(Power) - 6.25);
  }
  double calc_Refuel(double routeLength){
    double Cnt_refueling=(routeLength * (fuelCons / 100)) / Volume;
    if(Cnt_refueling > 1)
      return ceil(Cnt_refueling);
    else
     return floor(Cnt_refueling);
  };
  inline double calculateRaceTime(double routeLength) {
    return (routeLength / speed);
  };

  void set_name(string NameCar){name = NameCar;}
  void set_WheelCnt(int wheels){WheelCnt = wheels;}
  void set_Volume(double vol){Volume = vol;}
  void set_Power(double power){Power = power;}
  void output(){
    cout << "Count of wheels: " << WheelCnt << ";\n";
    cout << "power of engine: " << Power << " HP;\n";
    cout << "speed: " << speed << " km/h;\n";
    cout << "Fuel consumption: " << fuelCons << " l/100km;\n";
    cout << "mileage: " << mileage << " km;" << endl;
  }

  void time_show(){
    double t = this->Time;
    int hours = static_cast<int>(t);
    double cur_time = (t - hours)*60;
    int minutes = static_cast<int>((cur_time));
    int seconds = static_cast<int>((cur_time - minutes)*60);
    cout << "Time: " << hours << ":" << minutes << ":" << seconds << endl;
  }
};

//int menu(int &flag);
//void clean(int var = 1);
//void newCar(Vehicle *&pVehicles, int &num, Vehicle cars);
//Vehicle *Results(Vehicle *&pVehicles, int num);
//void outputResults(Vehicle *&pVehicles, int num);

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

void newCar(Vehicle *&pVehicles, int &num, Vehicle cars) {
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
      if ((results[i].Time - results[j].Time < 0)&&(results[i].Cnt_refueling - results[i].Cnt_refueling <= 0)) {
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
    cout << "Refuel times: " << int(ceil(results[i].Cnt_refueling)) << endl;
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
      break;
    case 1:{
      clean();
      string NameCar = "";
      double vol = 0;
      double power = 0;
      int WheelCnt = 0;
      Vehicle cars(NameCar, vol, power, WheelCnt);
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
      }
      break;
    }
    case 3:{
      clean();
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
          pVehicles[i].Time = pVehicles[i].calculateRaceTime(trackLength);
          pVehicles[i].mileage = trackLength;
          pVehicles[i].Cnt_refueling = pVehicles[i].calc_Refuel(trackLength);
        }
            cout << "the calculation has beem made" << endl;
      }
      break;
    }
    case 5:{
      clean();
      outputResults(*&pVehicles, num);
      break;}
    default:
      clean();
      break;
    }
  }
  return 0;
}
