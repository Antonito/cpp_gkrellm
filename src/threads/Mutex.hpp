#ifndef MUTEX_HPP_
#define MUTEX_HPP_

#include <pthread.h>

class Mutex
{
public:
  Mutex();
  ~Mutex();

  bool lock();
  bool trylock();
  bool unlock();

  bool isLocked() const;

private:
  Mutex(Mutex const &);
  Mutex &         operator=(Mutex const &);
  bool            m_isLocked;
  pthread_mutex_t m_mut;
};

#endif // !MUTEX_HPP_