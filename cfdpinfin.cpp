#include<iostream>
#include<conio.h>
#include<math.h>
#include<iomanip>
#include<windows.h>
using namespace std;
int colorfunction(int a,int max);
void gotoxy (int x, int y) //Setting up graphical functions
    {
         COORD coordinates;     // coordinates is declared as COORD
         coordinates.X = x;     // defining x-axis
         coordinates.Y = y;     //defining  y-axis
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coordinates);       
    }
int main()
{
	HANDLE color=GetStdHandle(STD_OUTPUT_HANDLE);
    int a;
    int b; 
    int i,j;
    gotoxy(0,0);
	for(i=0;i<10;i++)
	{
		SetConsoleTextAttribute(color, 12);
			cout<<"** \n";
	}
	gotoxy(2,5);
	for(i=0;i<12;i++)
	{
		SetConsoleTextAttribute(color, 14);
			cout<<"**";
	}
	gotoxy(2,4);
	for(i=0;i<12;i++)
	{
		SetConsoleTextAttribute(color, 14);
			cout<<"**";
	}
	SetConsoleTextAttribute(color, 7);
	gotoxy(2,6);cout<<"<---------------->";
	gotoxy(27,4);cout<<"diameter";
	gotoxy(0,10);cout<<"T0";
	gotoxy(27,8);cout<<"T Ambient";
	gotoxy(5,0);cout<<"	Steady State Conduction in pinfin";
	gotoxy(0,13);
int n;// Number of nodes
float To;// Ambient temperature
float Tb;// Base temperature
float l;//pin length
float h;//heat transfer coefficient
float m;
float A;//area
float P;//perimeter
float k;//conductivity
float he;//edge length
float D;//diameter of pin
gotoxy(10,6);                           //Getting the inputs
cin>>l;
gotoxy(10,3);cout<<"No Of nodes";
cin>>n;
gotoxy(3,10);
cin>>Tb;
gotoxy(27,9);
cin>>To;
he=l/n;gotoxy(27,5);
cin>>D;
gotoxy(0,15);
A=3.142*D*D/4;
P=3.142*D;
h=250;
k=20;
m=sqrt((h*P)/(k*A));
double pin[n][n+1];
float ans[n];
float cellbiot = (m*m)*he*he;
float arrsim = 2+cellbiot;
for(int i=0;i<n;i++)
{
    for(int j=0;j<n+1;j++)
    {
        pin[i][j]=0;
    }
}
pin[0][n]=-100;
for(int i=0;i<n;i++)
{
    for(int j=0;j<n;j++)

    {
        if((i==0)&&(j<2))
        {
            pin[0][0]=-arrsim;
            pin[0][1]=1;
        }
        if(i==(n-1)&&j>=(n-2))
        {
            pin[n-1][n-1]=-arrsim/2;
            pin[n-1][n-2]=1;
        }
        if((i==j)&&(i!=0)&&(i!=n-1))
        {
            pin[i][j]=-arrsim;
            pin[i][j-1]=1;
            pin[i][j+1]=1;
        }
    }
}
    int ki;
    cout.precision(4);        //set precision
    cout.setf(ios::fixed);
                  //input the no. of equations
    float x[n];        //declare an array to store the elements of augmented-matrix    
       //input the elements of array
    for (i=0;i<n;i++)                    //Pivotisation
        for (ki=i+1;ki<n;ki++)
            if (abs(pin[i][i])<abs(pin[ki][i]))
                for (j=0;j<=n;j++)
                {
                    double temp=pin[i][j];
                    pin[i][j]=pin[ki][j];
                    pin[ki][j]=temp;
                }
        
    for (i=0;i<n-1;i++)            //loop to perform the gauss elimination
        for (ki=i+1;ki<n;ki++)
            {
                double t=pin[ki][i]/pin[i][i];
                for (j=0;j<=n;j++)
                    pin[ki][j]=pin[ki][j]-t*pin[i][j];    //make the elements below the pivot elements equal to zero or elimnate the variables
            }
    for (i=n-1;i>=0;i--)                //back-substitution
    {                        //x is an array whose values correspond to the values of x,y,z..
        x[i]=pin[i][n];                //make the variable to be calculated equal to the rhs of the last equation
        for (j=i+1;j<n;j++)
            if (j!=i)            //then subtract all the lhs values except the coefficient of the variable whose value                                   is being calculated
                x[i]=x[i]-pin[i][j]*x[j];
        x[i]=x[i]/pin[i][i];            //now finally divide the rhs by the coefficient of the variable to be calculated
    }
    gotoxy(2,15);
    for (i=0;i<n;i++)
    {
    	SetConsoleTextAttribute(color, 15);
        cout<<x[i]+20;cout<<">|"; //           // Print the values of x, y,z,.... 
	}
	cout<<"          Temperature";	 
	cout<<"\n";
	gotoxy(2,16);
	for (i=0;i<n;i++)
	{
		colorfunction(x[i]+20,Tb);
		cout<<"*********";
	}
	gotoxy(2,17);
	for (i=0;i<n;i++)
	{
		colorfunction(x[i]+20,Tb);
		cout<<"*********";
	}
	gotoxy(2,18);
	for (i=0;i<=n;i++)
	{
		SetConsoleTextAttribute(color, 15);
		cout<<"|<-"<<l-(i*((l)/n));
	}
	cout<<" Position";
	gotoxy(0,12);
	for (i=0;i<2*n;i++)
    {
    	SetConsoleTextAttribute(color, 12);
        cout<<"**\n"; //           // Print the values of x, y,z,.... 
	}
	gotoxy(0,22);
	for (i=0;i<n;i++)
    {
    	colorfunction(((Tb/10)*i)-(Tb/10),Tb);
    	cout<<((Tb/10)*i)<<" to "<<((Tb/10)*(i+1))<<endl;
	}	
    return 0;
    
}
int colorfunction(int a,int max)//determines the color output a is temperature and max is surface temp
{
	HANDLE color=GetStdHandle(STD_OUTPUT_HANDLE);
	int j = max/10;
	int i;
	int T = a;
	if(T >= 0)
	{
		SetConsoleTextAttribute(color, 1);
	}
	if(T > j)
	{
		SetConsoleTextAttribute(color, 11);
	}	
	if(T > 2*j)
	{
		SetConsoleTextAttribute(color, 2);
	}
	if(T > 3*j)
	{
		SetConsoleTextAttribute(color, 10);
	}
	if(T > 4*j)
	{
		SetConsoleTextAttribute(color, 14);
	}
	if(T > 5*j)
	{
		SetConsoleTextAttribute(color, 6);
	}
	if(T > 6*j)
	{
		SetConsoleTextAttribute(color, 13);
	}	
	if(T > 7*j)
	{
		SetConsoleTextAttribute(color, 5);
	}	
	if(T > 8*j)
	{
		SetConsoleTextAttribute(color, 12);
	}	
	if(T > 9*j)
	{
		SetConsoleTextAttribute(color, 4);
	}	
}
    
    
 //Gauss Elimination

