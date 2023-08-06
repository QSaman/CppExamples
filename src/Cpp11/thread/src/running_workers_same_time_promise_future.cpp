/// For more information please refer to:
/// https://www.modernescpp.com/index.php/thread-synchronization-with-condition-variables-or-tasks/
#include <array>
#include <atomic>
#include <chrono>
#include <future>
#include <mutex>
#include <iostream>
#include <thread>

constexpr std::size_t WORKERS_COUNT = 3;

struct Context
{
	Context() :
		startExecution(startExecutionPromise.get_future()),
		workersReady(workersReadyPromise.get_future())
	{
	}

	std::mutex print_mutex;
	std::promise<void> startExecutionPromise, workersReadyPromise;
	// Note that promise<void>>get_future() must be called only once.
	// Because of that we should use std::shared_future:
	std::shared_future<void> startExecution, workersReady;
} ctx;

/// Unlike condition_variable, there is no critical section, so we
/// should use atomic here:
std::atomic<std::size_t> unready_workers_count{WORKERS_COUNT};
std::atomic<bool> winner(false);

#define print(x) \
{ \
	std::unique_lock<std::mutex> unique_lock(ctx.print_mutex); \
	std::cout << x << std::endl; \
}	

void notifyWorkers()
{
	print("Waiting for all workers to be ready...");
	/// Unlike condition_variable, lost wakeup is not possible in futures.
	/// In other words, futures have memory. If promise<void>::set_value
	/// is called before wait(), it knows that the value has been already
	/// available:
	ctx.workersReady.wait();
	print("All workers are ready...");
	print("Notifying all workers to start...");
	ctx.startExecutionPromise.set_value();
}

void work()
{
	--unready_workers_count;
	if (unready_workers_count == 0)
	{
		print("Worker with id " << std::this_thread::get_id() << " notifies the manager...");
		ctx.workersReadyPromise.set_value();
	}

	print("Worker with id " << std::this_thread::get_id() << " is waiting...");
	ctx.startExecution.wait();

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

