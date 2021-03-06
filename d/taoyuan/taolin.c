inherit ROOM;
void create()
{
        set("short", "桃林");
        set("long", @LONG
这是一片茂密的桃树林，林中芳草鲜美，落英缤纷，一层淡淡的薄雾，混
合着青青的草香，弥漫在空气之中。偶尔的一两声鸟鸣，愈发地显出幽静来。
这里的小路已被落花铺满，早已辨不出痕迹来。
LONG
        );
        set("exits", ([ /* sizeof() == 4 */
  "east" : __DIR__"taolin1",
  "west" : "/u/wudang/xiaozhen",
]));

	set("item_desc", ([
	    "桃树": "粉云彩霞般的桃花，热热闹闹地开满了枝头。\n",
	    "peach tree": "粉云彩霞般的桃花，热热闹闹地开满了枝头。\n",
	]) );

 	set("objects", ([	
	__DIR__"obj/grass": 1,
	]) );

   	set("outdoors","taoyuan");
        set("coor/x",110);
	set("coor/y",-30);
	set("coor/z",0);
	setup();
}


void reset()
{
   object *inv;
   object item1, item2, grass;
   ::reset();

   grass = present("grass", this_object());
   inv = all_inventory(grass);
   if( !sizeof(inv)) {
      item1 = new(__DIR__"obj/petal");
      item2 = new(__DIR__"obj/mushroom");
      item1->move(grass);
      item2->move(grass);
   }
}

