#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <cmath>
using namespace std;

class SignedBinaryUIConverter {
private:
	long long _value;
	int _bitRange;
public:
	SignedBinaryUIConverter() {
		_value = 0;
		_bitRange = 0;
	}
	SignedBinaryUIConverter(int value, int bitRange) {
		_value = value;
		_bitRange = bitRange;
	}
public:
	bool isValidDec(long long, int);
	bool isValidBin(string);
	vector<int>	convertDecToBin(long long, int);
	long long convertBinToDec(string);
	string toString(vector<int>);
	vector<int> convertBack(string);
public:
	vector<int> getBinaryPlusOne(vector<int>);
	void reverseBinary(vector<int> &);
};

bool SignedBinaryUIConverter::isValidDec(long long value, int bitRange) {
	bool check8bit = false, check16bit = false, check32bit = false; 
	if (bitRange == 8 && value >= -pow(2, 8 - 1) && value <= pow(2, 8 - 1) - 1) {
		check8bit = true;	
	}
	if (bitRange == 16 && value >= -pow(2, 16 - 1) && value <= pow(2, 16 - 1) - 1) {
		check16bit = true;
	}	
	if (bitRange == 32 && value >= -pow(2, 32 - 1) && value <= pow(2, 32 - 1) - 1) {
		check32bit = true;	
	}
	bool result = check8bit || check16bit || check32bit;
	return result;
}

vector<int> SignedBinaryUIConverter::getBinaryPlusOne(vector<int> value) {
	int i = value.size() - 1;
	while (value[i] != 0) {
		value[i] = 0;
		i--;
	}
	value[i] = 1;
	return value;
}

void SignedBinaryUIConverter::reverseBinary(vector<int> &value) {
	int n = value.size();
	for (int i = 0; i < n; i++) {
		value[i] = abs(value[i] - 1);	
	}
}

vector<int>	SignedBinaryUIConverter::convertDecToBin(long long value, int bitRange) {
	vector<int> result(bitRange);
	long long temp = abs(value);
	while (temp != 0) {
		result[--bitRange] = temp % 2;
		temp /= 2;
	}
	if (value < 0) {
		reverseBinary(result);
		result = getBinaryPlusOne(result);
	}
	return result;
}

string SignedBinaryUIConverter::toString(vector<int> value) {
	stringstream builder;
	for (int u : value) {
		builder << u;
	}
	string result = builder.str();
	return result;
}

bool SignedBinaryUIConverter::isValidBin(string value) {
	int lenValue = value.size();
	if (lenValue <= 32) {
		return true;
	}
	return false;
}

vector<int> SignedBinaryUIConverter::convertBack(string value) {
	vector<int> result;
	int n = value.size();
	for (int i = 0; i < n; i++) {
		char c = value[i];
		string temp = "";
		temp += c;
		result.push_back(stoi(temp));
	}
	return result;
}

long long SignedBinaryUIConverter::convertBinToDec(string value) {
	vector<int> buffer = convertBack(value);
	long long result = 0;
	int cnt = 0;
	int n = value.size();
	int flag = 0;
	if (value[0] == '1') {
		flag = 1;
		reverseBinary(buffer);
		value = toString(buffer);
	}
	while (cnt < n) {
		char c = value[n - cnt - 1];
		string temp = "";
		temp += c;	
		result += stoi(temp) * pow(2, cnt);
		cnt++;
	}
	if (flag == 1) {
		result += 1;
		result = -result;
	}
	return result;	
}


int main() {
	SignedBinaryUIConverter _sbc;
	int n; cin >> n;
	int bitSize; cin >> bitSize;
	if (_sbc.isValidDec(n, bitSize)) {
		cout << _sbc.toString(_sbc.convertDecToBin(n, bitSize)) << endl;	
		cout << _sbc.convertBinToDec(_sbc.toString(_sbc.convertDecToBin(n, bitSize)));
	}	
	else {
		cout << "Error Format";
	}



	return 0;
}







