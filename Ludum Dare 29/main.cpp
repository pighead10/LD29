#include "stdafx.h"
#include "SFLD.h"
#include "StateManager.h"
#include "BaseState.h"

#define _HAS_ITERATOR_DEBUGGING 0
#define _SECURE_SCL 0
#define _SECURE_SCL_THROWS 0

int main(int argc, char* argv[])
{
	SFLD* sfld = new SFLD();
	sfld->start();
	delete sfld;
	return 0;
}