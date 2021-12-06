#include <array>
#include <deque>
#include <numeric>
#include <iostream>

using Index = int;
using Days = size_t;
using Fish = size_t;
using Fishes = std::deque<Fish>;

Fish DoCalc_2(const Fishes &fishes, Days numberOfRemainingDays) {
    std::array<Fish, 9> batches{};

    const auto PreProcess = [&]() {
        std::for_each(fishes.begin(), fishes.end(), [&](const Fish& fish) { batches[fish]++; });
    };
    
    const auto FishAccumulate = [&]() {
        return std::accumulate(batches.begin(), batches.end(), Fish(0), std::plus<Fish>());
    };

    PreProcess();

    while (numberOfRemainingDays > 0) {
        Fish prev = batches[8], cur = 0;
        for (Index i = 7; i >= 0; i--) {
            cur = batches[i], batches[i] = prev, prev = cur;
        }
        
        batches[6] += prev, batches[8] = prev;
        numberOfRemainingDays -- ;
    }

    return FishAccumulate();
}

using FishesPerDay = std::deque<std::pair<Days, Fish>>;

struct TestCase {
    TestCase(std::deque<Fish>&& fishes, FishesPerDay fishesPerDay) {
        _fishes = std::move(fishes);
        _fishesPerDay = fishesPerDay;
    }
    
    std::deque<Fish> _fishes;
    FishesPerDay _fishesPerDay;
};

std::deque<TestCase> testCases {
    { std::move(std::deque<Fish>{3,4,3,1,2}),
        { {18, 26}, { 80, 5934 }, { 256, 26984457539 } }
    },
    { std::move(std::deque<Fish> { 3,5,4,1,2,1,5,5,1,1,1,1,4,1,4,5,4,5,1,3,1,1,1,4,1,1,3,1,1,5,3,1,1,3,1,3,1,1,1,4,1,2,5,3,1,4,2,3,1,1,2,1,1,1,4,1,1,1,1,2,1,1,1,3,1,1,4,1,4,1,5,1,4,2,1,1,5,4,4,4,1,4,1,1,1,1,3,1,5,1,4,5,3,1,4,1,5,2,2,5,1,3,2,2,5,4,2,3,4,1,2,1,1,2,1,1,5,4,1,1,1,1,3,1,5,4,1,5,1,1,4,3,4,3,1,5,1,1,2,1,1,5,3,1,1,1,1,1,5,1,1,1,1,1,1,1,2,2,5,5,1,2,1,2,1,1,5,1,3,1,5,2,1,4,1,5,3,1,1,1,2,1,3,1,4,4,1,1,5,1,1,4,1,4,2,3,5,2,5,1,3,1,2,1,4,1,1,1,1,2,1,4,1,3,4,1,1,1,1,1,1,1,2,1,5,1,1,1,1,2,3,1,1,2,3,1,1,3,1,1,3,1,3,1,3,3,1,1,2,1,3,2,3,1,1,3,5,1,1,5,5,1,2,1,2,2,1,1,1,5,3,1,1,3,5,1,3,1,5,3,4,2,3,2,1,3,1,1,3,4,2,1,1,3,1,1,1,1,1,1 }),
        { {18, -1}, { 80, -1}, { 256, -1} }
    }
};

void RunTestCases() {
    const auto assertOutput = [](auto expected, auto actual) {
        if (actual != expected)
            std::cout << "Expected: [" << expected << "], Actual: [" << actual << "]\n";
        else
            std::cout << "Passed\n";
        assert(actual == expected);
    };

    Index major = 1;
    for (auto& test : testCases) {
        Index minor = 1;
        for (const auto& [day, fishCount] : test._fishesPerDay) {
            std::cout << "Test Case [ " << major << "." << minor++ << " ] : ";
            
            auto result = DoCalc_2(test._fishes, day);

            if (fishCount == -1)
                std::cout << "Result = " << result << "\n";
            else
                assertOutput(fishCount, result);
        }
        major++;
    }
}

int main() {
    RunTestCases();
}
