
inherit ROOM;
#include <room.h>
void create()
{
        set("short", "����");
        set("long", @LONG
�����Ǹ��������С���Ǹ�����ԡ�ģ����������ʮɫ�Ĳʴ�����ζ�˱ǵĻ���,
������������ض��ǣ�͸������ˮ��������Կ���������������޳��Ĵ��ȣ���ͦ��
���ţ����ںڵĳ���������������
LONG
        );
        set("exits", ([
                "west" : __DIR__"hfenglang2",
		"east" : __DIR__"hfengpool",
        ]));
        set("objects", ([
                __DIR__"npc/smileboy": 1,
        ]) );
	set("no_fight",1);
	set("no_magic",1);
        set("coor/x",31);
	set("coor/y",40);
	set("coor/z",0);
	setup();
        create_door("east", "̴ľ��", "west", DOOR_CLOSED);

}
int valid_leave(object me, string dir)
{
        object *inv;
        object ob;
        int i;
	int withtowel=0;
        if( dir == "east" && ob=present("jintong", this_object()))
        {
                inv = all_inventory(me);
                for(i=0; i<sizeof(inv); i++)
                {
			if((string)(inv[i]->query("id")) != "white towel")
                        return notify_fail(ob->name()+"����Ц�������ϴ�����ô�࣬��ô��ϴ�裿\n");
			if( (string)(inv[i]->query("id")) == "white towel" &&
			    !(int) inv[i]->query("equipped"))
			return notify_fail(ob->name()+"����Ц��������Χ��ë���ٽ�ȥ�ɣ���Ҫ�ŵ����ˣ�\n");
			if( (string)(inv[i]->query("id")) == "white towel" )
				withtowel = 1;
                }
	if( !withtowel)
	return notify_fail(ob->name()+"����Ц����û�а�ë����ôϴ��\n");
        }
	if( dir == "west" && ob=present("jintong", this_object()))
	{
                inv = all_inventory(me);
                for(i=0; i<sizeof(inv); i++)
                {
		if( (string)(inv[i]->query("id")) == "white towel")
			{
		tell_object(me,ob->name()+"Ц����Ľ�������ʪ��"+
		inv[i]->name()+"���˻�ȥ��\n\n\n");	
		destruct(inv[i]);
			}
                }


	}
        return 1;
}
