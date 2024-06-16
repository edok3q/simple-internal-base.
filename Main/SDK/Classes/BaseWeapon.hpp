#pragma once

/*
Source by: https://github.com/clxxe
Modify by: https://github.com/edok3q
If you used this source. Don't forget to credit me as an author
*/


class c_base_weapon 
{
public:
	auto name( ) -> const wchar_t* 
	{
		FIELD( "Item", info );
		const auto item_def = *reinterpret_cast< std::uintptr_t* >( this + info );
		if ( !item_def )
			return {};

		FIELD( "ItemDefinition", displayName );
		const auto display_name = *reinterpret_cast< std::uintptr_t* >( item_def + displayName );
		if ( !display_name )
			return {};

		const auto weapon_name = reinterpret_cast< managed_system::string* >( *reinterpret_cast< std::uintptr_t* >( display_name + 0x18 ) );

		return weapon_name->buffer;
	}
};