#ifdef _WIN32
#include <winsock.h>
#else
#include <sys/time.h>
#endif

#ifdef _WIN32
#include <sys/timeb.h>
#include <sys/types.h>
#include <winsock.h>
void gettimeofday(struct timeval* t,void* timezone)
{ struct _timeb timebuffer;
_ftime( &timebuffer );
t->tv_sec=timebuffer.time;
t->tv_usec=1000*timebuffer.millitm;
}
#endif

void mytime(double *t)
{
  static int sec = -1;
  struct timeval tv;
  gettimeofday(&tv, (struct timezone *)0);
  if (sec < 0) sec = tv.tv_sec;
  *t = (tv.tv_sec - sec) + 1.0e-6*tv.tv_usec;
}
