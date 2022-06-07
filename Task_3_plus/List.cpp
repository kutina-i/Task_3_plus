#include "List.h"

List::List() : count(0)
{
    buffer = new Node;
    buffer->next = buffer;
    buffer->prev = buffer;
    buffer->data = -1;
}

List::List(const List& list) : buffer(new Node), count(list.count)
{
    buffer = new Node;
    const Node* tmp = list.buffer->next;
    Node* p = buffer;
    Node* n;
    while (tmp != list.buffer)
    {
        n = new Node;
        p->next = n;
        n->prev = p;
        n->data = tmp->data;
        p = p->next;
        tmp = tmp->next;
    }
    buffer->prev = p;
    p->next = buffer;
}
List::List(List&& obj) :buffer(obj.buffer), count(obj.count)
{
    obj.buffer = nullptr;
    obj.count = 0;
}

List::~List()
{
    if (!isEmpty())
    {
        makeEmpty();
    }
    delete buffer;
    buffer = nullptr;
}

List::Iterator::Iterator(const List& list) { buf = list.getBuffer(); count = list.getCount(); }

//начать работу
void List::Iterator::start()
{
    p = buf;
    index = -1;
}
//проверка, все ли проитерировано
bool List::Iterator::finish() const
{
    return index >= count - 1;
}
//сдвинуть итератор на следующий элемент
void List::Iterator::next()
{
    p = p->next;
    index++;
}

//получить очередной элемент
Node* List::Iterator::get()
{
    return p;
}

//вставить элемент в позицию, отмеченную итератором
void List::addI(AIterator* index, int v)
{
    Node* tmp = new Node;
    if (count == 0) {
        tmp->next = buffer;
        tmp->prev = buffer;
        tmp->data = v;
        buffer->next = tmp;
        buffer->prev = tmp;
        count++;
    }
    else
    {
        Node* k = index->get();
        k->next->prev = tmp;
        tmp->next = k->next;
        tmp->prev = k;
        tmp->data = v;
        k->next = tmp;
        count++;
    }
}

//удалить элемент, отмеченный итератором
void List::deleteI(AIterator* index)
{
    Node* p = index->get();
    p->next->prev = p->prev;
    p->prev->next = p->next;
    delete p;
    count--;
}

Node* List::getBuffer() const
{
    return buffer;
}

//найти первое вхождение элемента в список, результат – итератор на найденный элемент
AIterator* List::searchFirst(int n)  const
{
    Node* p = buffer->next;
    int i = 0;
    while (p != buffer)
    {
        i++;
        if (p->data == n)
        {
            break;
        }
        p = p->next;
    }
    if (p == buffer)
    {
        return nullptr;
    }
    AIterator* it = new Iterator(*this);
    it->start();
    for (int j = 0; j < i; j++)
    {
        it->next();
    }
    return it;
}

//количество элементов в списке
int List::getCount() const
{
    return count;
}

//сделать список пустым
void List::makeEmpty()
{
    Node* tmp = buffer;
    Node* n = nullptr;
    while (tmp->next != buffer)
    {
        tmp = tmp->next;
        delete n;
        n = tmp;
        count--;
    }
    delete n;
}

//проверка на пустоту
bool List::isEmpty() const
{
    return count == 0;
}

//получить итератор на первый элемент списка
AIterator* List::first() const
{
    AIterator* it = new Iterator(*this);
    it->start();
    it->next();
    return it;
}

List& List::operator=(const List& obj)
{
    if (this != &obj)
    {
        buffer = new Node;
        const Node* tmp = obj.buffer->next;
        Node* p = buffer;
        Node* n;
        while (tmp != obj.buffer)
        {
            n = new Node;
            p->next = n;
            n->prev = p;
            n->data = tmp->data;
            p = p->next;
            tmp = tmp->next;
        }
        buffer->prev = p;
        p->next = buffer;
    }
    return *this;
}

List List::operator=(List&& obj)
{
    if (this != &obj)
    {
        makeEmpty();
        buffer = obj.buffer;
        count = obj.count;
        obj.buffer = nullptr;
        obj.count = 0;
    }
    return *this;
}
