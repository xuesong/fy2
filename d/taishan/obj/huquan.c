// Copyright (C) 1995, by Tie Yu and Daniel Yu. All rights reserved.
// This software can not be used, copied, or modified in any form without
// the written permission from authors.
inherit ITEM;
void create()
{
	set_name("山峦", ({ "山峦","hill", "shanluan" }));
	set_weight(600);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "");
		set("long",
			"你越看越觉得山势中似乎饱含着武学至理。\n");
		set("value", 70);
		set("material", "wood");
		set("no_shown",1);
		set("no_get",1);
		set("no_drop",1);
		set("skill", ([
			"name": 		"tigerstrike",	
			"exp_required":	0,		
			"sen_cost":		30,	
			"difficulty":	20,	
			"max_skill":	99		
		]) );
	}
}
