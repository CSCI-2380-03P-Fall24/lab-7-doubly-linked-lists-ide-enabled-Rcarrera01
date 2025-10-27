	#include "StudentList.h"

	// Define a constructor to initialize the list. The list starts with no Students
    StudentList::StudentList() {
		head = nullptr;
		tail = nullptr;
		numStudents = 0;
	}

	// return the number of students currently in the list
	int StudentList::listSize() {
		return numStudents;
	}

	//add a Node with a student to the front (head) of the list.
	void StudentList::addFront(Student s) {
		Node* newNode = new Node(s);
		newNode->next = head;
		newNode->prev = nullptr;

		if (head !=nullptr)
			head->prev = newNode;
		else
			tail = newNode;

		head = newNode;
		numStudents++;
	}

	//add a Node with a student to the back (tail) of the list.
	void StudentList::addBack(Student s) {
		Node* newNode = new Node(s);
    	newNode->next = nullptr;
   		newNode->prev = tail;

    	if (tail != nullptr)
        	tail->next = newNode;
    	else
        	head = newNode; // list was empty

    tail = newNode;
    numStudents++;
	}

	//Print out the names of each student in the list.
	void StudentList::printList() {
		if (!head) {
			cout << "List is empty." << endl;
			return;
		}

		Node* curr = head;
		cout << "Student List (" << numStudents << " students):" << endl;
		while (curr) {
			cout << "Name: " << curr->data.name
				 << ", ID: " << curr->data.id
				 << ", GPA: " << curr->data.GPA << endl;
			curr = curr->next;
   		}
	}

	// Remove the Node with the student at the back (tail) of the list
	// should not fail if list is empty! Print an error message if this occurs
	// Don't forget that your head and tail pointers will be null pointers if the list is empty
	void StudentList::popBack() {
		if (!tail) {
        	cout << "Cannot remove from back — list is empty." << endl;
			return;
    	}

    	Node* temp = tail;
    	tail = tail->prev;

    	if (tail)
        	tail->next = nullptr;
   		else
        	head = nullptr; // list became empty

    	delete temp;
    	numStudents--;
		}

	// Remove the Node with the student at the front (head) of the list
	// should not fail if list is empty! Print an error message if this occurs
	// Don't forget that your head and tail pointers will be null pointers if the list is empty
	void StudentList::popFront() {
		if (!head) {
        	cout << "Cannot remove from front — list is empty." << endl;
        return;
    }

    	Node* temp = head;
    	head = head->next;

    	if (head)
        	head->prev = nullptr;
    	else
        	tail = nullptr; // list became empty

    	delete temp;
   		numStudents--;
	}

	//insert a student at the position "index".
	// for this list, count head as index 0
	// if index is outside of current list range, 
	// print a message and insert the student at the back of the list
	// the previous Node at your target index should be moved forward. "For exampe, Node with student at index i, becomes index i+1" 
	// Remember that you already have methods that can add students to the front or back of list if needed! Don't repeat this code.
	void StudentList::insertStudent(Student s, int index) {
		if (index <= 0) {
        	addFront(s);
        	return;
    	}

    	if (index >= numStudents) {
        	cout << "Index out of range. Adding to back instead." << endl;
        	addBack(s);
        	return;
    	}

    	Node* curr = head;
    	for (int i = 0; i < index - 1; i++)
        	curr = curr->next;

    	Node* newNode = new Node(s);
    	newNode->next = curr->next;
    	newNode->prev = curr;

    	if (curr->next)
        	curr->next->prev = newNode;
    		curr->next = newNode;

    	numStudents++;
	}

	//find the student with the given id number and return them
	// if no student matches, print a message 
	// and create and return a dummy student object
	Student StudentList::retrieveStudent(int idNum) {
    Node* curr = head;
    while (curr) {
        if (curr->data.id == idNum)
            return curr->data;
        curr = curr->next;
    }

    cout << "Student with ID " << idNum << " not found." << endl;
    Student dummy;
    dummy.name = "nobody";
    dummy.id = -1;
    dummy.GPA = 0.0;
    return dummy;
	}

	// Remove a Node with a student from the list with a given id number
	// If no student matches, print a message and do nothing
	void StudentList::removeStudentById(int idNum) {
		    Node* curr = head;
    while (curr) {
        if (curr->data.id == idNum) {
            if (curr == head)
                popFront();
            else if (curr == tail)
                popBack();
            else {
                curr->prev->next = curr->next;
                curr->next->prev = curr->prev;
                delete curr;
                numStudents--;
            }
            cout << "Removed student with ID " << idNum << "." << endl;
            return;
        }
        curr = curr->next;
    }
    cout << "Student with ID " << idNum << " not found — no removal done." << endl;
	}

	//Change the gpa of the student with given id number to newGPA
	void StudentList::updateGPA(int idNum, float newGPA) {
	Node* curr = head;
    while (curr) {
        if (curr->data.id == idNum) {
            curr->data.GPA= newGPA;
            cout << "Updated GPA for " << curr->data.name << " to " << newGPA << endl;
            return;
        }
        curr = curr->next;
    }
    cout << "Student with ID " << idNum << " not found — no update done." << endl;
	}

	//Add all students from otherList to this list.
	//otherlist should be empty after this operation.
	/*
	For example, if the list has 3 students:
	s1 <-> s2 <-> s3
	and otherList has 2 students
	s4 <-> s5
	then after mergeList the currently list should have all 5 students
	s1 <-> s2 <-> s3 <-> s4 <-> s5
	and otherList should be empty and have zero students.
	*/
	void StudentList::mergeList(StudentList &otherList) {
	if (!otherList.head) return; // other list empty

    if (!head) {
        head = otherList.head;
        tail = otherList.tail;
    	} 
	else {
        tail->next = otherList.head;
        otherList.head->prev = tail;
        tail = otherList.tail;
    	}

    numStudents += otherList.numStudents;

    otherList.head = nullptr;
    otherList.tail = nullptr;
    otherList.numStudents = 0;
	}

	//create a StudentList of students whose gpa is at least minGPA.
	//Return this list.  The original (current) list should
	//not be modified (do not remove the students from the original list).
	StudentList StudentList::honorRoll(float minGPA) {
    StudentList honor;
    Node* curr = head;
    while (curr) {
        if (curr->data.GPA >= minGPA)
            honor.addBack(curr->data);
        curr = curr->next;
    }

    return honor;
	}

	//remove all students whose GPA is below a given threshold.
	// For example, if threshold = 3.0, all students with GPA less than 3.0
	// should be removed from the list. 
	// Be sure to correctly update both head and tail pointers when removing 
	// from the front or back, and adjust numStudents accordingly.
	// If the list is empty, print a message and do nothing.
	void StudentList::removeBelowGPA(float threshold) {
		if (!head) {
        	cout << "List is empty — no students removed." << endl;
        return;
    }

    Node* curr = head;
    while (curr) {
        Node* nextNode = curr->next;
        if (curr->data.GPA < threshold) {
            if (curr == head)
                popFront();
            else if (curr == tail)
                popBack();
            else {
                curr->prev->next = curr->next;
                curr->next->prev = curr->prev;
                delete curr;
                numStudents--;
            }
        }
        curr = nextNode;
    }
	}
