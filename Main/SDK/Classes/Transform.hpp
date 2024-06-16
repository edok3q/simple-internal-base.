#pragma once

/*
Source by: https://github.com/clxxe
Modify by: https://github.com/edok3q
If you used this source. Don't forget to credit me as an author
*/

class c_transform{
public:
	auto position( ) -> math::vector_t{
		METHOD( get_position_fn, "UnityEngine::Transform.get_position()", 0, "", -1, math::vector_t( * )( c_transform* ) );
		return get_position_fn( this );
	}
};