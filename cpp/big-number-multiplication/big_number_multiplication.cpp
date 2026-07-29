/*
This program prompts the user to enter two numbers, which can be either whole or decimal values. 
It also asks the user to provide a file name where the results will be saved. 
The first number is stored in a singly linked list, and the same process is repeated for the second number. 
After both numbers are stored in separate lists, the program performs ,ultiplication on these lists 
and outputs the final result to the specified file.

The List class has a time complexity of O(n) for operations such as insertItemToFront(), display(), and getLength(). 
The GetNumbersToTheFile class operates in O(n^2) time to write numbers to a file, create a list, and read data back. 
The AddToFileAndDisplay class takes O(n) time to reverse numbers, write them to a file, and read them back. 
The Multipy class combine addition and multiplication and have a time complexity of O(n * m), as they traverse and process each list element.

Overall, the program has an approximate time and space complexity of O(n).

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
	void copyFrom(const List& other) {
		head = nullptr;
		Node* temp = other.head;
		while (temp) {
			insertItem(temp->data);
			temp = temp->next;
		}
	}
	void clear() {
		Node* temp = head;
		while (temp) {
			Node* nextNode = temp->next;
			delete temp;
			temp = nextNode;
		}
		head = nullptr;
	}
public:
	List()
	{
		head = nullptr;	
	}
	List(const List& rhs) {
		//init();
		copyFrom(rhs);
	}
	List& operator=(List rhs) {		
		swap(rhs);
		return *this;
	}
	void swap(List& rhs) {
		std::swap(head, rhs.head);
		
	}
	~List() {
		clear();
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
	bool isEmpty(){
		return head == nullptr;
	}

	void display() {
		Node* temp = head;
		while (temp != nullptr) {
			cout << temp->data << "\n";
			temp = temp->next;
		}

	}
	int displayInt() {
		int number;

		Node* temp = head;
		while (temp != nullptr) {
			number = temp->data;
			return number;
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
	void init() {
		
		head = new Node();
		head->next = nullptr;
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

	AddToFileAndDisplay(string FileName, int dotPosition, List& newNumbersList)
		: fileName(FileName), dotPosition(dotPosition), newNumbersList(newNumbersList) {

		fstream NewestFile;

		string nums = newNumbersList.displayToFile();
		reverse(nums.begin(), nums.end());

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

class multiplyNumbers {

public:
	
	multiplyNumbers(List& listFirst, List& listSecond, string FileName, int dot1, int dot2) {
		
		List total;
		total.insertItem(0);

		Node* q = listSecond.getHead();
		int zeros = 0;

		while (q) {
			List part = multiplyDigits(listFirst, q->data);
			appendZeros(part, zeros);

			total = addLists(total, part);

			zeros++;
			q = q->next;
		}		
			int sum = dot1 + dot2;
			AddToFileAndDisplay(FileName, sum, total);
	}
	
	List multiplyDigits(List& a, int digit) {
		List result;
		Node* temp = a.getHead();
		int carry = 0;
		while (temp || carry) {

			int x;
			if (temp != nullptr) x = temp->data;
			else x = 0;

			int prod = x * digit + carry;
			result.insertItem(prod % 10);
			carry = prod / 10;

			if (temp) temp = temp->next;
		
		}
		return result;
	}
	void appendZeros(List& L, int count) {
		while (count--) {
			L.insertItemToFront(0);
		}
	}
	List addLists(List& A, List& B) {
		Node* p = A.getHead();
		Node* q = B.getHead();
		List result;
		int carry = 0;

		while (p || q || carry) {

			int x;
			if (p != nullptr) x = p->data;
			else x = 0;

			int y;
			if (q != nullptr) y = q->data;
			else y = 0;

			int sum = x + y + carry;
			result.insertItem(sum % 10);
			carry = sum / 10;

			if (p) p = p->next;
			if (q) q = q->next;
		}

		return result;
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

    int lengthFirst = listFirst.getLength(listFirst.getHead());
	int lengthSecond = listSecond.getLength(listSecond.getHead());

	if (lengthFirst < lengthSecond) {
		multiplyNumbers(listSecond, listFirst, FileName3, f1.getDotPlace(), f2.getDotPlace());
	}
	else {
		multiplyNumbers(listFirst, listSecond, FileName3, f1.getDotPlace(), f2.getDotPlace());
	}
	return 0;
}
