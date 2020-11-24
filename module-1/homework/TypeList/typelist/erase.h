#pragma once

#include "typelist.h"

template<typename TList, typename TargetType>
struct Erase;

template<typename TargetType, typename ...TList>
struct Erase<TypeList<TList...>, TargetType> {
    using CurrentHead = typename TypeList<TList...>::Head;
    using CurrentTail = typename TypeList<TList...>::Tail;
    using NewTypeList = TypeList<CurrentHead, typename Erase<CurrentTail, TargetType>::NewTypeList>;
};

template<typename TargetType, typename ...TList>
struct Erase<TypeList<TargetType, TypeList<TList...>>, TargetType> {
    using NewTypeList = TypeList<TList...>;
};

template<typename TargetType>
struct Erase<TypeList<TargetType, NullType>, TargetType> {
    using NewTypeList = NullType;
};

template<typename TargetType>
struct Erase<NullType, TargetType> {
    using NewTypeList = NullType;
};