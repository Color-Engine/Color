#pragma once

#define CL_CONCAT_DETAIL(l, r) l##r
#define CL_STRINGIFY_DETAIL(x) #x
#define CL_CONCAT(l, r)        CL_CONCAT_DETAIL(l, r)
#define CL_STRINGIFY(x)        CL_STRINGIFY_DETAIL(x)

#define CL_BIT(x) (1 << x)
