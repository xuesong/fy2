inherit ROOM;
#include <ansi.h>
#include <command.h>

void create()
{
        set("short", "崖底");
        set("long", @LONG
在你的面前是一个小湖，湖水泛著粼光，轻柔地拍打著岸边的细沙。
透过清澈的湖水，你可以看到在水中嘻戏的鱼虾，还有随著水波婆娑起舞
的水草。岸边有一些矮小的灌木，灌木丛后是一道高耸入云的危崖，给人
以高不可攀的感觉。
LONG
        );
        set("item_desc", ([
                "细沙": "洁白的沙滩上露出一角旧布。\n",
                "危崖": "崖壁如同刀削的一样般，滑不留人，上面寸草不生。抬头望，\n你隐约可见半崖上突出一块白色的山石。\n",
        ]) );
	set("objects", ([ 
		__DIR__"obj/sand" : 1,
	]));
	set("outdoors","fengyun");
        set("coor/x",200);
	set("coor/y",-30);
	set("coor/z",20);
	setup();
}

void init()
{
	add_action("do_climb", "climb");
	add_action("do_dive", "dive");
}

void reset()
{
        object          *inv;
        object          con, item;
        int             i;

        ::reset();
        con = present("sand", this_object());
        inv = all_inventory(con);
        if( sizeof(inv) != 1) {
                for(i=sizeof(inv)-1; i>=0; i--) destruct(inv[i]);
                item = new(__DIR__"obj/oilbag");
                item->move(con);
        }
}

int do_climb(string arg)
{
        object 	me;
	int	mlvl;

	if(!arg || arg != "危崖") {
		write("你要爬什么？\n");
		return 1;
	}
	me = this_player();
	mlvl = (int)me->query_skill("move");
	if(mlvl < 70) 
		message_vision(HIY "\n$N奋力向上爬去，爬了不到两三丈，只觉的手脚发软，向下滑了下去。\n" NOR, me);
	else {
		message_vision(HIY "\n$N小心翼翼地向上爬去，身形慢慢被云雾遮掩。\n" NOR, me);
		me->move(__DIR__"whiterock");
	}
	return 1;
}

int do_dive()
{
        object *inv,me;
        object bottom;
        int i;
	string	objname;

        me = this_player();
	inv = all_inventory(me);
	for(i=0; i<sizeof(inv); i++) {
		objname = (string)inv[i]->query("name");
		if( objname != "油皮袋" && objname != "芦苇")
	       		DROP_CMD->do_drop(me, inv[i]);
	}
        message_vision("$N脱光了所有衣服，一个猛子扎入湖水中．\n",me);
        bottom = load_object(__DIR__"bottom1");
        if(bottom) me->move(bottom);
        return 1;
}

