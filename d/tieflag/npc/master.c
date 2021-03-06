inherit NPC;
inherit F_MASTER;
void create()
{
        set_name("铁中棠", ({ "master tie", "master","tie" }) );
        set("gender", "男性" );
        set("age", 26);
        set("int", 30);
        set("per", 15);
	set("agi",35);
        set("apprentice_available", 50);
        create_family("铁血大旗门", 8, "掌门");
	set("long",
		"铁中棠是铁血大旗门的传人。\n"
		);
        set("force_factor", 30);
        set("max_gin", 3000);
        set("max_kee", 3000);
        set("max_sen", 3000);
        set("eff_gin", 3000);
        set("eff_kee", 3000);
        set("eff_sen", 3000);
        set("gin", 3000);
        set("kee", 3000);
        set("sen", 3000);
        set("max_force", 5000);
        set("force", 5000);
        set("attitude", "peaceful");
        set("combat_exp", 9999999);
        set("score", 90000);
        set_skill("dormancy",150);
        set_skill("unarmed", 100);
        set_skill("sword", 100);
        set_skill("force", 100);
        set_skill("parry", 100);
        set_skill("literate", 100);
		set_skill("dodge", 100);
		set_skill("ill-quan", 150);
		set_skill("fy-sword", 100);
		set_skill("cloudsforce", 100);
		set_skill("tie-steps", 150);
    	
		map_skill("unarmed", "ill-quan");
        map_skill("sword", "fy-sword");
        map_skill("force", "cloudsforce");
        map_skill("parry", "fy-sword");
        map_skill("dodge", "tie-steps");

		setup();
        	carry_object(__DIR__"obj/tieflag");
		carry_object("obj/cloth")->wear();
}
void reset()
{
        set("apprentice_available", 20);
}
void attempt_apprentice(object ob)
{
        if( query("apprentice_available") ) {
                if( find_call_out("do_recruit") != -1 )
                        command("say 慢著，一个一个来。");
                else
                        call_out("do_recruit", 2, ob);
        } else {
                command("say 本掌门今天已经收了二十个弟子，不想再收徒了。");
        }
}
void do_recruit(object ob)
{
        if (ob->query_temp("mark/can_apprentice_master_tie"))
        if( (string)ob->query("gender") != "男性" )
          {      command("say 我只收男弟子！");
          }
        else {

                command("smile");
                command("say 你日后必有大成！");
                command("smile");
                command("recruit " + ob->query("id") );
	 }
}
int recruit_apprentice(object ob)
{
        if( ::recruit_apprentice(ob) )
                ob->set("class", "tieflag");
        add("apprentice_availavble", -1);
}

int accept_object(object me, object obj)
{
        if(obj->query("id")=="silk book" && me->query_temp("mark/silkbook"))
        {
        	me->set_temp("mark/can_apprentice_master_tie",1);
        	me->delete_temp("mark/silkbook");
        	command("say 灵光，灵光她还好吗？\n");
        	return 1;
        }
	if(obj->query("id")=="flag" && obj->query("fake"))
	{
	command("say 大胆！从哪儿弄出一面破旗来愚弄老夫！\n");
	kill_ob(me);
	return 1;
	}
        return 0;
}

void re_rank(object student)
{
        int exp;
        exp = (int) student->query("combat_exp");
        if( exp <= 32000 ) {
                student->set("title","铁血大旗门弟子");
                return ;
        } else if ( exp <= 128000 ) {
                student->set("title","铁血大旗门小侠");
                return ;
        } else if ( exp <= 512000 ) {
                student->set("title","铁血大旗门少侠");
                return ;
        } else if ( exp <= 1536000 ) {
                student->set("title","铁血大旗门大侠");
                return ;
        } else if ( exp <= 3456000 ) {
                student->set("title","铁血大旗门奇侠");
                return ;
        } else if ( exp <= 5187000 ) {
                student->set("title","铁血大旗门元老");
                return ;
        } else if ( exp <= 26244000 ) {
                student->set("title","铁血大旗门元老");
                return ;
        } else
                student->set("title","铁血大旗门副掌门");
                return ;
}
