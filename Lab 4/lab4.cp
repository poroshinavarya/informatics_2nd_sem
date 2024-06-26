#include <iostream>
#include <cmath>
#include <limits>
#include <string>
#include <ctime>
#include <vector>
#include <iterator>
#include <algorithm>
#include <iomanip>
using namespace std;

int num = 0;
double RefuelTime=0.0003;// 1 секунда
double ChangeTime=0.008;// 30 секунд
double dt =0.0003;
double Check_input(double var);
int Check_input(int var);

class Wheel{
    double cur_mileage;
    int status;
public:
    int check_status(double mileage, double speed);
    Wheel(){status=0;cur_mileage=0;};
    virtual ~Wheel(){};
    void def_wheel(double mileage, double speed){
        if(mileage=0.){
            cur_mileage=0;
            status=0;}
        else{
            cur_mileage=mileage;
            status=check_status(mileage, speed);
        }
    }
    void output();
    int get_status(){return status;}
    void set_status(int status){this->status = status;}
};

class Engine{
protected:
    double engIntake; //потребление двигателя l/km
    double engPow; //мощность двигателя HP
public:
    double calc_Intake(){return fabs(pow(engPow, 1 / 3) + sqrt(engPow) - 6.25);}
    Engine(){engIntake=0;engPow=0;};
    void def_engine(double power);
    //virtual void output();
};

class Fuel_system{
protected:
    double cur_fuel;
public:
    double TankVolume;
    void calc_cur_fuel(double engIntake,double mileage);//расчёт текущего обЪёма топлива
    Fuel_system(){TankVolume=0;cur_fuel=0;};
    void def_fuel_system();
    //virtual void output();
};

class Vehicle: public Engine, public Fuel_system{
private:
    string name;
    int WheelCnt;
    double speed;
    int damaged_wheels;
    double mileage;
    double Cnt_refueling;//количество заправок
    double Time;//время в пути
    double cur_mileage;
    int cur_circle;
public:
    vector<Wheel> vecWheels;
    double pitStopTime=0;
    int stat_of_car;

    Vehicle(string NameCar, int wheels){
        cur_mileage = mileage = pitStopTime = damaged_wheels = cur_circle=0;
        name=NameCar;
        WheelCnt=wheels;
        for (int i = 0; i < wheels; i++) {
            Wheel newWheel;
            vecWheels.push_back(newWheel);
        }
        def_fuel_system();
        def_engine(0);
        calc_speed();
    }
    Vehicle(){
        name="Vehicle is added";
        Time=mileage=Cnt_refueling=damaged_wheels=0;
        cur_circle=cur_mileage=pitStopTime=0;
    }
    ~Vehicle(){cout << "Deletion of " << name << endl;}
    void reset();
    void calc_speed();
    double calc_Time(double routelength){
        return (routelength / speed);
    };

    void totalTime(){
        Time=Time+pitStopTime;
    }

    int calc_circle(double trackLength){
        if(cur_mileage-trackLength>=0){
            cur_circle=int(mileage/trackLength);
            cur_mileage=0;
            cout<<"\npit\n";
            return 1;
        }
        else {return 0;}
    }

    double change_wheels(){
        double t=damaged_wheels*ChangeTime;
        return t;
    }
    double refuel_time(){
        double t=((TankVolume-cur_fuel)*RefuelTime);
        return t;
    }


    string get_name(){return name;}
    void set_Time(double t){this->Time = t;}
    double get_Time(){return Time;}
    int get_WheelCnt(){return WheelCnt;}

    void setMileage(double tracklength){mileage=tracklength;}
    double get_Cnt_refueling(){return Cnt_refueling;}
    void Cnt_refueling_plus(){Cnt_refueling++;}
    double get_speed(){return speed;}
    int get_damaged_wheels(){return damaged_wheels;}
    double get_mileage(){return mileage;}
    void set_mileage(double tracklength){this->mileage=tracklength;}
    void mileage_plus(){this->mileage+=(speed*dt);}
    double get_cur_mileage(){return cur_mileage;}
    void set_cur_mileage(double length){this->cur_mileage=length;}
    void cur_mileage_plus(){this->cur_mileage+=(speed*dt);}
    int get_cur_circle(){return cur_circle;}
    void set_cur_circle(int circles){this->cur_circle=circles;}
    void cur_circle_plus(){this->cur_circle++;}
    double get_cur_fuel(){return cur_fuel;}

    void output();
    void need_refuel(double tracklength);
    void need_change();
    void time_show();
    double calc_refuel(double raceLength, int circles){
        double Refuel = (raceLength * (engIntake / 100)) / TankVolume;
        if (Refuel > 1)
            this->Cnt_refueling= ceil(Refuel);
        else
            this->Cnt_refueling= floor(Refuel);
    }
    void number_of_damaged_wheels();
    friend Vehicle *Results(int num);
    friend void outputResults(vector <Vehicle>);

    friend ostream &operator<<(ostream &stream, const Vehicle &obj){
        return stream <<"\nName: "<<obj.name<<"\n"
            << "Number of wheels: " << obj.WheelCnt << ";\n"
            << "Damaged wheels: " << obj.damaged_wheels << ";\n"
            << "Speed: " << obj.speed << " km/h;\n"
            << "Mileage: " << obj.mileage << " km;\n"
            << "fuel volume: "<<obj.TankVolume<<" l;\n"
            << "current fuel: "<<obj.cur_fuel<<" l;\n"
            << "engine power: "<<obj.engPow<<" HP;\n"
            << "engine intake: "<<obj.engIntake<<" l/100km;\n"<<endl;
    }
    friend istream &operator >> (istream &stream,Vehicle& obj){
        cout<<"Vehicle name: ";
        stream>>obj.name;
        try{
            cout<<"Number of wheels: ";
            stream>>obj.WheelCnt;
            if (obj.WheelCnt < 2){
                throw "Uncorrect number of wheels! try again";
            }
        }
        catch (const char* out){
            cerr << "Exception caught: " << out <<endl;
            obj.WheelCnt=Check_input(obj.WheelCnt);
        }
        for (int i = 0; i < obj.WheelCnt; i++){
            Wheel newWheel;
            obj.vecWheels.push_back(newWheel);
        }
        try{
            cout<<"Tank volume: ";
            stream>>obj.TankVolume;
            if (obj.TankVolume<=0){
                throw "Uncorrect tank capacity! try again";
            }
        }
        catch (const char* out){
            cerr << "Exception caught: " << out <<endl;
            obj.TankVolume=Check_input(obj.TankVolume);
        }
        try{
            cout<<"Engine power: ";
            stream>>obj.engPow;
            if (obj.engPow<=0){
                throw "Uncorrect power of engine! try again";
            }
        }
        catch (const char* out){
            cerr << "Exception caught: " << out <<endl;
            obj.engPow=Check_input(obj.engPow);
        }
            obj.stat_of_car=0;
            obj.cur_fuel=obj.TankVolume;
            obj.def_engine(obj.engPow);
            obj.calc_speed();
        return stream;
    }

    Vehicle& operator=(const Vehicle& u){
        name = u.name;
        WheelCnt = u.WheelCnt;
        speed = u.speed;
        mileage = u.mileage;
        cur_mileage=u.cur_mileage;
        cur_circle=u.cur_circle;
        Time=u.Time;
        return *this;
    }
};

int menu(int &cur){
    cout << "\nChoose action:\n";
    cout << "0 - exit\n";
    cout << "1 - to add new Vehicle\n";
    cout << "2 - output information about Vehicle\n";
    cout << "3 - to enter length of the track\n";
    cout << "4 - start the race\n";
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

vector<Vehicle> Results(vector<Vehicle> pVehicles){
    sort(pVehicles.begin(), pVehicles.end(), [](Vehicle& obj1,  Vehicle& obj2){
        if (obj1.get_Time() != obj2.get_Time()) {
            return obj1.get_Time() < obj2.get_Time();
        }
        else {
            return obj1.get_Cnt_refueling() < obj2.get_Cnt_refueling();
        }
    });
    return pVehicles;
}

void outputResults(vector<Vehicle> pVehicles) {
  vector<Vehicle> results = Results(pVehicles);
  for (int i = 0; i < results.size(); i++) {
    cout << results[i].get_name() << endl;
    results[i].time_show();
    cout<<"Circles "<<results[i].get_cur_circle()<<endl;
    cout << "Refuel times: " << int(results[i].get_Cnt_refueling()) << endl;
  }
}

double Check_input(double var){
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
    if (cin.fail() || var < 0){
        while (!(cin >> var) || var < 0){
            cout << "error, try again\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
    return var;
}

int Wheel :: check_status(double mileage, double speed){
    if (status == 0){
        int end = ceil(sqrt(mileage))+ceil(sqrt(speed));
        int start = -1000;
        int rat = ceil(((mileage)*(sqrt(speed)+1)));
        int damageProb = rand() % (end - (start)+rat)+start;
        if (damageProb - end>=0){
            return 1;
        }
        else{
            return 0;
        }
    }
    else
        return 1;
}

void Engine::def_engine(double power){
    engPow = power;
    engIntake = calc_Intake();
}

void Fuel_system ::def_fuel_system() {
    cout << "fuel volume: ";
    double volume = 0.;
    volume = Check_input(volume);
    TankVolume = volume;
    cur_fuel = volume;
}

void Wheel ::output(){
    if (status == 1) {
        cout << "damaged" << endl;
    } else {
        cout << "not damaged" << endl;
    }
}

void Vehicle ::time_show(){
    double t = this->Time;
    int hours = int(t);
    double cur_time = (t - hours) * 60;
    int minutes = int(cur_time);
    int seconds = int((cur_time - minutes) * 60);
    cout << "TIME: " << setw(4)<<setfill('0')<<hours << ":" << setw(2)<<setfill('0')<<minutes << ":" << setw(2)<<setfill('0')<<seconds << endl;
}

void Fuel_system ::calc_cur_fuel(double engIntake, double mileage){//расчёт текущего обЪёма топлива
    cur_fuel = double(TankVolume - ((engIntake / 100) * mileage));
}

void Vehicle ::calc_speed(){
    if (damaged_wheels == 0){
        speed= double(fabs(sqrt(engPow) * (70.0 / double(WheelCnt) - 2.5) /sqrt(cur_fuel)));
    }
    else{
        speed = (fabs(sqrt(engPow) * (70.0 / double(WheelCnt) - 2.5)  / sqrt(cur_fuel))*(pow(0.75, double(damaged_wheels))));
    }
}

void Vehicle :: number_of_damaged_wheels(){
    int count = 0;
    for (int i = 0; i < vecWheels.size(); i++) {
        if (vecWheels[i].get_status() == 1){
            count++;
        }
    }
    damaged_wheels = count;
}

void Vehicle :: need_refuel(double tracklength){
    if (cur_fuel < (engIntake*100) * tracklength){
        this->Cnt_refueling_plus();
        pitStopTime+=this->refuel_time();
        cur_fuel = TankVolume;
        cout << "Car " << get_name() << " pulls into a pit stop" << endl;
    }
}

void Vehicle :: need_change(){
    if (damaged_wheels!=0){
        pitStopTime+=this->change_wheels();
        for(int i=0;i<vecWheels.size();i++){
            if (vecWheels[i].get_status()==1){
                vecWheels[i].def_wheel(0.,0.);
                cout << "Car " << get_name() << " pulls into a pit stop" << endl;
            }
        }
    }
}

void Vehicle :: reset(){
    for(int i=0;i<vecWheels.size();i++){
        vecWheels[i].set_status(0);
    }
    damaged_wheels=0;
    cur_mileage=mileage=0;
    Cnt_refueling=cur_circle=0;
    Time=0;
    cur_fuel=TankVolume;
    calc_speed();
    for (int j = 0; j < vecWheels.size(); j++){
        vecWheels[j].def_wheel(mileage, get_speed());
    }
    cout<<"\n"<<name<<" reseted"<<endl;
 }

int allfinished(vector<Vehicle> &pVehicles,double trackLength,int circles){
    int count=0;
    for (int i=0;i<pVehicles.size();i++){
        if (pVehicles[i].get_cur_mileage()-trackLength*circles>=0){
            count++;
        }
    }
    if (count==pVehicles.size()){
        return 1;
    }
    else
        return 0;
}

int main(){
    clean();
    srand(time(NULL));
//    vector<Vehicle> race_rezult;
    vector<Vehicle> cars;
    int NumCircles;
    double trackLength = 0;
    int flag = 1;
    int cur = 0;
    int carcheck=0;
    while (flag == 1){
        int choice = 10;
        try{
            choice = menu(cur);
            if ((choice > 5) || (choice < 0)){
                throw "\nerror, try another number!\n";
            }
        }
        catch (const char* out){
            cerr << "Exception caught: " << out << endl;
            cout<<"try again ";
            choice = Check_input(choice);
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
            break;
        }
        break;
        case 1:{
            clean();
            Vehicle newCar;
            cin>>newCar;
            cars.push_back(newCar);
            clean();
            cout<<"Vehicle: "<<newCar.get_name()<<" was added"<<endl;
            cur = 0;
             carcheck++;
            break;
        }
        case 2:{
            clean();
            if(carcheck==0){
                cout<<"Firstly input vehicle!\n";
                break;
            }
            for (int i = 0; i < cars.size(); i++) {
                cout<<cars[i];
            }
            break;
        }
        case 3:{
            clean();
          if(carcheck==0){
                cout<<"Firstly input vehicle!\n";
                break;
              }
            try{
                cout<<"The number of circles: ";
                NumCircles=Check_input(NumCircles);
                if (NumCircles<=0){
                    throw "Uncorrect number of circles! try again";
                }
            }
            catch (const char* out){
                cerr << "Exception caught: " << out << endl;
                cout<<"try again ";
                NumCircles=Check_input(NumCircles);
            }
            cout << "Enter the length of the track (km): ";
            trackLength = Check_input(trackLength);
            cur = 0;
            break;
        }
        case 4:{
            clean();
            if(carcheck==0){
                cout<<"Firstly input vehicle!\n";
                break;
            }
            if (trackLength == 0 || NumCircles==0) {
                cout << "You haven't entered the length of the track!\n";
                cur = 0;
                break;
            }
            else{
                for(int i = 0; i < cars.size(); i++){
                    cars[i].reset();
                }
                double cur_time=0;
                vector<int> skip_id{-1};
                int racing_cars=cars.size();
                while(!allfinished(cars, trackLength, NumCircles)){
                    if(racing_cars<=0){
                        break;
                    }
                    for (int i = 0; i <cars.size(); i++){
                        int exit=0;
                        if (find(skip_id.begin(), skip_id.end(), i) == skip_id.end()){
//                        if (cars[i].stat_of_car==0){
                            cars[i].mileage_plus();
                            cars[i].cur_mileage_plus();
                            for (int j = 0; j < cars[i].vecWheels.size(); j++){
                                cars[i].vecWheels[j].def_wheel(cars[i].get_mileage(),cars[i].get_speed());
                            }
                            cars[i].number_of_damaged_wheels();
                            cars[i].calc_cur_fuel(cars[i].calc_Intake(),cars[i].get_cur_mileage());
                            cars[i].calc_speed();
                            cars[i].set_Time(cur_time);
                            cars[i].time_show();
                            cout<<"car: "<<cars[i].get_name()
                                <<" circle: "<<cars[i].get_cur_circle()+1
                                <<" speed: "<<cars[i].get_speed()<<"\n"
                                <<" Current fuel "<<cars[i].get_cur_fuel()
                                <<" Damaged wheels: "<<cars[i].get_damaged_wheels()<<"\n"
                                <<" Mileage: "<<cars[i].get_mileage()<<"\n";
                            if (cars[i].get_damaged_wheels()==cars[i].vecWheels.size() || (cars[i].get_cur_fuel()<=0)){
                                exit=1;
                                cars[i].set_Time(cur_time);
                                cars[i].cur_circle_plus();
                            }
                            if ((trackLength*NumCircles)-(cars[i].get_mileage())<=0){
                                exit=1;
                                cars[i].set_Time(cur_time);
                                cars[i].set_cur_circle(NumCircles);
                                cars[i].time_show();
                                cout<<""<<cars[i].get_name()<<" just finished"<<endl;
                            }
                            if (exit==1){
                                skip_id.push_back(i);
//                                cars[i].stat_of_car=1;
                                racing_cars=racing_cars-1;
                                break;
                            }
                            if (cars[i].calc_circle(trackLength)){
                                cars[i].need_refuel(trackLength);
                                cars[i].need_change();
                            }
                        }
                        else{
                            cout << "\ncar " << cars[i].get_name() << " in pit-stop" << endl;
                            continue;
                        }
                    }
                    cur_time+=dt;
                }
                for(int i=0;i<cars.size();i++){
                    cars[i].totalTime();
                }
            }
            break;
        }
        case 5:{
          clean();
          if (cur != 1) {
            cout << "Firstly route calculation!\n";
            cur = 0;
            break;
          }
          outputResults(cars);
          break;}
        default:
          clean();
          break;
        }
    }
    return 0;
}
