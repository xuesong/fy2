
inherit ROOM;

void create()
{
        set("short", "地牢");
        set("long", @LONG
这里黑黑暗暗，几乎伸手不见五指。唯一的光亮来自墙上忽明忽暗的
松油灯。地上和墙上布满了暗红色的血痕，散发出阵阵腥气。不断传来的
哀嚎声在死沉的地牢里回荡，令人毛骨耸然。
LONG
        );
        set("exits", ([ /* sizeof() == 3 */
  "east" : __DIR__"tunnel6",
  "north" : __DIR__"tunnel3",
  "south"   : __DIR__"tunnel1",
]));

        set("coor/x",120);
	set("coor/y",140);
	set("coor/z",90);
	setup();
}

