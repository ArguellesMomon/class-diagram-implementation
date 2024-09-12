#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Book {
public:
    string title;
    string author;
    int year;

    void Details() {
        cout << "Title  " << "   Author  " << "  Year" <<endl;
        cout << title << "    " << author << "    "<< year << endl;
    }
};

class Library {
private:
    vector<Book> books;

public:
    void addBook() {
    Book newBook;
    cout << "Enter book title: ";
    cin.ignore(); 
    getline(cin, newBook.title); 
    cout << "Enter book author: ";
    getline(cin, newBook.author); 
    cout << "Enter publication year: ";
    cin >> newBook.year;

    books.push_back(newBook);
    cout << "Book added successfully!" << endl;
}

    void displayBooks() {
        if (books.empty()) {
            cout << "No books in the library." << endl;
        } else {
            cout << "Book List:" << endl;
            for (Book book : books) {
                book.Details();
            }
        }
    }

    void searchBook() {
        string searchTitle;
        cout << "Enter a book to search";
        cin >> searchTitle;

        bool found = false;
        for (Book book : books) {
            if (book.title == searchTitle) {
                cout << "Book found!" << endl;
                book.Details();
                found = true;
                break;
            }
        }

        if (!found) {
            cout << "Book not found!" << endl;
        }
    }
};

int main() {
    Library library;
    int choice;

    do {
        cout << "\nWelcome to the Online Library Sysytem!\nWhere we help you with your books!\n";
        cout << "Menu:\n";
        cout << "1. Add a book\n";
        cout << "2. Display all books\n";
        cout << "3. Search for a book by title\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                    system("pause");
                    system("cls");
                library.addBook();
                    system("pause");
                    system("cls");
                break;
            case 2:
                    system("pause");
                    system("cls");
                library.displayBooks();
                    system("pause");
                    system("cls");
                break;
            case 3:
                    system("pause");
                    system("cls");
                library.searchBook();
                break;
                    system("pause");
                    system("cls");
            case 4:
                cout << "Exiting the program. Goodbye!";
                break;
            default:
                cout << "Invalid choice. Please try again." <<endl;
                    system("pause");
                    system("cls");
        }

    } while (choice != 4);

    return 0;
}
