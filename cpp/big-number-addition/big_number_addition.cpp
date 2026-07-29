/*
This program prompts the user to enter two numbers, which can be either whole or decimal values. 
It also asks the user to provide a file name where the results will be saved. 
The first number is stored in a singly linked list, and the same process is repeated for the second number. 
After both numbers are stored in separate lists, the program performs addition or subtraction on these lists 
and outputs the final result to the specified file.

The List class has a time complexity of O(n) for operations such as insertItemToFront(), display(), and getLength(). 
The GetNumbersToTheFile class operates in O(n^2) time to write numbers to a file, create a list, and read data back. 
The AddToFileAndDisplay class takes O(n) time to reverse numbers, write them to a file, and read them back. 
The Add and Subtract classes each have a time complexity of O(n^2), as they traverse and process each list element.

Overall, the program has an approximate time and space complexity of O(n^2).

*/


#include <iostream>
#include <list>
#include <fstream>
#include <string>
#include <algorithm>
using namespace std;

struct Node {
	int data;
	Node* next;
	
	Node(const int& d = int{}, Node* n = nullptr) :
		data{ d }, next{ n } {
	} // copy mode const

	Node(int&& d, Node* n = nullptr) :
		data{ move(d) }, next{ n } {
	}// move operator
};

class List {
private:
	Node* head;
public:
	List()
	{
		head = nullptr;	
	}
	void insertItem(int value) {
		Node* node = new Node(value);

		if (head == nullptr) {
			head = node;
			return;

		}
		Node* temp = head;
		while (temp->next)
			temp = temp->next;
		temp->next = node;
		
	}
	void insertItemToFront(int value) {
		Node* node = new Node(value);
		node->next = head;
		head = node;
	}

	void display() {
		Node* temp = head;
		while (temp != nullptr) {
			cout << temp->data << "\n";
			temp = temp->next;
		}

	}
	string displayToFile() {
		string ss;

		Node* temp = head;
			while (temp != nullptr) {
			ss += to_string(temp->data);
			temp = temp->next;
		}
		return ss;
	}

	Node* getHead() {
		return head;
	}
	
	int getLength(Node* p) {
		if (p == nullptr) return 0;
		else {
			return 1 + getLength(p->next);
		}
	}
	~List() {
		Node* temp = head;
		while (temp != nullptr) {
			Node* nextNode = temp->next;
			delete temp;
			temp = nextNode;
		}
		head = nullptr;

	}
};

class GetNumbersToTheFile {

public:
	int dotPlace = 0;
	bool pastDot = false;
	GetNumbersToTheFile(string FileName, string number, List& list) {

		fstream NewFile;
		FileName += ".txt";

		NewFile.open(FileName, ios::app); // write mode

		if (NewFile.is_open()) {
			
			for (auto& a : number) {
				NewFile << a << "\n";
			}
			NewFile.close();
		}
		
		NewFile.open(FileName, ios::in); // read mode
		if (NewFile.is_open()) {
			string line;
			string newNumber;
			
			cout << "\nList numbers: \n";
			
			while (getline(NewFile, line)) {
				if (!line.empty()) newNumber += line;
			
			}

			for (int i = newNumber.length() - 1; i >= 0; i--) {
				char c = newNumber[i];
				if (c == '.') {
					pastDot = true;
					continue;
				}
				if (isdigit(c)) {
					list.insertItem(c - '0');
					if (!pastDot) dotPlace++;
				}
			}
			
			NewFile.close();
			list.display();
		}

	}
	int getDotPlace() const {
		return pastDot ? dotPlace : 0;
	}
	
};


class AddToFileAndDisplay {

private:
	string fileName;
	int dotPosition;
	List& newNumbersList;
	bool negative;

public:

	AddToFileAndDisplay(string FileName, int dotPosition, List& newNumbersList, bool negative)
		: fileName(FileName), dotPosition(dotPosition), newNumbersList(newNumbersList), negative(negative) {

		fstream NewestFile;

		string nums = newNumbersList.displayToFile();
		reverse(nums.begin(), nums.end());

		nums.erase(0, nums.find_first_not_of('0'));
		if (nums.empty()) nums = "0";

		int n = nums.length();
		string result;
		
		if (dotPosition > 0 && n > dotPosition) {
			result = nums.substr(0, n - dotPosition) + "." + nums.substr(n - dotPosition);
		}
		else {
			result = nums;
		}

		FileName += ".txt";

		if (negative) result = '-' + result;

		ofstream out(FileName);

		if (out.is_open()) {
			for (char c : result) {
				out << c << "\n";
			}
		 out.close();
		}

		NewestFile.open(FileName, ios::in); // read mode
		if (NewestFile.is_open()) {
			string newNum;
			cout << "\nAdded list numbers in the file " << FileName << "\n";
			while (getline(NewestFile, newNum)) {
				for (auto& n : newNum) {
					if (isdigit(n) || n == '.') cout << n << "\n";
				}
			}
			
			NewestFile.close();
			cout << "Display the added list from the code \n";
			newNumbersList.display();
		}
	}
};



class AddDecimalNumbers {
public:
	List newNumbersList;

	AddDecimalNumbers(List& listFirst, List& listSecond, string FileName, int dot1, int dot2, bool negative) {

		int remainder = 0;
		if (dot1 > 0 || dot2 > 0) {
			while (dot1 < dot2) {
				listFirst.insertItemToFront(0);
				dot1++;
			}
			while (dot2 < dot1) {
				listSecond.insertItemToFront(0);
				dot2++;
			}
		}
		Node* first = listFirst.getHead();
		Node* second = listSecond.getHead();

		while (first != nullptr || second != nullptr || remainder != 0) {

			int val1 = (first) ? first->data : 0;
			int val2 = (second) ? second->data : 0;
           			
				int sum = val1 + val2 + remainder;
				remainder = sum / 10;
				int digit = sum % 10;

				newNumbersList.insertItem(digit);

				if (first) first = first->next;
				if (second) second = second->next;
			
		}
		AddToFileAndDisplay(FileName, max(dot1, dot2), newNumbersList, negative);	

	}


};




class SubstractNumbers {
public:
	List newNumbersList;

	SubstractNumbers(List& listFirst, List& listSecond, string FileName, int dot1, int dot2, bool negative) {
		
		int remainder = 0;

		if (dot1 > 0 || dot2 > 0) {
			while (dot1 < dot2) {
				listFirst.insertItemToFront(0);
				dot1++;
			}
			while (dot2 < dot1) {
				listSecond.insertItemToFront(0);
				dot2++;
			}
		}

		Node* first = listFirst.getHead();
		Node* second = listSecond.getHead();

		while (first != nullptr || second != nullptr || remainder != 0) {
			int val1 = 0;
			int val2 = 0;

			if (first) val1 = first->data;
			else  val1 = 0;

			if (second) val2 = second->data;
			else val2 = 0;

			int diff = val1 - val2 - remainder;
			if (diff < 0) {
				diff += 10;
				remainder = 1;
			}
			else {
				remainder = 0;
			}

			newNumbersList.insertItem(diff);

			if (first) first = first->next;
			if (second) second = second->next;
		}

		AddToFileAndDisplay(FileName, max(dot1, dot2), newNumbersList, negative);
	}

};

int main() {

	List listFirst, listSecond;
	
	
	string FileName1;
	cout << "\nPlease enter the name of the file for the first number\n->";
	cin >> FileName1;
	string number1;
	cout << "Enter the first number: \n";
	cin >> number1;
	GetNumbersToTheFile f1(FileName1, number1, listFirst);
	double n1 = stod(number1);

	string FileName2;
	cout << "\nPlease enter the name of the file for the second number\n->";
	cin >> FileName2;
	string number2;
	cout << "Enter the second number: \n";
	cin >> number2;
    double n2 = stod(number2);
	GetNumbersToTheFile f2(FileName2, number2, listSecond);

	string FileName3;
	cout << "\nPlease enter the name of the file for the output number\n->";
	cin >> FileName3;

	
		if ((number2[0] == '-') && (number1[0] != '-')) {
			if (n1 > n2) {
				SubstractNumbers(listFirst, listSecond, FileName3, f1.getDotPlace(), f2.getDotPlace(), false);
			}
			else {
				SubstractNumbers(listSecond, listFirst, FileName3, f2.getDotPlace(), f1.getDotPlace(), true);
			}
		}
		else 
		if ((number2[0] != '-') && (number1[0] == '-')) {
			if (n1 > n2) {
				SubstractNumbers(listFirst, listSecond, FileName3, f1.getDotPlace(), f2.getDotPlace(), true);
			}
			else {
				SubstractNumbers(listSecond, listFirst, FileName3, f2.getDotPlace(), f1.getDotPlace(), false);
			}
		}else 
		if ((number1[0] == '-') && (number2[0] == '-')) {
		AddDecimalNumbers(listFirst, listSecond, FileName3, f1.getDotPlace(), f2.getDotPlace(), true);
	    }
		else {
		
	    AddDecimalNumbers(listFirst, listSecond, FileName3, f1.getDotPlace(), f2.getDotPlace(), false);
		
	    }	

	return 0;

}
