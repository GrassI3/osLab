#include <iostream>
#include <string>
using namespace std;
int mutex = 1, full = 0, _empty, in = 0, out = 0, counter = 0;
int buffer_size;
string buffer[100];
int signal(int S)
{
    return ++S;
}
int wait(int S)
{
    if (S <= 0)
    {
        cout << "\nOperation cannot proceed (resource unavailable).\n";
        return S;
    }
    return --S;
}
void produce()
{
    if (_empty <= 0)
    {
        cout << "\nBuffer is full. Cannot produce more items.\n";
        return;
    }
    mutex = wait(mutex);
    string next_prod;
    cout << "Enter an item to produce: ";
    cin >> next_prod;
    buffer[in] = next_prod;
    in = (in + 1) % buffer_size;
    counter++;
    cout << "Item produced: " << next_prod << endl;
    mutex = signal(mutex);
    full = signal(full);
    _empty--;
}
void consume()
{
    if (full <= 0)
    {
        cout << "\nBuffer is empty. Nothing to consume.\n";
        return;
    }
    mutex = wait(mutex);
    string next_cons = buffer[out];
    out = (out + 1) % buffer_size;
    counter--;
    cout << "Item consumed: " << next_cons << endl;
    mutex = signal(mutex);
    _empty = signal(_empty);
    full--;
}
void showBuffer()
{
    if (counter == 0)
    {
        cout << "Buffer is empty.\n";
    }
    else
    {
        cout << "Buffer contents: ";
        int idx = out;
        for (int i = 0; i < counter; i++)
        {
            cout << buffer[idx] << " ";
            idx = (idx + 1) % buffer_size;
        }
        cout << endl;
    }
}
int main()
{
    int choice;
    cout << "Enter buffer size: ";
    cin >> buffer_size;
    _empty = buffer_size;
    do
    {
        cout << "\n1. Produce\n";
        cout << "2. Consume\n";
        cout << "3. Show buffer status\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice)
        {
        case 1: produce();
            break;
        case 2: consume();
            break;
        case 3: showBuffer();
            break;
        case 4:cout << "Exiting program...\n";
            break;
        default:
            cout << "Invalid choice! Try again.\n";
        }
    } while (choice != 4);
    return 0;
}