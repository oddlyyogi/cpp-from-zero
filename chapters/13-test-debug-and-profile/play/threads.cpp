#include <condition_variable>
#include <string>
#include <atomic>
#include <mutex>
#include <print>
#include <thread>
#include <vector>

int main() {
    std::mutex pen;
    long long guarded = 0;
    std::atomic<long long> fast{0};
    std::vector<std::jthread> workers;
    for (int t = 0; t < 4; ++t) {
        workers.emplace_back([&] {
            for (int i = 0; i < 100000; ++i) {
                std::scoped_lock lock(pen);
                ++guarded;
                fast.fetch_add(1);
            }
        });
    }
    workers.clear();
    std::println("guarded {} fast {}", guarded, fast.load());

    std::vector<std::string> queue;
    bool done = false;
    std::mutex m;
    std::condition_variable bell;
    std::jthread worker([&] {
        std::unique_lock lock(m);
        while (true) {
            bell.wait(lock, [&] { return !queue.empty() || done; });
            if (queue.empty()) {
                return;
            }
            std::println("handling {}", queue.back());
            queue.pop_back();
        }
    });
    for (std::string name : {"web.log", "jobs.log", "app.log"}) {
        std::scoped_lock lock(m);
        queue.push_back(name);
        bell.notify_one();
    }
    {
        std::scoped_lock lock(m);
        done = true;
    }
    bell.notify_one();
    std::jthread ticker([](std::stop_token stop) {
        while (!stop.stop_requested()) {
            std::this_thread::sleep_for(std::chrono::milliseconds(5));
        }
        std::println("ticker stopped");
    });
    std::this_thread::sleep_for(std::chrono::milliseconds(20));
    ticker.request_stop();
}