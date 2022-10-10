#include <iostream>


using namespace std;

int main()
{
	/*
	for (int i {0}; i < 3; i++){
		cout << "Hello world!" << endl;
	}
	
	
	double a {0};
	double b {0};
	cout << "Please enter 1st float number: ";
	cin >> a;
	cout << "Please enter 2nd float number: ";
	cin >> b;
	cout << "The result of addition between provided numbers is: " << a / b << endl;
	
	
	string name;
	string ans1 = " you have nice age!";
	cout << "Please enter your name: ";
	getline(cin, name);
	cout << "Please enter your age: ";
	int age;
	cin >> age;
	cout << "Hello I am " << name << " and I am " << age << " years old." << endl;
	cout << "Hello " << name << ". Welcome in our faculty!" << endl;
	cout << name << ans1 << endl;
	*/
	
	int sum = 1;
	for (int i = 2; i <= 10; i++){
		sum *= i;
	}
	cout << "10! = " << sum << endl;

	int j = 1;
	int ans = 1;
	while (j <= 10){
		ans *= j; // ans = ans * j
		cout << "Answer: " << ans << " aktualni j: " << j << endl;
		j++;
	}
	cout << "ans: " << ans << endl;
	

	return 0;
}
