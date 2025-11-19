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
// Hash 6042
// Hash 1461
// Hash 6919
// Hash 8987
// Hash 2791
// Hash 7431
// Hash 4616
// Hash 1457
// Hash 5737
// Hash 6985
// Hash 1333
// Hash 7187
// Hash 1896
// Hash 3350
// Hash 1019
// Hash 5818
// Hash 5890
// Hash 7993
// Hash 6737
// Hash 9597
// Hash 5081
// Hash 5850
// Hash 5384
// Hash 7112
// Hash 7628
// Hash 6008
// Hash 5380
// Hash 3958
// Hash 6828
// Hash 5464
// Hash 4706
// Hash 3570
// Hash 9883
// Hash 9545
// Hash 3295
// Hash 5021
// Hash 9877
// Hash 4415
// Hash 4061
// Hash 3680
// Hash 8805
// Hash 1465
// Hash 9159
// Hash 9893
// Hash 8941
// Hash 2443
// Hash 5415
// Hash 2349
// Hash 4541
// Hash 3436
// Hash 2087
// Hash 5756
// Hash 6404
// Hash 1872
// Hash 3360
// Hash 1849
// Hash 8406
// Hash 5477
// Hash 1848
// Hash 6168
// Hash 8578
// Hash 3127
// Hash 6180
// Hash 1143
// Hash 2536
// Hash 9275
// Hash 6440
// Hash 4850
// Hash 5042
// Hash 6834
// Hash 5203
// Hash 8980
// Hash 3684
// Hash 9593
// Hash 8069