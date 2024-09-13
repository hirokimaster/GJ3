#include "Timer.h"

void Timer::Start()
{
    if (!running_)
    {
        startTime_ = std::chrono::steady_clock::now();
        running_ = true;
    }
}

void Timer::Stop()
{
    if (running_)
    {
        auto end_time = std::chrono::steady_clock::now();
        elapsed_seconds_ += static_cast<int>(std::chrono::duration_cast<std::chrono::seconds>(end_time - startTime_).count());
        running_ = false;
    }
}

void Timer::Update()
{

}

void Timer::Reset()
{
    elapsed_seconds_ = 0;
    running_ = false;
}

int Timer::GetElapsedSeconds()
{
    if (running_)
    {
        auto current_time = std::chrono::steady_clock::now();
        return elapsed_seconds_ + static_cast<int>(std::chrono::duration_cast<std::chrono::seconds>(current_time - startTime_).count());
    }
    return elapsed_seconds_;
}

