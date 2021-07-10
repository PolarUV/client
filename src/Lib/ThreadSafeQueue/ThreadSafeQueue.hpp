#ifndef CLIENT_THREADSAFEQUEUE_HPP
#define CLIENT_THREADSAFEQUEUE_HPP

#include <queue>
#include <shared_mutex>
#include <condition_variable>

template<typename ObjType>
class Queue{
public:
    void AddToQueue(ObjType &obj){
        std::unique_lock lock(_queueMutex);
        _objQueue.push(&obj);
        _queueIsNotEmpty.notify_one();
    }

    ObjType &GetTask() {
        std::unique_lock guard(_queueMutex);

        _queueIsNotEmpty.wait(guard, [&]() noexcept { return !_objQueue.empty(); });

        auto &obj = *_objQueue.front();
        _objQueue.pop();

        return obj;
    }

private:
    std::queue<ObjType*> _objQueue{};
    std::mutex _queueMutex;
    std::condition_variable _queueIsNotEmpty;
};

#endif