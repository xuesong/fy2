// Room: /d/oldpine/passage.c

inherit ROOM;

void create()
{
        set("short", "秘密通道入口");
        set("long", @LONG
你现在正站在一个岩石的通道之中，在你南边有一片亮晶晶的帘幕，
从帘幕後面传来阵阵轰隆隆的水声，通道两边的石壁上安置著许多铜铸
的烛台，照亮了这个密穴，往北似乎有亮光。
LONG
        );
        set("item_desc", ([ /* sizeof() == 1 */
  "帘幕" : "这片帘幕似乎是用一种极薄的丝绸织成的，後面还传来阵阵水声。\n",
]));
        set("exits", ([ /* sizeof() == 2 */
  "north" : "/d/oldpine/secrectpath1",
  "south" : "/d/oldpine/waterfall",
]));
        set("objects", ([ /* sizeof() == 1 */
  "/d/oldpine/npc/maniac" : 1,
]));
        set("no_clean_up", 0);

        set("coor/x",-260);
	set("coor/y",-330);
	set("coor/z",70);
	setup();
        replace_program(ROOM);
}
