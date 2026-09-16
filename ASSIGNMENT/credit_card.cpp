#include <iostream>
#include <cmath>
#include <string>

using namespace std;

bool isValid(long long number);
int sumOfDoubleEvenPlace(long long number);
int getDigit(int number);
int sumOfOddPlace(long long number);
bool prefixMatched(long long number, int d);
int getSize(long long d);
long long getPrefix(long long number, int k);

int main() {
    long long number;
    cout << "Enter your credit card number: ";
    cin >> number;

    if (isValid(number)) {
        cout << "The Credit Card:" << number << " is valid" << endl;
    } else {
        cout << "The Credit Card:" << number << " is invalid" << endl;
    }

    return 0;
}


bool isValid(long long number) {
    int totalSize = getSize(number);

    if (totalSize < 13 || totalSize > 16) {
        return false;
    }

        if (!prefixMatched(number, 4) && 
        !prefixMatched(number, 5) && 
        !prefixMatched(number, 37) && 
        !prefixMatched(number, 6)) {
        return false;
    }

    int totalSum = sumOfDoubleEvenPlace(number) + sumOfOddPlace(number);
    return (totalSum % 10 == 0);
}


int sumOfDoubleEvenPlace(long long number) {
    int sum = 0;
    number /= 10; 

    while (number > 0) {
        int digit = number % 10;
        sum += getDigit(digit * 2);
        number /= 100; 
    }

    return sum;
}

int getDigit(int number) {
    if (number < 10) {
        return number;
    }
    return (number / 10) + (number % 10);
}

int sumOfOddPlace(long long number) {
    int sum = 0;

    while (number > 0) {
        int digit = number % 10;
        sum += digit;
        number /= 100; 
        }

    return sum;
}

bool prefixMatched(long long number, int d) {
    int sizeD = getSize(d);
    return getPrefix(number, sizeD) == d;
}

int getSize(long long d) {
    if (d == 0) return 1;
    int count = 0;
    while (d > 0) {
        count++;
        d /= 10;
    }
    return count;
}

long long getPrefix(long long number, int k) {
    int numSize = getSize(number);
    if (numSize < k) {
        return number;
    }
    
    long long factor = pow(10, numSize - k);
    return number / factor;
}