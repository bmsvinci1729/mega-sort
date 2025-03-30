#include <iostream>
#include <thread>
#include <vector>
#include <atomic>
#include <pthread.h>
#include <unistd.h>
#include <sched.h>
#include <chrono>

std::atomic<int> global_sum(0);  // Shared atomic variable for safe concurrent access

// Function to pin a thread to a specific CPU core
void pin_thread_to_core(int core_id) {
    cpu_set_t cpuset;
    CPU_ZERO(&cpuset);
    CPU_SET(core_id, &cpuset);

    pthread_t current_thread = pthread_self();
    if (pthread_setaffinity_np(current_thread, sizeof(cpu_set_t), &cpuset) != 0) {
        std::cerr << "Warning: Failed to pin thread to core " << core_id << std::endl;
    }
}

// Thread function to compute partial sum
void partial_sum(int start, int end, int core_id, std::atomic<int>& partial_result) {
    pin_thread_to_core(core_id);  // Ensure thread runs on specified core

    int local_sum = 0;
    for (int i = start; i <= end; ++i) {
        local_sum += i;
    }

    partial_result = local_sum;
}

// Function to collect all partial results into global_sum
void collect_results(std::vector<std::atomic<int>>& partial_sums, int core_id) {
    pin_thread_to_core(core_id);

    for (auto& sum : partial_sums) {
        global_sum += sum.load();
    }
}

int main() {
    const int num_threads = 4;
    std::vector<std::thread> threads;
    std::vector<std::atomic<int>> partial_sums(num_threads);

    // Start measuring time
    auto start_time = std::chrono::high_resolution_clock::now();

    // Launch 4 threads for partial sums
    for (int i = 0; i < num_threads; ++i) {
        int start = i * 250000000 + 1;
        int end = start + 249999999;
        threads.emplace_back(partial_sum, start, end, i, std::ref(partial_sums[i]));
    }

    // Wait for all worker threads to finish
    for (auto& t : threads) {
        t.join();
    }

    // Launch collector thread to combine results on core 4
    std::thread collector(collect_results, std::ref(partial_sums), num_threads);
    collector.join();

    // End time measurement
    auto end_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> elapsed = end_time - start_time;

    std::cout << "Sum from 1 to 100 is: " << global_sum.load() << std::endl;
    std::cout << "Total time taken: " << elapsed.count() << " ms" << std::endl;

    return 0;
}
