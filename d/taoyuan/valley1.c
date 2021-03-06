inherit ROOM;
void create()
{
        set("short", "山谷");
        set("long", @LONG
树林到了此处逐渐变得稀疏起来，眼前赫然出现一座千层叠翠、万里点苍的山峰，
围成一处幽谷，中有一泓清潭，泉水从峰间奔流而下，喷珠泄玉，直入清潭。几只白尾
巴的野兔，正在潭边悠闲的喝水。此处空气清凉湿润，沁人心肺，四周却看不见任何明
显的出路，看来，你只好四处转转看了。
LONG
        );
        set("item_desc", ([
           "清潭":  "清潭明澈见底，里面小鱼小虾皆若空游无所依。\n",
           "pond":  "清潭明澈见底，里面小鱼小虾皆若空游无所依。\n",
        ]));
        set("exits", ([ /* sizeof() == 4 */
   "south" : __DIR__"taolin1",
]));
        set("outdoors","taoyuan");
        set("coor/x",150);
	set("coor/y",-30);
	set("coor/z",0);
	setup();
}
void init()
{
   add_action("do_around", "around");
}

int do_around(string arg)
{
   object me, room;

   me = this_player();
   tell_object(me, "你转来转去，也没找到出口，你迷了路！！\n\n");
   room = find_object(__DIR__"valley2");
   if(!objectp(room)) room=load_object(__DIR__"valley2");
   me->move(room);

   return 1;
}

void fish_notify(object obj, int i)
{
   object me, room, fish, *inv, bait;

   me = this_player();
	
   switch (i) { 
   case 0:
      bait = present("dead qu", obj);
      if(!objectp(bait)) {
      message("vision",me->name() + "掏出了" + obj->name() + "又放了回去。\n", environment(me), me);
      tell_object(me, obj->name() + "上没有饵怎么可以钓鱼呢 ? \n");
      }
   else {
      message_vision("$N挥动了一下," + obj->name() + "在空中划了一道漂亮的弧线, 鱼钩落入了水中. \n" , me);
      destruct(bait);
      remove_call_out("do_fishing");              
      call_out("do_fishing", 5, me);
      }
   break;
   }
   return;
}

void do_fishing(object me)
{
   object 	fish;

   if(me && environment(me) == this_object()) {
   message_vision("$N很快又扯动了一下鱼杆, " , me);
   switch (random(3)) {
      case 0:
         message_vision("却什么都没钓上来 ! \n", me);
         break;
      case 1:
         message_vision("什么都没钓上来 , 鱼饵却被鱼吃了 !!  \n", me);
         break;
      case 2:
         message_vision("鱼钩上钓这一条大鱼 !!  \n", me);
         fish = new(__DIR__"obj/fish");
         fish->move(me);
         break;
      }
   }
   return;
}
