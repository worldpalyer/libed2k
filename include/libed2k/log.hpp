#ifndef __LOG__
#define __LOG__

#ifdef LIBED2K_DEBUG

#include "boost/logging/format_fwd.hpp"

// Step 1: Optimize : use a cache string, to make formatting the message faster
BOOST_LOG_FORMAT_MSG(optimize::cache_string_one_str<>)

#ifndef BOOST_LOG_COMPILE_FAST
#include "boost/logging/format.hpp"
#include "boost/logging/writer/ts_write.hpp"
#endif

using namespace boost::logging;

const unsigned char LOG_CONSOLE = 1;
const unsigned char LOG_FILE = 2;
const unsigned char LOG_ALL = '\xFF';

// Step 3 : Specify your logging class(es)
// typedef boost::logging::logger_format_write< > logger_type;
// typedef boost::logging::writer::threading::ts_write<> log_type;
typedef logger_format_write<default_, default_, writer::threading::ts_write> logger_type;

// Step 4: declare which filters and loggers you'll use
BOOST_DECLARE_LOG_FILTER(g_l_filter, boost::logging::level::holder)
BOOST_DECLARE_LOG(g_l, logger_type)

// Step 5: define the macros through which you'll log
#define LDBG_ BOOST_LOG_USE_LOG_IF_LEVEL(g_l(), g_l_filter(), debug) << "[dbg] "
#define LERR_ BOOST_LOG_USE_LOG_IF_LEVEL(g_l(), g_l_filter(), error) << "[ERR] "
#define LAPP_ BOOST_LOG_USE_LOG_IF_LEVEL(g_l(), g_l_filter(), info) << "[inf] "

#define DBG(x) LDBG_ << x
#define APP(x) LAPP_ << x
#define ERR(x) LERR_ << x

#define LOGGER_INIT(x) init_logs(x);
#define LOGGER_INIT_FILE(x, y) init_logs(x, y);

void init_logs(unsigned char log_destination = LOG_ALL, const char* outfile = "out.txt");

#else

#define DBG(x)
#define APP(x)
#define ERR(x)
#define LOGGER_INIT(x)
#define LOGGER_INIT_FILE(x, y)

#endif

#endif  //__LOG__
