
#include <ansi.h>
inherit ITEM;

void create()
{
        set_name("铁盒", ({ "box"}) );
        set_weight(300);
	set("unit", "个");
	set("long", "一个生满铁锈的铁盒。你可以试着把它打开(open)\n");
	set("opened", 0);
	set("value", 200);
}

int is_container() {return 1;}

void init()
{
	if(this_player()==environment())
		 add_action("do_open","open");
}

int do_open(string arg)
{
	object		me, ob;
	int		kar;
	
        if( !arg || arg != "box" )
                return notify_fail("你要打开什么？\n");
	me = this_player();
	ob = this_object();
	message_vision("$N小心地把$n打开。\n", me, ob);
	kar = me->query("kar");
	if( kar < 27 && random(5) != 3) { 
		message_vision(HIR "只听到＂咯＂的一声，接着从$n里射出几只黑色的银针，正打在$N的脸上！\n" NOR, me, ob);
		me->apply_condition("no_shadow", 10);
		message_vision(HIR "$N中了针上的毒！\n" NOR, me);
	}
	else {
		ob->set("opened",1);
        message_vision("$N小心地把$n打开。\n", me, ob);
	}
        return 1;
}

int is_locked()
{
return (int) this_object()->query("opened");
}
