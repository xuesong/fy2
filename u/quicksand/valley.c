
inherit ROOM;

void create()
{
        set("short", "死谷");
        set("long", @LONG
死谷是一个名副其实的死地，四面峭壁如削，寸草不生。除了有几只飞鸟
从空中掠过，谷内死气沉沉，全无生机。
LONG
        );
        set("outdoors", "quicksand");
        set("objects", ([
                __DIR__"npc/redlama" : 1,
        ]) );

        set("coor/x",-1130);
	set("coor/y",-20);
	set("coor/z",-10);
	setup();
}
void init()
{
        add_action("climbing", "climb");
}

int climbing(string arg)
{
        object obj;
        object me;
        if(!arg || arg=="")
        {
                write("你要爬什么？\n");
                return 1;
        }
        if( arg == "valley" || arg == "up" || arg == "死谷")
        {
        me = this_player();
        message_vision("$N抓着突出的石角，慢慢的顺着谷壁爬了上去。\n", me);
        me->start_busy(2);
        call_out("fliping",2,me);
        me->stop_busy();
        return 1;
        }
        else
        {
                write("你不可以爬"+arg+"\n");
                return 1;
        }
}
int fliping(object me)
{
	if( !me->is_ghost()) {
        me->move(__DIR__"cliff");
        message_vision("$N顺着谷壁爬了上来。\n", me);
	}
        return 1;
}

