// TIE@FY3
inherit NPC;
int give_letter();
void create()
{
	set_name("札木合", ({ "muhe", "zha" }) );
	set("title", "无影神刀");
	set("gender", "男性" );
	set("age", 52);
	set("agi",35);
	set("str",35);
	set("long",
		"天下有名的第一快刀\n"
		);
       set("chat_chance", 2);
        set("chat_msg", ({
                "札木合道：我死得不明不白呀！可恨呀．．\n",
                (: random_move :),
                (: random_move :),
        }) );
	set("max_force",random(100)+20);
	set("force", random(100)+20);
	set("attitude", "peaceful");
	set_skill("blade", 60);
	set_skill("shenji-blade", 80);
	set_skill("shenji-steps",90);
	set_skill("dodge",90);
	map_skill("dodge","shenji-steps");
	map_skill("blade","shenji-blade");
	set("combat_exp", 9000000);
	setup();
        carry_object(__DIR__"obj/dafeng")->wield();
}
int is_ghost() { return 1; }

