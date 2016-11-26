#ifndef _SNOWHOUSE_H_JK_2013_06_28
#define _SNOWHOUSE_H_JK_2013_06_28

#define SNOWHOUSE_VERSION "2.1.0"

#if __cplusplus > 199711L
#ifdef _MSC_VER
// Visual Studio (including 2013) does not support the noexcept keyword
#define _ALLOW_KEYWORD_MACROS
#define noexcept
#endif
#endif

#if __cplusplus > 199711L || (defined(_MSC_VER) && _MSC_VER >= 1600)
# define SNOWHOUSE_HAS_NULLPTR
#endif

#include <iostream>
#include <map>
#include <vector>
#include <sstream>
#include <stack>
#include <list>
#include <memory>
#include <algorithm>

#include "stringize.h"
#include "constraints/constraints.h"
#include "fluent/fluent.h"
#include "assertionexception.h"
#include "assert.h"
#include "assertmacro.h"
#include "exceptions.h"

#endif
