#pragma once

/*
Source by: https://github.com/clxxe
Modify by: https://github.com/edok3q
If you used this source. Don't forget to credit me as an author
*/


namespace Enums{
		enum Player_Flags : int {
			unused_1 = ( 1 << 0 ),
			unused_2 = ( 1 << 1 ),
			is_admin = ( 1 << 2 ),
			receiving_snapshot = ( 1 << 3 ),
			sleeping = ( 1 << 4 ),
			spectating = ( 1 << 5 ),
			wounded = ( 1 << 6 ),
			is_developer = ( 1 << 7 ),
			connected = ( 1 << 8 ),
			third_person_viewmode = ( 1 << 10 ),
			eyes_viewmode = ( 1 << 11 ),
			chat_mute = ( 1 << 12 ),
			no_sprint = ( 1 << 13 ),
			aiming = ( 1 << 14 ),
			display_sash = ( 1 << 15 ),
			relaxed = ( 1 << 16 ),
			safe_zone = ( 1 << 17 ),
			server_fall = ( 1 << 18 ),
			workbench_1 = ( 1 << 20 ),
			workbench_2 = ( 1 << 21 ),
			workbench_3 = ( 1 << 22 ),
		};

		enum class Event : int{
			mouse_down = 0,
			mouse_up = 1,
			mouse_drag = 3,
			key_down = 4,
			key_up = 5,
			repaint = 7
		};

		enum Primitive_Mode : int {
			lines = 1,
			line_strip,
			line_loop,
			triangles = 4,
			triangle_strip,
			quads = 7
		};
}