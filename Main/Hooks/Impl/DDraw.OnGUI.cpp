#include "../Hooks.hpp"

/*
Source by: https://github.com/clxxe
Modify by: https://github.com/edok3q
If you used this source. Don't forget to credit me as an author
*/

auto impl::hooks::hk_ddraw_ongui( std::uintptr_t rcx ) -> void{
	rendering::init( );

	METHOD( get_current_event_fn, xrs("UnityEngine::Event.get_current()"), 0, xrs(""), -1, std::uintptr_t( * )( ) );
	METHOD( get_type_fn, xrs("UnityEngine::Event.get_type()"), 0, xrs(""), -1, Enums::Event( * )( std::uintptr_t ) );

	if (get_type_fn(get_current_event_fn()) == Enums::Event::repaint ){
		/*ESP Init*/
		visuals::object.init( );
		rendering::draw_string( { 8, unity::c_screen::get_height( ) - 40.f, 300, 50 }, xrs(L"Special for Yougame.biz"), { 255, 255, 255, 255 }, true, true, true);
	}
}