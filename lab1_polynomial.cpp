#include "lab1_polynomial.h"
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <random>
#include <time.h>
#include <stdlib.h>
#include <algorithm>
#include <cassert>

// Authors: Sarah Dykstra 20817609, Adam Courchesne 20824794, Lauren Knoff 20817903

using namespace std;

Polynomial::Polynomial(int A[], int size){
	data.resize(size);
	for(int i = 0; i < size; i++){
		data[i] = A[i];
	}
}

Polynomial::Polynomial(){
	int length = rand() % 1001;
	data.resize(length);
	for(int i = 0; i < length; i++){
		data[i] = (rand() % 2001) - 1000;
	}
}

Polynomial::Polynomial(string file_name){
	ifstream reader;
	reader.open(file_name);
	if(!reader.fail()){
		int length;
		reader >> length;
		int input = 0;
		data.resize(length);
		for(int i = 0; i < length; i++){
			if (reader >> input)
				data[i] = input;
			else
				data[i] = 0;
		}
		reader.close();
	}
	else
		cout << "File failed" << endl;

}

bool Polynomial::operator==(const Polynomial& target){
	bool match = false;
	Polynomial new_this, new_target;
	new_target = target;
	if(this->data.size() != 0)
		new_this = this->trim();
	else
		new_this = *this;
	if(target.data.size() != 0){
		new_target = new_target.trim();
	}
	if(new_this.data.size() == 0 && new_target.data.size() == 0) 
		match = true;
	else if(new_this.data.size() == new_target.data.size()){
		bool failed = false;
		for(int i = 0; i < new_this.data.size(); i++){
			if(new_this.data[i] != new_target.data[i])
				failed = true;
		}
		match = !failed; 
	}
	return match;
}

Polynomial Polynomial::trim(){
	Polynomial result;
	int counter = this->data.size() - 1;
	int size = this->data.size();
	while(this->data[counter] == 0) {
		counter--;
		size--;
	}
	result.data.resize(size);
	for(int i = 0; i < size; i++){
		result.data[i] = this->data[i];
	}
	return result;
}

void Polynomial::print(){
	Polynomial target = trim();
	if(target.data.size() > 0){
		cout << target.data[target.data.size() - 1] << "x^" << (target.data.size() - 1);
		for(int i = target.data.size() - 2; i >= 0; i--){
			if(target.data[i] > 0)
				cout << " + " << target.data[i] << "x^" << i;
			else if (target.data[i] < 0)
				cout << " - " << -target.data[i] << "x^" << i;
		}
	}
	cout << endl;	
}

Polynomial Polynomial::operator+(const Polynomial& target){
	Polynomial result;
	result.data.resize(max(this->data.size(), target.data.size()));
	
	for(int i = 0; i < result.data.size(); i++){
		result.data[i] = 0;
	}
	for(int i = 0; i < this->data.size(); i++){
		result.data[i] += this->data[i];
	}
	for(int i = 0; i < target.data.size(); i++)
		result.data[i] += target.data[i];
	return result;
}

Polynomial Polynomial::operator-(const Polynomial& target){
	Polynomial result;
	result.data.resize(max(this->data.size(), target.data.size()));
	
	for(int i = 0; i < result.data.size(); i++){
		result.data[i] = 0;
	}
	for(int i = 0; i < this->data.size(); i++){
		result.data[i] += this->data[i];
	}
	for(int i = 0; i < target.data.size(); i++){
		result.data[i] -= target.data[i];
	}
	
	return result;
}

Polynomial Polynomial::operator*(const Polynomial& target){
	Polynomial result;
	if(this->data.size() == 0 || target.data.size() == 0)
		result.data.resize(0);
	else
		result.data.resize(this->data.size() + target.data.size() - 1);
	
	for(int i = 0; i < result.data.size(); i++){
		result.data[i] = 0;
	}
	for(int i = 0; i < this->data.size(); i++){
		for(int j = 0; j < target.data.size(); j++){
			result.data[i + j] += this->data[i] * target.data[j];
		}
	}
	return result;
}

Polynomial Polynomial::derivative(){
	Polynomial result;
	
	if(this->data.size() == 0)
		return *this;
	else
		result.data.resize(this->data.size() - 1);
		
	for(int i = 0; i < this->data.size() - 1; i++){
		result.data[i] = this->data[i + 1] * (i + 1);
	}
	return result;	
}

Polynomial::~Polynomial(){}

class PolynomialTest{
	int array1[0] = {};
	int array2[5] = {1, 2, 3, 4, 5};
	int array3[3] = {1, 2, 3};
	Polynomial test_case1;
	Polynomial test_case2;
	Polynomial test_case3;
	Polynomial test_case4;
public:
	
	void test_constructors(Polynomial &test1, Polynomial &test2, Polynomial &test3, Polynomial &test4){
		test1 = Polynomial("polynomial_empty.txt");
		cout << "File constructor test 1 passed." << endl;
		test2 = Polynomial(array2, 5);
		cout << "Array constructor test 1 passed." << endl;
		test3 = Polynomial("polynomial_info.txt");
		cout << "File constructor test 2 passed." << endl;
		test4 = Polynomial(array3, 3);
		cout << "Array constructor test 2 passed." << endl;
		Polynomial test5 = Polynomial();
		cout << "Empty constructor test 1 passed." << endl;
		Polynomial test6 = Polynomial();
		cout << "Empty constructor test 2 passed." << endl;
		
		assert(test1.data.size() == 0);
		cout << "File constructor length test 1 passed." << endl;
		assert(test2.data.size() == 5);
		cout << "Array constructor length test 1 passed." << endl;
		assert(test3.data.size() == 5);
		cout << "File constructor length test 2 passed." << endl;
		assert(test4.data.size() == 3);
		cout << "Array constructor length test 2 passed." << endl;
		assert(test5.data.size() < 1001 && test5.data.size() >= 0 && test6.data.size() < 1001 && test6.data.size() >= 0);
		cout << "Empty constructor length test passed." << endl;
		assert(!(test5 == test6));
		cout << "Empty constructor varied test passed." << endl;
		assert(test2 == test3);
		cout << "File constructor read correctly test passed." << endl;
		cout << "All constructor tests passed." << endl << endl;
	}
	
	void test_print(){
		test_case1.print();
		test_case3.print();
		
		int zero_e[] = {1, -1, 0};
		Polynomial zero_exponent = Polynomial(zero_e, 3);
		zero_exponent.print();
		
		Polynomial random = Polynomial();
		random.print();
		
		cout << endl;
	}
	
	void test_equals(){
		assert(!(test_case1 == test_case2));
		cout << "Operator == test 1 passed." << endl;
		assert(test_case2 == test_case3);
		cout << "Operator == test 2 passed." << endl;
		assert(!(test_case3 == test_case4));
		cout << "Operator == test 3 passed." << endl;
		cout << "All operator == tests passed." << endl << endl;
	}
	
	void test_plus(){
		int expected_array1[5] = {2, 4, 6, 4, 5};
		Polynomial expected1 = Polynomial(expected_array1, 5);
		
		assert(test_case2 + test_case4 == expected1);
		cout << "Operator + test 1 passed." << endl;
		assert(test_case1 + test_case2 == test_case2);
		cout << "Operator + test 2 passed." << endl;
		assert(test_case1 + test_case1 == test_case1);
		cout << "Operator + test 3 passed." << endl;
		cout << "All operator + tests passed." << endl << endl;
	}
	
	void test_minus(){
		int expected_array[5] = {0, 0, 0, 4, 5};
		Polynomial expected = Polynomial(expected_array, 5);
		
		assert(test_case2 - test_case4 == expected);
		cout << "Operator - test 1 passed." << endl;
		assert(test_case2 - test_case1 == test_case2);
		cout << "Operator - test 2 passed." << endl;
		assert(test_case3 - test_case3 == test_case1);
		cout << "Operator - test 3 passed." << endl;
		cout << "All operator - tests passed." << endl << endl;		
	}
	
	void test_times(){
		int expected_array[7] = {1, 4, 10, 16, 22, 22, 15};
		Polynomial expected = Polynomial(expected_array, 7);
		
		assert(test_case2 * test_case4 == expected);
		cout << "Operator * test 1 passed." << endl;
		assert(test_case1 * test_case2 == test_case1);
		cout << "Operator * test 2 passed." << endl;
		assert(test_case1 * test_case1 == test_case1);
		cout << "Operator * test 3 passed." << endl;
		cout << "All operator * tests passed." << endl << endl;
	}
	
	void test_derivative(){
		int expected_array1[4] = {2, 6, 12, 20};
		Polynomial expected1 = Polynomial(expected_array1, 4);
		Polynomial test = Polynomial();
		
		assert(test_case1.derivative() == test_case1);
		cout << "Derivative test 1 passed." << endl;
		assert(test_case2.derivative() == expected1);
		cout << "Derivative test 2 passed." << endl;
		assert(test.derivative().data.size() + 1 == test.data.size());
		cout << "Derivative test 3 passed." << endl;
		cout << "All derivative tests passed." << endl;
	}
	
	void run(){
		test_constructors(test_case1, test_case2, test_case3, test_case4);
		test_print();
		test_equals();
		test_plus();
		test_minus();
		test_times();
		test_derivative();
	}
};

int main(){
	PolynomialTest test_cases = PolynomialTest();
	test_cases.run();
	return 0;
}
