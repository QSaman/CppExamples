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
		// Since a spurious wakeup is possible, it's better stop_waiting (second argument)
		// is provided:
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
	{
		std::unique_lock<std::mutex> unique_lock(ctx.notify_worker_threads_mutex);

		{
			// It's important the workers first acquires ctx.notify_worker_threads_mutex
			// and then ctx.notify_manager_thread_mutex so the manager waits for the
			// last one before it asks all of them to start:
			std::unique_lock<std::mutex> unique_lock(ctx.notify_manager_thread_mutex);
			if (--ctx.waiting_workers_count == 0)
			{
				ctx.are_all_workers_ready = true;
			}
		}

		if (ctx.waiting_workers_count == 0)
		{
			print("Worker with id " << std::this_thread::get_id() << " notifies the manager...");
			// Since notify_one awakens the manager, the last worker should first release
			// ctx.notify_manager_thread_mutex before calling notify_one():
			ctx.notify_manager_thread.notify_one();
		}
		print("Worker with id " << std::this_thread::get_id() << " is waiting...");

		// Since a spurious wakeup is possible, it's better stop_waiting (second argument)
		// is provided:
		ctx.notify_worker_threads.wait(unique_lock, [](){return ctx.start_execution;});
	}

	// All workers competing each other to execute this part first:
	bool expected = false;
	constexpr bool desired = true;
	if (winner.compare_exchange_strong(expected, desired))
	{
		print("Thread with id " << std::this_thread::get_id() << " won the race!");
	}
	else
	{
		print("Thread with id " << std::this_thread::get_id() << " lost the race!");
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
