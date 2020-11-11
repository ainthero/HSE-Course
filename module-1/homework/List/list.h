#pragma once

#include <cstddef>


namespace task {


    class list {

    public:

        list();

        explicit list(size_t count, const int &value = int());

        list(const list &ref);

        ~list();

        list &operator=(const list &other);


        int &front();

        const int &front() const;

        int &back();

        const int &back() const;


        bool empty() const;

        size_t size() const;

        void clear();


        void push_back(const int &value);

        void pop_back();

        void push_front(const int &value);

        void pop_front();

        void resize(size_t count);

        void swap(list &other);


        void remove(const int &value);

        void unique();

        void sort();

        // Your code goes here?..

    private:

        struct node {
            int val;
            node *prev;
            node *next;
        };

        node *begin;
        node *end;
        size_t _size;

    };

}  // namespace task
