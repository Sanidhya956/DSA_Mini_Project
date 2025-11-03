#include <iostream>
#include <string>
#include "ds.h"
using namespace std;

int main() {
    SubjectTree subjectTree;
    Stack nav;
    SubjectNode* currentSubject = NULL;
    TopicNode* currentTopic = NULL;
    string subject, topic, lesson;
    int choice;

    cout << "=== INTERACTIVE LEARNING NAVIGATOR ===\n";

    do {
        cout << "\n-----------------------------\n";
        cout << "1. Add Subject\n";
        cout << "2. Add Topic to Subject\n";
        cout << "3. Add Lesson to Topic\n";
        cout << "4. Show All Subjects\n";
        cout << "5. Show Topics & Lessons of a Subject\n";
        cout << "6. Navigate to Topic\n";
        cout << "7. Go Back\n";
        cout << "8. Show Navigation Path\n";
        cout << "9. Display Full Hierarchy\n";
        cout << "10. Exit\n";
        cout << "-----------------------------\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
        case 1:
            cout << "Enter subject name: ";
            getline(cin, subject);
            subjectTree.root = subjectTree.insert(subjectTree.root, subject);
            cout << "Subject \"" << subject << "\" added successfully!\n";
            break;

        case 2:
            cout << "Enter subject name: ";
            getline(cin, subject);
            currentSubject = subjectTree.search(subjectTree.root, subject);
            if (currentSubject == NULL)
                cout << "Subject not found!\n";
            else {
                cout << "Enter topic name: ";
                getline(cin, topic);
                currentSubject->topics.addTopic(topic);
            }
            break;

        case 3:
            cout << "Enter subject name: ";
            getline(cin, subject);
            currentSubject = subjectTree.search(subjectTree.root, subject);
            if (currentSubject == NULL)
                cout << "Subject not found!\n";
            else {
                cout << "Enter topic name: ";
                getline(cin, topic);
                currentTopic = currentSubject->topics.searchTopic(topic);
                if (currentTopic == NULL)
                    cout << "Topic not found!\n";
                else {
                    cout << "Enter lesson name: ";
                    getline(cin, lesson);
                    currentTopic->lessons.addLesson(lesson);
                }
            }
            break;

        case 4:
            cout << "\nSubjects:\n";
            subjectTree.inorder(subjectTree.root);
            break;

        case 5:
            cout << "Enter subject name: ";
            getline(cin, subject);
            currentSubject = subjectTree.search(subjectTree.root, subject);
            if (currentSubject == NULL)
                cout << "Subject not found!\n";
            else {
                cout << "\nSubject: " << subject << endl;
                currentSubject->topics.showTopicsAndLessons();
            }
            break;

        case 6:
            cout << "Enter subject name: ";
            getline(cin, subject);
            currentSubject = subjectTree.search(subjectTree.root, subject);
            if (currentSubject == NULL)
                cout << "Subject not found!\n";
            else {
                cout << "Enter topic to navigate: ";
                getline(cin, topic);
                currentTopic = currentSubject->topics.searchTopic(topic);
                if (currentTopic == NULL)
                    cout << "Topic not found!\n";
                else {
                    nav.push(subject);
                    nav.push(topic);
                    cout << "Now exploring: " << subject << " -> " << topic << endl;
                }
            }
            break;

        case 7:
            if (!nav.isEmpty()) {
                nav.pop();
                cout << "Moved back. Current: " << nav.peek() << endl;
            } else {
                cout << "Already at Home.\n";
            }
            break;

        case 8:
            nav.display();
            break;

        case 9:
            cout << "\n----- Full Hierarchical View -----\n";
            subjectTree.showAllHierarchy(subjectTree.root);
            break;

        case 10:
            cout << "Thank you for using the Navigator!\n";
            break;

        default:
            cout << "Invalid choice! Try again.\n";
        }
    } while (choice != 10);

    return 0;
}