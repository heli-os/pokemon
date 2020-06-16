#ifndef _POKEMON_ENVIRONMENT_HEADER_
#define _POKEMON_ENVIRONMENT_HEADER_
#include "nginx_common.h"

/// <summary>
/// 클라이언트 데이터 저장 함수
/// </summary>
/// <param name="userNo"></param>
/// <param name="flags"></param>
void environmentSave(int userNo, int flags);

/// <summary>
/// 로드된 세이브 파일을 파싱하는 함수
/// </summary>
/// <param name="pData"></param>
void environmentParse(const json_t* pData);

/// <summary>
/// 세이브 파일을 로드하는 함수
/// 로딩 시작을 서버에 알린다.
/// </summary>
/// <param name="userNo"></param>
void environmentLoad(int userNo);

#define BUF_SIZE 50000
#endif