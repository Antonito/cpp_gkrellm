#include "Semaphore.hpp"

Semaphore::Semaphore(unsigned int val)
{
  sem_init(&m_sem, 0, val);
}

Semaphore::~Semaphore()
{
  sem_destroy(&m_sem);
}

bool Semaphore::wait()
{
  return (!sem_wait(&m_sem));
}

bool Semaphore::trywait()
{
  return (!sem_trywait(&m_sem));
}

bool Semaphore::post()
{
  return (!sem_post(&m_sem));
}