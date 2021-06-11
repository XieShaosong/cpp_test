#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/shm.h>
#include <sys/shm.h>
using namespace std;

template <typename T>
class SharedMemory
{
public:
  SharedMemory();
  bool create(key_t id, size_t size);
  bool connect();
  void setting();
  void remove();

public:
  T *shared;

private:
  void *shm;
  int shmid;
};

class Task
{
public:
  int written;
  string text; 
};

template <typename T>
SharedMemory<T>::SharedMemory()
{
  shared = NULL;
  shm = NULL;
  shmid = 1;
}

template <typename T>
bool SharedMemory<T>::create(key_t id, size_t size)
{
  shmid = shmget(id, size, 0666|IPC_CREAT);
  if (shmid == -1)
    return false;
  else
    return true;
}

template <typename T>
bool SharedMemory<T>::connect()
{
  shm = shmat(shmid, 0, 0);
  if (shm == (void*)-1)
    return false;
  else
    return true;
}

template <typename T>
void SharedMemory<T>::setting()
{
  shared = (T *)shm;
}

template <typename T>
void SharedMemory<T>::remove()
{
  shmdt(shm);
  shmctl(shmid, IPC_RMID, 0);
}

int main()
{
  SharedMemory<Task> shm;
  shm.create((key_t)123456, 4096);
  shm.connect();
  shm.setting();

  shm.shared->written = 0;

  while (1)
  {
    while(shm.shared->written == 1)
    {
      sleep(1);
      shm.shared->written = 0;
    }
    
    shm.shared->text = "1231231adfadf";
    shm.shared->written = 1;

    cout << "111" << endl;
  }
  
  shm.remove();
  sleep(2);
  return 0;
}