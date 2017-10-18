#include <iostream>
#include <mutex>
#include <thread>
#include <condition_variable>
#include <queue>
#include <string>
#include <vector>

using namespace std;

static vector<string> messageList {"saman", "revan", "bastila", "galen", "juno", "anakin", "padme"};
static queue<string> messageQueue;
static mutex queueMutex;
static condition_variable messageCondition;

void producer()
{
    for(const auto& str : messageList)
    {
        unique_lock<mutex> lock{queueMutex};
        cout << "push " << str << endl; // I use lock for synchronizing cout
        messageQueue.push(str);
        lock.unlock();  //I should release the lock before notifying consumer
        messageCondition.notify_one();  //notify consumer if it's blocked, in this case, if messageQueue.empty() is true.
                                        //Note that notify_one do nothing if we don't have any blocked threads. So when
                                        //consumer calls wait after producer called notify_one, it won't be unblocked
                                        //even though notify_one have been called before. In other words, notify_one can unblock
                                        //those threads which have called wait before itself and it won't unblock those
                                        //threads which will call wait in the future.
    }
}

void consumer()
{
    for (vector<string>::size_type i = 0; i < messageList.size(); ++i)
    {
        unique_lock<mutex> lock{queueMutex};
        messageCondition.wait(lock, []{return !messageQueue.empty();});    //wait if messageQueue.empty() is true
        auto message = messageQueue.front();
        messageQueue.pop();
        cout << "pop " << message << endl;  //I use lock for synchronizing cout
    }   //Here lock will be released
}

int main()
{
    thread producerThread {producer};
    thread consumerThread {consumer};
    producerThread.join();
    consumerThread.join();
}
