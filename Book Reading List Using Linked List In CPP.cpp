#include <iostream>
#include <string>
using namespace std;

struct Node
{
    string bookName;
    Node *next;
};

// Add a book
void addBook(Node *&head)
{
    string name;

    cout << "Enter book name: ";
    cin.ignore();
    getline(cin, name);

    Node *newNode = new Node;
    newNode->bookName = name;
    newNode->next = NULL;

    if (head == NULL)
    {
        head = newNode;
    }
    else
    {
        Node *temp = head;

        while (temp->next != NULL)
        {
            temp = temp->next;
        }

        temp->next = newNode;
    }

    cout << "Book added successfully!" << endl;
}

// Display all books
void displayBooks(Node *head)
{
    if (head == NULL)
    {
        cout << "Reading list is empty." << endl;
        return;
    }

    Node *temp = head;
    int count = 1;

    cout << "\n===== BOOK READING LIST =====" << endl;

    while (temp != NULL)
    {
        cout << count << ". " << temp->bookName << endl;
        temp = temp->next;
        count++;
    }
}

// Search for a book
void searchBook(Node *head)
{
    string name;

    cout << "Enter book name to search: ";
    cin.ignore();
    getline(cin, name);

    Node *temp = head;

    while (temp != NULL)
    {
        if (temp->bookName == name)
        {
            cout << "Book found in the reading list!" << endl;
            return;
        }

        temp = temp->next;
    }

    cout << "Book not found." << endl;
}

// Delete a book
void deleteBook(Node *&head)
{
    string name;

    cout << "Enter book name to delete: ";
    cin.ignore();
    getline(cin, name);

    if (head == NULL)
    {
        cout << "Reading list is empty." << endl;
        return;
    }

    Node *temp = head;
    Node *prev = NULL;

    while (temp != NULL && temp->bookName != name)
    {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL)
    {
        cout << "Book not found." << endl;
        return;
    }

    if (prev == NULL)
    {
        head = head->next;
    }
    else
    {
        prev->next = temp->next;
    }

    delete temp;

    cout << "Book deleted successfully!" << endl;
}

// Count books
void countBooks(Node *head)
{
    int count = 0;
    Node *temp = head;

    while (temp != NULL)
    {
        count++;
        temp = temp->next;
    }

    cout << "Total number of books: " << count << endl;
}

// Main function
int main()
{
    Node *head = NULL;
    int choice;

    do
    {
        cout << "\n========== BOOK READING LIST ==========" << endl;
        cout << "1. Add Book" << endl;
        cout << "2. Display Books" << endl;
        cout << "3. Search Book" << endl;
        cout << "4. Delete Book" << endl;
        cout << "5. Count Books" << endl;
        cout << "6. Exit" << endl;

        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            addBook(head);
            break;

        case 2:
            displayBooks(head);
            break;

        case 3:
            searchBook(head);
            break;

        case 4:
            deleteBook(head);
            break;

        case 5:
            countBooks(head);
            break;

        case 6:
            cout << "Thank you for using Book Reading List!" << endl;
            break;

        default:
            cout << "Invalid choice. Please try again." << endl;
        }

    } while (choice != 6);

    return 0;
}