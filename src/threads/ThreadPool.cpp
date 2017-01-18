#include "ThreadPool.hpp"

ThreadPool::ThreadPool()
{
}

ThreadPool::~ThreadPool()
{
  stopAll();
  for (std::vector<Thread *>::iterator it = m_threads.begin();
       it != m_threads.end(); ++it)
    {
      delete *it;
    }
  m_threads.clear();
}

void ThreadPool::addThread(void *(func)(void *), void *arg)
{
  m_threads.push_back(new Thread(func, arg));
}

bool ThreadPool::removeThread(size_t ndx)
{
  if (getNbThreads() <= ndx)
    {
      return (false);
    }
  m_threads[ndx]->stopThread();
  delete m_threads[ndx];
  m_threads.erase(m_threads.begin() + static_cast<signed>(ndx));
  return (true);
}

bool ThreadPool::startAll()
{
  bool ret = true;

  for (std::vector<Thread *>::iterator it = m_threads.begin();
       it != m_threads.end(); ++it)
    {
      if ((*it)->startThread() == false)
	{
	  ret = false;
	}
    }
  return (ret);
}

bool ThreadPool::stopAll()
{
  bool ret = true;

  for (std::vector<Thread *>::iterator it = m_threads.begin();
       it != m_threads.end(); ++it)
    {
      if ((*it)->stopThread() == false)
	{
	  ret = false;
	}
    }
  return (ret);
}

bool ThreadPool::restartAll()
{
  bool ret = true;

  for (std::vector<Thread *>::iterator it = m_threads.begin();
       it != m_threads.end(); ++it)
    {
      if ((*it)->restartThread() == false)
	{
	  ret = false;
	}
    }
  return (ret);
}

size_t ThreadPool::getNbThreads() const
{
  return (m_threads.size());
}

Thread &ThreadPool::operator[](size_t ndx)
{
  if (ndx > getNbThreads())
    {
      throw std::exception();
    }
  return (*m_threads[ndx]);
}
