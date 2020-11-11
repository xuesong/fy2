// Copyright (C) 1995, by Tie Yu and Daniel Yu. All rights reserved.
// This software can not be used, copied, or modified in any form without
// the written permission from authors.
#include <room.h>
inherit ROOM;
void create()
{
  set("short","济南城口");
  set("long",@LONG
这里就是济南城的入口，也就是丐帮和朱砂帮的地盘了。
一进济南城便是朱砂帮的赌场快意堂。
LONG
  );
  set("exits",([
         "north"  :"/d/qianfo/tanghuai.c",
	 "south" : __DIR__"casino1",
               ]));
        set("outdoors", "jinan");
  	set("coor/x",30);
	set("coor/y",1990);
	set("coor/z",1);
	setup();
        replace_program(ROOM);

}

