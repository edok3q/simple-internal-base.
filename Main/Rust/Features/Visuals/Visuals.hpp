#pragma once
#include <SDK.hpp>

/*
Source by: https://github.com/clxxe
Modify by: https://github.com/edok3q
If you used this source. Don't forget to credit me as an author
*/

class c_visuals{
public:
	auto init( ) -> void;
private:
	std::uintptr_t client_entities, shader;

	struct box_t{
		math::vector_2d_t position;
		math::vector_2d_t size;
	};

	auto render_player(c_base_player* player) -> void;
};
	namespace visuals{
		inline c_visuals object;
	}
