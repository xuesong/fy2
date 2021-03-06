#include <ansi.h>
inherit ROOM;
void create()
{
        set("short", "草坪");
        set("long", @LONG
梧桐树后俨然一方小小天空，宽大的梧桐树叶湿润绿厚，叶叶心心、舒
卷有馀情，微风中徐徐摆动。一张石桌，两个石凳端端正正地摆在小草坪中
央，小河无声无息地从你身旁绕了个圈儿流过，一股清新的凉风从河面上吹
来，你不由得觉得精神为之一振，一句不知何人的诗涌入脑中：落叶流水杳
然去 别有天地非人间 ．．
LONG
        );
        set("exits", ([ 
	"south" : __DIR__"grassland",
	]) );

	set("item_desc", ([
           "river" : "一条清澈的小河，河里有小鱼在游动。\n",
           "小河" : "一条清澈的小河，河里有小鱼在游动。\n",
	]) );
	
	set("outdoors","taoyuan");
        set("coor/x",220);
	set("coor/y",0);
	set("coor/z",0);
	setup();
}

void fish_notify(object obj, int i)
{
   object me, room, fish, *inv, bait;

   me = this_player();
	
   switch (i) { 
   case 0:
      bait = present("qiu yin", obj);
      if(!objectp(bait)) {
      message("vision",me->name() + "掏出了" + obj->name() + "又放了回去。\n", environment(me), me);
      tell_object(me, obj->name() + "上没有饵怎么可以钓鱼呢 ? \n");
      }
   else {
      message_vision("$N挥动了一下," + obj->name() + "在空中划了一道漂亮的弧线, 鱼钩落入了水中. \n" , me);
      destruct(bait);
      remove_call_out("do_fishing");              
      me->start_busy(2);
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
