#pragma once
#include <iostream>


struct Node
{
    Node* prev;
    Node* next;
    int data;
};

class AIterator
{
public:
    virtual void start() = 0;
    virtual Node* get() = 0;
    virtual void next() = 0;
    virtual bool finish() const = 0;
};
class AList {
protected:
    int count;
    Node* buffer;
public:
    virtual Node* getBuffer() const = 0;
    virtual void addI(AIterator* index, int v) = 0;
    virtual void deleteI(AIterator* index) = 0;
    virtual AIterator* searchFirst(int n) const = 0;
    virtual void makeEmpty() = 0;
    virtual bool isEmpty() const = 0;
    virtual int getCount() const = 0;
    virtual const AIterator* first() const = 0;
};

class List : public AList
{
private:
    int count;
    Node* buffer;

public:
    class Iterator : public AIterator
    {
    private:
        int index;
        int count;
        Node* buf;
        Node* p;
    public:
        Iterator(const List& list);
        void start()  override;
        bool finish() const override;
        void next() override;
        Node* get() override;
    };

    List();
    List(const List& list);
    List(List&& obj);
    ~List();

    void addI(AIterator* const index, int v) override;
    void deleteI(AIterator* const index) override;
    Node* getBuffer() const override;
    AIterator* searchFirst(int n) const override;
    int getCount() const override;
    void makeEmpty() override;
    bool isEmpty() const override;
    AIterator* first() const override;
    List& operator=(const List& obj);
    List operator =(List&& obj);

};