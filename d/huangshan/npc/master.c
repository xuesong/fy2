// taolord.c

inherit NPC;
inherit F_MASTER;
#include <ansi.h>
void create()
{
        set_name( "玉兰溪" , ({ "master yu", "master", "yu" }) );
        set("gender", "女性");
        set("age", 46);
        set("long",
                
"一个小道观的主持．\n");

        set("combat_exp", 1000000);
        set("score", 200000);

        set("class", "taoist");

        set("str", 20);
        set("int", 30);
        set("cor", 20);
        set("cps", 30);
        set("spi", 30);

        set("force", 2000);
        set("max_force", 1000);
        set("force_factor", 30);

        set("atman", 1400);
        set("max_atman", 1400);

        set("mana", 4000);
        set("max_mana", 2000);
        set("mana_factor", 5);

        set("apprentice_available", 3);
        create_family("松谷庵", 1, "女主持");

        set_skill("literate", 70);
        set_skill("force", 30);
        set_skill("spells", 200);
	set_skill("move", 40);
        set_skill("unarmed", 150);
	set_skill("tenderzhi",150);
        set_skill("sword", 100);
        set_skill("parry", 40);
        set_skill("dodge", 40);

        set_temp("apply/dodge", 200);
        set_temp("apply/armor", 20);

        setup();

        carry_object("obj/cloth")->wear();
}

void attempt_apprentice(object ob)
{
        if( query("apprentice_available") ) {
                if( find_call_out("do_recruit") != -1 )
                        command("say 慢著，一个一个来。");
                else
                        call_out("do_recruit", 2, ob);
        } else {
                command("say 贫道今天已经收了三个弟子，不想再收徒了。");
        }
}

void do_recruit(object ob)
{
        if( (string)ob->query("gender") != "女性" )
                command("say 贫道是出家人，不便收男徒，得罪了。");
        else {
                command("say 嗯... 想入松谷庵？也好....");
                command("recruit " + ob->query("id") );
        }
}

int recruit_apprentice(object ob)
{
        if( ::recruit_apprentice(ob) )
                ob->set("class", "taoist");
        add("apprentice_availavble", -1);
}

 
void re_rank(object student)
{
	student->set("title","松谷庵庵姑");
                return ;

}
