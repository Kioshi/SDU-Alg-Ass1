#include <iostream>
#include <random>
#include <algorithm>
#include <chrono>
#include <mutex>

typedef std::vector<int> bins_t;

enum eData
{
    TEST_SAMPLE = 1000,
    NR_TEST1 = 10007,
};

void distribute(bins_t& bins, int nrBalls)
{

    std::default_random_engine generator((unsigned int)std::chrono::system_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<int> distribution(0, (int)bins.size()-1);

    for (int i = 0; i < nrBalls; i++)
        bins[distribution(generator)]++;
}


void test1(std::mutex& mutex)
{
    int binballs = NR_TEST1;

    int max = 0;
    double maxSum = 0;
    for(int i = 0; i < TEST_SAMPLE; i++)
    {
        bins_t bins = bins_t(binballs);
        distribute(bins, binballs);
        int localMax = 0;
        for (auto value : bins)
            localMax = std::max(localMax, value);
        
        max = std::max(max, localMax);
        maxSum += localMax;
    }
    
    std::lock_guard<std::mutex> lock(mutex);
    std::cout << "==============================" << std::endl;
    std::cout << "Test nr 1." << std::endl;
    std::cout << "Test sample: " << TEST_SAMPLE << std::endl;
    std::cout << "Avg max number: " << maxSum / TEST_SAMPLE << std::endl;
    std::cout << "Max number: " << max << std::endl;
    std::cout << "==============================" << std::endl;
    
}

typedef std::unique_ptr<std::thread> thread_ptr;

thread_ptr spawnTestWorker(void(&test)(std::mutex&))
{
    static std::mutex mutex;
    return std::make_unique<std::thread>([&]() { test(mutex); });    
}

void main()
{
    thread_ptr t1 = spawnTestWorker(test1);
    thread_ptr t2 = spawnTestWorker(test1);

    t1->join();
    t2->join();

}