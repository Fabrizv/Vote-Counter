#ifndef HEADER_FILE_NAME
#define HEADER_FILE_NAME

#include <iostream>
#include <string>


template <typename t1, typename t2>
class hashMap
{
public:
    struct hashPair
    {
        t1 key;
        t2 value;
        hashPair * link;
    };

    struct iteratorPair
    {
        t1 * key;
        t2 * value;
        iteratorPair * link;
    };

    class iterator
    {
    public:
        friend class hashMap;
        iterator ();
        const iterator& operator ++(int);
        bool operator ==( const iterator &) const;
        bool operator !=( const iterator &) const;
        t1 first ();
        t2 second ();
    private:
        iterator(iteratorPair *);
        iteratorPair * element;
    };

    hashMap ();
    ~hashMap ();
    t2& operator [](t1);
    iterator begin () const;
    iterator end() const;
private:
    void resize ();
    int h(std:: string) const;
    int items;
    int size;
    hashPair ** table;
    iteratorPair * head;
};

// Default constructor
hashMap<t1, t2>::hashMap()
{
    size = 5;
    items = 0;
    head = NULL;
    table = new hashPair*[size];

    for (int i = 0; i < size; i++)
        table[i] = NULL;
}

// Destructor
hashMap<t1, t2>::~hashMap()
{
    for (int i = 0; i < size; i++)
    {
        delete table[i];
        table[i] = NULL;
    }

    delete table;
    table = NULL;

    iteratorPair * del;
    while (head != NULL)
    {
        del = head;
        head = head->link;
        delete del;
        del = NULL;
    }
}

#endif
