#include <stdio.h>
#include "activity_gen.h"
#include "consistency_api.h"
__declspec(thread) unsigned long __CSCounter = 0;
__declspec(thread) unsigned long __CSHapenned = 0;
CRITICAL_SECTION DSM_STACK_CS;
__declspec(thread) int *old_esp;
int *CActivity::stack = (int *) 0;
int CActivity::my_esp = 0xffff;
__declspec(thread) unsigned long childs_number = 0;
__declspec(thread) BOOL msg_sent = FALSE;
__declspec(thread) unsigned long parfor_start = 0;
__declspec(thread) unsigned long parfor_end  = 0;
__declspec(thread) unsigned long parfor_step = 0;
extern BOOL exit_system;
#pragma check_stack(off)




void CActivity::f3(CActivationRecord *__spRec,int k,int *v)
{
{
  int j;
  int y;
  y=k;
  for (j=0; ((j<k)&&(A[j]<100)); j++)
    y=(y*A[j]);
  *v=y;
}

}
                                                        