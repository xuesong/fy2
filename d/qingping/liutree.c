//XXDER
inherit ROOM;

void create()
{
        set("short", "柳树上");
        set("long", @LONG
柳树很大，由于树横卧在水面上，所以并不高。坐在这里，你的脚几乎可以
碰到水面，微风袭来，柳条轻佛着你的面颊，好似情人的手一般得温柔。几条锦
鲤在树下的水中悠闲地游来游去，不远处的小桥倒映在水中，从这里看去别有一
番景致。
LONG
        );

   set("exits", ([ /* sizeof() == 4 */
      "down" : __DIR__"northpond",
   ]));

   set("outdoors", "qingping");
   set("coor/x",190);
        set("coor/y",2010);
        set("coor/z",10);
   setup();
}

int fish_notify(object obj, int i)
{
   object me, room, fish, *inv, bait;
   int llvl;

   me = this_player();
   llvl = (int)me->query("kar");
	
   switch (i) { 
   case 0:
      bait = present("qiu yin", obj);
      if(!objectp(bait)) {
      message("vision",me->name() + "掏出了" + obj->name() + "又放了回去。\n", environment(me), me);
      tell_object(me, obj->name() + "上没有饵怎么可以钓鱼呢 ? \n");
      }
   else {
      message_vision("$N坐在树干上静静的开始垂钓。 \n" , me);
      me->start_busy(3);
      if(llvl > 15) {
         if(random(100) < llvl) {
            tell_object(me, "无聊中你注意到桥头雪白的石头上似乎有一块黑斑。\n");
            me->set_temp("marks/bridge", 1);
         }
      }
      else {
         if(random(300) < llvl) {
            tell_object(me, "无聊中你注意到桥头雪白的石头上似乎有一块黑斑。\n");
            me->set_temp("marks/bridge", 1);
         }
      }
      destruct(bait);
      remove_call_out("do_fishing");              
      call_out("do_fishing", 5, me);
      }
   break;
   }
   return 0;
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
         message_vision("鱼钩上钓着一条鱼 !!  \n", me);
         fish = new(__DIR__"obj/fish");
         fish->move(me);
         break;
      }
   }
   return;
}

