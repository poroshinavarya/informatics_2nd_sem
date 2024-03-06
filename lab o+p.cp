#include <iostream>
#include <math.h>
#include <cstdlib>
//#include <limits>
using namespace std;
# define pi M_PI

//# define pi     3.141592653589

struct figure{
    int n;
    double lg;
    double S;
    int P;
    double x, y;
};
struct center{
    int x0;
    int y0;
};
double Square(figure *num, int i);
int Perimetr(figure *num, int i);
void coordinates(figure *num);
void input(figure *num, int i);
void newFigure(figure *number, int count);
void deleteStruct(figure **num, int &count);
void maxSquare(figure *num, int count);
void maxPerimetr(figure *num, int count);
void information(figure *num, int count);

void menu(figure *number, int count);


int main()
{
    int count;
    cout << "Enter count of figure: ";
    if(!(cin >> count)){
        cout << "error!" << endl;
        return 1;
    }
    figure *number;
    //cout << number;
    number = new figure[count];
    //cout << number << &number;
    for (int iStruct = 0; iStruct < count; ++iStruct){
        input(&number[iStruct], iStruct);

        number[iStruct].P = Perimetr(&number[iStruct], iStruct);
        number[iStruct].S = Square(&number[iStruct], iStruct);
        cout << "Perimetr " << iStruct+1 << " figure: " << number[iStruct].P << endl;
        cout << "Square " << iStruct+1 << " figure: " << number[iStruct].S << endl;
        coordinates(&number[iStruct]);
    }
    menu(number, count);
    delete[] number;
    return 0;
}


double Square(figure *num, int i){
    double result = 0.0; // Initialize result to avoid returning uninitialized data
    if (num[i].n == 3){
        result = ((double) pow((int) num[i].lg, 2) * sqrt(3) / 4);
    }
    else if (num[i].n == 4){
        result = ((double) pow((int) num[i].lg, 2));
    }
    else if (num[i].n > 4){
        result = (num[i].n * ((double) pow((int) num[i].lg, 2)) / 4 * tan(pi / num[i].n));
    }
    //return result; // Add return statement for all code paths
}


int Perimetr(figure *num, int i){
    //int P=lg*n;
    return (num[i].lg*num[i].n);
}


/*void coordinates(figure *num, int i){
    double R = num[i].lg/(2*sin(pi/num[i].n));
    //cout << "R = " << R << endl;
    double *X = new double[num[i].n];
    double *Y = new double[num[i].n];

    double pi2 = 2*pi;

    double angleIncrement = 360.0 / num[i].n; // ”гол между вершинами в градусах
    double X0 = num[i].x - (num[i].lg/2)*cos(angleIncrement);
    double Y0 = num[i].y - (num[i].lg/2)*sin(angleIncrement);

    for(int k=0; k<num[i].n-1; k++){

        X[k]= X0 + R*cos(pi2*k/num[i].n);
        Y[k]= Y0 + R*sin(pi2*k/num[i].n);
    }
    for(int k=0; k<num[i].n-1; k++){
        //cout << "k = " << k << endl;
        // cout << "n = " << num[i].n << endl;
        cout << "Point " << k+2 << ": \"" << X[k] << "\", \"" << Y[k] << "\"" << endl;
    }
    delete[] X;
    delete[] Y;
    cout << "coordinates done" << endl;
}*/
void coordinates(figure *num)
{
    center Point = {0, 0};
    float AO = sqrt(pow((Point.x0 - num->x), 2) + pow((Point.y0 - num->y), 2));
    cout << "AO = " << AO << endl;

    float R = num->lg/(2*sin(pi/num->n));
    cout << "R = " << R << endl;
    if(AO > R){
  float a=0;//angle
  float a_temp=0;
  a=((num->n-2)*M_PI)/num->n;
  cout << "count " << num->n << endl;
  //cout<<"\n"<<a<<"\n";
  //num->x=num->x-(num->lg);
  //num[i].y=num[i].y;
  //cout<<"\n"<<num[i].x<<"\t"<<num[i].y;
    //double *X = new double[num.n];
    //double *Y = new double[num.n];
   if(num[0].x > 0){
  num[1].x=num[0].x-(num->lg);
  num[1].y=num[0].y;
  for(int j=2; j<num->n; j++)
    {
      num[j].x = num[j-1].x-cos(M_PI-a+a_temp);
      num[j].y = num[j-1].y-(pow(-1,j))*(num->lg)*sin(M_PI-a+a_temp);
      a_temp=(M_PI-a)+a_temp;
      //cout<<"\n"<<num[j].x<<"\t"<<num[j].y;
    }
  }
    else{
    num[1].x = num[0].x+(num->lg);
    num[1].y = num[0].y;
    cout<<"\n"<<num[1].x<<"\t"<<num[1].y;
  for(int j=2; j<num->n; j=j+1)
    {
      num[j].x=num[j-1].x+cos(M_PI-a+a_temp);
      num[j].y=num[j-1].y-(pow(-1,j))*(num->lg)*sin(M_PI-a+a_temp);
      a_temp=(M_PI-a)+a_temp;
  }
  }
    for (int j=0; j<num->n; j++)
    {
      cout<< "point "<< j << ": " << num[j].x<<" "<<num[j].y<<"\n";
    }
    //delete[] X;
    //delete[] Y;
    }while(AO > R);
    cout << "AO < R error!!!!" << endl;
    cout << "coordinates done" << endl;
}


void input(figure *num, int i){
    cout << "enter count of points ";
    if(!(cin >> num[i].n)){
        cout << "error!" << endl;
        exit (2);
    }
    cout << "enter length ";
    if(!(cin >> num[i].lg)){
        cout << "error!" << endl;
        exit (4);
    }
    cout << "enter coordinates ";
    if(!(cin >> num[i].x) || !(cin >> num[i].y)){
        cout << "error!" << endl;
        exit (3);
    }
}


/*void newFigure(figure *number, int count){
    number = new figure[count+1];
    input(&number[count+1], count+1);
    for (int iStruct = 0; iStruct < count+1; ++iStruct){

        if(iStruct == count){
            number[iStruct].P = Perimetr(&number[iStruct], iStruct);
            number[iStruct].S = Square(&number[iStruct], iStruct);
            cout << "Perimetr " << iStruct+1 << " figure: " << number[iStruct].P << endl;
            cout << "Square " << iStruct+1 << " figure: " << number[iStruct].S << endl;
        }

        //coordinates(&number[iStruct], iStruct);

    }
    delete[] number;
}*/
void newFigure(figure *number, int count) {
    figure *temp = new figure[count+1];

    for (int iStruct = 0; iStruct < count; ++iStruct) {
        temp[iStruct] = number[iStruct];
        cout << temp[iStruct].lg << endl;
        cout << "iStruct: " << iStruct << endl;
    }
    cout << "count: " << count << endl;

    input(&temp[count], count+1);
    cout << "done 2" << endl;
    for (int iStruct = 0; iStruct < count+1; ++iStruct) {
        if (iStruct == count) {
            temp[iStruct].P = Perimetr(&temp[iStruct], iStruct);
            temp[iStruct].S = Square(&temp[iStruct], iStruct);
            cout << "Perimetr " << iStruct+1 << " figure: " << temp[iStruct].P << endl;
            cout << "Square " << iStruct+1 << " figure: " << temp[iStruct].S << endl;
            coordinates(&temp[iStruct]);
        }
    }
    delete[] number;
    number = temp;
    cout << "done3 " << endl;
}


void deleteStruct(figure *num, int &count){ ///не работает
    int key;
    cout << "enter number of figure to delete: ";
    cin >> key;
    int newCount = 0;
    figure *Newnum = new figure[count-1];
    for(int iStruct = 0; iStruct < count; iStruct++){
        if (iStruct != key){
           Newnum[newCount] = num[iStruct];
           newCount++;
        }
    }
    delete[] num;
    num = Newnum;
    count = newCount;
    information(num, count);
}


void maxSquare(figure *num, int count){
    double maxVal = 0;
    for(int h = 0; h < count; h++){
        if(num[h].S > maxVal){
            maxVal = num[h].S;
        }
    }
    for(int h = 0; h < count; h++){
        if(num[h].S==maxVal){
             cout << "max Square " << h+1 << " is " << num[h].S << endl;
        }
    }
}


void maxPerimetr(figure *num, int count){
    double maxVal = 0;
    for(int h = 0; h < count; h++){
        if(num[h].P > maxVal){
            maxVal = num[h].P;
        }
    }
    for(int h = 0; h < count; h++){
        if(num[h].P == maxVal){
             cout << "max Perimetr " << h+1 << " is " << num[h].P << endl;
        }
    }
}


void information(figure *num, int count){
    for(int i = 0; i < count; i++){
    cout << "figure: " << i << " count of points: " << num[i].n << endl;
    cout << " coordinates of points: " << endl;
    coordinates(&num[i]);
    cout << endl << "Square " << Square(num, i) << " Perimetr " << Perimetr(num, i) << endl;
    cout << "DONE" << endl;
    }
}


void menu(figure *number, int count){
    char next;
    do{
    int choice;
    cout << "choice action: " << endl;
    cout << "1 - new figure" << endl;
    cout << "2 - information of the figure" << endl;
    cout << "3 - delete the figure" << endl;
    cout << "4 - max Square and Perimetr" << endl;
    cout << "5 - exit from programm" << endl;
    if(!(cin >> choice)){
        cout << "error!" << endl;
        exit (5);
    }
    switch(choice){
    case 1:
        newFigure(number, count);
        break;
    case 2:
        information(number, count);
        break;
    case 3:
        deleteStruct(number, count);
        break;
    case 4:
        int choice2;
        cout << "choice action: " << endl;
        cout << "1 - max Square" << endl;
        cout << "2 - max Perimetr" << endl;
        cout << " - exit from submenu" << endl;
        if(!(cin >> choice2)){
            cout << "error!" << endl;
            exit (1);
        }
        switch(choice2){
        case 1:
            maxSquare(number, count);
            break;
        case 2:
            maxPerimetr(number, count);
            break;
        default:
            cout << "Main menu:" << endl;
            break;
        }
        break;
    default:
        cout << "exit from programm" << endl;
        break;
    }
    cout << "do you want to continue?(y/n)" << endl;
    if(!(cin >> next)){
        cout << "error!" << endl;
        exit (6);
    }
    }while(next=='y');
        cout << "bye bye" << endl;
}

