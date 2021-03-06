// Copyright (C) 1995, by Tie Yu and Daniel Yu. All rights reserved.
// This software can not be used, copied, or modified in any form without
// the written permission from authors.
inherit ROOM;
void create()
{
        set("short", "沉香镇中心");
        set("long", @LONG
这里就算是沉香镇的中心广场了，广场的北面是一条小河流，河流的
旁边有一块大青石，就当做船夫的上岸的小码头。江南不愧被赞为鱼米之
乡，就连一个小镇的中心也显出不同一般的热闹。
LONG
        );
        set("exits", ([ /* sizeof() == 4 */
  "north" : __DIR__"cx4",
  "south" : __DIR__"cxs1",
  "east" : __DIR__"cxe1",
  "west" : __DIR__"nanbank",
]));
        set("objects", ([
        __DIR__"npc/fishseller": 1,
	__DIR__"npc/fishbuyer": 1,
	__DIR__"npc/ditou" : 2,
	__DIR__"npc/half_god" : 1,
	__DIR__"npc/pettrainer2" : 1,
                        ]) );
        set("outdoors", "chenxiang");
        set("coor/x",-500);
	set("coor/y",-500);
	set("coor/z",0);
	setup();
        replace_program(ROOM);
}
