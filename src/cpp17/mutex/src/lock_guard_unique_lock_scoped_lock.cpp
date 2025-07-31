#include <functional>
#include <iostream>
#include <mutex>
#include <vector>
#include <thread>

using namespace std;

struct bank_account
{
	explicit bank_account(int balance) : m_balance(balance) {}
	int m_balance;
	mutex m_balance_mutex;
};

void transfer_lock_guard(bank_account& from, bank_account& to, int amount)
{
	if (&from == &to)
		return;

	lock(from.m_balance_mutex, to.m_balance_mutex);

	// mutexes are already locked. We us RAII only for realsing them:
	const lock_guard lock1(from.m_balance_mutex, adopt_lock);
	const lock_guard lock2(to.m_balance_mutex, adopt_lock);
	from.m_balance -= amount;
	to.m_balance += amount;
}

void transfer_unique_lock(bank_account& from, bank_account& to, int amount)
{
	if (&from == &to)
		return;
	unique_lock<mutex> lock1(from.m_balance_mutex, defer_lock);
	unique_lock<mutex> lock2(to.m_balance_mutex, defer_lock);

	// This will cause a deadlock. We need to lock unique_lock objects:
	//lock(from.m_balance_mutex, to.m_balance_mutex);
	
	lock(lock1, lock2);

	from.m_balance -= amount;
	to.m_balance += amount;
}

void transfer_scoped_lock(bank_account& from, bank_account& to, int amount)
{
	if (&from == &to)
		return;

	const scoped_lock lock(from.m_balance_mutex, to.m_balance_mutex);

	from.m_balance -= amount;
	to.m_balance += amount;
}

int main()
{
	bank_account from(100), to(100);
	vector<thread> threads;
	threads.emplace_back(transfer_lock_guard, ref(from), ref(to), 50);
	threads.emplace_back(transfer_unique_lock, ref(to), ref(from), 50);
	threads.emplace_back(transfer_scoped_lock, ref(from), ref(to), 100);

	for (auto& thread : threads)
		thread.join();

	cout << "from balance: " << from.m_balance << ", to balance: " << to.m_balance << endl;
}

