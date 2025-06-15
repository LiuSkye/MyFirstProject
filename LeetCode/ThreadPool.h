/*
 * @Author: Skye
 * @Date: 2021-07-22 14:08:03
 * @LastEditTime: 2021-09-13 10:55:42
 * @Description: 线程池
 * Skye:'Never stop!'
 */

#include <assert.h>
#include <atomic>
#include <condition_variable>
#include <deque>
#include <functional>
#include <iostream>
#include <mutex>
#include <thread>

#include <semaphore.h>

using namespace std;
class NonCopyable {
protected:
    NonCopyable() { }
    ~NonCopyable() { }

private:
    NonCopyable(const NonCopyable&) = delete;
    NonCopyable& operator=(const NonCopyable&) = delete;
};

typedef function<void()> Task;
class ThreadPool : public NonCopyable {
public:
    explicit ThreadPool(int max_task_size, int thread_num = 8)
    {
        assert(thread_num > 0);
        _max_size = max_task_size;
        _is_run = false;
        _thread_num = thread_num;
    }
    ~ThreadPool()
    {
        // 回收线程
        Stop();
        for (int i = 0; i < _threads.size(); ++i) {
            _threads[i]->join();
            cout << "thread:" << i << "stop" << endl;
            delete _threads[i];
        }
    }

    void Start()
    {
        _is_run = true;
        Init(_thread_num);
    }

    void Stop()
    {
        _is_run = false;
        _cond_is_empty.notify_all();
    }

    bool AddTask(Task task)
    {
        // 如果满了会阻塞或者返回false
        unique_lock<mutex> mtx(_mtx);
        // while (_tasks.size() >= _max_size)
        // {
        //     _cond_is_full.wait(mtx);
        // }
        if (_tasks.size() >= _max_size) {
            return false;
        }
        _tasks.push_back(move(task));
        mtx.unlock();
        _cond_is_empty.notify_one();
        return true;
    }

private:
    void Init(int num)
    {
        while (num--) {
            _threads.emplace_back(new thread([&] {
                unique_lock<mutex> locker(_mtx);
                while (_is_run) {
                    // 检查是否为空，加锁，取任务
                    if (!_tasks.empty()) {
                        auto task = std::move(_tasks.front());
                        _tasks.pop_front();
                        locker.unlock();
                        task();
                        cout << "solve a task" << endl;
                        // 抢锁准备去取下一个任务
                        locker.lock();
                    } else {
                        _cond_is_empty.wait(locker);
                    }
                }
            }));
        }
    }

private:
    deque<Task> _tasks;
    int _max_size;
    mutex _mtx;
    // condition_variable _cond_is_full;
    condition_variable _cond_is_empty;
    vector<thread*> _threads;
    int _thread_num;
    atomic<bool> _is_run;
};

/////////////////////////////////////////////////////////////////
/**
 * @description: 信号量实现生产者消费者队列
 * @param {*}
 * @return {*}
 */
template <typename T>
class TaskQueue : public NonCopyable {
public:
    TaskQueue(int capacity = 30)
        : _capacity(capacity)
        , _task_que(capacity)
    {
        sem_init(&_sem_empty, 0, _capacity);
        sem_init(&_sem_full, 0, 0);
    }
    ~TaskQueue()
    {
        // 释放资源
        sem_destroy(&_sem_empty);
        sem_destroy(&_sem_full);
    }

    T Consume()
    {
        // 先检查再上锁
        sem_wait(&_sem_full); // 原子操作
        lock_guard<mutex> locker(_mtx);

        auto task = move(_task_que.front());
        _task_que.pop_front();

        sem_post(&_sem_empty);
        return task;
    }

    void Product(T task)
    {
        sem_wait(&_sem_empty);
        lock_guard<mutex> locker(_mtx);

        _task_que.push_back(move(task));
        sem_post(&_sem_full);
    }

    size_t size() const
    {
        lock_guard<mutex> locker(_mtx);
        return _task_que;
    }

private:
    int _capacity;
    deque<T> _task_que;
    mutable mutex _mtx;
    sem_t _sem_empty;
    sem_t _sem_full;
};

/**
 * @description: 条件变量实现生产者消费者队列
 * @param {*}
 * @return {*}
 */
template <typename T>
class BoundedBlockingQueue : public NonCopyable {
public:
    explicit BoundedBlockingQueue(int max_size)
        : _mtx()
        , _queue(max_size)
    {
    }

    void Push(const T& x)
    {
        unique_lock<mutex> locker(_mtx);
        while (_queue.size() >= _max_size) {
            _cond_full.wait(locker);
        }
        assert(_queue.size() >= _max_size);
        _queue.push_back(x);
        _cond_empty.notify_one();
    }

    T Take()
    {
        unique_lock<mutex> locker(_mtx);
        while (_queue.empty()) {
            _cond_empty.wait(locker);
        }
        auto front = move(_queue.front());
        _queue.pop_front();
        _cond_full.notify_one();
        return front;
    }

    bool Empty() const
    {
        lock_guard<mutex> locker(_mtx);
        return _queue.empty();
    }

    bool Full() const
    {
        lock_guard<mutex> locker(_mtx);
        return _queue.size() >= _max_size;
    }

    size_t size() const
    {
        lock_guard<mutex> locker(_mtx);
        return _queue.size();
    }

    size_t capacity() const
    {
        return _max_size;
    }

private:
    mutable mutex _mtx;
    std::deque<T> _queue;
    size_t _max_size;
    condition_variable _cond_empty;
    condition_variable _cond_full;
};