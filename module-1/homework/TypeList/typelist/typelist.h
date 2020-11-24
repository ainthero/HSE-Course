#pragma once


struct NullType {
};

template<typename ...Args>
struct TypeList {
};


template<typename H, typename ...T>
struct TypeList<H, TypeList<T...>> {
    using Head = H;
    using Tail = TypeList<T...>;
};


template<typename H, typename T>
struct TypeList<H, T> {
    using Head = H;
    using Tail = T;
};
