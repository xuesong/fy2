// waterskin.c
#include <login.h>
inherit ITEM;
inherit F_LIQUID;
string *revive_loc= ({
        "/d/fy/church",
        "/u/guanwai/tower",
});
void create()
{
	set_name("大海碗", ({ "aiwan", "wan" }) );
	set_weight(700);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("long", "一个青瓷大海碗\n");
		set("unit", "个");
		set("value", 20);
		set("max_liquid", 15);
	}

	// The liquid contained in the container is independent, we set a copy
	// in each cloned copy.
	set("liquid", ([
		"type": "alcohol",
		"name": "孟婆汤",
		"remaining": 5,
		"drunk_apply": 6,
	]) );
}

int do_drink(string arg)
{
   int foo;
   foo=::do_drink(arg);
   if (!foo) return foo;
   if(this_player()->is_ghost())
   {
	this_player()->reincarnate();
	this_player()->unconcious();
	this_player()->move(revive_loc[random(sizeof(revive_loc))]);
	this_player()->set("startroom", base_name(environment(this_player())));
	message("vision",
                "你忽然发现前面多了一个人影，不过那人影又好像已经在那里\n"
                "很久了，只是你一直没发觉。\n", environment(this_player()), this_player());
   }	
  return 1;
}

