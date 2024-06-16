#include "Visuals.hpp"

/*
Source by: https://github.com/clxxe
Modify by: https://github.com/edok3q
If you used this source. Don't forget to credit me as an author
*/

auto c_visuals::init() -> void
{
	//Init BaseNetworkable
	auto get_client_entities = [&]() { client_entities = il2cpp_lib::field(xrs("BaseNetworkable"), xrs("clientEntities"), false); };

	if (!client_entities)
		get_client_entities();

	const auto entity_list = reinterpret_cast<managed_system::list_dictionary*>(client_entities);

	if (!entity_list) {
		get_client_entities();
		return;
	}

	const auto buffer = entity_list->buffer< std::uintptr_t >();

	for (size_t idx{ 0 }; idx <= entity_list->size(); idx++){
		auto current_object = *reinterpret_cast<std::uintptr_t*>(buffer + 0x20 + (idx * 0x8));
		if (!current_object)
			continue;

		auto base_object = *reinterpret_cast<std::uintptr_t*>(current_object + 0x10);
		if (!base_object)
			continue;

		auto object = *reinterpret_cast<std::uintptr_t*>(base_object + 0x30);
		if (!object)
			continue;

		const auto tag = *reinterpret_cast<std::uint16_t*>(object + 0x54);
		if (tag != 6)
			continue;

		const auto ent = *reinterpret_cast<std::uintptr_t*>(base_object + 0x28);
		if (!ent)
			continue;

		auto player = reinterpret_cast<c_base_player*>(ent);

		//Check if local_player! Comment this if you want render visuals on local_player
		if (player->is_local_player())
			continue;

		//Check if npc! Comment this if you want render visuals on npc
		if (player->is_npc())
			continue;

		//Check if player_sleeping! Comment this if you want render visuals on sleepers
		if (player->is_sleeping())
			continue;

		//Init Render_Player
		render_player(player);
	}
}

auto c_visuals::render_player( c_base_player* player ) -> void{
	METHOD( get_transform_fn, xrs("UnityEngine::Component.get_transform()"), 0, xrs(""), -1, c_transform * ( * )( void* ) );

	//Getting player position
	auto base_pos = unity::screen_transform( get_transform_fn( player )->position( ) );
	//Getting player head position
	auto head_pos = unity::screen_transform( player->get_bone_transform( 48 )->position( ) );
	//Getting player stand position
	auto standing_pos = unity::screen_transform( get_transform_fn( player )->position( ) + math::vector_t{ 0, 1.9f, 0, } );

	if ( base_pos.is_empty( ) || head_pos.is_empty( ) || standing_pos.is_empty( ) ) return;

	const auto box_width = ( base_pos.y - standing_pos.y ) * 0.45f;
	const auto box_height = ( base_pos.y - head_pos.y ) * 1.15f;
	const auto box = box_t{ { base_pos.x - box_width * 0.5f, base_pos.y - box_height  }, { box_width, box_height } };

	//Player Box
	gl_rendering::box({ box.position.x - 1, box.position.y - 1 }, { box.size.x + 2, box.size.y + 2 }, { 0, 0, 0, 255 });
	gl_rendering::box({ box.position.x, box.position.y }, { box.size.x, box.size.y }, { 255, 255, 255, 255 });
	gl_rendering::box({ box.position.x + 1, box.position.y + 1 }, { box.size.x - 2, box.size.y - 2 }, { 0, 0, 0, 255 });
	//Filled box
	gl_rendering::filled_box({ box.position.x + 1, box.position.y + 1 }, { box.size.x - 2, box.size.y - 2 }, { 0, 0, 0, 80 });

	//Player Name
	rendering::draw_string( { box.position.x - 100.f, box.position.y - 18.f, ((box.size.x) / 2 * 2 ) + 200.f, 20 }, player->name(), { 255, 255, 255, 255 }, true, false, false);

	//Player Weapon Name
	if ( const auto player_weapon = player->weapon( ) ){
			rendering::draw_string( { box.position.x - 100.f, box.position.y + box.size.y - 1.f, ((box.size.x) / 2 * 2 ) + 200.f, 20 }, player->weapon()->name(), { 255, 255, 255, 255 }, true, false, false);
	}

	const auto health = box_t{ { box.position.x - 5, box.position.y + ( box.size.y - box.size.y * ( player->_health( ) ) / (player->is_npc() ? player->_maxHealth( ) : 100 ) ) }, { 2, box.size.y * ( player->_health( ) ) / (player->is_npc() ? player->_maxHealth( ) : 100 ) } };
	const auto health_bg = box_t{ { box.position.x - 5, box.position.y }, { 2, box.size.y } };

	//Player Health
	rendering::draw_filled_rect( { health_bg.position.x, health_bg.position.y - 1,  health_bg.size.x + 1, health_bg.size.y + 2 }, clr_t( 0, 0, 0, 180 ) );
	rendering::draw_filled_rect( { health.position.x + 1, health.position.y, health.size.x - 1, health.size.y }, clr_t( 135, 186, 49, 240 ) );
}
