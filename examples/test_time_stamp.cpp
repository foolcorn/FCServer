// *测试时间戳类
#include "../base/TimeStamp.h"

//-测试引用传递，并打印格式化输出
void passByConstReference(const TimeStamp& x)
{
    printf("%s\n", x.toString().c_str());
}

//-测试值传递，并打印格式化输出
void passByValue(TimeStamp x)
{
    printf("%s\n", x.toString().c_str());
}

void benchmark()
{
    const int kNumber = 1000*1000;

    vector<TimeStamp> stamps;
    stamps.reserve(kNumber);
    //-插入100w个时间戳
    for (int i = 0; i < kNumber; ++i)
    {
        stamps.push_back(TimeStamp::now());
    }
    printf("push 1M: strat time:%s\n", stamps.front().toString().c_str());
    printf("push 1M: end time:%s\n", stamps.back().toString().c_str());
    printf("push 1M: used time:%f\n", timeDifference(stamps.back(), stamps.front()));

    int increments[100] = {0};
    int64_t start = stamps.front().getMicroSeconds();
    for (int i = 1; i < kNumber; ++i)
    {
        int64_t next = stamps[i].getMicroSeconds();
        int64_t inc = next - start;
        start = next;
        if (inc < 0)
        {
            printf("reverse!\n");
        }
        else if (inc < 100)
        {
            ++increments[inc];
        }
        else
        {
            printf("big gap %d\n", static_cast<int>(inc));
        }
    }

    for (int i = 0; i < 100; ++i)
    {
        printf("%2d: %d\n", i, increments[i]);
    }
}

int main()
{
    TimeStamp now(TimeStamp::now());
    printf("%s\n", now.toString().c_str());
//    passByValue(now);
//    passByConstReference(now);
    benchmark();
    exit(0);
}