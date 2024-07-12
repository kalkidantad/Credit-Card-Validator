/*
ID- 040
Name - KALKIDAN TADESSE
Section - A

*/
#include <iostream> 
#include <string> 
#include <cstring>
#include <cctype>  
#include <cstdlib>
#include <bits/stdc++.h> 
#include <cmath>
#include <algorithm>
using namespace std;

struct CreditCardValidator{

bool isNumberString(const string& s) {
    int len = s.length();
    for (int i = 0; i < len; i++) {
        if (s[i] < '0' || s[i] > '9')
            return false;
    }
    return true;
}

bool containsNonZeroDigits(const string& s) {
    for (char c = 0; c < s.length(); c++){
        if (s[c] != '0') {
            return true;
        }
    }
    return false;
}

  // first condition
int sumOfDigits(long long num) {
    if (num == 0) {
        return 0;
    }
    return num % 10 + sumOfDigits(num / 100);
}
  // second condition 
int sumOfDoubleDigits(long long num) {
    if (num == 0) {
        return 0;
    }
    int lastsecdigit = num % 10;
    int timesTwo = lastsecdigit * 2;
    return (timesTwo % 10) + (timesTwo / 10) + sumOfDoubleDigits(num / 100);
}
   
int countDigits(long long num) {
    if (num == 0) {
        return 0;
    }
    return 1 + countDigits(num / 10);
}

int getFirstTwoDigits(long long num, int count) {
    if (count <= 2) {
        return num;
    }
    return getFirstTwoDigits(num / 10, count - 1);
}
int getFirstFourDigits(long long num, int count, int current = 0) {
    if (current == 4 || count == 0) {
        return num;
    } else {
        return getFirstFourDigits(num / 10, count - 1, current + 1);
    }
}

string getCardType(long long num, int count) {
    int firstdigit = num / pow(10, count - 1);
    int first_two = getFirstTwoDigits(num, count);
    int first_four = getFirstFourDigits(num, count);
    
    if (firstdigit == 4 && (count == 13 || count == 16)) {
        return "VISA";
    }
    else if ((first_two == 34 || first_two == 37) && count == 15) {
        return "AMERICAN EXPRESS";
    }
    else if ((first_two == 6 || first_two == 60 || first_two == 64 || first_two == 65) && count == 16) {
        return "DISCOVER";
    }
    else if ((50 < first_two && first_two < 56) && count == 16) {
        return "MASTERCARD";
    }
    else if ((first_two == 36 || first_two == 38 || first_four == 3000 || first_four == 3050 || first_four == 3095) && (count == 16 || count == 19)) {
        return "DINERS CLUB";
    }
    else if ((first_two == 49 || first_two == 56 || first_two == 58 || first_two == 67) && (count == 16 || count == 18 || count == 19)) {
        return "SWITCH";
    }
    else if ((firstdigit == 4 || first_two == 42 || first_two == 45) && (count == 16 || count == 19)) {
        return "VISA ELECTRON";
    }
    else if ((first_two == 50 || first_two == 56 || first_two == 57 || first_two == 58 || (first_four >= 5000 && first_four <= 5099)) && (count == 12 || count == 16 || count == 18 || count == 19)) {
        return "MAESTRO";
    }
    else if ((first_two == 35) && (count == 16 || count == 19)) {
        return "JCB";
    }
    else if ((first_two == 63 || first_two == 67) && (count == 16 || count == 18 || count == 19)) {
        return "SOLO";
    }
    else {
        return "OTHER CARD TYPE";
    }
}

void validateCreditCard(){
	string creditnum;

    int terminalWidth = 80;
        int leftPadding = (terminalWidth - 25) / 2; // Assuming the output is around 25 characters wide
        string padding(leftPadding, ' ');

        cout << padding << "You can enter 'exit' anytime to quit." << endl;
        cout << padding << "DO NOT INCLUDE SPACE ! " << endl;

    while (true) {
        cout<< padding << "Please enter a Credit Card number to validate: ";
        getline(cin, creditnum);

        if (creditnum == "exit") {
            break;
        }
        
        creditnum.erase(remove(creditnum.begin(), creditnum.end(), ' '), creditnum.end());
        if (!isNumberString(creditnum)) {
            cout << "Bad input! You can not include non-digit characters. " << endl;
            continue;
        }
        else if (!containsNonZeroDigits(creditnum)) {
            cout << "Invalid input! The credit card number cannot contain only zeros." << endl;
            continue;
        }
         
        long long num = atoll(creditnum.c_str());
        int sum = sumOfDigits(num) + sumOfDoubleDigits(num / 10);
        int count = countDigits(num);
        string cardType = getCardType(num, count);

        if (sum % 10 == 0) {
            cout << "VALID" << endl;
            cout << "CARD TYPE: " << cardType << endl;
        }
        else {
            cout << "INVALID" << endl;
        }
    }	
}
};
int main() {
    CreditCardValidator validator;
    validator.validateCreditCard();

    return 0;
}