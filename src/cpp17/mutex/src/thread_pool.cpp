#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <future>
#include <functional>
#include <atomic>
#include <iostream>

class ThreadPool
{
public:
	ThreadPool(std::size_t num_of_threads);
	~ThreadPool();

	template<typename F, typename... Args>
	auto enqueue(F&& f, Args... args) -> std::future<decltype(f(args...))>;

private:
	std::vector<std::thread> workers;
	std::queue<std::function<void()>> tasks;

	std::mutex queue_mutex;
	std::condition_variable condition;
	std::atomic<bool> finish;
};

ThreadPool::ThreadPool(std::size_t num_of_threads) : finish(false)
{
	for (std::size_t i = 0; i < num_of_threads; ++i)
	{
		workers.emplace_back([this]()
							 {
							 	while (!finish)
								{
									std::function<void()> task;

									{
										std::unique_lock<std::mutex> lock(this->queue_mutex);
										condition.wait(lock, [this]()
													   {
															return this->finish || !tasks.empty();
													   });

										if (this->finish && this->tasks.empty())
											return;
										task = std::move(this->tasks.front());
										this->tasks.pop();
									}

									task();
								}
							 });
	}
}

template<typename F, typename... Args>
auto ThreadPool::enqueue(F&& f, Args... args) -> std::future<decltype(f(args...))>
{
	using return_type = decltype(f(args...));

	//packaged_task is not copyable so we should use shared_ptr:
	auto task = std::make_shared<std::packaged_task<return_type()>>(std::bind(std::forward<F>(f), std::forward<Args>(args)...));
	std::future<return_type> result = task->get_future();

	{
		std::lock_guard<std::mutex> lock(queue_mutex);
		if (!finish)
		{
			tasks.emplace([task]() {(*task)();});
		}
	}

	condition.notify_one();
	return result;
}

ThreadPool::~ThreadPool()
{
	finish = true;
	condition.notify_all();
	for (auto& worker : workers)
		worker.join();
}

int main()
{
	ThreadPool pool(4);

	auto future1 = pool.enqueue([](){return 1 + 2;});
	auto future2 = pool.enqueue([](int x){return x * 2;}, 10);

	std::cout << future1.get() << std::endl;
	std::cout << future2.get() << std::endl;
}
