// TIE@FY3 ALL RIGHTS RESERVED
inherit ROOM;
void create()
{
        set("short", "清凉台");
        set("long", @LONG
这乃黄山观日出的所在，每天清晨，当人登上三面凌空的危岩向
北海远眺，只见“白云倒海忽平铺，点点螺髻时有无”，巍峨的群峰
大都淹没在云海之中。接着天际的鱼肚白变成了五彩瑰丽的朝霞，云
层中射出的红光越来越亮，直到那轮火球冲破云海，腾空而出。久久
地让人回味。
LONG
        );
        set("exits", ([ 
  "southwest" : __DIR__"diezhang",
  "northwest" : __DIR__"feilong",
  "east" : __DIR__"shizi",
]));
        set("outdoors", "huangshan");
	set("coor/x",-630);
	set("coor/y",-530);
	set("coor/z",30);
	setup();
        replace_program(ROOM);
}
