#pragma once

#include "typelist.h"

template<typename NewType, typename ...TList>
struct Append;

template<typename NewType, typename ...TList>
struct Append<TypeList<TList...>, NewType> {
    using CurrentHead = typename TypeList<TList...>::Head;
    using CurrentTail = typename TypeList<TList...>::Tail;
    using NewTypeList = TypeList<CurrentHead, typename Append<CurrentTail, NewType>::NewTypeList>;
};

template<typename NewType>
struct Append<NullType, NewType> {
    using NewTypeList = TypeList<NewType, NullType>;
};

template<typename ...TList>
struct Append<TypeList<TList...>, NullType> {
    using NewTypeList = TypeList<TList...>;
};

template<>
struct Append<NullType, NullType> {
    using NewTypeList = NullType;
};


