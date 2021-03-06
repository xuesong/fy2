
inherit ROOM;

void create()
{
	set("short", "后院");
	set("long", @LONG
院子四角各种著一株参天松树，中央是一口水井。青石板铺成的
地面，没有任何杂草落叶。院子左面是一排厢房，右面是练武厅。不
时可以听到阵阵的拳风声从里面传出来。
LONG
	);
	set("exits", ([ 
  		"out" : __DIR__"wuroad4",
  		"north" : __DIR__"wudang4",
  		"south" : __DIR__"wudang5",
	]));
        set("item_desc", ([
                "jing": "武当弟子日常用的水井。你似乎可以试着钻(enter)进去。\n",
                "well": "武当弟子日常用的水井。你似乎可以试着钻(enter)进去。\n",
                "井": "武当弟子日常用的水井。你似乎可以试着钻(enter)进去。\n",
	]) );
        set("resource/water",1);
	set("outdoors", "wudang");
	set("coor/x",150);
	set("coor/y",-110);
	set("coor/z",50);
	set("coor/x",150);
	set("coor/y",-110);
	set("coor/z",50);
	set("coor/x",150);
	set("coor/y",-110);
	set("coor/z",50);
	set("coor/x",150);
	set("coor/y",-110);
	set("coor/z",50);
	setup();
}

void init()
{
        add_action("do_enter", "enter");
        add_action("do_fillwater", "fillwater");
}

int do_enter(string arg)
{
        object obj;
        object me;

        if(!arg || arg=="")
        {
                write("你要往哪里钻？\n");
                return 1;
        }
        me = this_player();
        if( arg == "jing" || arg == "well" || arg == "井")
        {
                message_vision("$N向四周看了一看，趁没人注意，深吸一口气钻进了井里。\n", me);
                me->move(__DIR__"jing.c");
                return 1;
        }
        else
        {
                write("你不可以往"+arg+"里钻！\n");
                return 1;
        }
}

int do_fillwater(string arg)
{
        object *list, ob;
        int i, can_fillwater;
        string dir;

        if( !arg || arg=="" ) return 0;

        if( arg=="skin" || arg=="wineskin" ) {
                list = all_inventory(this_player());
                i = sizeof(list);
                can_fillwater = 0;
                while (i--) {
                  if (((string)list[i]->query("liquid/type") == "alcohol") 
			|| ((string)list[i]->query("liquid/type") == "water")         ) {
                        ob = list[i];
                        can_fillwater = 1;
                        ob->set("liquid", ([
                                "type": "water",
                                "name": "清水",
                                "remaining": 30,
                                "drunk_apply": 6,
                        ]) );
                        write("你从井里装满了清水! \n");
                        return 1;
                   }
                }
                if (can_fillwater ==0) {
                        write("你没有装水的东西啊....\n");
                        return 1;
                }
        }
        else {
                write("你要往什么东西里灌水？");
        }
        return 1;
}

