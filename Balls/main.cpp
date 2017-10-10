#include <iostream>
#include <random>
#include <algorithm>
#include <chrono>
#include <mutex>

typedef std::vector<int> bins_t;

enum eData
{
    TEST_SAMPLE = 1000,
    NR_TEST_1 = 10007,
    NR_TEST_2 = 32768,
};

void distribute(bins_t& bins, int nrBalls, bool powerOfTwo)
{

    std::default_random_engine generator((unsigned int)std::chrono::system_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<int> distribution(0, (int)bins.size()-1);

    for (int i = 0; i < nrBalls; i++)
    {
        if (!powerOfTwo)
        {
            bins[distribution(generator)]++;
            continue;
        }

        int a = distribution(generator);
        int b = distribution(generator);

        if (bins[a] < bins[b])
            bins[a]++;
        else
            bins[b]++;
    }
}


void test(std::mutex& mutex, int testNr, int binballs, bool powerOfTwo)
{
    int max = 0;
    double maxSum = 0;
    for(int i = 0; i < TEST_SAMPLE; i++)
    {
        bins_t bins = bins_t(binballs);
        distribute(bins, binballs, powerOfTwo);
        int localMax = 0;
        for (auto value : bins)
            localMax = std::max(localMax, value);
        
        max = std::max(max, localMax);
        maxSum += localMax;
    }
    
    std::lock_guard<std::mutex> lock(mutex);
    std::cout << "Test nr "<< testNr<<". Using power of two: " << (powerOfTwo ? "true" : "false") << std::endl;
    std::cout << "Test sample: " << TEST_SAMPLE << std::endl;
    std::cout << "Avg max number: " << maxSum / TEST_SAMPLE << std::endl;
    std::cout << "Max number: " << max << std::endl;
    std::cout << "==============================" << std::endl;
    
}

typedef std::unique_ptr<std::thread> thread_ptr;

thread_ptr spawnTestWorker(void(&test)(std::mutex&, int, int, bool), int testNr, int binballs, bool powerOfTwo)
{
    static std::mutex mutex;
    return std::make_unique<std::thread>([&]() { test(mutex, testNr, binballs, powerOfTwo); });    
}

void main()
{
    thread_ptr t1 = spawnTestWorker(test, 1, NR_TEST_1, false);
    thread_ptr t2 = spawnTestWorker(test, 1, NR_TEST_1, true);
    thread_ptr t3 = spawnTestWorker(test, 2, NR_TEST_2, false);
    thread_ptr t4 = spawnTestWorker(test, 2, NR_TEST_2, true);

    t1->join();
    t2->join();
    t3->join();
    t4->join();

}
