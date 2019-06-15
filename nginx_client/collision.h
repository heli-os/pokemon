#include "nginx_common.h"
#include "player.h"
#include "object.h"

object_info object_list[OBJECT_COUNT];
bool isCollision(player_status _player);