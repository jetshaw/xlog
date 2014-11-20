#ifndef _xLOG_H___
#define _xLOG_H___

#include<stdarg.h>
#include<syslog.h>
#include<string>
using namespace std;

#include"xdouble_buffer.h"

typedef enum 
{
    LOG_MODE_NONE   = 0x00,
    LOG_MODE_DEBUG  = 0x01,
    LOG_MODE_ERROR  = 0x02,
    LOG_MODE_INFO   = 0x04,
    LOG_MODE_CRIT   = 0x08,
    LOG_MODE_WARN   = 0x10,
    LOG_MODE_NOTICE = 0x20,
} E_LogMode;

#define DEFAULT_LOG_OPTIONS LOG_CONS|LOG_NDELAY|LOG_PID
#define DEFAULT_LOG_MODE LOG_MODE_CRIT 
class xlog_config {
public:
    xlog_config():log_mode(DEFAULT_LOG_MODE),log_facility(LOG_LOCAL3),
                 log_options(DEFAULT_LOG_OPTIONS),
                 log_ident("with_out_initiazed")
                 {

    }

    ~xlog_config(){ }

    void clear() { 
        log_mode = DEFAULT_LOG_MODE;
        log_facility = LOG_LOCAL3;
        log_options = DEFAULT_LOG_OPTIONS;
        log_ident = "";
    }

public:
    int log_mode;
    int log_facility;
    int log_options;
    string log_ident;

};

class xlog 
{
public:
    ~xlog() { closelog(); }

    static xlog& inst() {
        static xlog log;
        return log;
    }

    int init(const string &config_file);

    int info(const char *format, ...);
    int warn(const char *format, ...);
    int error(const char *format, ...);
    int crit(const char *format, ...);
    int notice(const char *format, ...);
    int debug(const char *format, ...);

private:
    xlog() {
        xlog_config &cur_config = _log_configs.get();
        openlog(cur_config.log_ident.c_str(),cur_config.log_options,cur_config.log_facility);
    }

private:
    xdouble_buffer<xlog_config> _log_configs;
};

#endif //_xLOG_H___
