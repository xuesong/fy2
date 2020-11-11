// Copyright (C) 1995, by Tie Yu and Daniel Yu. All rights reserved.
inherit ROOM;
void create()
{
  set("short","中天门");
  set("long",@LONG
中天门位泰山正中，地处黄岘岭，中溪在这蜿蜒而下，以甘冽的清
泉和悦耳的泉声迎接奋力登山的游人。一个巨大的门楼是中天门的胜景
依傍着嶙峋的山石，石雕门楼是那么的精巧，但又浑然天成，历代经无
数能工巧匠的描绘，中天门已经成为了一个永远留传的艺术史诗。再往
上便是出名的胜景---云步桥。
LONG
  );
  set("exits",([
	"down" : __DIR__"butian",
	"up" : __DIR__"buyun",
               ]));
        set("objects", ([
        "/d/fy/npc/beggar" : 3,
                        ]) );

        set("outdoors", "fengyun");
	set("coor/x",-490);
	set("coor/y",-320);
	set("coor/z",60);
	setup();
  	replace_program(ROOM);
}
