#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

class Student {
public:
    int id;
    std::string name;
    int biology;
    int physics;
    int chemistry;
    int totalMarks;

    void calculateTotalMarks() {
        totalMarks = biology + physics + chemistry;
    }
};

void writeStudentDataToFile(const Student& student, const std::string& stream) {
    std::ofstream outFile(stream + "_students.txt", std::ios::app);
    outFile << student.id << " " << student.name << " " << student.biology << " " << student.physics << " " << student.chemistry << std::endl;
    outFile.close();
}

Student readStudentDataFromFile(const std::string& stream) {
    Student student;
    std::ifstream inFile(stream + "_students.txt");
    inFile >> student.id >> student.name >> student.biology >> student.physics >> student.chemistry;
    inFile.close();
    return student;
}

void calculateTotalMarksAndRanking(std::vector<Student>& students) {
    for (auto& student : students) {
        student.calculateTotalMarks();
    }

    // Sort students by total marks in descending order
    std::sort(students.begin(), students.end(), [](const Student& a, const Student& b) {
        return a.totalMarks > b.totalMarks;
    });

    // Assign ranks
    for (size_t i = 0; i < students.size(); ++i) {
        students[i].totalMarks = i + 1; // This can be used as the rank
    }
}

void printRanks(const Student& student, const std::string& stream) {
    std::cout << "Student ID: " << student.id << " | Name: " << student.name
              << " | Total Marks: " << student.totalMarks << " | Stream: " << stream << std::endl;
}

void writeRanksToFile(const Student& student, const std::string& stream) {
    std::ofstream outFile(stream + "_ranks.txt", std::ios::app);
    outFile << "Student ID: " << student.id << " | Name: " << student.name
            << " | Total Marks: " << student.totalMarks << " | Stream: " << stream << std::endl;
    outFile.close();
}

int main() {
    std::vector<Student> bioStudents;
    std::vector<Student> mathStudents;

    // Assume you have read student data from somewhere and populated the vectors
    // ...

    calculateTotalMarksAndRanking(bioStudents);
    calculateTotalMarksAndRanking(mathStudents);

    for (const auto& bioStudent : bioStudents) {
        printRanks(bioStudent, "Bio");
        writeRanksToFile(bioStudent, "Bio");
    }

    for (const auto& mathStudent : mathStudents) {
        printRanks(mathStudent, "Math");
        writeRanksToFile(mathStudent, "Math");
    }

    return 0;
}
