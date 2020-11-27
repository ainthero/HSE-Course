#pragma once

#include "typelist.h"

template<typename TList, typename OldType, typename NewType>
struct Replace;


template<typename ...TList, typename OldType, typename NewType>
struct Replace<TypeList<OldType, TypeList<TList...>>, OldType, NewType> {
    using NewTypeList = TypeList<NewType, typename Replace<TypeList<TList...>, OldType, NewType>::NewTypeList>;
};

template<typename ...TList, typename OldType, typename NewType>
struct Replace<TypeList<TList...>, OldType, NewType> {
    using CurrentHead = typename TypeList<TList...>::Head;
    using CurrentTail = typename TypeList<TList...>::Tail;
    using NewTypeList = TypeList<CurrentHead, typename Replace<CurrentTail, OldType, NewType>::NewTypeList>;
};

template<typename OldType, typename NewType>
struct Replace<TypeList<OldType, NullType>, OldType, NewType> {
    using NewTypeList = TypeList<NewType, NullType>;
};

template<typename TList, typename OldType, typename NewType>
struct Replace<TypeList<TList, NullType>, OldType, NewType> {
    using NewTypeList = TypeList<TList, NullType>;
};

template<typename OldType, typename NewType>
struct Replace<NullType, OldType, NewType> {
    using NewTypeList = NullType;
};

