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
    double P;
    double x, y;
};
struct center{
    double x0;
    double y0;
};
void Square_Perimetr(figure *num, int count);
void coordinates(figure *num, int count);
void input(figure *num, int i);
void new_page();
void newFigure(figure *&num, int cur, int &count);
void deleteStruct(figure *&num, int &count);
void maxSquare(figure *num, int count);
void maxPerimetr(figure *num, int count);
void information(figure *num, int count);

void menu(figure *number, int count);


int main()
{
    int count=0;
    figure *number;
    //cout << number;
    number = NULL;
//    cout << "Enter count of figure: ";
//    if(!(cin >> count)){
//        cout << "error!" << endl;
//        return 1;
//    }
//
//    //cout << number << &number;
//    for (int iStruct = 0; iStruct < count; ++iStruct){
//        input(&number[iStruct], iStruct);
//        Square_Perimetr(&number[iStruct], iStruct);
//        cout << "Perimetr " << iStruct+1 << " figure: " << number[iStruct].P << endl;
//        cout << "Square " << iStruct+1 << " figure: " << number[iStruct].S << endl;
//        coordinates(&number[iStruct], count);
//    }
    menu(number, count);
    delete number;
    return 0;
}


void Square_Perimetr(figure *num, int count){
    double result = 0.0; // Initialize result to avoid returning uninitialized data
    for(int i=0; i<count; i++){
    if (num[i].n == 3){
        result = ((double) pow((int) num[i].lg, 2) * sqrt(3) / 4);
    }
    else if (num[i].n == 4){
        result = ((double) pow((int) num[i].lg, 2));
    }
    else if (num[i].n > 4){
        result = (num[i].n * ((double) pow((int) num[i].lg, 2)) / 4 * tan(pi / num[i].n));
    }
    num[i].S= result;
    //return result; // Add return statement for all code paths
    //int Perimetr(figure *num, int i){
    //int P=lg*n;
    num[i].P = num[i].lg*num[i].n;
    //return (num[i].lg*num[i].n);
    }
}


void coordinates(figure *num, int count)
{
    center Point = {0, 0};
    for(int i=0; i<count; i++){
//    cout << "x = " << num->x << endl;
//    cout << "y = " << num->y << endl;

    double AO = sqrt(pow((Point.x0 - num[i].x), 2) + pow((Point.y0 - num[i].y), 2));
    cout << "AO = " << AO << endl;

    double R = num[i].lg/(2*sin(pi/num[i].n));
    cout << "R = " << R << endl;

    if(AO > R){
        double x_centre;
        double y_centre;
        double alpha, beta;
        alpha = atan2(num[i].x, num[i].y);
        x_centre = num[i].x - R*cos(alpha);
        y_centre = num[i].y - R*sin(alpha);

        beta = (2*pi)/num[i].n;
        double *X = new double[num[i].n];
        double *Y = new double[num[i].n];
        X[0]=num[i].x;
        Y[0]=num[i].y;
        for(int j = 1; j < num[i].n; j++)
        {
            X[j] = x_centre + R*cos(alpha+beta*j);
            Y[j] = y_centre + R*sin(alpha+beta*j);
        }
        //cout << num[i].n << endl;
        for (int j=0; j<num[i].n; j++){
            cout<< "point "<< j << ": " << X[j] <<" "<< Y[j] <<endl;
        }
        delete X;
        delete Y;
    }
        else{
            cout << "AO < R error!" << endl;
        }
    }

    cout << "coordinates done" << endl;
}


void input(figure *num, int cur, int count){
    for(int i=0; i<count; i++){
        cout<<"Polygon  "<<i+1<<endl;
        cout << "enter count of points ";
        if(!(cin >> num[i].n)){
            cout << "error!" << endl;
            return;
        }
        cout << "enter length ";
        if(!(cin >> num[i].lg)){
            cout << "error!" << endl;
            return;
        }
        cout << "enter poligon's " << cur << " coordinates: ";
        if(!(cin >> num[cur-1].x) || !(cin >> num[cur-1].y)){
            cout << "error!" << endl;
            return;
        }
    }
}


void new_page(){
  for(int i=0;i<30;++i){
      cout<<"\n";
    }
}


void newFigure(figure *&num, int cur, int &count){
    count++;
    figure *temp = new figure[count];
    for(int i=0;i < count-1;++i){
      temp[i]=num[i];
    }
  delete num;
  num=temp;
  for(int i=cur-1;i<cur;i++){
        input(num, cur, count);
//      cout<<"Polygon:  "<<i+1<<endl;
//      cout<<"Enter lenght of side:";
//      cin>>num[i].lg;
//      cout<<"Count of angles:"<<endl;
      do{
        //cin>>num[i].n;
        if(num[i].n<3){
            cout<<"Amount of angles must be more than 2, Try again";
            if(!(cin >> num[i].n)){
                cout << "error!" << endl;
                return;
            }
        }
      }while(num[i].n<3);
      //input_coordinates(current,amount_polygons,p_polygon);
   }
//    figure *temp = new figure[count+1];
//
//    for (int iStruct = 0; iStruct < count; ++iStruct) {
//        temp[iStruct] = number[iStruct];
//        cout << temp[iStruct].lg << endl;
//        cout << "iStruct: " << iStruct << endl;
//    }
//    cout << "count: " << count << endl;
//
//    input(&temp[count], count+1);
//    cout << "done 2" << endl;
//
//    delete[] number;
//    number = temp;
//    for (int iStruct = 0; iStruct < count+1; ++iStruct) {
//        if (iStruct == count) {
//            Square_Perimetr(&number[iStruct], iStruct);
//            //temp[iStruct].P = Perimetr(&temp[iStruct], iStruct);
//            //temp[iStruct].S = Square(&temp[iStruct], iStruct);
//            cout << "Perimetr " << iStruct+1 << " figure: " << temp[iStruct].P << endl;
//            cout << "Square " << iStruct+1 << " figure: " << temp[iStruct].S << endl;
//            coordinates(&temp[iStruct]);
//        }
//    }
    cout << "done new figure " << endl;

}


void deleteStruct(figure *&num, int &count){
    int key;
    cout << "enter number of figure to delete: ";
    cin >> key;
    if (key < 1 || key > count)
    {
        cout << "No polygon with this number";
        return;
    }
//    int newCount = 0;
//    figure *Newnum = new figure[count-1];
//    for(int iStruct = 0; iStruct < count; iStruct++){
//        if (iStruct != key){
//           Newnum[newCount] = num[iStruct];
//           newCount++;
//        }
//    }
//    delete[] num;
//    num = Newnum;
//    count = newCount;
//    information(num, count);
  figure *Newnum = new figure[count-1];

  for (int i = 0; i < key-1; ++i){
    Newnum[i] = num[i];
  }

  for (int i = key; i < count; ++i){
    Newnum[i-1] = num[i];
  }

  delete num;
  num = Newnum;
  count--;
}


void maxSquare(figure *num, int count){
    int maxNum = 0;
    double maxSquare = num[0].S;
    int maxNumCount = 0;
    int arrMaxNumCount[count];
    for(int h = 1; h < count; h++){
        if((num[h].S - num[maxNum].S) >= 0){
            maxNum = h;
            maxSquare = num[h].S;
        }
    }
    for(int h = 0; h < count; h++){
        if((count !=0) && (num[h].S==maxSquare)){
            maxNumCount++;
            arrMaxNumCount[h]=h+1;
        }
    }
    if(maxNumCount==1){
        cout<<"Figure's number with max Square: " << maxNum+1 <<endl;
    }
    if(maxNumCount>1){
        for(int h = 0; h < maxNumCount; h++){
            cout << "number of the figure with max Square is  " << arrMaxNumCount[h] << endl;
        }
    }
}


void maxPerimetr(figure *num, int count){
    int maxNum = 0;
    double maxPerimetr = num[0].P;
    int maxNumCount = 0;
    int arrMaxNumCount[count];
    for(int h = 1; h < count; h++){
        if((num[h].P - num[maxNum].P) >= 0){
            maxNum = h;
            maxPerimetr = num[h].P;
        }
    }
    for(int h = 0; h < count; h++){
        if((count !=0) && (num[h].P==maxPerimetr)){
            maxNumCount++;
            arrMaxNumCount[h]=h+1;
        }
    }
    if(maxNumCount==1){
        cout<<"Figure's number with max Perimetr: " << maxNum+1 <<endl;
    }
    if(maxNumCount>1){
        for(int h = 0; h < maxNumCount; h++){
            cout << "number of the figure with max Perimetr is  "<< arrMaxNumCount[h] << endl;
        }
    }
}


void information(figure *num, int count){
    for(int i = 0; i < count; i++){
    cout << "figure: " << i <<endl;
    cout << " count of points: " << num[i].n << endl;
    Square_Perimetr(num, count);
    cout << endl << "Square " << num[i].S << " Perimetr " << num[i].P << endl;
    }
    cout << " coordinates of points: " << endl;
    coordinates(num, count);
    cout << "DONE" << endl;
}


void menu(figure *number, int count){
    char next;
    int cur=0;
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
        break;
    }
    switch(choice){
    case 1:
        new_page();
        cur++;
        newFigure(number, cur, count);
        break;
    case 2:
        new_page();
        Square_Perimetr(number, count);
        information(number, count);
        break;
    case 3:
        new_page();
        deleteStruct(number, count);
        break;
    case 4:
        new_page();
        int choice2;
        cout << "choice action: " << endl;
        cout << "1 - max Square" << endl;
        cout << "2 - max Perimetr" << endl;
        cout << " - exit from submenu" << endl;
        if(!(cin >> choice2)){
            cout << "error!" << endl;
            break;
        }
        switch(choice2){
        case 1:
            new_page();
            Square_Perimetr(number, count);
            maxSquare(number, count);
            break;
        case 2:
            new_page();
            Square_Perimetr(number, count);
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
