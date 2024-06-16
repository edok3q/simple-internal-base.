#pragma once

/*
Source by: https://github.com/clxxe
Modify by: https://github.com/edok3q
If you used this source. Don't forget to credit me as an author
*/

#include "../Utils/Il2cpp/Hook/Hook.hpp"
#include <SDK.hpp>

#define HOOK( type, name, args ) inline impl::virt_hook_c name; type hk_##name args;
#define SWAP( type, name, args ) inline impl::swap_ptr_c name; type hk_##name args;
#define HOOK_CUSTOM( addr, orig, repl ) orig = *addr; *addr = reinterpret_cast< std::uintptr_t >( repl ); 

namespace impl 
{
	namespace hooks{
		HOOK( void, bp_client_input, ( c_base_player* base_player, std::uintptr_t* input_state ) )
		HOOK( void, bce_client_init, ( c_base_player* instance, void* entity ) )
		SWAP( void, ddraw_ongui, ( std::uintptr_t rcx ) )
	}
}