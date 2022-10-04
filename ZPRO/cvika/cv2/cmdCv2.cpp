#include <iostream>
#include <cmath>
using namespace std;
#define PI 3.14159
#define max 10
#define precision 0.0001

float power(float a, int b);
int maxf(int a, int b);

int main()
{

	cout << power(5,1) << endl;
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

float power(float a, int b)
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

int maxf(int a, int b)
{
	return (a > b? a : b);
}





