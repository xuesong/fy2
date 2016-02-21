// shadowsteps.c

inherit SKILL;

string *dodge_msg = ({
	"$nһ�С���Ӱ���Ρ�����һ��,���Ƶ�һ���������Բ������Ƶ��ĵط���\n",
	"ֻ��$n������ǰ,��Ȼ�硸����֮�������˷���,����������\n",
	"$nʹ������Ӱ���١�����Ȼ�������ټ���\n",
	"$n����һ�㣬һ�С��������롹��Ӱ��Ȼ��Ϊ����,��ͣ��ת,�����޷����\n",
	
});

int valid_enable(string usage)
{
	return (usage=="dodge") || (usage=="move");
}

string query_dodge_msg(string limb)
{
	return dodge_msg[random(sizeof(dodge_msg))];
}

int practice_skill(object me)
{
	if( (int)me->query("kee") < 30
	||	(int)me->query("force") < 3 )
		return notify_fail("��������������������������ٻ�Ӱ������\n");
	me->receive_damage("kee", 30);
	me->add("force", -3);
	return 1;
}
int effective_level() { return 12;}

int learn_bonus()
{
	return 0;
}
int practice_bonus()
{
	return 0;
}
int black_white_ness()
{
	return 10;
}

string perform_action_file(string action)
{
        return CLASS_D("shaolin") + "/shadowsteps/" + action;
}
