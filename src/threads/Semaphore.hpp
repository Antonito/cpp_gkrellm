#ifndef Semaphore_HPP_
#define Semaphore_HPP_

#include <semaphore.h>

class Semaphore
{
public:
  explicit Semaphore(unsigned int val);
  ~Semaphore();

  bool wait();
  bool trywait();
  bool post();

private:
  Semaphore(Semaphore const &);
  Semaphore &operator=(Semaphore const &);
  sem_t      m_sem;
};

#endif // !Semaphore_HPP_