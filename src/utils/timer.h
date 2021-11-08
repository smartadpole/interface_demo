#ifndef TIMER_H
#define TIMER_H

#include <sys/time.h> //test
#include <iostream>

class Timer
{
public:
    Timer()
    {
        Start();
    }

    double Timing(const std::string message = "", bool print = false)
    {
        gettimeofday(&end, nullptr);
        double timeuse = (1000000 * (end.tv_sec - start.tv_sec) + end.tv_usec -
                          start.tv_usec) * 1.0 / 1000;

        if ("" != message)
        {
            if (print)
            {
                std::cout << "\033[32muse time(" << message << "): \033[32m"
                          << timeuse << "\033[32mms\033[0m" << std::endl;
            }
        }
        Start();

        return timeuse;
    }

    std::string TimingStr(const std::string message = "", bool print = false)
    {
        gettimeofday(&end, nullptr);
        double timeuse = (1000000 * (end.tv_sec - start.tv_sec) + end.tv_usec -
                          start.tv_usec) * 1.0 / 1000;

        std::ostringstream useTime("");

        useTime << "\033[0muse time(" << message << "): \033[34m"
                << timeuse << "\033[0mms\033[0m";
        std::string useTimeStr = useTime.str();

        if (print)
        {
            std::cout << useTimeStr << std::endl;
        }

        Start();

        return useTimeStr;
    }


private:
    void Start()
    {
        gettimeofday(&start, nullptr);
    }

private:
    struct timeval start, end;
};


#endif // TIMER_H
