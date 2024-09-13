#pragma once
#include <iostream>
#include <chrono>
#include <thread>

class Timer
{
public:

    // タイマー開始
    void Start();

    // タイマー停止
    void Stop();

    void Update();

    // リセット
    void Reset();


    // 経過時間取得
    int GetElapsedSeconds();




private:
    std::chrono::steady_clock::time_point startTime_;
    int elapsed_seconds_;
    bool running_;


};
