#include <array>
#include <atomic>
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <thread>

constexpr std::size_t WORKERS_COUNT = 3;

struct Context
{
	std::condition_variable notify_worker_threads, notify_manager_thread;
	std::mutex notify_worker_threads_mutex, notify_manager_thread_mutex, print_mutex;
	bool are_all_workers_ready = false;
	bool start_execution = false;
	std::size_t waiting_workers_count = WORKERS_COUNT;
} ctx;

std::atomic<bool> winner(false);

#define print(x) \
{ \
	std::unique_lock<std::mutex> unique_lock(ctx.print_mutex); \
	std::cout << x << std::endl; \
}	

void notifyWorkers()
{
	{
		std::unique_lock<std::mutex> unique_lock(ctx.notify_manager_thread_mutex);
		print("Waiting for all workers to be ready...");
		ctx.notify_manager_thread.wait(unique_lock, [](){return ctx.are_all_workers_ready;});
		print("All workers are ready...");
	}

	{
		std::unique_lock<std::mutex> unique_lock(ctx.notify_worker_threads_mutex);
		ctx.start_execution = true;
		print("Notifying all workers to start...");
	}

	// Since notify_all awakens all workers, manager should first release
	// ctx.notify_worker_threads_mutex before calling notify_all():
	ctx.notify_worker_threads.notify_all();
}

void work()
{
	// We need to use this local variable so the manager waits for the last worker:
	bool are_all_workers_ready = false;

	{
		std::unique_lock<std::mutex> unique_lock(ctx.notify_manager_thread_mutex);
		if (--ctx.waiting_workers_count == 0)
		{
			are_all_workers_ready = true;
		}
	}

	{
		std::unique_lock<std::mutex> unique_lock(ctx.notify_worker_threads_mutex);
		if (are_all_workers_ready)
		{
			{
				// It's important the last worker first acquires ctx.notify_worker_threads_mutex
				// and then ctx.notify_manager_thread_mutex so the manager waits for it before
				// it asks all workers to start:
				std::unique_lock<std::mutex> unique_lock(ctx.notify_manager_thread_mutex);
				ctx.are_all_workers_ready = are_all_workers_ready;
				print("Worker with id " << std::this_thread::get_id() << " is the last one");
			}
			// Since notify_one awakens the manager, the last worker should first release
			// ctx.notify_manager_thread_mutex before calling notify_one():
			ctx.notify_manager_thread.notify_one();
		}
		print("Worker with id " << std::this_thread::get_id() << " is waiting...");
		ctx.notify_worker_threads.wait(unique_lock, [](){return ctx.start_execution;});
		print("Worker with id " << std::this_thread::get_id() << " finished waiting...");
	}

	// All workers competing each other to execute this part first:
	bool expected = false;
	constexpr bool desired = true;
	if (winner.compare_exchange_strong(expected, desired))
	{
		print("Thread with id " << std::this_thread::get_id() << " wins the race!");
	}
}

int main()
{
	std::array<std::thread, WORKERS_COUNT> workers = {{ std::thread(work), std::thread(work), std::thread(work) }};
	std::thread manager(notifyWorkers);

	for (auto& worker : workers)
	{
		worker.join();
	}
	manager.join();
}
