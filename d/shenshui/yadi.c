// TIE@FY3 ALL RIGHTS RESERVED
inherit ROOM;
void create()
{
        set("short", "崖底");
        set("long", @LONG
石头是黑色的，浪似乎也是黑色的，浪头打到崖底的石头上溅起朵朵白
色的水花，你用尽浑身的力气也挣脱不了浪头的束缚，你终于向大自然的力
量屈服了，任凭海浪带着你上下沉浮。
LONG
        );
   set("outdoors","shenshui");
        set("coor/x",190);
        set("coor/y",12310);
        set("coor/z",-70);
   setup();
}

void init()
{
   if(interactive(this_player()))
   call_out("do_flush",30,this_player());
}

void do_flush(object me)
{
   object room;

   if(!me || environment(me) != this_object())
   return;
   tell_object(me,"\n突然一个大浪把你卷了出去！\n\n");
   room = find_object(__DIR__"ocean1");
   if(!objectp(room)) room= load_object(__DIR__"ocean1");
   me->move(room);
}


