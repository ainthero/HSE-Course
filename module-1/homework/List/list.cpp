#include "list.h"

// Your code goes here...

using namespace task;

list::list() {
    begin = nullptr;
    end = nullptr;
    _size = 0;
}

list::list(size_t count, const int &value) : list() {
    for (size_t i = 0; i < count; i++) push_back(value);
}

list::list(const list &ref) : list() {
    *this = ref;
}

list::~list() {
    clear();
}

int &list::front() {
    return begin->val;
}

const int &list::front() const {
    return begin->val;
}

int &list::back() {
    return end->val;
}

const int &list::back() const {
    return end->val;
}

bool list::empty() const {
    return _size == 0;
}

size_t list::size() const {
    return _size;
}

void list::clear() {
    while (!empty()) pop_back();
    begin = nullptr;
    end = nullptr;
    _size = 0;
}

void list::push_back(const int &value) {
    if (_size == 0) {
        begin = new node{value, nullptr, nullptr};
        end = begin;
    } else {
        end->next = new node{value, end, nullptr};
        end = end->next;
    }
    ++_size;
}

void list::pop_back() {
    if (_size == 1) {
        delete begin;
        begin = end = nullptr;
    } else {
        end = end->prev;
        delete end->next;
        end->next = nullptr;
    }
    --_size;
}

void list::push_front(const int &value) {
    if (_size == 0) {
        begin = new node{value, nullptr, nullptr};
        end = begin;
    } else {
        begin->prev = new node{value, nullptr, begin};
        begin = begin->prev;
    }
    ++_size;
}

void list::pop_front() {
    if (_size == 1) {
        delete begin;
        begin = end = nullptr;
    } else {
        begin = begin->next;
        delete begin->prev;
        begin->prev = nullptr;
    }
    --_size;
}

void list::resize(size_t count) {
    list tmp(count, 0);
    tmp.swap(*this);
}

template<typename T>
void swap(T &a, T &b) {
    auto t = a;
    a = b;
    b = t;
}

void list::swap(list &other) {
    ::swap(begin, other.begin);
    ::swap(end, other.end);
    ::swap(_size, other._size);
}

void list::remove(const int &value) {
    auto val = value;//это надо потому что value по ссылке передают и оно может быть в листе
    while (!empty() && front() == value) pop_front();
    while (!empty() && back() == value) pop_back();
    if (_size <= 2) return;
    auto node_ptr = begin->next;
    while (node_ptr != end) {
        if (node_ptr->val == val) {
            auto tmp_ptr = node_ptr->next;
            node_ptr->prev->next = node_ptr->next;
            node_ptr->next->prev = node_ptr->prev;
            delete node_ptr;
            node_ptr = tmp_ptr;
            --_size;
        } else {
            node_ptr = node_ptr->next;
        }
    }
}


void list::unique() {
    if (_size <= 1) return;
    for (auto node_ptr = begin->next; node_ptr != end;) {
        if (node_ptr->val == node_ptr->prev->val) {
            auto tmp_ptr = node_ptr->next;
            node_ptr->prev->next = node_ptr->next;
            node_ptr->next->prev = node_ptr->prev;
            delete node_ptr;
            node_ptr = tmp_ptr;
            --_size;
        } else {
            node_ptr = node_ptr->next;
        }
    }
    if (end->val == end->prev->val) pop_back();
}

list &list::operator=(const list &other) {
    if (this == &other) return *this;
    clear();
    for (auto node_ptr = other.begin; node_ptr != nullptr; node_ptr = node_ptr->next) {
        push_back(node_ptr->val);
    }
    return *this;
}

void list::sort() {
    if (_size == 1) return;
    list left;
    for (int i = 0; i < _size / 2; i++) {
        left.push_back(front());
        pop_front();
    }
    left.sort();
    sort();
    list ans;
    while (!empty() && !left.empty()) {
        if (front() <= left.front()) {
            ans.push_back(front());
            pop_front();
        } else {
            ans.push_back(left.front());
            left.pop_front();
        }
    }
    while (!left.empty()) {
        ans.push_back(left.front());
        left.pop_front();
    }
    while (!empty()) {
        ans.push_back(front());
        pop_front();
    }
    *this = ans;
}

