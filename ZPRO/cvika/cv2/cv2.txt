#include <iostream>
#include <cmath>
using namespace std;
#define PI 3.14159
#define max 10
#define precision 0.0001

float power(float a, int b); // tohle je deklarace funkci jakoze jenom jejich hlavicka, aby se pak mohli pouzivat v mainu;
int maxf(int a, int b);// pak jsou deklarovany dole, presnej zapis
float powerWhile(float, int); // taky jeden z moznych zapisu, nemusis tam psat nazvy promennych, jen typ

float mocnina(float a, int b)
{
    float c = 1;
    if (b >= 0){
        while (b--){ // odcita to po kazdym pruchodu od b - 1
            c *= a;
        }
        return c;
    }else{
        while (b++){ // pricita to k b, + 1
            c /= a;
        }
        return c;
    }
}

int main()
{

    float a {0};
    int b {0};
    cout << "Please enter first the number next the power: ";
    cin >> a >> b;
	cout << "Power for result: " << power(a,b) << endl;
    cout << "Power while result: " << powerWhile(a,b) << endl;
    cout << "Mocnina result: " << mocnina(a, b) << endl;
	cout << maxf(-40,-30) << endl;
	/*
	float x {0};
	while (abs(x-1.0) > precision){
		cout << x << endl;
		x += 0.1;
	}
	
	int i = 0;
	while (i++ < max){
		cout << i << endl;;
	}
	
	float r;
	float s, v;
	cout << "Program pro vypocet objemu a povrchu koule" << endl;
	cout << "Zadejte prosim polomer koule [m]: ";
	cin >> r;
	if (r >= 0){
		s = 4*PI*pow(r,2);
		v = 4./3*PI*pow(r,3);
		cout << "Povrch koule je " << s << " m2\n";
		cout << "Objem koule je " << v << " m3\n";
	}else{
		cout << "Polomer musi byt kladny\n";
		return 1;
	}
	*/
	return 0;
} 

float power(float a, int b) // mocnina pomoci for cyklu
{	
	if (b == 0){
		return 1;
	}else if (b >= 1){
		float x = 1;
		for (int i {0}; i < b; i++){
			x *= a;
		}
		return x;
	}else{
		float c = 1;
		for (int i {0}; i < -b; i++){
			c /= a;
		}
		return c;
	}
}

int maxf(int a, int b) // max ze dvou cislo
{
	return (a > b? a : b); // ternary operator - funguje jako if (a > b){ return a; }else {return b;}
}

float powerWhile(float a, int b) //mocnina pomocny while cyklu trochu jinak
{
    float x = 1;
    if (b == 0){
        return x;
    }else if (b > 0){
        int i = 0;
        x = 1;
        while (i < b){
            x *= a;
            i++;
        }
        return x;
    }else{
        x = 1;
        int i = 0;
        while (i < -b){
            x /= a;
            i++;
        }
        return x;
    }
}


