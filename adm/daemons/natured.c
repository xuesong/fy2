// natured.c

#define TIME_TICK (time()*60)

static int current_day_phase;
mapping *day_phase;

string *weather_msg = ({
	"天空中万里无云",
	"几朵淡淡的云彩妆点著清朗的天空",
	"白云在天空中飘来飘去",
	"厚厚的云层堆积在天边",
	"天空中乌云密布",
});

mapping *read_table(string file);
void init_day_phase();

void create()
{
	day_phase = read_table("/adm/etc/nature/day_phase");
	init_day_phase();
}

void init_day_phase()
{
	mixed *local;
	int i, t;

	// Get minutes of today.
	local = localtime(TIME_TICK);
	t = local[2] * 60 + local[1];		// hour * 60 + minutes

	// Find the day phase for now.
	for( i=0; i < sizeof(day_phase); i++)
		if( t >= day_phase[i]["length"] )
			t -= (int)day_phase[i]["length"];
		else
			break;

	current_day_phase = (i==0? sizeof(day_phase)-1: i - 1);

	// Since in our time scale, 1 minute == 1 second in RL, so we don't need
	// any conversion before using this number as call_out dalay, if you 
	// changed the time scale, be sure to convert it.

	call_out("update_day_phase",
		(int)day_phase[(current_day_phase+1) % sizeof(day_phase)]["length"] - t);
}

void update_day_phase()
{
	remove_call_out("update_day_phase");

	current_day_phase = (++current_day_phase) % sizeof(day_phase);
	message("outdoor:vision", day_phase[current_day_phase]["time_msg"] + "\n", users());
	if( !undefinedp(day_phase[current_day_phase]["event_fun"]) )
		call_other(this_object(), day_phase[current_day_phase]["event_fun"]);
	call_out("update_day_phase", day_phase[current_day_phase]["length"]);
}
//void event_sunrise()
//{
//        message("system", "\n event sunrise\n", users());
//}
//void event_morning()
//{
//        message("system", "\n event morning\n", users());
//}
//void event_afternoon()
//{
//        message("system", "\n event afternoon\n", users());
//}
//void event_night()
//{
//        message("system", "\n event night\n", users());
//}
//void event_midnight()
//{
//        message("system", "\n event midnight\n", users());
//}
//
// This is called everyday dawn by update_day_phase, defined in the
// "event_fun" field in /adm/etc/nature/day_phase
void event_midnight()
{
	object badguy;
	object room;
	if(!random(10))
	{
		if(objectp(room=load_object("/d/fy/fysquare")) && 
		objectp(badguy = new("/d/fy/npc/badguy")))
		badguy->move(room);
		badguy->ccommand("chat 月黑杀人，风高放火！");
		badguy = new("/d/fy/npc/badguy");
		badguy->move(room);
                badguy = new("/d/fy/npc/badguy");
                badguy->move(room);
	}
        if(!random(10))
        {
                if(objectp(room=load_object("/d/chenxiang/cxcenter")) && 
                objectp(badguy = new("/d/fy/npc/badguy")))
                badguy->move(room);
                badguy->ccommand("chat 月黑杀人，风高放火！");
                badguy = new("/d/fy/npc/badguy");
                badguy->move(room);
        }
        if(!random(10))
        {
                if(objectp(room=load_object("/u/guanwai/octo4")) && 
                objectp(badguy = new("/d/fy/npc/badguy")))
                badguy->move(room);
                badguy->ccommand("chat 月黑杀人，风高放火！");
                badguy = new("/d/fy/npc/badguy");
                badguy->move(room);
                badguy = new("/d/fy/npc/badguy");
                badguy->move(room);
        }
}
void event_sunrise()
{
	object *ob_list;
	int i;
	ob_list = children("/d/fy/npc/badguy");
                for(i=0; i<sizeof(ob_list); i++) 
		if(environment(ob_list[i]))
		{
			message_vision("$N叫道：天晓也，扯乎！\n",ob_list[i]);
			destruct(ob_list[i]);
                }
}
void event_dawn()
{
        object room;
	room = find_object("/d/qianjin/qianjin.c");
        if( !room) room = load_object("/d/qianjin/qianjin.c");
        if(room)
        room->set("enter_permission", 0);
//	room = find_object("/d/yingou/yingou.c");
//        if (!room) room = load_object("/d/yingou/yingou");
//        if( room )
//        room->set("enter_permission", 0);
        return;
}
// This is called everyday evening by update_day_phase, defined in the
// "event_fun" field in /adm/etc/nature/day_phase
void event_evening()
{
        object room;
	room = find_object("/d/qianjin/qianjin.c");
        if( !room) room = load_object("/d/qianjin/qianjin.c");
        if( room )
        room->set("enter_permission", 1);
//        room = find_object("/d/yingou/yingou.c");
//        if (!room) room = load_object("/d/yingou/yingou.c");
//        if( room )
//        room->set("enter_permission", 1);

        return;

}

// This is called everyday noon by update_day_phase, defined in the
// "event_fun" field in /adm/etc/nature/day_phase
void event_noon()
{
	object *ob;
	int i, skill;

	ob = users();
	for(i=0; i<sizeof(ob); i++) {
		if( !environment(ob[i]) ) continue;
		if( !environment(ob[i])->query("outdoors") ) continue;
		if( !ob[i]->query("mana") ) continue;
		if( !(skill = ob[i]->query_skill("spells", 1) )) {
			tell_object(ob[i], "你觉得一阵晕眩，好像有一股能量从身上被人吸走了。\n");
			ob[i]->set("mana", 0);
			ob[i]->receive_damage("sen", 0);
		} else if( skill < 25 ) {
			tell_object(ob[i], "正午时刻，你觉得你的法力开始消失了。\n");
			ob[i]->set("mana", (int)ob[i]->query("mana") * skill / 25 );
		}
	}
}
string outdoor_room_description()
{
	return "    " + day_phase[current_day_phase]["desc_msg"] + "。\n";
}

string game_time()
{
	return CHINESE_D->chinese_date(TIME_TICK);
}

// This function is to read a regular type of data table for day_phase and
// etc.
mapping *read_table(string file)
{
	string *line, *field, *format;
	mapping *data;
	int i, rn, fn;

	line = explode(read_file(file), "\n");
	data = ({});
	for(i=0; i<sizeof(line); i++) {
		if( line[i]=="" || line[i][0]=='#' ) continue;
		if( !pointerp(field) ) {
			field = explode( line[i], ":" );
			continue;
		}
		if( !pointerp(format) ) {
			format = explode( line[i], ":" );
			continue;
		}
		break;
	}

	for( rn = 0, fn = 0; i<sizeof(line); i++) {
		if( line[i]=="" || line[i][0]=='#' ) continue;
		if( !fn ) data += ({ allocate_mapping(sizeof(field)) });
		sscanf( line[i], format[fn], data[rn][field[fn]] );
		fn = (++fn) % sizeof(field);
		if( !fn ) ++rn;
	}
	return data;
}


mapping *query_day_phase() { return day_phase; }
