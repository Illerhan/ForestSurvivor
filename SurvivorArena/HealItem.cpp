#include "HealItem.h"

void HealItem::heal(Player* player)
{
	player->set_hp(player->get_hp()+healAmount_);
}
