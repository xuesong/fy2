//	equip.c

#include <dbase.h>
#include <weapon.h>

int wear()
{
	object owner;
	mapping armor_prop, applied_prop;
	string *apply, type;

	// Only character object can wear armors.
	if( !(owner = environment())->is_character() ) return 0;

	// If already worn, just recognize it.
	if( query("equipped") ) return 1;

	// Check if we have "armor_prop" defined.
	if( !mapp(armor_prop = query("armor_prop")) )
		return notify_fail("你只能穿戴可当作护具的东西。\n");
	type = query("armor_type");
	if(type == "shield")
        if(owner->query_temp("left_hand") && owner->query_temp("right_hand"))
        return notify_fail("你必须至少空出一只手来使用武器。\n");
	if( owner->query_temp("armor/" + type) )
		return notify_fail("你已经穿戴了同类型的护具了。\n");

	owner->set_temp("armor/" + type, this_object());
	apply = keys(armor_prop);
	applied_prop = owner->query_temp("apply");
	if( !mapp(applied_prop) ) applied_prop = ([]);
	for(int i = 0; i<sizeof(apply); i++)
		if( undefinedp(applied_prop[apply[i]]) )
			applied_prop[apply[i]] = armor_prop[apply[i]];
		else
			applied_prop[apply[i]] += armor_prop[apply[i]];
	owner->set_temp("apply", applied_prop);
	set("equipped", "worn");
//	make shield a lefthand toy
	if (type == "shield")
	{
	if(!objectp(owner->query_temp("left_hand"))) owner->set_temp("left_hand",this_object());
	else if(!objectp(owner->query_temp("right_hand"))) owner->set_temp("right_hand",this_object());
	}
	return 1;
}

int wield()
{
	object owner, old_weapon;
	mapping weapon_prop;
	string *apply, type;
	int flag;

	// Only character object can wear armors.
	if( !(owner = environment())->is_character() ) return 0;

	// If already wielded, just recognize it.
	if( query("equipped") ) return 1;

	// Check if we have "weapon_prop" defined.
	if( !mapp(weapon_prop = query("weapon_prop")) )
		return notify_fail("你只能装备可当作武器的东西。\n");

// if both hands has something, then forget about it
// the rule is also that primary weapon can only be in RIGHT hand
	if(owner->query_temp("left_hand") && owner->query_temp("right_hand"))
	return notify_fail("你必须至少空出一只手来使用盾。\n");
	flag = query("flag");
	if(flag & NO_HANDED)
	{
	if(!(owner->query_temp("left_hand"))) owner->set_temp("left_hand", this_object());
	else  owner->set_temp("right_hand",this_object());
	}
	else if (flag & TWO_HANDED) {
		if( owner->query_temp("left_hand") || owner->query_temp("right_hand"))
			return notify_fail("你必须空出双手才能装备双手武器。\n");
		owner->set_temp("weapon", this_object());
                owner->set_temp("left_hand", this_object());
                owner->set_temp("right_hand", this_object());
	} else if ( flag & SECONDARY ) {
			if(!(owner->query_temp("right_hand"))) owner->set_temp("right_hand",this_object());
			else owner->set_temp("left_hand",this_object());
			if(!(owner->query_temp("weapon"))) owner->set_temp("weapon",this_object());
                        else owner->set_temp("secondary_weapon",this_object());
	}
	else //  we try to wield a single hand primary weapon
	{
		if(!(owner->query_temp("left_hand")) && !(owner->query_temp("right_hand"))) // both hand empty
		{ owner->set_temp("right_hand",this_object()); owner->set_temp("weapon",this_object());}
		else
		{
		if(old_weapon = owner->query_temp("right_hand") )
		if( !((int)old_weapon->query("flag") & SECONDARY))
		return notify_fail("你必须先放下你目前装备的武器。\n");
		// do a switch
		owner->set_temp("left_hand",old_weapon);
		owner->set_temp("secondary_weapon",old_weapon);
		owner->set_temp("right_hand",this_object());
		owner->set_temp("weapon",this_object());
		}
	}

	apply = keys(weapon_prop);
	for(int i = 0; i<sizeof(apply); i++)
		owner->add_temp("apply/" + apply[i], weapon_prop[apply[i]]);

	owner->reset_action();
	set("equipped", "wielded");
	return 1;
}

int unequip()
{
	object owner;
	mapping prop, applied_prop;
	string *apply, equipped;

	if( !(owner = environment())->is_character() ) return 0;

	if( !stringp(equipped = query("equipped")) )
		return notify_fail("你目前并没有装备这样东西。\n");

	if( equipped=="wielded" ) {
		if( (object)owner->query_temp("weapon") == this_object() )
		{
			owner->delete_temp("weapon");
			if(objectp(owner->query_temp("secondary_weapon")))
			{owner->set_temp("weapon",(owner->query_temp("secondary_weapon")));
			 owner->delete_temp("secondary_weapon");}	
		}
		else if( (object)owner->query_temp("secondary_weapon") == this_object() )
			owner->delete_temp("secondary_weapon");
		prop = query("weapon_prop");
		owner->reset_action();
	} else if( equipped=="worn" ) {
		owner->delete_temp("armor/" + query("armor_type") );
		prop = query("armor_prop");
	}
                if((object)owner->query_temp("left_hand") == this_object())
                owner->delete_temp("left_hand");
                if ((object)owner->query_temp("right_hand") == this_object())
                owner->delete_temp("right_hand");

	apply = keys(prop);
	applied_prop = owner->query_temp("apply");
	for(int i = 0; i<sizeof(apply); i++)
		// To support array apply, we cannot add_temp() here.
		applied_prop[apply[i]] -= prop[apply[i]];

	delete("equipped");
	return 1;
}
