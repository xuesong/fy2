// Copyright (C) 1995, by Tie Yu and Daniel Yu. All rights reserved.
inherit ROOM;
void create()
{
  set("short","������");
  set("long",@LONG
ɽ�ƶ��ͣ�������ǧ�ߣ����絶������̩ɽ֮���ϣ�ǧ�ž��գ���
�����磬����Ħ��ʯ�̣��������ɣ����Ͼ�����٣�˳�¶��£�������
�ܹ��ɽ�������Ħ�£������ؿ��ٶ��£����ֲ��ף��ɼ�һ�ߣ������
�в���ȼ��һ������֮�顣
LONG
  );
  set("exits",([
	"westdown" : __DIR__"wangmu",
               ]));
        set("objects", ([
        __DIR__"obj/cliff" : 1,
                        ]) );
        set("outdoors", "fengyun");
	set("coor/x",-470);
	set("coor/y",-320);
	set("coor/z",10);
	setup();
}
void init()
{
        add_action("climbing", "climb");
}

int climbing(string arg)
{
        object obj;
        object me;
        if(!arg || arg=="")
        {
                write("��Ҫ��ʲô��\n");
                return 1;
        }
        if( arg == "����" || arg == "down" || arg == "vine")
        {
        me = this_player();
        message_vision("$Nץ��ͻ���Ŀ��٣�������˳�Źȱ�������ȥ��\n", me);
        me->start_busy(2);
        call_out("fliping",2,me);
        me->stop_busy();
        return 1;
        }
        else
        {
                write("�㲻������"+arg+"\n");
                return 1;
        }
}
int fliping(object me)
{
	if( !me->is_ghost()) {
        me->move(__DIR__"shandong");
        message_vision("$N˳�ſ�������������\n", me);
	}
        return 1;
}
