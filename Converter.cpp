#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <cmath>
using namespace std;

class UnsignedBinaryUIConverter {
private:
	long long _value;
	int _bitRange;
public:
	UnsignedBinaryUIConverter() {
		_value = 0;
		_bitRange = 0;
	}
	UnsignedBinaryUIConverter(long long value, int bitRange) {
		_value = value;
		_bitRange = bitRange;
	}
public:
	bool isValidDec(long long, int);
	bool isValidBin(string);
	vector<int> convertDecToBin(const long long&);
	long long convertBinToDec(string);
	string toString(vector<int>, int);
};


bool UnsignedBinaryUIConverter::isValidDec(long long value, int bitRange) {
	bool check8bit = false, check16bit = false, check64bit = false;
	if (bitRange == 8 && value >= 0 && value <= 225) {
		check8bit = true;
	}	
	if (bitRange == 16 && value >= 0 && value <= 65535) {
		check16bit = true;
	}
	if (bitRange == 32 && value >= 0 && value <= 4294967295) {
		check64bit = true;
	}
	bool result = check8bit || check16bit || check64bit;
	return result;
}

vector<int> UnsignedBinaryUIConverter::convertDecToBin(const long long& value) {
	static vector<int> result;
	if (value < 2) {
		result.push_back(value);
		return result;
	}
	convertDecToBin(value / 2);
	result.push_back(value % 2);
	return result;
}

string UnsignedBinaryUIConverter::toString(vector<int> values, int bitRange) {
	stringstream builder;
	for (int value : values) {
		builder << value;
	}
	string result = builder.str();
	string buffer = "";
	for (int i = 0; i < bitRange - values.size(); i++) {
		buffer += '0';
	}
	result = buffer + result;
	return result;
}

bool UnsignedBinaryUIConverter::isValidBin(string value) {
	int lenValue = value.size();
	if (lenValue <= 32) {
		return true;
	}
	return false;
}

long long UnsignedBinaryUIConverter::convertBinToDec(string value) {
	long long result = 0;
	int cnt = 0;
	int n = value.size();
	while (cnt < n) {
		char c = value[n - cnt - 1];
		string temp = "";
		temp += c;	
		result += stoi(temp) * pow(2, cnt);
		cnt++;
	}
	return result;	
}


int main() {
	long long n;
	cout << "Input Decimal Value: \n";
   	cin >> n; // input decimal value
	cout << "Input Bit Size: \n";
	int bitRange; cin >> bitRange;
	vector<int> values;
	UnsignedBinaryUIConverter _ubc(n, bitRange);
	if (_ubc.isValidDec(n, bitRange)) {
		values = _ubc.convertDecToBin(n);
		cout << "Bin: ";
		cout << _ubc.toString(values, bitRange) << endl;
	}
	else {
		cout << "Error!";
	}
	cout << "Dec: ";
	cout << _ubc.convertBinToDec(_ubc.toString(values, bitRange));

	return 0;
}
