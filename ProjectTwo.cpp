//============================================================================
// Name        : ProjectTwoVector.cpp
// Author      : Steven Davis
//============================================================================

// include standard libraries 
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>
#include <stdlib.h>

using namespace std;

// structure course to represent courseList data
struct Course {
	string courseTitle;
	string courseId;
	vector<string> prerequisites;
	// set course to default size
	Course() = default;
};

//initilize vector course list
std::vector<Course> courseList;

// Load Data Structure into vector
void LoadCourseData() {

	// initilize file name variable
	string fileName;

	// set filename to file for course information
	fileName = "CS 300 ABCU_Advising_Program_Input.csv";

	// Open file
	ifstream infile;
	infile.open(fileName);

	// check for file to be open
	if (infile.is_open()) {
		string line;

		// Read file line by line 
		while (getline(infile, line)) {
			vector <string> courseData;
			string course;
			stringstream ss(line);

			// seperate courseData at ','
			while (getline(ss, course, ',')) {
				courseData.push_back(course);
			}

			// Create new course and set tokens for course id and course title
			Course newCourse = Course();
			newCourse.courseId = courseData[0];
			newCourse.courseTitle = courseData[1];

			// If prereqs exist add to prerequisites vector
			if (courseData.size() > 2) {
				for (int i = 2; i < courseData.size(); i++) {
					newCourse.prerequisites.push_back(courseData[i]);
				}
			}
			// Add the new course into list
			courseList.push_back(newCourse);
		}

		cout << "Data loaded successfully!" << endl;
	}
	else {
		cout << "Error: File not found." << endl;
	}

	infile.close();
}

// Print Course List function
void PrintCourseList() {

	// Validating course data is loaded 
	if (courseList.size() > 0) {

		// Sorting the course list in alphanumeric order
		for (int i = 0; i < courseList.size() - 1; i++) {
			for (int j = 0; j < courseList.size() - i - 1; j++) {
				if (courseList[j].courseId > courseList[j + 1].courseId) {
					swap(courseList[j + 1], courseList[j]);
				}
			}
		}

		// Loop to print courses data in pre sorted order
		cout << "Here is a sample schedule: " << endl;
		cout << endl;
		for (int i = 0; i < courseList.size(); i++) {
			cout << courseList[i].courseId << ", ";
			cout << courseList[i].courseTitle << endl;
		}
		cout << endl;
	}
	else {
		cout << "Error: Please load course data first." << endl;

	}
}

// Print Course method
void PrintSearchedCourse() {

	// Validate data loaded from file
	if (courseList.size() > 0) {
		string courseInput;
		bool courseSearch = false;

		cout << "What course do you want to know about? ";
		cin >> courseInput;

		// Convert user input to uppercase so input wont be case senitive.
		transform(courseInput.begin(), courseInput.end(), courseInput.begin(), ::toupper);

		// Loop funtion to search for user input for match in vector courselist
		for (int i = 0; i < courseList.size(); i++) {
			if (courseList[i].courseId == courseInput) {
				// set courseSearch to true if course Id inputed by user is found courselist
				courseSearch = true;
				// Print course information for the searched course Id 
				cout << endl;
				cout << "Course Information" << endl;
				cout << endl;
				cout << courseList[i].courseId << ", ";
				cout << courseList[i].courseTitle << endl;
				cout << "Prerequisites: ";
				if (courseList[i].prerequisites.size() > 0) {
					int prereqSize = courseList[i].prerequisites.size();

					// Loop through course prerequisties if course has any prerequisties 
					for (int j = 0; j < prereqSize - 1; j++) {
						cout << courseList[i].prerequisites[j] << ", ";
					}
					// Eliminate comma from last entry
					cout << courseList[i].prerequisites[prereqSize - 1];
					cout << endl;

				}
				else {
					cout << "None" << endl;
				}

			}

		}

		// Course input validation
		if (courseSearch == false) {
			cout << "Invalid Course. Please enter valid course Id." << endl;
		}

	}
	else {
		cout << "Error: Course Data not found" << endl;

	}
}

// main function with calls to load, sort, and print functions 
int main() {

	// Using boolean variable for to stay in loop
	bool quit = false;

	// Program title
	cout << endl;
	cout << "Welcome to the course planner." << endl;

	do {
		string input;

		// Print User interface options
		cout << endl;
		cout << "  1. Load Data Structure." << endl;
		cout << "  2. Print Course List." << endl;
		cout << "  3. Print Course." << endl;
		cout << "  9. Exit" << endl;
		cout << endl;
		cout << "What would you like to do? ";
		cin >> input;
		cout << endl;

		// User input validation
		while ((input != "1") && (input != "2") && (input != "3") && (input != "9")) {

			cout << input << " is not a valid option." << endl;

			cout << endl;
			cout << "  1. Load Data Structure" << endl;
			cout << "  2. Print Sorted Course List" << endl;
			cout << "  3. Print Specific Course" << endl;
			cout << "  9. Exit" << endl;
			cout << endl;
			cout << "Please Chose an option? ";
			cin >> input;
			cout << endl;
		}

		// function calls for users input 
		if (input == "1") {
			LoadCourseData();
		}

		if (input == "2") {
			PrintCourseList();
		}

		if (input == "3") {
			PrintSearchedCourse();
		}

		if (input == "9") {
			cout << endl;
			cout << "Thank You for using the course planner!" << endl;
			exit(quit);
		}

	} while (!quit);

	return 0;
}