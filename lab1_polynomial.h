#include <vector>
#include <string>
#ifndef LAB1_POLYNOMIAL
#define LAB1_POLYNOMIAL

//Authors: Sarah Dykstra 20817609, Adam Courchesne 20824794, Lauren Knoff 20817903
using namespace std;

class Polynomial{
	vector<int> data;

	Polynomial(int A[], int size);
	Polynomial();
	Polynomial(string file_name);
	~Polynomial();	
	
	bool operator==(const Polynomial& target);
	void print();
	Polynomial trim();
	Polynomial operator+(const Polynomial& target);
	Polynomial operator-(const Polynomial& target);
	Polynomial operator*(const Polynomial& target);
	Polynomial derivative();
	
	friend class PolynomialTest;
};

#endif
