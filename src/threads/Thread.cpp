#include "Thread.hpp"

Thread::Thread(void *(func)(void *), void *arg)
    : m_isStarted(false), m_thread(0), m_func(func), m_arg(arg)
{
}

Thread::~Thread()
{
  if (m_isStarted)
    {
      stopThread();
    }
}

bool Thread::startThread()
{
  if (m_isStarted == false &&
      pthread_create(&m_thread, NULL, m_func, m_arg) == 0)
    {
      m_isStarted = true;
      return (true);
    }
  return (false);
}

bool Thread::stopThread()
{
  if (!pthread_cancel(m_thread) && !pthread_join(m_thread, NULL))
    {
      return (true);
    }
  return (false);
}

bool Thread::restartThread()
{
  if (m_isStarted)
    {
      stopThread();
    }
  startThread();
  return (true);
}

bool Thread::isStarted() const
{
  return (m_isStarted);
}