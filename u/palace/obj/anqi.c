// tea_leaf.c

#include <weapon.h>

inherit THROWING;
#include <ansi.h>
void create()
{
	set_name( "����ɳ" , ({ "sand", "poison sand" }) );
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("long",	"��ǿ��ɱ�����ľ޶��ޱȵĶ���ɳ\n");
		set("unit", "��");
		set("value", 10);
		set("base_unit", "��");
		set("base_weight", 1);
		set("base_value", 1);
	}
	set_amount(3);
	init_throwing(2);
	setup();
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
	victim->apply_condition("green_blood",random(10)+10);
	message_vision("$N���˶���ɳ�ϵĶ���\n", victim);
}
