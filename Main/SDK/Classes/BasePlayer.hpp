#pragma once

/*
Source by: https://github.com/clxxe
Modify by: https://github.com/edok3q
If you used this source. Don't forget to credit me as an author
*/

class c_base_player{
public:
	DECLARE_MEMBER( float, "BaseCombatEntity", _health )
	DECLARE_MEMBER( float, "BaseCombatEntity", _maxHealth )
	DECLARE_MEMBER( std::uintptr_t, "BasePlayer", playerModel )
	DECLARE_MEMBER( std::uintptr_t, "BasePlayer", playerFlags )

	auto is_npc() -> bool {
		METHOD(get_is_npc_fn, "PlayerModel.get_IsNpc()", -1, "", -1, bool(*)(std::uintptr_t));
		return get_is_npc_fn(this->playerModel());
	}

	auto is_sleeping() -> bool {
		return this->playerFlags() & Enums::Player_Flags::sleeping;
	}

	auto is_local_player() -> bool {
		auto player_model = this->playerModel();

		FIELD("PlayerModel", isLocalPlayer);
		return *reinterpret_cast<bool*>(player_model + isLocalPlayer);
	}

	auto name( ) -> const wchar_t* {
		FIELD( "BasePlayer", _displayName );
		auto player_name = reinterpret_cast< managed_system::string* >( *reinterpret_cast< std::uintptr_t* >( this + _displayName ) );
		return player_name->buffer;
	}

	auto weapon() -> c_base_weapon*{
		FIELD("BasePlayer", clActiveItem);
		const auto active_uid = *reinterpret_cast<unsigned int*>(this + clActiveItem);
		if (!active_uid)
			return 0;

		FIELD("Item", uid);
		FIELD("BasePlayer", inventory);
		FIELD("PlayerInventory", containerBelt);
		FIELD("ItemContainer", itemList);

		const auto inv = *reinterpret_cast<std::uint64_t*>(this + inventory);
		const auto belt = *reinterpret_cast<std::uint64_t*>(inv + containerBelt);
		const auto item_list = *reinterpret_cast<std::uint64_t*>(belt + itemList);

		const auto items = *reinterpret_cast<std::uint64_t*>(item_list + 0x10);
		if (!items)
			return {};

		for (int i = 0; i < 6; i++)
		{
			const auto weapon_info = *reinterpret_cast<c_base_weapon**>(items + 0x20 + (i * 0x8));
			if (!weapon_info)
				return {};

			const auto weapon_uid = *reinterpret_cast<unsigned int*>(weapon_info + uid);
			if (!weapon_uid)
				return {};

			if (active_uid == weapon_uid)
				return weapon_info;
		}
		return {};
	}

	auto get_bone_transform(int id) -> c_transform* {
		FIELD("BaseEntity", model); FIELD("Model", boneTransforms);

		const auto entity_model = *reinterpret_cast<std::uintptr_t*>(this + model);
		if (!entity_model)
			return { };

		const auto bone_dict = *reinterpret_cast<std::uintptr_t*>(entity_model + boneTransforms);
		if (!bone_dict)
			return { };

		return *reinterpret_cast<c_transform**>(bone_dict + 0x20 + id * 0x8);
	}
};