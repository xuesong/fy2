// zhuzao.c
#include <ansi.h>
inherit NPC;
string *names = ({
         __DIR__"redgirl",
         __DIR__"orggirl",
         __DIR__"yelgirl",
         __DIR__"grngirl",
         __DIR__"cyngirl",
         __DIR__"blugirl",
         __DIR__"maggirl",
        });

string *girls= ({
          "red girl",
          "orange girl",
          "yellow girl",
          "green girl",
          "cyan girl",
          "blue girl",
          "mag girl",
         });
object girl;         
int test_array();
int tell_array();
int go_jiayi();
void create()
{
    set_name("����",({"zhu zao","zhu","zao"}));
    set("long","��������\n");
    set("title","���¿�");
    set("gender","����");
    set("no_arrest",1);
    set("age",32);
    set("int",22);
    set("cor",30);
    set("per",30);
    set("cps",20);
    set("gin",1000);
    set("max_gin",1000);
    set("eff_gin",1000);
    set("max_kee",1000);
    set("eff_kee",1000);
    set("kee",1000);  
    set("max_sen",1000);
    set("sen",1000);    
    set("eff_sen",1000);
    set("combat_exp",2000000);  
    set_skill("ill-quan",100);
    set_skill("force",100);
    set_skill("lotusforce",100);
    set_skill("unarmed",100);
    set_skill("parry",150);
    set_skill("dodge",150);
    set("force",10000);
    set("max_force",10000);
    set("force_factor",200);
    map_skill("force","lotusforce");
    map_skill("unarmed","ill-quan");
    set("attitude", "heroism");
    set("inquiry",([
          "jiayi": (: go_jiayi :),
          "����" : (: go_jiayi :),
          "����": (: test_array :),
          "test": (: test_array :),
          "����Ů��": (:tell_array :),
	  "array" : (:tell_array :),
          ])   );
    set("chat_chance",10);     
    set("chat_msg",({
          "���������û�����ܹ��ҵ�����Ů�󡣡�\n",
          }) );

    setup();
    carry_object(__DIR__"obj/macloth")->wear();   
    add_money("thousand-cash", 1);
}
void init()
{
        object ob;

        ::init();
        if( interactive(ob = this_player()) && !is_fighting() ) {
                remove_call_out("greeting");
                call_out("greeting", 1, ob);
        }
}

int greeting(object me)
{
 
    if( !me || environment(me) != environment() ) return 1;
    say ("����˵��������Ȼ��Զǧ�����������������ˣ����������������������\n");
    return 1;
}
int havenothingon(object ob)
{  
   object *inv;
   object dress;      
   int i;
   inv = all_inventory(ob);
   if (sizeof(inv)==0) return 1;
   for (i=0;i<sizeof(inv);i++){
       dress=inv[i];
       if ((string)dress->query("equipped")=="worn" ) return 0;
       }                                        
   return 1;
}
int test_array()
{
    object me;
    int i;
    me=this_player();
    if(me->query_temp("mark/sucarray"))
    {
     command("say ���治���������ҵ�����Ů��\n");
	return 1;
    }
    if (query_temp("mark/arraying"))
    {
      command("say �����������Ѿ������ڹ����ˡ�\n");
      return 1;
    }
    if (me->query("age")<16)
    { 
      command("sigh");
      command("say С���Ӳ�����Ϲ�ʣ�\n");
      return 1;
    }
    command("laugh");
    message_vision("$N˵�������þ������ʶ��ʶ��\n",this_object());
    message_vision("$N�������֣������������߳��߸���Ů��Χ��$n���ߡ�\n",this_object(),me);
    set_temp("mark/arraying",1);
    for (i=6;i>=0;i--)
         {
           girl=new(names[i]);
            girl->move(environment(this_object()));
          }
   
    call_out("begin_array",2,me);
 
    return 1;
}
void begin_array(object me)
{
    message_vision("������Ů������һЦ��������������$N����Χ�˸�������Բ��Ȧ�ӡ�\n",me);
    message_vision("$N���Ƶ����������󷢣���\n",this_object());
    call_out("fighting",1,me,0);
    me->set_temp("mark/arraying",1);
    me->delete_temp("mark/striped");
}
void fighting(object me,int count)
{ 
    string msg; 
    object *inv;
    object dress;
    int i;
    if (havenothingon(me) && !me->query_temp("mark/striped"))
    {
       message_vision("$N����Ц��������λ"+RANK_D->query_respect(me)+"��Ҳ���ɣ�����������˰ɣ���\n",this_object());
       me->delete_temp("mark/arraying");
       this_object()->delete_temp("mark/arraying");
       me->set_temp("mark/sucarray",1);
       message_vision("$N��һ�ӣ��߲���Ů��������ȥ��\n",this_object());
       for (i=0;i<7;i++)
         destruct(present(girls[i],environment()));
       return;
     }
    if (!present(me,environment(this_object())))
    { 
       message_vision("$N̾�˿�����˵��������С����ļһ����һ������ˡ���\n",this_object());
       me->delete_temp("mark/arraying");
       this_object()->delete_temp("mark/arraying");
       message_vision("$N��һ�ӣ��߲���Ů��������ȥ��\n",this_object());
       for (i=0;i<7;i++)
         destruct(present(girls[i],environment()));
       return;
    }
    i=count%7;
    girl=present(girls[i],environment());
    if (!objectp(girl)) {
               notify_fail("wrong\n");
               return;
         }
    if (i==3) 
    {
           if (random(me->query("combat_exp"))<50000 && !me->is_busy())
                 {
           message_vision( HIR "\n      ������Ů��ԽתԽ�죮���ɵ���ȹ�ǣ����Ĵ�Ƣ�����㣮��\n\n" NOR,me);
                 message_vision("$N��ת����\n",me);
                 me->start_busy(3);
                }
	switch(random(5)) {
	case 0:
            message_vision(HIR "\n    ������Ů���½��⣬�������ʣ����⻬�ļ����������޳������ȣ�����
      ��͢�����飬��Բ�����Σ��������������ܵģ�����\n\n" NOR,me);
	break;
	case 1:
            message_vision(HIR "\n    ������Ů��������������������$N������
һ����������Ů�������е�����,�����Ĵ���$N�ı��У�����������Ů����׽��$N����,������С�ɷ����е��Ե��ز�����\n\n" NOR,me);
	break;
	case 2:
            message_vision(HIR "\n    ������Ů����ж�������ѣ�������������չ¶���ţ�����
�����������ƣ��������е��ԣ��������ĺ촽,�����������������������ˣ������۵���Һ������\n\n" NOR,me);
	break;
	case 3:
            message_vision(HIR "\n    ���ţ�ม���������������ѽ����ֻ��������Ů������������
������������������룬�����Ļ�ϣ���ǰ���������˫��һ��һ�͵Ĳ�������������\n\n" NOR,me);
	break;
	case 4:
            message_vision(HIR "\n    ������Ů��׶�͸��ϸ��ļ�������һ��覱ӿ�Ѱ����
��ʵ��������������������������������ߵ����ģ���ƽƽ��С�����޳���԰�Ĵ��ȣ���������Ľ���������\n\n" NOR,me);
		}
            if (random(me->query_cps())<5) 
            { 
               message_vision("$N������ˮ�Ľ�������Ƿ�������\n",me);
               me->unconcious();
            };
    };       
    inv = all_inventory(girl);
    dress=inv[random(sizeof(inv))];
    if( (string)dress->query("equipped")=="worn" )
        if (dress->unequip()) {
             if( !stringp(dress->query("unequip_msg")) )
                message_vision(YEL "$N��$n����������\n" NOR,girl,dress);
             else
                message_vision(dress->query("unequip_msg"),girl,dress);
        };

    if (random(100)>50){
    dress->move(environment(girl));
    destruct(dress); //we think it should to drop on ground,but..
    COMBAT_D->do_attack(girl, me, girl->query_temp("weapon"));
    }
    else{
        msg="$N�����ڱۣ������е�"+dress->name()+"��$n��ȥ��";
        dress->move(environment(girl));
        destruct(dress);                                      
        COMBAT_D->do_attack(girl, me, girl->query_temp("weapon"),0,msg);
        }
     //query if success
   
   if(me->query("kee") <= 0   || !present(me, environment()))
   {
      message_vision("$N̾���������⼸�ж��Ų���ȥ����\n",this_object());
      me->delete_temp("mark/arraying");
      this_object()->delete_temp("mark/arraying");
      me->set_temp("mark/sucarray",1);
      message_vision("$N��һ�ӣ��߲���Ů��������ȥ��\n",this_object());
      for (i=0;i<7;i++)
         destruct(present(girls[i],environment()));
      return;  
   };               
   
   if(me->query_temp("mark/striped"))
   {          
      message_vision("$N��Ц��������ô������Ҫ���������ˡ�\n",this_object());
      if (!random(10)) message_vision("$N˵����������ǽ�Ͽ̵��ǹ���ľ��У���ú��ж��ɣ�\n",this_object());
      me->delete_temp("mark/arraying");
      this_object()->delete_temp("mark/arraying");
  
      message_vision("$N��һ�ӣ��߲���Ů��������ȥ��\n",this_object());
      for (i=0;i<7;i++)
         destruct(present(girls[i],environment()));
      return;  
   }                 
   
   for (i=0;i<7;i++)
       {
         girl=present(girls[i],environment());
         inv=all_inventory(girl); 
         if (sizeof(inv)) 
                {
       
                 call_out("fighting",1,me,count+1);
                 return;
                 }

       }
      message_vision("$N��Ц��������������������������Ů���ˡ���\n",this_object());
        if(!me->query("m_success/����Ů��"))
        {
                me->set("m_success/����Ů��",1);
                me->add("score",1000);

        }
      me->delete_temp("mark/arraying");
      me->set_temp("mark/sucarray",1);
      this_object()->delete_temp("mark/arraying");
      if (!query_temp("mark/pass_array"))
      {
      		command("say ���ǽ����һ������ģ��ܺúܺá�");
      		me->add("combat_exp",50+random(100));
      		me->add("potential",50+random(150));
      }
      set_temp("mark/pass_array",1);
      message_vision("$N��һ�ӣ��߲���Ů��������ȥ��\n",this_object());
      for (i=0;i<7;i++)
         destruct(present(girls[i],environment()));
      return;   
   
}        
int tell_array()
{
   message_vision("$N��Ц����������ֻӦ�����У��˼��ǵü����ţ�$n��һ��������Ȼ���ˣ�����Ҳ�㲻������\n",this_object(),this_player());
   message_vision("�������߸���ɫ��Ů���书�䲻�ߣ���Ҳ�������������˽���Χ�����룬\nһ�����£�һ�涯��������·������������·��Ѿ���������·�δ����\n������һ������һ�������Ӯ�ˡ�\n",this_player());
   return 1;

}
int go_jiayi()
{
	object me;
	object ark;
	me=this_player();
	if (!me->query("marks/����"))
		message_vision("$N����ص���$nһ�ۣ������������ʲô����\n",this_object(),me);
	else	
	{
		command("say лл��������ҵ�ĸ�ף�������ȥ�������ɣ�");
		if (!objectp(ark=find_object("/d/tieflag/ark")))
                ark=load_object("/d/tieflag/ark");
        me->move(ark);
    }
    return 1;
} 