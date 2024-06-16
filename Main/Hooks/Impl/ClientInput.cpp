#include "../Hooks.hpp"

/*
Source by: https://github.com/clxxe
Modify by: https://github.com/edok3q
If you used this source. Don't forget to credit me as an author
*/

auto impl::hooks::hk_bp_client_input( c_base_player* base_player, std::uintptr_t* input_state ) -> void{
	if ( base_player ){ 
		//Init DDraw
		METHOD( draw_get, xrs("UnityEngine::DDraw.Get()"), -1, xrs(""), -1, void ( * )( ) ); draw_get( );
	}
	//Return bp_client_input
	impl::hooks::bp_client_input.get_original< decltype( &impl::hooks::hk_bp_client_input ) >( )( base_player, input_state );
}