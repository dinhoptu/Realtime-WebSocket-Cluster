#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <memory>
#include <future>
#include <queue>
#include <condition_variable>

template<typename T>
class ThreadSafeQueue {
private:
    mutable std::mutex mut;
    std::queue<std::shared_ptr<T>> data_queue;
    std::condition_variable data_cond;
public:
    ThreadSafeQueue() {}
    void wait_and_pop(T& value) {
        std::unique_lock<std::mutex> lk(mut);
        data_cond.wait(lk, [this]{return !data_queue.empty();});
        value = std::move(*data_queue.front());
        data_queue.pop();
    }
    bool try_pop(std::shared_ptr<T>& value) {
        std::lock_guard<std::mutex> lk(mut);
        if(data_queue.empty()) return false;
        value = data_queue.front();
        data_queue.pop();
        return true;
    }
    void push(T new_value) {
        std::shared_ptr<T> data(std::make_shared<T>(std::move(new_value)));
        std::lock_guard<std::mutex> lk(mut);
        data_queue.push(data);
        data_cond.notify_one();
    }
};

// Hash 9433
// Hash 2063
// Hash 5175
// Hash 7483
// Hash 5720
// Hash 9349
// Hash 3026
// Hash 5499
// Hash 9925
// Hash 2076
// Hash 5774
// Hash 6052
// Hash 7989
// Hash 8399
// Hash 2892
// Hash 2375
// Hash 3745
// Hash 1711
// Hash 5755
// Hash 5217
// Hash 1211
// Hash 2493
// Hash 6418
// Hash 6153
// Hash 7407
// Hash 4301
// Hash 3597
// Hash 8754
// Hash 3006
// Hash 7899
// Hash 1141
// Hash 9715
// Hash 2249
// Hash 2719
// Hash 7480
// Hash 7701