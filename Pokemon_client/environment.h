#ifndef _POKEMON_ENVIRONMENT_HEADER_
#define _POKEMON_ENVIRONMENT_HEADER_
#include "nginx_common.h"

void environmentSave(int userNo, int flags);
void environmentParse(const json_t* pData);
void environmentLoad(int userNo);

#endif