#include "List.h"

using namespace std;

int main()
{
    List l;
    AIterator* it = new List::Iterator(l);
    it->start();
    l.addI(it, 1);
    l.addI(it, 2);
    it->start();
    it->next();
    cout << it->get()->data << endl;
    it->next();
    cout << it->get()->data << endl;
    cout << "\n Make empty";
    l.makeEmpty();
    cout << "\n isEmpty " << l.isEmpty() << endl;

    cout << "add" << endl;
    it->start();
    l.addI(it, 3);
    it->next();
    l.addI(it, 4);
    it->next();
    l.addI(it, 3);

    cout << "search" << endl;
    cout << l.searchFirst(3)->get()->data << endl;

    cout << "first" << endl;
    cout << l.first()->get()->data << endl;

    it->start();
    it->next();
    l.deleteI(it);

    cout << "first" << endl;
    cout << l.first()->get()->data << endl;
    cout << "List l" << endl;

    it = new List::Iterator(l);
    it->start();
    while (!it->finish())
    {
        it->next();
        cout << it->get()->data << endl;
    }

    List l1 = l;


    AIterator* i = new List::Iterator(l1);
    i->start();

    cout << "List l1" << endl;
    while (!i->finish())
    {
        i->next();
        cout << i->get()->data << endl;
    }
    cout << "end";
    return 0;
}