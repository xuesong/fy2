
inherit SKILL;

string *dodge_msg = ({
	"$n一招「金蝉脱壳」，步法轻灵，身形飘动，$N的招式落空。\n",
	"只见$n呆立不动，等$N的招式用老，一式「假痴不癫」，轻松地躲在一旁。\n",
	"$n使出「欲擒故纵」，斜斜地窜开。\n",
	"$n左足一点，一招「暗渡陈仓」腾空而起，避了开去。\n",
	"可是$n使一招「以逸待劳」，步法飘忽不定，$N的攻击失去了准头。\n",
	"$n经藉一招「隔岸观火」，身形飘退，轻轻闪过。\n",
	"但是$n一招「李代桃僵」使出，身形晃动，幻出数道身影，自己早已飘出三丈开外！\n",

});

int valid_enable(string usage)
{
	return (usage=="dodge") ;
}

int valid_learn(object me)
{
	if( (int)me->query("max_force") < 100 )
		return notify_fail("你的内力不够，没有办法练神机步。\n");

	return 1;
}

string query_dodge_msg(string limb)
{
	return dodge_msg[random(sizeof(dodge_msg))];
}

int practice_skill(object me)
{
	if( (int)me->query("kee") < 30
	||	(int)me->query("force") < 3 )
		return notify_fail("你的气或内力不够，不能练神机步法。\n");
	me->receive_damage("kee", 30);
	me->add("force", -3);
	return 1;
}
int effective_level() { return 19;}

int learn_bonus()
{
	return -90;
}
int practice_bonus()
{
	return -50;
}
int black_white_ness()
{
	return 40;
}

string perform_action_file(string action)
{
        return CLASS_D("shaolin") + "/shenji-steps/" + action;
}

