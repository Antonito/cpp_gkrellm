#include "Mutex.hpp"

Mutex::Mutex() : m_isLocked(false)
{
  pthread_mutex_init(&m_mut, NULL);
}

Mutex::~Mutex()
{
  if (m_isLocked)
    {
      unlock();
    }
  pthread_mutex_destroy(&m_mut);
}

bool Mutex::lock()
{
  if (!pthread_mutex_lock(&m_mut))
    {
      m_isLocked = true;
      return (true);
    }
  return (false);
}

bool Mutex::trylock()
{
  if (!pthread_mutex_trylock(&m_mut))
    {
      m_isLocked = true;
      return (true);
    }
  return (false);
}

bool Mutex::unlock()
{
  if (!pthread_mutex_unlock(&m_mut))
    {
      m_isLocked = false;
      return (true);
    }
  return (false);
}

bool Mutex::isLocked() const
{
  return (m_isLocked);
}
