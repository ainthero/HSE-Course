#pragma once

#include "typelist.h"

template<typename TList, typename TargetType>
struct EraseAll;

template<typename TargetType, typename ...TList>
struct EraseAll<TypeList<TList...>, TargetType> {
    using CurrentHead = typename TypeList<TList...>::Head;
    using CurrentTail = typename TypeList<TList...>::Tail;
    using NewTypeList = TypeList<CurrentHead, typename EraseAll<CurrentTail, TargetType>::NewTypeList>;
};

template<typename TargetType, typename ...TList>
struct EraseAll<TypeList<TargetType, TypeList<TList...>>, TargetType> {
    using NewTypeList = typename EraseAll<TypeList<TList...>, TargetType>::NewTypeList;
};

template<typename TargetType>
struct EraseAll<TypeList<TargetType, NullType>, TargetType> {
    using NewTypeList = NullType;
};

template<typename TargetType>
struct EraseAll<NullType, TargetType> {
    using NewTypeList = NullType;
};