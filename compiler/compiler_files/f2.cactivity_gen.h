#ifndef __ACTIVITY_GEN_H__
#define __ACTIVITY_GEN_H__
#include <windows.h>
#include "consistency_api.h"
#include "activation_record.h"


enum ActivityTypes {ParForType = 0, ParBlockType = 1,ParMainType = 2};
enum CSWTypes {CSWMaster = 0, CSWSlave, CSWBoth,CSWNone};
extern __declspec(thread) unsigned long __CSCounter;
extern CRITICAL_SECTION DSM_STACK_CS;


class CActivity
{
	char __Dummy[PAGE_SIZE];
	static int *stack;
	static int my_esp;
	void Finalize(CActivationRecord *, unsigned long &);
	void csw(CActivationRecord *&);
	void __RunParBlock(CActivationRecord &, unsigned long );
	void __RunParBlock(int, int, ...);
	void __RunInPlaceParBlock(CActivationRecord *, int, int, ...);
	void __RunParFor(int , int , int , int , int , ...);
	void __RunInPlaceParFor(CActivationRecord *, int , int , int , int , int , ...);
	public :
	CActivity();
	void Run(CActivationRecord *);
	void CheckEsp(){}
	void InitGlobals(unsigned int stack_size)
	{
		InitializeCriticalSection(&DSM_STACK_CS);
		stack = (int *) dsm_malloc(stack_size);
	}
	void Init()
    {
        __CSCounter = 0;
    }
	void __SpawnParConstruct(CActivationRecord *);
int A[100];
int B[100];
int C[100];
int D[100];
int y;
int f2(CActivationRecord * ,int k);
                                      };

#endif
