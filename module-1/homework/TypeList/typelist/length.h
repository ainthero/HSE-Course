#pragma once

#include "typelist.h"

template<typename Head>
struct Length{
    static const int length = 1;
};

template<typename ...TList>
struct Length<TypeList<TList...>> {
    static const int length = Length<typename TypeList<TList...>::Tail>::length + 1;
};

template<>
struct Length<NullType> {
    static const int length = 0;
};