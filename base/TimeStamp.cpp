// * 实现时间戳的api

#include "TimeStamp.h"
#include <sys/time.h>

//-获取当前微秒数
int64_t TimeStamp::getMicroSeconds(){
    return micro_seconds_since_epoch;
};

//-静态方法，获取换算比例
int TimeStamp::getMicroSecondPerSecond(){
    return TimeStamp::micro_seconds_per_second;
};

//-转换成格式化字符串输出
string TimeStamp::toString() const{
    char buf[32] = {0};
    //-计算多少秒
    int64_t seconds = micro_seconds_since_epoch / micro_seconds_per_second;
    //-剩余多少微秒
    int64_t micro_seconds = micro_seconds_since_epoch % micro_seconds_per_second;
    snprintf(buf,sizeof(buf),"%ld.%06ld",seconds,micro_seconds);
    return buf;
};

//-转换成格式化字符串输出
string TimeStamp::toFormatString() const{
    char buf[64] = {0};
    time_t seconds = static_cast<time_t>(micro_seconds_since_epoch/micro_seconds_per_second);
    struct tm tm_time;
    gmtime_r(&seconds, &tm_time);//-线程安全的
    //-format:年月日，时分秒
    snprintf(buf,sizeof(buf),"%4d-%02d-%02d %02d:%02d:%02d",
             tm_time.tm_year+1900,tm_time.tm_mon+1, tm_time.tm_mday,
             tm_time.tm_hour, tm_time.tm_min, tm_time.tm_sec);
    return buf;
};

//-获取当前时间的时间戳
TimeStamp TimeStamp::now(){
    struct timeval tv;
    gettimeofday(&tv, NULL);//-返回结构体由秒数和微秒数两个成员组成
    int64_t seconds = tv.tv_sec;//-秒数
    return TimeStamp(seconds*micro_seconds_per_second + tv.tv_usec);//-微秒数
};


