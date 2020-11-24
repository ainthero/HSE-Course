#pragma once

#include "typelist.h"
#include "length.h"

template<typename TList, typename TargetType>
struct IndexOf;

template<typename TargetType, typename ...TList>
struct IndexOf<TypeList<TargetType, TypeList<TList...>>, TargetType> {
    static const unsigned int pos = 0;
};

template<typename TargetType, typename ...TList>
struct IndexOf<TypeList<TList...>, TargetType> {
    static const unsigned int tmp = IndexOf<typename TypeList<TList...>::Tail, TargetType>::pos;
    static const unsigned int pos = (1 + tmp == Length<TypeList<TList...>>::length) ? -1 : (1 + tmp);
};

template<typename TList, typename TargetType>
struct IndexOf<TypeList<TList, NullType>, TargetType> {
    static const unsigned int pos = 1;
};

template<typename TargetType>
struct IndexOf<TypeList<TargetType, NullType>, TargetType> {
    static const unsigned int pos = 0;
};

template<typename TargetType>
struct IndexOf<NullType, TargetType> {
    static const unsigned int pos = -1;
};

