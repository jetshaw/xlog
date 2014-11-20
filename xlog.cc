#include"xlog.h"
#include"xini_file.h"

typedef struct _code {
    char *c_name;
    int c_val;
} CODE;

static CODE prioritynames[]=
{
    {"crit",LOG_MODE_CRIT },
    {"debug",LOG_MODE_DEBUG },
    {"error",LOG_MODE_ERROR },
    {"info",LOG_MODE_INFO },
    {"notice",LOG_MODE_NOTICE },
    {"warn",LOG_MODE_WARN },
    { NULL,-1 }
};

static CODE facilitynames[]=
{
  { "auth", LOG_AUTH },
  { "authpriv", LOG_AUTHPRIV },
  { "cron", LOG_CRON },
  { "daemon", LOG_DAEMON },
  { "ftp", LOG_FTP },
  { "kern", LOG_KERN },
  { "lpr", LOG_LPR },
  { "mail", LOG_MAIL },
#if 0
  { "mark", INTERNAL_MARK },      /* INTERNAL */
#endif
  { "news", LOG_NEWS },
  { "security", LOG_AUTH },       /* DEPRECATED */
  { "syslog", LOG_SYSLOG },
  { "user", LOG_USER },
  { "uucp", LOG_UUCP },
  { "local0", LOG_LOCAL0 },
  { "local1", LOG_LOCAL1 },
  { "local2", LOG_LOCAL2 },
  { "local3", LOG_LOCAL3 },
  { "local4", LOG_LOCAL4 },
  { "local5", LOG_LOCAL5 },
  { "local6", LOG_LOCAL6 },
  { "local7", LOG_LOCAL7 },
  { NULL, -1 }
};

int xlog::init(const string &config_file)
{
    xini_file inifile; 
    if( true != inifile.init(config_file) )
    {
        std::cout<<"inifile.init("<<config_file.c_str()<<") failed \n"<<std::endl;
        return -1;
    }
    xlog_config& next_log_config = _log_configs.get_next();
    next_log_config.clear();
    next_log_config.log_ident = inifile.get("log","ident","");
    std::cout<<"log_ident="<<next_log_config.log_ident.c_str()<<"\n"<<std::endl;
    string options_str = inifile.get("log","options","cons,nodelay,pid");
    set<string> set_list;
    if( true != xutils::parse_line(options_str,",",set_list) )
    {
        std::cout<<" can not parse ling { "<<options_str.c_str()<<" } \n"<<std::endl;
        return -1;
    }
    set<string>::iterator setit=set_list.begin();
    for(;setit!=set_list.end();setit++)
    {
        if( setit->compare("cons")==0 )
            next_log_config.log_options |= LOG_CONS;
        else if (setit->compare("pid") == 0) 
			next_log_config.log_options |= LOG_PID;
		else if (setit->compare("nodelay") == 0) 
			next_log_config.log_options |= LOG_NDELAY;
		else if (setit->compare("odelay") == 0) 
			next_log_config.log_options |= LOG_ODELAY;
		else if (setit->compare("nowait") == 0) 
			next_log_config.log_options |= LOG_NOWAIT;
		else if (setit->compare("perror") == 0) 
		    next_log_config.log_options |= LOG_PERROR;
		else {}
    }

    string facility_str = inifile.get("log","facility","daemon");
    int i;
    for( i=0;facilitynames[i].c_name != NULL; i++)
    {
        if( facility_str.compare(facilitynames[i].c_name)==0 )
        {
            next_log_config.log_facility = facilitynames[i].c_val;
            break;
        }
    }
    set_list.erase(set_list.begin(),set_list.end());
    string enabled_level_str = inifile.get("log","enabled-levels","crit");
    if( true !=xutils::parse_line(enabled_level_str,",",set_list) )
    {
        std::cout<<"parsed enabled-levels failed!\n"<<std::endl;
        return -1;
    }
    for( setit=set_list.begin();setit!=set_list.end();setit++ )
    {
        for( i=0;prioritynames[i].c_name != NULL;++i)
        {
            if( setit->compare(prioritynames[i].c_name) == 0 )
            {
                next_log_config.log_mode |= prioritynames[i].c_val;
                break;
            }
        }
    }
    _log_configs.alter();
    //std::cout<<"after alter :ident="<<string(_log_configs.get().log_ident()).c_str()<<"\n"<<std::endl;
    std::cout<<"in init xlog::init success\n"<<std::endl;
    xlog_config &cur_config = _log_configs.get();
    openlog(cur_config.log_ident.c_str(),cur_config.log_options,cur_config.log_facility);
    return 0;
}


int xlog::info(const char *format, ...)
{
    xlog_config& log_config = _log_configs.get();
    if( !(log_config.log_mode & LOG_MODE_INFO) )
        return -1;
    va_list ap;
    va_start(ap,format);
    vsyslog(LOG_INFO|log_config.log_facility,format,ap);
    va_end(ap);
    return 0;
}

int xlog::warn(const char *format, ...)
{
    xlog_config& log_config = _log_configs.get();
    if( !(log_config.log_mode & LOG_MODE_WARN) )
        return -1;
    va_list ap;
    va_start(ap,format);
    vsyslog(LOG_WARNING|log_config.log_facility,format,ap);
    va_end(ap);
    return 0;

}

int xlog::error(const char *format, ...)
{
    xlog_config& log_config = _log_configs.get();
    if( !(log_config.log_mode & LOG_MODE_ERROR) )
        return -1;
    va_list ap;
    va_start(ap,format);
    vsyslog(LOG_ERR|log_config.log_facility,format,ap);
    va_end(ap);
    return 0;

}

int xlog::crit(const char *format, ...)
{
    xlog_config& log_config = _log_configs.get();
    if( !(log_config.log_mode & LOG_MODE_CRIT) )
        return -1;
    va_list ap;
    va_start(ap,format);
    vsyslog(LOG_CRIT|log_config.log_facility,format,ap);
    va_end(ap);
    return 0;

}

int xlog::notice(const char *format, ...)
{
    xlog_config& log_config = _log_configs.get();
    if( !(log_config.log_mode & LOG_MODE_NOTICE) )
        return -1;
    va_list ap;
    va_start(ap,format);
    vsyslog(LOG_NOTICE|log_config.log_facility,format,ap);
    va_end(ap);
    return 0;

}

int xlog::debug(const char *format, ...)
{
    xlog_config& log_config = _log_configs.get();
    if( !(log_config.log_mode & LOG_MODE_DEBUG) )
        return -1;
    va_list ap;
    va_start(ap,format);
    vsyslog(LOG_DEBUG|log_config.log_facility,format,ap);
    va_end(ap);
    return 0;

}

#if 1
//test xlog
// 1 : compile: g++ xlog.cc xutils.cc -o log 
// 2 : modify rsyslog.conf : sudo mv /etc/rsyslog.conf /etc/rsyslog.conf.bak sudo cp rsyslog.conf /etc/ 
// 3 : restart the rsyslog : sudo service rsyslog restart
// 4 : testing: ./log data.ini &&   cat /data/logs/xlogs/crit.log
//                                  cat /data/logs/xlogs/debug.log
//                                  cat /data/logs/xlogs/warn.log
//                                  cat /data/logs/xlogs/info.log
//                                  cat /data/logs/xlogs/err.log
//                                  cat /data/logs/xlogs/notice.log
int main(int argc,char **argv)
{
    if( argc<2 )
    {
        std::cout<<"no input config file\n"<<std::endl;
        return -1;
    }
    if( 0 !=xlog::inst().init(argv[1]) )
    {
        std::cout<<"xlog init failed\n"<<std::endl;
        return -1;
    }
    xlog::inst().info("info...");
    xlog::inst().debug("debug...");
    xlog::inst().warn("warn...");
    xlog::inst().crit("crit...");
    xlog::inst().error("error...");
    xlog::inst().notice("notice...");
    return 0;
}

#endif
