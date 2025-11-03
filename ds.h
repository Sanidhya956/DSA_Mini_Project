#include <iostream>
#include <string>
using namespace std;

// ---------------- STACK ----------------
class Stack {
    int top;
    string arr[50];
public:
    Stack() { top = -1; }

    void push(string x) {
        if (top == 49)
            cout << "Stack Overflow!\n";
        else
            arr[++top] = x;
    }

    void pop() {
        if (top == -1)
            cout << "Already at Home.\n";
        else
            top--;
    }

    string peek() {
        if (top == -1)
            return "Home";
        return arr[top];
    }

    bool isEmpty() {
        return top == -1;
    }

    void display() {
        if (top == -1)
            cout << "At Home.\n";
        else {
            cout << "Navigation Path: ";
            for (int i = 0; i <= top; i++)
                cout << arr[i] << " -> ";
            cout << "Current\n";
        }
    }
};

// ---------------- LESSON LINKED LIST ----------------
struct LessonNode {
    string lesson;
    LessonNode* next;
};

class LessonList {
    LessonNode* head;
public:
    LessonList() { head = NULL; }

    void addLesson(string name) {
        LessonNode* n = new LessonNode;
        n->lesson = name;
        n->next = NULL;

        if (head == NULL)
            head = n;
        else {
            LessonNode* temp = head;
            while (temp->next != NULL)
                temp = temp->next;
            temp->next = n;
        }
        cout << "Lesson \"" << name << "\" added successfully!\n";
    }

    void showLessons() {
        if (head == NULL)
            cout << "   No lessons yet.\n";
        else {
            LessonNode* temp = head;
            while (temp != NULL) {
                cout << "      - " << temp->lesson << endl;
                temp = temp->next;
            }
        }
    }
};

// ---------------- TOPIC LINKED LIST ----------------
struct TopicNode {
    string topic;
    TopicNode* next;
    LessonList lessons;
};

class TopicList {
    TopicNode* head;
public:
    TopicList() { head = NULL; }

    void addTopic(string name) {
        TopicNode* n = new TopicNode;
        n->topic = name;
        n->next = NULL;

        if (head == NULL)
            head = n;
        else {
            TopicNode* temp = head;
            while (temp->next != NULL)
                temp = temp->next;
            temp->next = n;
        }
        cout << "Topic \"" << name << "\" added successfully!\n";
    }

    TopicNode* searchTopic(string name) {
        TopicNode* temp = head;
        while (temp != NULL) {
            if (temp->topic == name)
                return temp;
            temp = temp->next;
        }
        return NULL;
    }

    void showTopicsAndLessons() {
        if (head == NULL)
            cout << " No topics added yet.\n";
        else {
            TopicNode* temp = head;
            while (temp != NULL) {
                cout << " - Topic: " << temp->topic << endl;
                temp->lessons.showLessons();
                temp = temp->next;
            }
        }
    }
};

// ---------------- SUBJECT TREE ----------------
struct SubjectNode {
    string subject;
    TopicList topics;
    SubjectNode* left;
    SubjectNode* right;
};

class SubjectTree {
public:
    SubjectNode* root;
    SubjectTree() { root = NULL; }

    SubjectNode* createNode(string name) {
        SubjectNode* n = new SubjectNode;
        n->subject = name;
        n->left = n->right = NULL;
        return n;
    }

    SubjectNode* insert(SubjectNode* r, string name) {
        if (r == NULL)
            r = createNode(name);
        else if (name < r->subject)
            r->left = insert(r->left, name);
        else
            r->right = insert(r->right, name);
        return r;
    }

    SubjectNode* search(SubjectNode* r, string name) {
        if (r == NULL || r->subject == name)
            return r;
        if (name < r->subject)
            return search(r->left, name);
        else
            return search(r->right, name);
    }

    void inorder(SubjectNode* r) {
        if (r != NULL) {
            inorder(r->left);
            cout << " - " << r->subject << endl;
            inorder(r->right);
        }
    }

    void showAllHierarchy(SubjectNode* r) {
        if (r != NULL) {
            showAllHierarchy(r->left);
            cout << "\nSubject: " << r->subject << endl;
            r->topics.showTopicsAndLessons();
            showAllHierarchy(r->right);
        }
    }
};