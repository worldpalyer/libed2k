#ifndef __LOG__
#define __LOG__

#ifdef LIBED2K_DEBUG

#include <boost/log/common.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/console.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/attributes/timer.hpp>
#include <boost/log/attributes/named_scope.hpp>
#include <boost/log/sources/logger.hpp>
#include <boost/log/support/date_time.hpp>

// Here we define our application severity levels.
// enum logger_level { debug, info, error };

//// The formatting logic for the severity level
// template <typename CharT, typename TraitsT>
// inline std::basic_ostream<CharT, TraitsT>& operator<<(std::basic_ostream<CharT, TraitsT>& strm, logger_level lvl) {
//    static const char* const str[] = {"D", "E", "I"};
//    if (static_cast<std::size_t>(lvl) < (sizeof(str) / sizeof(*str)))
//        strm << str[lvl];
//    else
//        strm << static_cast<int>(lvl);
//    return strm;
//}
// boost::log::sources::severity_logger<logger_level>& shared_severity_logger();
boost::log::sources::logger& shared_logger();
// Step 5: define the macros through which you'll log
//#define LDBG_ BOOST_LOG_SEV(g_l(), debug) << "[dbg] "
//#define LERR_ BOOST_LOG_SEV(g_l(), error) << "[ERR] "
//#define LAPP_ BOOST_LOG_SEV(g_l(), info) << "[inf] "

#define DBG(x) BOOST_LOG(shared_logger()) << "D " << x
#define APP(x) BOOST_LOG(shared_logger()) << "I " << x
#define ERR(x) BOOST_LOG(shared_logger()) << "E " << x

#define LOGGER_INIT(x) init_logs(x);

void init_logs(std::string = "");

#else

#define DBG(x)
#define APP(x)
#define ERR(x)
#define LOGGER_INIT(x)

#endif

#endif  //__LOG__
