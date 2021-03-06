// TIE@FY3
#include <ansi.h>
#include <vote.h>
inherit F_CLEAN_UP;
int main(object me, string arg)
{
	string who,what;
	string msg;
	object victim;
	int result;
	int diff;
	seteuid(getuid());
	if(!arg) return notify_fail("指令格式：vote <what> on <who>\n");
	if(sscanf(arg,"%s on %s",what,who)	!= 2)
	return notify_fail("指令格式：vote <what> on <who>\n");
        if((int)me->query("mud_age") < NEW_PERIOD)
        return notify_fail("你还没有到能投票的年纪！\n");
        if(me->query("vote_denied"))
        return notify_fail("你已经被剥夺了投票的权力！\n");
	if(what == "on" || what == "off")
	{
		if(who != "chat" && who != "rumor" && who != "fy" &&
			who != "new")
		return notify_fail("公共频道只可以是chat,fy,new,rumor！\n");	

	}
	else if ( what == "redis" )
	{
		if( who != "tasks")
		return notify_fail("从新散播的只可以是tasks！\n");

	}
	else
	{
	victim= LOGIN_D->find_body(who);
        if (!victim) return notify_fail("咦．．．有这个人吗？\n");
	}
	if(me==victim)
	return notify_fail("你不可以投自己的票！\n");
	switch(what) 
	{
	case "redis":
         if( CRON_D->query_last_hard_dis() > time() - 3600*3)
	 return notify_fail("离上此从新分布还不到三个小时！\n");
	 result = VOTE_D->add_vote(me,what,who);
         if(!result)
         return notify_fail("你已经投过票了！\n");
	 log_file("VOTE",sprintf("%s %s (%s) vote redis on tasks\n",ctime(time()), me->query("id"),query_ip_number(me),));
	 diff = sizeof(users())/2 - result + 1;
         if(diff > 0)
         {
         msg = sprintf(HIY"【投票表决】：%s投票从新分布所有的使命，还差%s票。\n"NOR,
                                me->name(),
                                chinese_number(diff));
         }
         else
        {
         msg = sprintf(HIY"【投票表决】：%s投票从新分布所有的使命，表决通过。\n"NOR,
                                me->name());
	seteuid(ROOT_UID);
	TASK_D->init_dynamic_quest(1);
	CRON_D->set_last_hard_dis();
	VOTE_D->delete(who+"/"+what);
        }                                
        message("system",msg,users());
        break;
	case "right":
	 if(!victim->query("vote_denied") || wizardp(victim))
	 return notify_fail("他/她并没有被剥夺投票的权力！\n");
	 result = VOTE_D->add_vote(me,what,who);
	 if(!result)
	 return notify_fail("你已经投过票了！\n");	
	log_file("VOTE",sprintf("%s %s (%s) vote right on %s\n",ctime(time()), me->query("id"),query_ip_number(me),victim->query("id")));
	 diff = right_no - result;
	 if(diff > 0)
	 {
	 msg = sprintf(HIY"【投票表决】：%s投票给予%s（%s）投票的权利，还差%s票。\n"NOR,
				me->name(),victim->name(),victim->query("id"),
				chinese_number(diff));
	 }
	 else
	{
         msg = sprintf(HIY"【投票表决】：%s投票给予%s（%s）投票的权利，表决通过。\n"NOR,
                                me->name(),victim->name(),victim->query("id"));
	victim->delete("vote_denied");
	}                                
	message("system",msg,users());
	break;
        case "noright":
         if(victim->query("vote_denied") || wizardp(victim))
         return notify_fail("他/她已经被剥夺投票的权力！\n");
         result = VOTE_D->add_vote(me,what,who);
         if(!result)
         return notify_fail("你已经投过票了！\n");
	 log_file("VOTE",sprintf("%s %s (%s) vote noright on %s\n",ctime(time()),me->query("id"),query_ip_number(me),victim->query("id")));
         diff = noright_no - result;
         if(diff > 0)
         {
         msg = sprintf(HIY"【投票表决】：%s投票剥夺%s（%s）投票的权利，还差%s票。\n"NOR,
                                me->name(),victim->name(),victim->query("id"),
                                chinese_number(diff));
         }
         else
        {
         msg = sprintf(HIY"【投票表决】：%s投票剥夺%s（%s）投票的权利，表决通过。\n"NOR,
                                me->name(),victim->name(),victim->query("id"));
        victim->set("vote_denied",1);
        }                                
        message("system",msg,users());
        break;
        case "kickout":
	 if(wizardp(victim))
         return notify_fail("你不可以剥夺他/她的任何权力！\n");
         result = VOTE_D->add_vote(me,what,who);
         if(!result)
         return notify_fail("你已经投过票了！\n");
	 log_file("VOTE",sprintf("%s %s (%s) vote kickout on %s\n",ctime(time()), me->query("id"),query_ip_number(me),victim->query("id")));
         diff = kickout_no - result;
         if(diff > 0)
         {
         msg = sprintf(HIY"【投票表决】：%s投票剥夺%s（%s）进入风云的权利，还差%s票。\n"NOR,
                                me->name(),victim->name(),victim->query("id"),
                                chinese_number(diff));
         }
         else
        {
         msg = sprintf(HIY"【投票表决】：%s投票剥夺%s（%s）进入风云的权利，表决通过。\n"NOR,
                                me->name(),victim->name(),victim->query("id"));
        victim->set("kickout_time",time());
        }                                
        message("system",msg,users());
	if(diff <=0)
	{
	victim->save();
	seteuid(ROOT_UID);
	destruct(victim);
	}
        break;
        case "block":
         if(victim->query("chblk_on") || wizardp(victim))
         return notify_fail("他/她已经被剥夺了使用公共频道的权力！\n");
         result = VOTE_D->add_vote(me,what,who);
         if(!result)
         return notify_fail("你已经投过票了！\n");
	 log_file("VOTE",sprintf("%s %s (%s) vote block on %s\n",ctime(time()), me->query("id"),query_ip_number(me),victim->query("id")));
         diff = block_no - result;
         if(diff > 0)
         {
         msg = sprintf(HIY"【投票表决】：%s投票剥夺%s（%s）使用公共频道的权利，还差%s票。\n"NOR,
                                me->name(),victim->name(),victim->query("id"),
                                chinese_number(diff));
         }
         else
        {
         msg = sprintf(HIY"【投票表决】：%s投票剥夺%s（%s）使用公共频道的权利，表决通过。\n"NOR,
                                me->name(),victim->name(),victim->query("id"));
        victim->set("chblk_on",1);
	victim->save();
        }                                
        message("system",msg,users());
        break;
        case "noblock":
         if(!victim->query("chblk_on") || wizardp(victim))
         return notify_fail("他/她没有被剥夺了使用公共频道的权力！\n");
         result = VOTE_D->add_vote(me,what,who);
         if(!result)
         return notify_fail("你已经投过票了！\n");
	 log_file("VOTE",sprintf("%s %s (%s) vote noblock on %s\n",ctime(time()), me->query("id"),query_ip_number(me),victim->query("id")));
         diff = noblock_no - result;
         if(diff > 0)
         {
         msg = sprintf(HIY"【投票表决】：%s投票给予%s（%s）使用公共频道的权利，还差%s票。\n"NOR,
                                me->name(),victim->name(),victim->query("id"),
                                chinese_number(diff));
         }
         else
        {
         msg = sprintf(HIY"【投票表决】：%s投票给予%s（%s）使用公共频道的权利，表决通过。\n"NOR,
                                me->name(),victim->name(),victim->query("id"));
        victim->delete("chblk_on");
	victim->save();
        }                                
        message("system",msg,users());
        break;
        case "robot":
         if(wizardp(victim))
         return notify_fail("他/她是管理员，不是机器人！\n");
         result = VOTE_D->add_vote(me,what,who);
         if(!result)
         return notify_fail("你已经投过票了！\n");
	 log_file("VOTE",sprintf("%s %s (%s) vote robot on %s\n",ctime(time()), me->query("id"),query_ip_number(me),victim->query("id")));
         diff = robot_no -result;
         if(diff > 0)
         {
         msg = sprintf(HIY"【投票表决】：%s投票检举%s（%s）为机器人，还差%s票。\n"NOR,
                                me->name(),victim->name(),victim->query("id"),
                                chinese_number(diff));
         }
         else
        {
	object room;
         msg = sprintf(HIY"【投票表决】：%s投票检举%s（%s）为机器人，表决通过。\n"NOR,
                                me->name(),victim->name(),victim->query("id"));
        message_vision(HIY"忽然一阵闪光罩住了$N。\n"NOR,victim);
        victim->set_temp("last_location", base_name(environment(victim)));
        room = load_object("/d/wiz/courthouse");
        victim->move(room);
        }                                
        message("system",msg,users());
        break;
        case "imprison":
         if(wizardp(victim))
         return notify_fail("他/她是管理员，这招没用！\n");
	if(base_name(environment(victim)) == "/d/wiz/jail")
	return notify_fail("他/她已经在风云狱里了！\n");
         result = VOTE_D->add_vote(me,what,who);
         if(!result)
         return notify_fail("你已经投过票了！\n");
         log_file("VOTE",sprintf("%s %s (%s) vote imprison on %s\n",ctime(time()), me->query("id"),query_ip_number(me),victim->query("id")));
         diff = imprison_no -result;
         if(diff > 0)
         {
         msg = sprintf(HIY"【投票表决】：%s投票囚禁%s（%s），还差%s票。\n"NOR,
                                me->name(),victim->name(),victim->query("id"),
                                chinese_number(diff));
         }
         else
        {
        object room;
         msg = sprintf(HIY"【投票表决】：%s投票囚禁%s（%s），表决通过。\n"NOR,
                                me->name(),victim->name(),victim->query("id"));
        message_vision(HIY"忽然一阵闪光罩住了$N。\n"NOR,victim);
        room = load_object("/d/wiz/jail");
        victim->move(room);
        }                                
        message("system",msg,users());
        break;
        case "ban":
         if(wizardp(victim))
         return notify_fail("你不可以对他/她这么做！\n");
         result = VOTE_D->add_vote(me,what,who);
         if(!result)
         return notify_fail("你已经投过票了！\n");
log_file("VOTE",sprintf("%s %s (%s) vote ban on %s\n",ctime(time()), me->query("id"),query_ip_number(me),victim->query("id")));
         diff = ban_no - result;
         if(diff > 0)
         {
         msg = sprintf(HIY"【投票表决】：%s投票禁止%s（%s）站点联线的权利，还差%s票。\n"NOR,
                                me->name(),victim->name(),victim->query("id"),
                                chinese_number(diff));
         }
         else
        {
         msg = sprintf(HIY"【投票表决】：%s投票禁止%s（%s）站点联线的权利，表决通过。\n"NOR,
                                me->name(),victim->name(),victim->query("id"));
        }                                
        message("system",msg,users());
        if(diff <=0)
        {
        victim->save();
        seteuid(ROOT_UID);
	BAN_D->dynamic_add(query_ip_number(victim));
        destruct(victim);
        }
        break;
	case "on" :
	if( !CHANNEL_D->query("block_"+who))
	return notify_fail(who+"频道已经是开启的。\n");
         result = VOTE_D->add_vote(me,what,who);
         if(!result)
         return notify_fail("你已经投过票了！\n");
	 log_file("VOTE",sprintf("%s %s (%s) vote on on %s\n",ctime(time()), me->query("id"),query_ip_number(me),who));
         diff = on_no - result;
         if(diff > 0)
         {
         msg = sprintf(HIY"【投票表决】：%s投票开启%s频道，还差%s票。\n"NOR,
                                me->name(),who,
                                chinese_number(diff));
         }
         else
        {
         msg = sprintf(HIY"【投票表决】：%s投票开启%s频道，表决通过。\n"NOR,
                                me->name(),who);
	 CHANNEL_D->set_block(who,0);
         EMOTE_D->set_block(who,0);
        }                                
        message("system",msg,users());
	break;
	case "off" :
        if( CHANNEL_D->query("block_"+who))
        return notify_fail(who+"频道已经是关闭的。\n");
         result = VOTE_D->add_vote(me,what,who);
         if(!result)
         return notify_fail("你已经投过票了！\n");
         log_file("VOTE",sprintf("%s %s (%s) vote off on %s\n",ctime(time()), me->query("id"),query_ip_number(me),who));
         diff = off_no - result;
         if(diff > 0)
         {
         msg = sprintf(HIY"【投票表决】：%s投票关闭%s频道，还差%s票。\n"NOR,
                                me->name(),who,
                                chinese_number(diff));
         }
         else
        {
         msg = sprintf(HIY"【投票表决】：%s投票关闭%s频道，表决通过。\n"NOR,
                                me->name(),who);
         CHANNEL_D->set_block(who,1);
         EMOTE_D->set_block(who,1);
        }                                
        message("system",msg,users());
	break;
	default:
		return notify_fail("指令格式：vote <what> on <who>\n");

	}
	return 1;
}
int help(object me)
{
  write(@HELP

这条指令是众玩家在没有管理人员在线的时候来处理
违反风云天条的人的，需要在五分钟内有足够票数才可以生效。

指令格式：vote <what> on <who>

其中<what>可以是以下中的一项： 

right:		给予投票的权利（需要七票）
noright:	剥夺投票的权利（需要十票）
kickout:	剥夺进入风云的权利（需要八票）
block:		剥夺使用公共频道的权力（需要七票）
noblock:	给予使用公共频道的权力（需要五票）
robot:		检举为机器人（需要五票）
imprison	将某人监禁起来（需要九票）
ban:		禁止站点联线的权利（site ban）（需要十五票）
off:		关闭公共频道，其中的who可以是chat,fy,new,rumor（需要十票）
on:		开启公共频道，其中的who可以是chat,fy,new,rumor（需要六票）
redis:		从新分布所有（完成和没完成）的使命（ｔａｓｋｓ）（需要半数在线玩家）

注：所有的投票活动都有记录，凡是滥用投票的人一经察出都会
按照风云天条处置！

HELP
    );
    return 1;
}
