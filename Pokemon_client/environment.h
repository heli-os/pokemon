#ifndef _POKEMON_ENVIRONMENT_HEADER_
#define _POKEMON_ENVIRONMENT_HEADER_
#include "nginx_common.h"

void environmentSave(int userNo);
void environmentParse(const json_t* pData);
void environmentLoad(int userNo);

#endif