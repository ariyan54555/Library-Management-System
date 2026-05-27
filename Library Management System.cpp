#include<bits/stdc++.h>
#include <fstream>
using namespace std;

struct Book {
    int id;
    string title;
    string author;
    bool available;
};

class Library {
private:
    vector<Book> books;

    bool isNumber(const string &s) {
        if (s.empty()) return false;
        for (char c : s) {
            if (!isdigit(c)) return false;
        }
        return true;
    }

    void sortBooks() {
        int n = books.size();
        for (int i = 0; i < n - 1; i++) {
            for (int j = 0; j < n - i - 1; j++) {
                if (books[j].id > books[j + 1].id) {
                    swap(books[j], books[j + 1]);
                }
            }
        }
    }

    int binarySearch(int id) {
        int left = 0, right = books.size() - 1;
        while (left <= right) {
            int mid = (left + right) / 2;
            if (books[mid].id == id) return mid;
            else if (books[mid].id < id) left = mid + 1;
            else right = mid - 1;
        }
        return -1;
    }

    void saveToFile() {
        ofstream file("library.txt");
        for (auto &b : books) {
            file << b.id << endl;
            file << b.title << endl;
            file << b.author << endl;
            file << b.available << endl;
        }
        file.close();
    }

    void loadFromFile() {
        ifstream file("library.txt");
        if (!file) return;

        books.clear();
        Book b;

        while (file >> b.id) {
            file.ignore();
            getline(file, b.title);
            getline(file, b.author);
            file >> b.available;
            file.ignore();
            books.push_back(b);
        }

        file.close();
        sortBooks();
    }

public:
    Library() {
        loadFromFile();
    }

    void addBook() {
        string input;
        int id;

        while (true) {
            cout << "Enter Book ID: ";
            getline(cin >> ws, input);

            if (!isNumber(input)) {
                cout << "Invalid input!\n";
                continue;
            }

            id = stoi(input);

            if (binarySearch(id) != -1) {
                cout << "ID already exists!\n";
                continue;
            }
            break;
        }

        string title, author;

        cout << "Enter Title: ";
        getline(cin >> ws, title);

        cout << "Enter Author: ";
        getline(cin >> ws, author);

        books.push_back({id, title, author, true});
        sortBooks();
        saveToFile();

        cout << "Book added successfully!\n";
    }

    void viewBooks() {
        if (books.empty()) {
            cout << "No books available!\n";
            return;
        }

        cout << "\n========== LIBRARY BOOK LIST ==========\n";
        for (auto &b : books) {
            cout << "ID: " << b.id
                 << " | " << b.title
                 << " | " << b.author
                 << " | "
                 << (b.available ? "Available" : "Checked Out")
                 << endl;
        }
        cout << "======================================\n";
    }

    void searchBook() {
        string input;
        int id;

        cout << "Enter ID: ";
        getline(cin >> ws, input);

        if (!isNumber(input)) {
            cout << "Invalid input!\n";
            return;
        }

        id = stoi(input);

        int i = binarySearch(id);

        if (i == -1) cout << "Book not found!\n";
        else {
            cout << "\nBook Found!\n";
            cout << "ID: " << books[i].id << endl;
            cout << "Title: " << books[i].title << endl;
            cout << "Author: " << books[i].author << endl;
        }
    }

    void checkoutBook() {
        string input;
        int id;

        cout << "Enter ID: ";
        getline(cin >> ws, input);

        if (!isNumber(input)) {
            cout << "Invalid input!\n";
            return;
        }

        id = stoi(input);
        int i = binarySearch(id);

        if (i == -1) cout << "Not found!\n";
        else if (!books[i].available) cout << "Already checked out!\n";
        else {
            books[i].available = false;
            saveToFile();
            cout << "Checked out!\n";
        }
    }

    void returnBook() {
        string input;
        int id;

        cout << "Enter ID: ";
        getline(cin >> ws, input);

        if (!isNumber(input)) {
            cout << "Invalid input!\n";
            return;
        }

        id = stoi(input);
        int i = binarySearch(id);

        if (i == -1) cout << "Not found!\n";
        else {
            books[i].available = true;
            saveToFile();
            cout << "Returned!\n";
        }
    }

    void deleteBook() {
        string input;
        int id;

        cout << "Enter ID: ";
        getline(cin >> ws, input);

        if (!isNumber(input)) {
            cout << "Invalid input!\n";
            return;
        }

        id = stoi(input);
        int i = binarySearch(id);

        if (i == -1) cout << "Not found!\n";
        else {
            books.erase(books.begin() + i);
            saveToFile();
            cout << "Deleted!\n";
        }
    }
};

// PIN SYSTEM
bool login() {
    string pin;
    const string correctPin = "6969";

    cout << "ENTER SECURITY PIN: ";
    getline(cin >> ws, pin);

    if (pin == correctPin) {
        cout << "Access Granted\n";
        return true;
    } else {
        cout << "Wrong PIN\n";
        return false;
    }
}

// MENU
void showMenu() {
    cout << "\n====================================\n";
    cout << "        LIBRARY SYSTEM MENU\n";
    cout << "====================================\n";
    cout << " 1. Add Book\n";
    cout << " 2. View All Books\n";
    cout << " 3. Search Book\n";
    cout << " 4. Checkout Book\n";
    cout << " 5. Return Book\n";
    cout << " 6. Delete Book\n";
    cout << " 7. Exit\n";
    cout << "====================================\n";
    cout << "Enter your choice: ";
}

int main() {
    if (!login()) return 0;

    Library lib;
    string input;
    int choice;

    while (true) {
        showMenu();

        getline(cin >> ws, input);

        if (input.length() == 1 && input[0] >= '1' && input[0] <= '7') {
            choice = input[0] - '0';
        } else { 
            cout << "Invalid input!\n";
            continue;
        }

        switch(choice) {
            case 1: lib.addBook(); break;
            case 2: lib.viewBooks(); break;
            case 3: lib.searchBook(); break;
            case 4: lib.checkoutBook(); break;
            case 5: lib.returnBook(); break;
            case 6: lib.deleteBook(); break;
            case 7: cout << "Goodbye!\n"; return 0;
        }
    }
}