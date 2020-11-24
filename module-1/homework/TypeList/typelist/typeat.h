#pragma once

#include "typelist.h"

template<typename TList, unsigned int index>
struct TypeAt;

template<typename ...TList, unsigned int index>
struct TypeAt<TypeList<TList...>, index> {
    using TargetType = typename TypeAt<typename TypeList<TList...>::Tail, index - 1>::TargetType;
};

template<typename ...TList>
struct TypeAt<TypeList<TList...>, 0> {
    using TargetType = typename TypeList<TList...>::Head;
};