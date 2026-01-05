#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <iomanip>
#include <algorithm>

using namespace std;

// Book class to represent a single book
class Book {
private:
    int bookID;
    string title;
    string author;
    string isbn;
    string genre;
    bool isAvailable;
    string borrowerName;
    time_t borrowDate;
    time_t dueDate;

public:
    // Constructor
    Book(int id, string t, string a, string isbn_val, string g)
        : bookID(id), title(t), author(a), isbn(isbn_val), genre(g),
          isAvailable(true), borrowerName(""), borrowDate(0), dueDate(0) {}

    // Getters
    int getBookID() const { return bookID; }
    string getTitle() const { return title; }
    string getAuthor() const { return author; }
    string getISBN() const { return isbn; }
    string getGenre() const { return genre; }
    bool getAvailability() const { return isAvailable; }
    string getBorrowerName() const { return borrowerName; }

    // Setters
    void borrowBook(string name, int days = 14) {
        isAvailable = false;
        borrowerName = name;
        borrowDate = time(0);
        dueDate = borrowDate + (days * 24 * 60 * 60); // days in seconds
    }

    void returnBook() {
        isAvailable = true;
        borrowerName = "";
        borrowDate = 0;
        dueDate = 0;
    }

    // Display book details
    void display() const {
        cout << "\n========================================" << endl;
        cout << "Book ID: " << bookID << endl;
        cout << "Title: " << title << endl;
        cout << "Author: " << author << endl;
        cout << "ISBN: " << isbn << endl;
        cout << "Genre: " << genre << endl;
        cout << "Status: " << (isAvailable ? "Available" : "Borrowed") << endl;
        
        if (!isAvailable) {
            cout << "Borrowed by: " << borrowerName << endl;
            cout << "Due Date: " << ctime(&dueDate);
        }
        cout << "========================================" << endl;
    }

    // Check if book is overdue
    bool isOverdue() const {
        if (isAvailable) return false;
        return time(0) > dueDate;
    }

    // Get days until due
    int getDaysUntilDue() const {
        if (isAvailable) return -1;
        int daysLeft = (dueDate - time(0)) / (24 * 60 * 60);
        return max(0, daysLeft);
    }
};

// Library class to manage all books
class Library {
private:
    vector<Book> books;
    int nextBookID;

public:
    // Constructor
    Library() : nextBookID(1001) {}

    // Add a new book to the library
    void addBook(string title, string author, string isbn, string genre) {
        books.push_back(Book(nextBookID++, title, author, isbn, genre));
        cout << "\n✓ Book added successfully! Book ID: " << (nextBookID - 1) << endl;
    }

    // Remove a book from the library
    bool removeBook(int bookID) {
        auto it = find_if(books.begin(), books.end(),
                         [bookID](const Book& b) { return b.getBookID() == bookID; });

        if (it != books.end()) {
            if (!it->getAvailability()) {
                cout << "\n✗ Cannot remove book. It's currently borrowed!" << endl;
                return false;
            }
            books.erase(it);
            cout << "\n✓ Book removed successfully!" << endl;
            return true;
        }

        cout << "\n✗ Book not found!" << endl;
        return false;
    }

    // Search for books by title
    void searchByTitle(string title) {
        vector<Book*> results;
        for (auto& book : books) {
            if (book.getTitle().find(title) != string::npos) {
                results.push_back(&book);
            }
        }

        if (results.empty()) {
            cout << "\n✗ No books found with that title!" << endl;
            return;
        }

        cout << "\nFound " << results.size() << " book(s):\n";
        for (auto book : results) {
            book->display();
        }
    }

    // Search for books by author
    void searchByAuthor(string author) {
        vector<Book*> results;
        for (auto& book : books) {
            if (book.getAuthor().find(author) != string::npos) {
                results.push_back(&book);
            }
        }

        if (results.empty()) {
            cout << "\n✗ No books found by that author!" << endl;
            return;
        }

        cout << "\nFound " << results.size() << " book(s):\n";
        for (auto book : results) {
            book->display();
        }
    }

    // Search for books by genre
    void searchByGenre(string genre) {
        vector<Book*> results;
        for (auto& book : books) {
            if (book.getGenre().find(genre) != string::npos) {
                results.push_back(&book);
            }
        }

        if (results.empty()) {
            cout << "\n✗ No books found in that genre!" << endl;
            return;
        }

        cout << "\nFound " << results.size() << " book(s):\n";
        for (auto book : results) {
            book->display();
        }
    }

    // Search for book by ID
    Book* findBookByID(int bookID) {
        for (auto& book : books) {
            if (book.getBookID() == bookID) {
                return &book;
            }
        }
        return nullptr;
    }

    // Borrow a book
    bool borrowBook(int bookID, string borrowerName) {
        Book* book = findBookByID(bookID);

        if (!book) {
            cout << "\n✗ Book not found!" << endl;
            return false;
        }

        if (!book->getAvailability()) {
            cout << "\n✗ Book is currently borrowed by: " << book->getBorrowerName() << endl;
            return false;
        }

        book->borrowBook(borrowerName);
        cout << "\n✓ Book borrowed successfully!" << endl;
        cout << "Return within 14 days to avoid late fees." << endl;
        return true;
    }

    // Return a book
    bool returnBook(int bookID) {
        Book* book = findBookByID(bookID);

        if (!book) {
            cout << "\n✗ Book not found!" << endl;
            return false;
        }

        if (book->getAvailability()) {
            cout << "\n✗ This book is not borrowed!" << endl;
            return false;
        }

        if (book->isOverdue()) {
            cout << "\n⚠ Warning: This book is overdue!" << endl;
            cout << "Late fees may apply!" << endl;
        }

        book->returnBook();
        cout << "\n✓ Book returned successfully!" << endl;
        return true;
    }

    // Check availability of a book
    void checkAvailability(int bookID) {
        Book* book = findBookByID(bookID);

        if (!book) {
            cout << "\n✗ Book not found!" << endl;
            return;
        }

        book->display();
    }

    // Display all books
    void displayAllBooks() const {
        if (books.empty()) {
            cout << "\n✗ No books in the library!" << endl;
            return;
        }

        cout << "\n========== ALL BOOKS IN LIBRARY ==========" << endl;
        for (const auto& book : books) {
            book.display();
        }
    }

    // Display only available books
    void displayAvailableBooks() const {
        vector<const Book*> available;
        for (const auto& book : books) {
            if (book.getAvailability()) {
                available.push_back(&book);
            }
        }

        if (available.empty()) {
            cout << "\n✗ No available books!" << endl;
            return;
        }

        cout << "\n========== AVAILABLE BOOKS ==========" << endl;
        for (const auto book : available) {
            book->display();
        }
    }

    // Display borrowed books
    void displayBorrowedBooks() const {
        vector<const Book*> borrowed;
        for (const auto& book : books) {
            if (!book.getAvailability()) {
                borrowed.push_back(&book);
            }
        }

        if (borrowed.empty()) {
            cout << "\n✗ No borrowed books!" << endl;
            return;
        }

        cout << "\n========== BORROWED BOOKS ==========" << endl;
        for (const auto book : borrowed) {
            book->display();
        }
    }

    // Display overdue books
    void displayOverdueBooks() const {
        vector<const Book*> overdue;
        for (const auto& book : books) {
            if (book.isOverdue()) {
                overdue.push_back(&book);
            }
        }

        if (overdue.empty()) {
            cout << "\n✓ No overdue books!" << endl;
            return;
        }

        cout << "\n========== OVERDUE BOOKS ==========" << endl;
        for (const auto book : overdue) {
            cout << "\nBook ID: " << book->getBookID() << endl;
            cout << "Title: " << book->getTitle() << endl;
            cout << "Borrowed by: " << book->getBorrowerName() << endl;
            cout << "Status: OVERDUE" << endl;
        }
    }

    // Get total number of books
    int getTotalBooks() const {
        return books.size();
    }

    // Get number of available books
    int getAvailableCount() const {
        int count = 0;
        for (const auto& book : books) {
            if (book.getAvailability()) count++;
        }
        return count;
    }

    // Get number of borrowed books
    int getBorrowedCount() const {
        int count = 0;
        for (const auto& book : books) {
            if (!book.getAvailability()) count++;
        }
        return count;
    }

    // Display library statistics
    void displayStatistics() const {
        cout << "\n========== LIBRARY STATISTICS ==========" << endl;
        cout << "Total Books: " << getTotalBooks() << endl;
        cout << "Available Books: " << getAvailableCount() << endl;
        cout << "Borrowed Books: " << getBorrowedCount() << endl;
        cout << "========================================" << endl;
    }
};

// Main menu function
void displayMenu() {
    cout << "\n========== LIBRARY MANAGEMENT SYSTEM ==========" << endl;
    cout << "1. Add a new book" << endl;
    cout << "2. Remove a book" << endl;
    cout << "3. Search books by title" << endl;
    cout << "4. Search books by author" << endl;
    cout << "5. Search books by genre" << endl;
    cout << "6. Check book availability" << endl;
    cout << "7. Borrow a book" << endl;
    cout << "8. Return a book" << endl;
    cout << "9. Display all books" << endl;
    cout << "10. Display available books" << endl;
    cout << "11. Display borrowed books" << endl;
    cout << "12. Display overdue books" << endl;
    cout << "13. Display library statistics" << endl;
    cout << "0. Exit" << endl;
    cout << "==============================================\n" << endl;
}

// Main function
int main() {
    Library library;
    int choice;
    string tempString;
    int tempInt;

    // Add some sample books
    library.addBook("The Great Gatsby", "F. Scott Fitzgerald", "978-0743273565", "Fiction");
    library.addBook("To Kill a Mockingbird", "Harper Lee", "978-0061120084", "Fiction");
    library.addBook("1984", "George Orwell", "978-0451524935", "Dystopian");
    library.addBook("Pride and Prejudice", "Jane Austen", "978-0141439518", "Romance");
    library.addBook("The Hobbit", "J.R.R. Tolkien", "978-0547928227", "Fantasy");
    library.addBook("C++ Primer", "Stanley Lippman", "978-0321714114", "Technical");
    library.addBook("Data Structures", "Mark Allen Weiss", "978-0132576277", "Technical");

    cout << "\n╔════════════════════════════════════════════════════╗" << endl;
    cout << "║   WELCOME TO LIBRARY MANAGEMENT SYSTEM             ║" << endl;
    cout << "║   Manage books, borrowing, and returns easily!     ║" << endl;
    cout << "╚════════════════════════════════════════════════════╝" << endl;

    while (true) {
        displayMenu();
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(); // Clear newline from input buffer

        switch (choice) {
        case 1: {
            // Add a new book
            cout << "\n--- Add New Book ---" << endl;
            cout << "Enter book title: ";
            getline(cin, tempString);
            string title = tempString;

            cout << "Enter author name: ";
            getline(cin, tempString);
            string author = tempString;

            cout << "Enter ISBN: ";
            getline(cin, tempString);
            string isbn = tempString;

            cout << "Enter genre: ";
            getline(cin, tempString);
            string genre = tempString;

            library.addBook(title, author, isbn, genre);
            break;
        }

        case 2: {
            // Remove a book
            cout << "\n--- Remove Book ---" << endl;
            cout << "Enter book ID to remove: ";
            cin >> tempInt;
            cin.ignore();
            library.removeBook(tempInt);
            break;
        }

        case 3: {
            // Search by title
            cout << "\n--- Search by Title ---" << endl;
            cout << "Enter book title to search: ";
            getline(cin, tempString);
            library.searchByTitle(tempString);
            break;
        }

        case 4: {
            // Search by author
            cout << "\n--- Search by Author ---" << endl;
            cout << "Enter author name to search: ";
            getline(cin, tempString);
            library.searchByAuthor(tempString);
            break;
        }

        case 5: {
            // Search by genre
            cout << "\n--- Search by Genre ---" << endl;
            cout << "Enter genre to search: ";
            getline(cin, tempString);
            library.searchByGenre(tempString);
            break;
        }

        case 6: {
            // Check availability
            cout << "\n--- Check Availability ---" << endl;
            cout << "Enter book ID: ";
            cin >> tempInt;
            cin.ignore();
            library.checkAvailability(tempInt);
            break;
        }

        case 7: {
            // Borrow a book
            cout << "\n--- Borrow a Book ---" << endl;
            cout << "Enter book ID: ";
            cin >> tempInt;
            cin.ignore();
            cout << "Enter borrower name: ";
            getline(cin, tempString);
            library.borrowBook(tempInt, tempString);
            break;
        }

        case 8: {
            // Return a book
            cout << "\n--- Return a Book ---" << endl;
            cout << "Enter book ID: ";
            cin >> tempInt;
            cin.ignore();
            library.returnBook(tempInt);
            break;
        }

        case 9: {
            // Display all books
            library.displayAllBooks();
            break;
        }

        case 10: {
            // Display available books
            library.displayAvailableBooks();
            break;
        }

        case 11: {
            // Display borrowed books
            library.displayBorrowedBooks();
            break;
        }

        case 12: {
            // Display overdue books
            library.displayOverdueBooks();
            break;
        }

        case 13: {
            // Display statistics
            library.displayStatistics();
            break;
        }

        case 0: {
            // Exit
            cout << "\n╔════════════════════════════════════════════════════╗" << endl;
            cout << "║   Thank you for using Library Management System!   ║" << endl;
            cout << "║   Goodbye!                                         ║" << endl;
            cout << "╚════════════════════════════════════════════════════╝" << endl;
            return 0;
        }

        default: {
            cout << "\n✗ Invalid choice! Please try again." << endl;
        }
        }
    }

    return 0;
}

/*
==============================================================================
                    LIBRARY MANAGEMENT SYSTEM - FEATURES
==============================================================================

BOOK CLASS:
-----------
- Stores book information: ID, Title, Author, ISBN, Genre
- Tracks availability status
- Manages borrowing details: borrower name, borrow date, due date
- Calculates if book is overdue
- Days until due calculation

LIBRARY CLASS:
--------------
- Manages collection of books
- Auto-generates unique Book IDs
- Add/Remove books from library
- Search functionality:
  * Search by title
  * Search by author
  * Search by genre
- Borrow/Return books
- View book availability
- Display functions:
  * All books
  * Available books only
  * Borrowed books only
  * Overdue books
- Library statistics
- Validation and error handling

KEY FEATURES:
-------------
1. Add Books: Input title, author, ISBN, and genre
2. Remove Books: Delete books (only if not borrowed)
3. Search: Find books by multiple criteria
4. Borrow: Checkout books with 14-day borrowing period
5. Return: Check in books with overdue detection
6. Availability: Check if books are available
7. Statistics: View library status at a glance
8. Overdue Tracking: Identify late returns
9. Error Handling: Proper validation for all operations
10. User-friendly Interface: Clear menus and messages

SAMPLE DATA:
-----------
- The Great Gatsby by F. Scott Fitzgerald
- To Kill a Mockingbird by Harper Lee
- 1984 by George Orwell
- Pride and Prejudice by Jane Austen
- The Hobbit by J.R.R. Tolkien
- C++ Primer by Stanley Lippman
- Data Structures by Mark Allen Weiss

COMPILATION:
-----------
g++ -std=c++11 -o library_system library_management_system.cpp
./library_system

OR (Windows):
g++ -std=c++11 -o library_system.exe library_management_system.cpp
library_system.exe

==============================================================================
*/
