#include <iostream>

using namespace std;

struct car
{
	string brand;
	int yearOfManufactutry = 0;
	string color = "red";
	public:
		void printInfo(){
			cout << brand << " " << yearOfManufactutry << " " << color << endl;
			color = "blue";
			brand = "toyota";
		}
		void changeBrand(){
			cout << "Zadej znacku auta: ";
			getline(cin, brand);
		}
		void changeYear(){
			if (yearOfManufactutry == 0){
				cout << "Enter the year: ";
				cin >> yearOfManufactutry;
			}else{
				cout << "yearOfManufactutry was set!" << endl;
			}
		}
}car1, car2;

int main()
{
	car honza;
	honza.printInfo();
	honza.changeYear();
	honza.printInfo();
	honza.changeYear();
	return 0;
}
