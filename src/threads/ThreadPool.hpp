#ifndef THREADPOOL_HPP_
#define THREADPOOL_HPP_

#include <vector>
#include "Thread.hpp"

class ThreadPool
{
public:
  ThreadPool();
  ~ThreadPool();

  void addThread(void *(func)(void *), void *arg);
  bool removeThread(size_t ndx);

  bool startAll();
  bool stopAll();
  bool restartAll();

  // Getters
  size_t getNbThreads() const;
  Thread &operator[](size_t ndx);

private:
  ThreadPool(ThreadPool const &);
  ThreadPool &          operator=(ThreadPool const &);
  std::vector<Thread *> m_threads;
};

#endif // !THREADPOOL_HPP_
