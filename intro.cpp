#include <iostream>
#include <string>
#include <stdexcept>
using namespace std;

#define MAX_ITEMS 100


class LibraryItem
{
private:   
    string title;
    string author;
    string dueDate;

public:
    LibraryItem(string t = "N/A", string a = "N/A", string d = "N/A")
    {
        title = t;
        author = a;
        dueDate = d;
    }

    string getTitle() const { return title; }
    string getAuthor() const { return author; }
    string getDueDate() const { return dueDate; }

    void setTitle(string newTitle)
    {
        if (newTitle.empty())
            throw runtime_error("Title cannot be empty!");
        title = newTitle;
    }

    void setAuthor(string newAuthor)
    {
        if (newAuthor.empty())
            throw runtime_error("Author cannot be empty!");
        author = newAuthor;
    }

    void setDueDate(string newDate)
    {
        dueDate = newDate;
    }

    virtual void checkOut() = 0;
    virtual void returnItem() = 0;
    virtual void displayDetails() const = 0;

    virtual ~LibraryItem() {}
};

class Book : public LibraryItem
{
private:
    string isbn;

public:
    Book(string t, string a, string d, string i)
        : LibraryItem(t, a, d)
    {
        if (i.length() < 5)
            throw runtime_error("ISBN must be minimum 5 characters!");
        isbn = i;
    }

    void checkOut() override
    {
        cout << "Book \"" << getTitle() << "\" checked out.\n";
    }

    void returnItem() override
    {
        cout << "Book \"" << getTitle() << "\" returned.\n";
    }

    void displayDetails() const override
    {
        cout << "\n--- BOOK ---\n";
        cout << "Title: " << getTitle() << endl;
        cout << "Author: " << getAuthor() << endl;
        cout << "Due Date: " << getDueDate() << endl;
        cout << "ISBN: " << isbn << endl;
    }
};

class DVD : public LibraryItem
{
private:
    int duration;

public:
    DVD(string t, string a, string d, int du)
        : LibraryItem(t, a, d)
    {
        if (du <= 0)
            throw runtime_error("Duration must be positive!");
        duration = du;
    }

    void checkOut() override
    {
        cout << "DVD \"" << getTitle() << "\" checked out.\n";
    }

    void returnItem() override
    {
        cout << "DVD \"" << getTitle() << "\" returned.\n";
    }

    void displayDetails() const override
    {
        cout << "\n--- DVD ---\n";
        cout << "Title: " << getTitle() << endl;
        cout << "Producer: " << getAuthor() << endl;
        cout << "Due Date: " << getDueDate() << endl;
        cout << "Duration: " << duration << " mins" << endl;
    }
};



class Magazine : public LibraryItem
{
private:
    int issueNumber;

public:
    Magazine(string t, string a, string d, int issue)
        : LibraryItem(t, a, d)
    {
        if (issue <= 0)
            throw runtime_error("Issue number must be positive!");
        issueNumber = issue;
    }

    void checkOut() override
    {
        cout << "Magazine \"" << getTitle() << "\" checked out.\n";
    }

    void returnItem() override
    {
        cout << "Magazine \"" << getTitle() << "\" returned.\n";
    }

    void displayDetails() const override
    {
        cout << "\n--- MAGAZINE ---\n";
        cout << "Title: " << getTitle() << endl;
        cout << "Publisher: " << getAuthor() << endl;
        cout << "Due Date: " << getDueDate() << endl;
        cout << "Issue Number: " << issueNumber << endl;
    }
};


class LibrarySystem
{
private:
    LibraryItem* items[MAX_ITEMS];
    int count;

public:
    LibrarySystem() { count = 0; }

    void addItem(LibraryItem* item)
    {
        if (count >= MAX_ITEMS)
        {
            cout << "Library full!\n";
            return;
        }

        items[count++] = item;
        cout << "Item added successfully!\n";
    }

    void displayAll()
    {
        if (count == 0)
        {
            cout << "No items in library.\n";
            return;
        }

        for (int i = 0; i < count; i++)
        {
            items[i]->displayDetails();
        }
    }

    void search(string title)
    {
        for (int i = 0; i < count; i++)
        {
            if (items[i]->getTitle() == title)
            {
                items[i]->displayDetails();
                return;
            }
        }
        cout << "Item not found.\n";
    }

    void checkout(string title)
    {
        for (int i = 0; i < count; i++)
        {
            if (items[i]->getTitle() == title)
            {
                items[i]->checkOut();
                return;
            }
        }
        cout << "Item not found.\n";
    }

    void returnItem(string title)
    {
        for (int i = 0; i < count; i++)
        {
            if (items[i]->getTitle() == title)
            {
                items[i]->returnItem();
                return;
            }
        }
        cout << "Item not found.\n";
    }

    ~LibrarySystem()
    {
        for (int i = 0; i < count; i++)
            delete items[i];
    }
};



int main()
{
    LibrarySystem lib;
    int choice;

    while (true)
    {
        cout << "\n========== LIBRARY MENU ==========\n";
        cout << "1. Add Item\n";
        cout << "2. View All Items\n";
        cout << "3. Search Item\n";
        cout << "4. Check Out Item\n";
        cout << "5. Return Item\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        try
        {
            if (choice == 1)
            {
                int type;
                cout << "\nSelect Type:\n";
                cout << "1. Book\n";
                cout << "2. DVD\n";
                cout << "3. Magazine\n";
                cout << "Enter: ";
                cin >> type;

                string t, a, d;
                cout << "Title: ";
                cin >> t;
                cout << "Author/Producer: ";
                cin >> a;
                cout << "Due Date: ";
                cin >> d;

                if (type == 1)
                {
                    string isbn;
                    cout << "ISBN: ";
                    cin >> isbn;
                    lib.addItem(new Book(t, a, d, isbn));
                }
                else if (type == 2)
                {
                    int duration;
                    cout << "Duration: ";
                    cin >> duration;
                    lib.addItem(new DVD(t, a, d, duration));
                }
                else if (type == 3)
                {
                    int issue;
                    cout << "Issue Number: ";
                    cin >> issue;
                    lib.addItem(new Magazine(t, a, d, issue));
                }
                else
                {
                    cout << "Invalid type!\n";
                }
            }

            else if (choice == 2)
                lib.displayAll();

            else if (choice == 3)
            {
                string key;
                cout << "Enter Title: ";
                cin >> key;
                lib.search(key);
            }

            else if (choice == 4)
            {
                string key;
                cout << "Enter Title: ";
                cin >> key;
                lib.checkout(key);
            }

            else if (choice == 5)
            {
                string key;
                cout << "Enter Title: ";
                cin >> key;
                lib.returnItem(key);
            }

            else if (choice == 6)
            {
                cout << "Exiting...\n";
                break;
            }

            else
                cout << "Invalid choice!\n";
        }

        catch (exception &e)
        {
            cout << "Error: " << e.what() << endl;
        }
        catch (...)
        {
            cout << "Unknown error occurred!\n";
        }
    }

    return 0;
}
