inherit ROOM;
void create()
{
        set("short", "农家");
        set("long", @LONG
这是一户很简朴的农家，土坯垒成的墙冬暖夏凉，茅草盖顶，虽然简陋却
足以遮风僻雨。门敞开着，屋内陈设十分简单，而且静悄悄的，主人好象出去
做活了。墙上挂着一些常用的农具，泥痕还很新鲜。
LONG
        );

        set("exits", ([ /* sizeof() == 4 */
  	"east" : __DIR__"nongjia",
	]) );

   set("objects", ([
      __DIR__"obj/wall": 1,
   ]) );

   set("coor/x",180);
	set("coor/y",-30);
	set("coor/z",0);
	setup();
}

void reset()
{
	object *inv;
        object item1, item2, item3, wall;
        ::reset();
        wall = present("wall", this_object());
        inv = all_inventory(wall);
        if( !sizeof(inv)) {
        item1 = new(__DIR__"obj/liandao");
        item1->move(wall);
        item2 = new(__DIR__"obj/hook");
        item2->move(wall);
        item3 = new(__DIR__"obj/raincoat");
        item3->move(wall);
        }
}

