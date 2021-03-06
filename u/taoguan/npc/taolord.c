// taolord.c

inherit NPC;
inherit F_MASTER;
#include <ansi.h>
void create()
{
        set_name("丁乘风", ({ "master ding", "master", "ding" }) );
        set("nickname", HIG"碧海乘风" NOR);
        set("gender", "男性");
        set("age", 47);
        set("long",
                
"丁乘风原本出身武林世家，但从小好学，擅长钻研心法，\n"
"于是隐居于此精修成仙降魔之道。\n");

        set("combat_exp", 10000000);
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

        set("inquiry", ([
                "谷衣心法": 
"谷衣心法是我三清宫为对抗邪魔外道所创的内功心法。\n",
                "三清宫": 
"我三清宫自张天师开山立派至今，世世代代皆以降妖伏魔为己任。\n"
        ]) );

        set("apprentice_available", 3);
        create_family("三清宫", 5, "主持");

        set_skill("literate", 70);
        set_skill("magic", 40);
        set_skill("force", 30);
        set_skill("move", 40);
        set_skill("scratching", 200);
	set_skill("spells",50);
        set_skill("unarmed", 30);
        set_skill("sword", 100);
        set_skill("parry", 40);
        set_skill("dodge", 40);
        set_skill("gouyee", 60);
	set_skill("notracesnow", 100);
	set_skill("snowshade-sword", 100);

        set_skill("taoism", 100);
        set_skill("scratmancy", 100);
	set_skill("necromancy",50);

        map_skill("scratching", "scratmancy");
        map_skill("parry", "snowshade-sword");
        map_skill("sword", "snowshade-sword");
        map_skill("move", "notracesnow");
        map_skill("dodge", "notracesnow");



        set_temp("apply/dodge", 20);
        set_temp("apply/armor", 20);
        setup();

        carry_object(__DIR__"obj/sword")->wield();
        carry_object(__DIR__"obj/robe")->wear();
        carry_object(__DIR__"obj/hat")->wear();
        carry_object(__DIR__"obj/shoe")->wear();
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
        if( (string)ob->query("gender") != "男性" )
                command("say 贫道是出家人，不便收女徒，得罪了。");
        else {
                command("say 嗯... 想入我三清宫？也好....");
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
        int exp;
        exp = (int) student->query("combat_exp");
        if( exp <= 32000 ) {
                student->set("title","三清宫道士");
                return ;
        } else if ( exp <= 128000 ) {
                student->set("title","三清宫小真人");
                return ;
        } else if ( exp <= 512000 ) {
                student->set("title","三清宫真人");
                return ;
        } else if ( exp <= 1536000 ) {
                student->set("title","三清宫小天师");
                return ;
        } else if ( exp <= 3456000 ) {
                student->set("title","三清宫天师");
                return ;
        } else if ( exp <= 5187000 ) {
                student->set("title","三清宫大天师");
                return ;
        } else if ( exp <= 26244000 ) {
                student->set("title","三清宫副主持");
                return ;
        } else
                student->set("title","三清宫主持");
                return ;
}
 
