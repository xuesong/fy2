
inherit ROOM;

void create()
{
        set("short", "草原");
        set("long", @LONG
这里是一望无际的大草原。绿色的草地美丽得就象晴朗的蓝天。草原上
三三两两的羊群则是蓝天上飘浮的朵朵白云。远处的布达拉宫在骄阳下看来
亮如纯银；到了夕阳西下时又变得灿烂如黄金。你也许从没想到，在塞外的
边陲之地竟有如此美妙的地方，美得辉煌而神秘，美得令人迷惑，美得令人
都醉了。
LONG
        );
        set("exits", ([ 
  "west" : __DIR__"grassland3",
  "east" : __DIR__"grassland1",
]));
        set("outdoors", "guanwai");
        set("objects", ([
                __DIR__"npc/sheepgirl2" : 2,
		__DIR__"npc/sheep2" : 5,
        ]) );
        set("coor/x",-1160);
	set("coor/y",-10);
	set("coor/z",0);
	setup();
}

