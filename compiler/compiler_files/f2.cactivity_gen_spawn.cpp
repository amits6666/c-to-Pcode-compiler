#include "activity_gen.h"


void CActivity::__SpawnParConstruct(CActivationRecord *__spRec)
{
if (__spRec->GetSize() == 0)
	return;
va_list __p  = __spRec->GetParams(0);
unsigned long sel_number = __spRec->GetSelNumber(0);
__spRec->RemoveActivity(0);
	switch(sel_number) {
	case 0: 
		main(__spRec);
		break;
	
}
}
