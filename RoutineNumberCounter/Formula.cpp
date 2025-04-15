#include <iostream>
#include <fstream>
#include <string>
#include <map>

using namespace std;

int main() {
	
	double info[17];
	double sport[3][3][2];
	
	ifstream inputFile("FormulaInput.txt");
	string str;
	inputFile >> str;
//	cout << str;
	for (int i = 0; i < 3; i++) {
		for ( int k = 0; k < 3; k++) {
			inputFile >> sport[i][k][0];
			//cout << ' ' << sport[i][k][0];
			inputFile >> sport[i][k][1];
			//cout << ' ' << sport[i][k][1];
		}
	}
	//cout << endl;
	for (int i = 0; i < 17; i++){
		inputFile >> str;
		//cout << str << ' ';
		inputFile >> info[i];
		//cout << info[i] << endl;
	}
	
	double sum = 0.0;
	double sportSum = 0.0;
	for (int i = 0; i < 3; i++) {
		double avg = (sport[i][0][0] + sport[i][1][0] + sport[i][2][0]) /3.0;
		sportSum+= avg;
	}
//	cout << sportSum << endl;
	sum += sportSum / 3.0;
	sportSum = 0.0;
	for (int i = 0; i < 3; i++) {
		double avg = (sport[i][0][1] + sport[i][1][1] + sport[i][2][1]) /3.0;
		sportSum+= avg;
	}
//	cout << sportSum << endl;
	sum += sportSum / 3.0;
	sum /= 10;
	
	sum += (8.0 - info[0]) / 4.0 + 1.0;
	sum += (info[1] - 8.0) / 4.0 + 1.0;
	sum += info[2];
	sum += info[3] - 1.0;
	sum += 1.25 - info[4] / 2.0;
	sum += info[5] * 1.5;
	sum += 1.0 - info[6];
	sum += 0.8 + info[7] / 10.0;
	sum += 0.8 + info[8] * 2.0 / 5.0;
	sum += 0.8 + info[9] * 2.0 / 5.0;
	sum += 0.8 + info[10] * 3.0 / 10.0;
	sum += 1.0 - info[11] / 2.5;
	sum += 1.0 + info[12] / 5.0;
	sum += 0.6 + info[13] / 5.0;
	sum += 1.0 - info[14] / 2.5;
	sum += 1.0 + info[15] / 5.0;
	sum += 0.8 + info[16] * 2.0 / 5.0;
	
	double avgAll = sum / 17.0;
	cout << "Sum: " << sum << "\nAvg: " << avgAll;
}