#include "libed2k/log.hpp"

#ifdef LIBED2K_DEBUG
// static boost::log::sources::severity_logger<logger_level>* _severity_shared_ = 0;
static boost::log::sources::logger* _shared_ = 0;

// boost::log::sources::severity_logger<logger_level>& shared_severity_logger() {
//    if (_severity_shared_) {
//        return *_severity_shared_;
//    }
//    _severity_shared_ = new boost::log::sources::severity_logger<logger_level>();
//    return *_severity_shared_;
//}

boost::log::sources::logger& shared_logger() {
    if (_shared_) {
        return *_shared_;
    }
    _shared_ = new boost::log::sources::logger();
    return *_shared_;
}

void init_logs(std::string filepath) {
    namespace logging = boost::log;
    namespace sinks = boost::log::sinks;
    namespace attrs = boost::log::attributes;
    namespace src = boost::log::sources;
    namespace expr = boost::log::expressions;
    namespace keywords = boost::log::keywords;
    // This is a simple tutorial/example of Boost.Log usage

    // The first thing we have to do to get using the library is
    // to set up the logging sinks - i.e. where the logs will be written to.
    logging::add_console_log(
        std::clog, keywords::format = expr::stream
                                      << expr::format_date_time<boost::posix_time::ptime>("TimeStamp", "%m-%d %H:%M:%S")
                                      //<< " " << expr::format_named_scope("Scope", keywords::format = "%n (%f:%l)")
                                      << " " << expr::message
        /*
         keywords::format = expr::format("%1% [%2%] [%3%] <%4%> %5%")
         % expr::format_date_time< boost::posix_time::ptime >("TimeStamp", "%Y-%m-%d, %H:%M:%S.%f")
         % expr::format_date_time< attrs::timer::value_type >("Uptime", "%O:%M:%S")
         % expr::format_named_scope("Scope", keywords::format = "%n (%f:%l)")
         % expr::attr< severity_level >("Severity")
         % expr::message
         */
        );
    // One can also use lambda expressions to setup filters and formatters
    //    logging::add_file_log("sample.log", keywords::filter = expr::attr<logger_level>("Severity") >= info,
    //                          keywords::format =
    //                              expr::stream
    //                              << expr::format_date_time<boost::posix_time::ptime>("TimeStamp", "%Y-%m-%d,
    //                              %H:%M:%S.%f")
    //                              << " [" << expr::format_date_time<attrs::timer::value_type>("Uptime", "%O:%M:%S") <<
    //                              "] ["
    //                              << expr::format_named_scope("Scope", keywords::format = "%n (%f:%l)") << "] <"
    //                              << expr::attr<logger_level>("Severity") << "> " << expr::message);

    // Also let's add some commonly used attributes, like timestamp and record counter.
    logging::add_common_attributes();
    logging::core::get()->add_thread_attribute("Scope", attrs::named_scope());

    BOOST_LOG_FUNCTION();
}

#endif
