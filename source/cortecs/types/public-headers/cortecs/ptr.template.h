#ifndef TYPE_PARAM_T
#error "Expected TYPE_PARAM_T to be define"
#endif

#include <cortecs/mangle.h>

typedef TYPE_PARAM_T *CN(Cortecs, Ptr, CT(TYPE_PARAM_T));

#undef TYPE_PARAM_T