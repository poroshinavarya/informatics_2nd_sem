#include <iostream>
#include <math.h>

using namespace std;
#define pi M_PI

struct figure{
    int n;
    double lg;
    double S;
    double P;
    double x, y;
};

void ignoreLine(){
    cin.clear();
    cin.ignore();
}
void Square_Perimetr(figure *num, int count);
void coordinates(figure *num, int count);
void input(figure *num, int cur, int i);
void new_page();
void newFigure(figure *&num, int cur, int &count);
void deleteStruct(figure *&num, int &count);
void max_P_S(int count, figure *num, int p);
void information(figure *num, int count, int cur);

void menu(figure *number, int count);


int main()
{
    int count=0;
    figure *number;

    number = NULL;
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


void coordinates(figure *num, int count){
    for(int i=0; i<count; i++){
//        double AO = sqrt(pow(num[i].x, 2) + pow(num[i].y, 2));
      double R,dxR,dyR,xR,yR,k;
      double modx=fabs(num[i].x);
      double mody=fabs(num[i].y);
      int flagX=1;
      int flagY=1;
      if(num[i].x<0){flagX=-1;}
      if(num[i].y<0){flagY=-1;}
      R = num[i].lg/(2*sin(pi/num[i].n));
      k=atan((mody)/(modx));
      dxR=R*cos(k);
      dyR=R*sin(k);
      xR=modx-dxR;
      yR=mody-dyR;
      double angle=2*M_PI/num[i].n;
      cout<<"Coordinates of polygon: "<<i+1<<"\n";
      cout<<"point 1: "<<num[i].x<<"; "<<num[i].y<<"\n";
      for(int j=1; j<num[i].n; ++j)
      {
         if(flagX != flagY){
            double NewAngle=((atan(mody/modx))-(j)*angle);
            double Next_X=xR+R*cos(NewAngle);
            double Next_Y=yR+R*sin(NewAngle);
            cout<<"point"<<j+1<<": " <<Next_X*flagX<<"; "<<Next_Y*flagY<<"\n";
          }else{
            double NewAngle=atan(mody/modx)+(j)*angle;
            double Next_X=xR+R*cos(NewAngle);
            double Next_Y=yR+R*sin(NewAngle);
            cout<<"point"<<j+1<<": " <<Next_X*flagX<<"; "<<Next_Y*flagY<<"\n";
          }
        }
    }
    cout << "coordinates done" << endl;
}


void input(figure *num, int cur, int count){
    for(int i=cur-1; i<cur; i++){
        cout<<"Polygon  "<<i+1<<endl;
        cout << "enter count of points: ";
        cin >> num[i].n;
        while (cin.fail()){
            ignoreLine();
            cout << "You entered symbol, please enter a number" << endl;
            cin >> num[i].n;
        }
        do{
            //cin>>num[i].n;
            if(num[i].n<3){
                cout<<"Amount of angles must be more than 2, Try again: ";
                cin >> num[i].n;
                while (cin.fail()){
                    ignoreLine();
                    cout << "You entered symbol, please enter a number" << endl;
                    cin >> num[i].n;
                }
            }
        }while(num[i].n<3);
        cout << "enter length: ";
        cin >> num[i].lg;
                while (cin.fail()){
                    ignoreLine();
                    cout << "You entered symbol, please enter a number" << endl;
                    cin >> num[i].lg;
                }
        do{
            if(num[i].lg<=0){
                cout<<"Error. Length must be more 0. Try again: "<<endl;
                cin >> num[i].lg;
                while (cin.fail()){
                    ignoreLine();
                    cout << "You entered symbol, please enter a number" << endl;
                    cin >> num[i].lg;
                }
            }
        }while(num[i].lg<=0);

        int check=1;
        double correct_y = 0;
        double R = fabs(num[i].lg/(2*sin(pi/num[i].n)));
    do{
        cout << "\nPoligon's " << cur << " coordinates: ";
        cout << "\nenter x:\n";
        cin >> num[i].x;
        while (cin.fail()){
            ignoreLine();
            cout << "You entered symbol, please enter a number" << endl;
            cin >> num[i].x;
        }

         cout <<"\nenter y:\n";
        cin >> num[i].y;
        while (cin.fail()){
            ignoreLine();
            cout << "You entered symbol, please enter a number" << endl;
            cin >> num[i].y;
        }
    if((sqrt(pow(num[i].x,double(2))+pow(num[i].y,double(2)))-R)<0){
        cout<<"Error coordinate\n";
         correct_y = sqrt(pow(R,double(2))-pow(num[i].x,double(2)));
         cout<<"With this x, the y must modulo more than\n"<<correct_y<<"\n";
        }
        else{
            check=0;
        }
    }while(check!=0);
    }
}


void new_page(){
  for(int i=0;i<30;++i){
      cout<<endl;
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
   }
    cout << "done new figure " << endl;
}


void deleteStruct(figure *&num, int &count){
    if(count == 0){
        cout<<"No polygons\n";
        return;
    }
    int key;
    cout << "enter number of figure to delete: ";
    cin >> key;
    if (key < 1 || key > count){
        cout << "No polygon with this number";
        return;
    }
  figure *Newnum = new figure[count-1];

  for (int i = 0; i < key-1; ++i){
    Newnum[i] = num[i];
  }

  for (int i = key; i < count; ++i){
    Newnum[i-1] = num[i];
  }

  delete[] num;
  num = Newnum;
  count--;
  cout <<"figure " << key <<" deleted!\n";
}


void max_P_S(int count, figure *num, int p){
    if(count==0)
  {
    cout<<"No polygons\n";
    return;
  }
double max_value=0;
int amount_max=0;
int indexmax[count];
double values[count];
if(p==1){
    for(int i=0;i<count;++i){
        values[i]=num[i].P;
    }
}
if(p==0){
    for(int i=0;i<count;++i){
        values[i]=num[i].S;
    }
}
  for(int i=0;i<count;++i){
      if(values[i]>max_value){
        max_value=values[i];
      }
    }
  for(int i=0;i<count;++i){
      if(values[i]==max_value){
        indexmax[amount_max]=i;
        amount_max++;
      }
    }
  if((amount_max==1)&&(p==1)){
    cout<<"Max perimeter = "<<max_value<<" and it is polygon "<<indexmax[0]+1<<endl;
  }
  if((amount_max==1)&&(p==0)){
    cout<<"Max square = "<<max_value<<" and it is polygon "<<indexmax[0]+1<<endl;
  }
  if((amount_max>1)&&(p==1)){
    cout<<"Max perimeter= "<<max_value<<" and they are polygons: ";
    for(int i=0;i<amount_max;++i){
        cout<<indexmax[i]+1<<endl;
      }
  }
  if((amount_max>1)&&(p==0))
  {
    cout<<"Max area= "<<max_value<<" and they are polygons: ";
    for(int i=0;i<amount_max;++i)
      {
        cout<<indexmax[i]+1<<endl;
      }
  }
}


void information(figure *num, int count, int cur){
    if(count==0){
        cout<<"No polygons\n";
    }
    else{
        for(int i = 0; i < count; i++){
            cout << "Figure: " << i <<endl;
            cout << "Count of points: " << num[i].n << endl;
            Square_Perimetr(num, count);
            cout << endl << "Square: " << num[i].S << " Perimetr: " << num[i].P << endl;
        }
        cout << "Coordinates of points: " << endl;
        coordinates(num, count);
    }
    cout << "INFORMATION DONE\n";
}


void sub_menu(figure *number, int count){
        int return_sub=0;
    while(return_sub==0){
        int choice2;
        cout << "choice action: " << endl;
        cout << "1 - max Square" << endl;
        cout << "2 - max Perimetr" << endl;
        cout << "3 - return sub menu" << endl;
        //cout << " - exit from submenu" << endl;
        cin >> choice2;
        while (cin.fail()){
            ignoreLine();
            cout << "You entered symbol, please enter a number" << endl;
            cin >> choice2;
        }
        int p=-1;
        switch(choice2){
        case 1:
            new_page();
            Square_Perimetr(number, count);
            p=0;
            max_P_S(count, number, p);
            break;
        case 2:
            new_page();
            Square_Perimetr(number, count);
            p=1;
            max_P_S(count, number, p);
            break;
        case 3:
            new_page();
            return_sub++;
            break;
        default:
            cout << "Error" << endl;

        }
    }
}


void menu(figure *number, int count){
    int next=-1;
    int cur=0;
  do{
    int choice;
    cout << "\nchoice action: " << endl;
    cout << "1 - new figure" << endl;
    cout << "2 - information of the figure" << endl;
    cout << "3 - delete the figure" << endl;
    cout << "4 - max Square and Perimetr" << endl;
    cout << "5 - exit from programm" << endl;
    cin >> choice;
        while (cin.fail()){
            ignoreLine();
            cout << "You entered symbol, please enter a number" << endl;
            cin >> choice;
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
        information(number, count, cur);
        break;
    case 3:
        new_page();
        deleteStruct(number, count);
        cur--;
        break;
    case 4:
        new_page();
        sub_menu(number, count);
        break;
    case 5:
        new_page();
        cout << "do you want to exit from programm?(0 - no/1- yes)" << endl;
        cin >> next;
        while (cin.fail()){
            ignoreLine();
            cout << "You entered symbol, please enter a number" << endl;
            cin >> next;
        }
        if(next==1){
            next++;
            cout << "programm is completed" << endl;
        }
        if(next==0){
            new_page();
            menu(number, count);
        }
        break;
    default:
        cout << "error" << endl;

    }
  }while(next==-1);
}
