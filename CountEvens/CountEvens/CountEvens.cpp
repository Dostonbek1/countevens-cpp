#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

class Node {
private:
	int data;
	Node *next;

public:
	Node(int initdata) {
		data = initdata;
		next = NULL;
	}

	int getData() {
		return data;
	}

	Node *getNext() {
		return next;
	}

	void setData(int newData) {
		data = newData;
	}

	void setNext(Node *newnext) {
		next = newnext;
	}
};

class UnorderedList {
public:
	Node *head;

	UnorderedList() {
		head = NULL;
	}

	bool isEmpty() {
		return head == NULL;
	}

	void add(int item) {
		Node *temp = new Node(item);
		temp->setNext(head);
		head = temp;
	}

	int size() {
		Node *current = head;
		int count = 0;
		while (current != NULL) {
			count++;
			current = current->getNext();
		}

		return count;
	}

	bool search(int item) {
		Node *current = head;
		while (current != NULL) {
			if (current->getData() == item) {
				return true;
			}
			else {
				current = current->getNext();
			}
		}
		return false;
	}

	void remove(int item) {
		Node *current = head;
		Node *previous = NULL;
		bool found = false;
		while (!found) {
			if (current->getData() == item) {
				found = true;
			}
			else {
				previous = current;
				current = current->getNext();
			}
		}
		if (previous == NULL) {
			head = current->getNext();
		}
		else {
			previous->setNext(current->getNext());
		}
	}

	friend ostream& operator<<(ostream& os, const UnorderedList& ol);
};

ostream& operator<<(ostream& os, const UnorderedList& ol) {
	Node *current = ol.head;
	while (current != NULL) {
		os << current->getData() << endl;
		current = current->getNext();
	}
	return os;
}

int count_evens(Node currentNode) {
	// recursive function to count the number of even numbers in this linked list.

	if (currentNode.getNext() == NULL) {
		return 0;
	}
	else {
		if (currentNode.getData() % 2 == 0) {
			return 1 + count_evens(currentNode.getNext());
		}
		else {
			return count_evens(currentNode.getNext());
		}
	}
	
}

UnorderedList read_numbers_return_list(bool verbose) {
	/*
	preconditions: none
	postconditions : the numbers in the file with the name asked by the user will
	be placed into a linked list and returned.
	*/
	string filename;
	cout << "What is the name of the file? ";
	cin >> filename;

	// get the list of strings from the file.This list will need to be converted to
	// a list of numbers in a
	vector<string> stringList;
	ifstream myFile;
	myFile.open(filename);
	char output[100];
	if (myFile.is_open()) {
		while (!myFile.eof()) {
			myFile >> output;
			stringList.push_back(output);
		}
	}
	myFile.close();

	// time to create an integer version of the numbers list
	vector<int> numberList;
	for (int i = 0; i < stringList.size(); i++) {
		if (verbose) {
			cout << stringList[i] << endl;
			numberList.push_back(atoi(stringList[i].c_str()));
		}
	}

	// Now create a linked list version of this number sequence
	UnorderedList created_list;
	for (int i = 0; i < numberList.size(); i++) {
		created_list.add(numberList[i]);
	}

	return created_list;
}


int main() {
	UnorderedList numbersList;
	numbersList = read_numbers_return_list(true);
	cout << "There are " << to_string(count_evens(numbersList.head)) << " even numbers in the list.";
	
	return 0;
}


