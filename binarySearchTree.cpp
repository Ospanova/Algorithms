#include <iostream>

using namespace std;

#include <unordered_map>
#include <unordered_set>
#include <list>
#include <queue>
#include<string>


class Date {
	int yy, mm, dd;
	
public:
	Date(int yy, int mm, int dd) : yy(yy), mm(mm), dd(dd) {}
	Date() : yy(0), mm(0), dd(0) {}
	string toString() {
		return to_string(yy) + "#" + to_string(mm) + "#" + to_string(dd);
	}
};

class Person {
	string firstName, lastName, address;
	Date birthday;
	int age;
	string serialized;
	string serializeForHash() {
		return this->firstName + "#" + this->lastName + "#" + this->address + "#" + this->birthday.toString();
	}
	int getIndex(char c) {
		if (c >= 'a' && c <= 'z')
			return c - 'a' + 1; // 1 - 26
		if (c >= 'A' && c <= 'Z')
			return c - 'A' + 1 + 26; // 27 - 52
		if (c >= '0' && c <= '9')
			return c - '0' + 1 + 26 + 26; // 53 - 62
		if (c == '#')
			return 63;
		return 64;
	}
public:
	Person(string firstName, string lastName, string address, Date birthday, int age) :
	firstName(firstName), lastName(lastName), address(address), birthday(birthday), age(age) {
		serialized = serializeForHash();

	}
	long long compute_hash() {
	    const int p = 67;  // since max value is 64
	    const int mod = 1e9 + 9;
	    long long hashValue = 0;
	    long long pPow = 1;
	    for (char c : serialized) {
	        hashValue = (hashValue + getIndex(c) * pPow) % mod;
	        pPow = (pPow * p) % mod;
	    }
	    return hashValue;
	}	
};


int main() {
	Person p = Person("Aidz", "Zspanova", "Aqtau", Date(1999, 3, 8), 22);
	cout << p.compute_hash() << endl;

}