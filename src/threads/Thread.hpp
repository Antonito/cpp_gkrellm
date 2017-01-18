#ifndef THREAD_HPP_
#define THREAD_HPP_

#include <pthread.h>

class Thread
{
public:
  explicit Thread(void *(func)(void *), void *arg);
  ~Thread();

  // Those functions return true on success, false otherwise
  bool startThread();
  bool stopThread();
  bool restartThread();

  // Getters
  bool isStarted() const;

private:
  // Disable copy
  Thread(Thread const &);
  Thread &operator=(Thread const &);

  bool      m_isStarted;
  pthread_t m_thread;
  void *(*m_func)(void *);
  void *m_arg;
};

#endif // !THREAD_HPP_
