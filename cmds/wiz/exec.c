// smash.c 2-22-95
 
#include "/doc/help.h"

inherit F_CLEAN_UP;
 
int main(object me, string arg)
{
	object ob;
	if (!arg) return notify_fail("指令格式: smash <living>\n");
	ob = find_player(arg);
	if (!ob) return notify_fail("找不到这个玩家。\n");
	message_vision("$N双手一举，一个焦雷将$n劈为飞灰！！\n",me,ob);
	ob -> save();
        BAN_D->dynamic_add(query_ip_number(ob));
	seteuid(ROOT_UID);
	destruct(ob);
	return 1;
}
 
int help(object me)
{
   write(@HELP
指令格式: exec <玩家>
将某个玩家踢出风云 
并将其IP暂时BAN掉
当风云重新REBOOT后，这个IP才可以再连线

also see ban
HELP
   );
   return 1;
}
