#pragma once

#include "eraseall.h"
#include "typelist.h"

template<typename TList>
struct NoDuplicates;

template<typename ...TList>
struct NoDuplicates<TypeList<TList...>> {
    using CurrentHead = typename TypeList<TList...>::Head;
    using CurrentTail = typename TypeList<TList...>::Tail;
    using ErasedTail = typename EraseAll<CurrentTail, CurrentHead>::NewTypeList;
    using NewTypeList = TypeList<CurrentHead, typename NoDuplicates<ErasedTail>::NewTypeList>;
};

template<typename TList>
struct NoDuplicates<TypeList<TList, NullType>> {
    using NewTypeList = TypeList<TList, NullType>;
};

template<>
struct NoDuplicates<NullType> {
    using NewTypeList = NullType;
};