// TIE@FY3
inherit NPC;
inherit F_VENDOR;
void create()
{
	set_name("白老三", ({ "bai laosan","bai" }) );
	set("gender", "男性" );
	set("age", 52);
	set("long",
		"无垢山庄的老仆人，陪着庄主夫人跑到这里来做点小生意。\n");
	set("combat_exp", 500000);
	set("attitude", "friendly");
	set("rank_info/respect", "老板");
	set("vendor_goods", ([
		__DIR__"obj/tie1" : 10,
		__DIR__"obj/tie2" : 30,
		__DIR__"obj/tie3" : 10,
		__DIR__"obj/tie4" : 5,
	]) );
	setup();
}

void init()
{	
	object ob;

	::init();
	if( interactive(ob = this_player()) && !is_fighting() ) {
		remove_call_out("greeting");
		call_out("greeting", 1, ob);
	}
	add_action("do_vendor_list", "list");
}

void greeting(object ob)
{
	if( !ob || environment(ob) != environment() ) return;
	switch( random(3) ) {
		case 0:
			say( "白老三道：这位" + RANK_D->query_respect(ob)
				+ "，要买什么？\n");
			break;
		case 1:
			say( "白老三看着门外的落叶道：又到秋天了。。。。\n");
			break;
		case 2:
			say( "白老三向你问道：这位" + RANK_D->query_respect(ob)
				+ "，好久没有回无垢山庄了，有什么消息吗？\n");

			break;
	}
}
