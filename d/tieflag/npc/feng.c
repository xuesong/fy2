// feng.c

inherit NPC;

void create()
{
    set_name("风九幽",({"feng jiuyou","feng"}));
    set("long","风梭风九幽，但他现在走火入魔，一动也不能动了。\n");
    set("nickname","九幽阴风");
    set("gender","男性");
    set("age",42);
    set("no_arrest",1);
    set("int",22);
    set("cor",0);
    set("per",30);
    set("con",0);
    set("cps",20);
    set("agi",0);
    set("gin",1000);
    set("max_gin",1000);
    set("eff_gin",1000);
    set("max_kee",1000);
    set("eff_kee",1000);
    set("kee",1000);  
    set("max_sen",1000);
    set("sen",0);    
    set("eff_sen",1000);
    set("combat_exp",400000);  
    set_skill("nine-moon-claw",100);
    set_skill("force",100);
    set_skill("demon-force",150);
    set_skill("unarmed",100);
    set_skill("parry",150);
    set_skill("dodge",150);
    set("force",10000);
    set("max_force",10000);
    set("force_factor",20);
    map_skill("force","demon-force");
    map_skill("unarmed","nine-moon-claw");
    set("attitude", "friendly");
    setup();
    carry_object("obj/cloth")->wear();   
    add_money("silver", 30);
}
int accept_fight(object me)
{
	return notify_fail("风九幽已经不能战斗了。\n");
}              
