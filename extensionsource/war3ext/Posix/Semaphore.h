/////////////////////////////////////////////////////////////////////
//  Written by Phillip Sitbon
//  Copyright 2003
//
//  Posix/Semaphore.h
//    - Resource counting mechanism
//
/////////////////////////////////////////////////////////////////////

#ifndef _Semaphore_Posix_
#define _Semaphore_Posix_

#include <semaphore.h>

class Semaphore
{
  sem_t S;

  public:
  Semaphore( int init = 0 )
  { sem_init(&S,1,init); }

  virtual ~Semaphore()
  { sem_destroy(&S); }

  void Wait()
  { sem_wait((sem_t *)&S); }

  int Wait_Try()
  //{ return (sem_trywait((sem_t *)&S)?errno:0); } //returns -1 if did not acquire, 0 if acquired
  { return  (sem_trywait((sem_t *)&S)==-1  )?0:1 ; }

  //post / free
  int Signal()
  { return (sem_post((sem_t *)&S)?errno:0); }

  //get value
  int Value()
  {
	  int V = -1;
	  sem_getvalue((sem_t *)&S,&V);
	  return V;
  }

  void Reset( int init = 0 )
  { sem_destroy(&S); sem_init(&S,0,init); }
};

#endif // !_Semaphore_Posix_
