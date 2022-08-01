// *定义时间戳类

#ifndef FCSERVER_TIMESTAMP_H
#define FCSERVER_TIMESTAMP_H

#include "BaseType.h"

class TimeStamp{
private:
    //-从1970开始计时的微秒数
    int64_t micro_seconds_since_epoch;
    //-每秒有多少纳秒
    static const int micro_seconds_per_second = 1000 * 1000;
public:
    //-构造函数（内联）
    TimeStamp(): micro_seconds_since_epoch(0){}
    //-构造函数(有参，内联)
    TimeStamp(int64_t micro_seconds_arg): micro_seconds_since_epoch(micro_seconds_arg){}
    //-获取当前微秒数（内联）
    int64_t getMicroSeconds();
    //-静态方法，获取换算比例（内联）
    static int getMicroSecondPerSecond();
    //-转换成秒数字符串输出
    string toString() const;
    //-转换成格式化字符串输出
    string toFormatString() const;
    //-静态方法，获取当前的时间戳（不内联，主要开销）
    static TimeStamp now();
};

//-计算两个时间戳之差，以秒为单位
inline double timeDifference(TimeStamp high, TimeStamp low){
    int64_t diff = high.getMicroSeconds()-low.getMicroSeconds();
    return static_cast<double>(diff)/TimeStamp::getMicroSecondPerSecond();
};



#endif //FCSERVER_TIMESTAMP_H
