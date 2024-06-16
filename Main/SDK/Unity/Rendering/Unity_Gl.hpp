#pragma once

namespace gl_rendering{
	inline std::uintptr_t draw_material;
		class c_gl {
		public:
			static auto push( ) -> void {
				METHOD( push_fn, xrs("UnityEngine::GL.PushMatrix()"), 0, xrs(""), -1, void( * )( void ) );
				return push_fn( );
			}

			static auto pop( ) -> void {
				METHOD( pop_fn, xrs("UnityEngine::GL.PopMatrix()"), 0, xrs(""), -1, void( * )( void ) );
				return pop_fn( );
			}

			static auto begin( int mode ) -> void {
				METHOD( begin_fn, xrs("UnityEngine::GL.Begin()"), 1, xrs(""), -1, void( * )( int ) );
				return begin_fn( mode );
			}

			static auto end( ) -> void {
				METHOD( end_fn, xrs("UnityEngine::GL.End()"), 0, xrs(""), -1, void( * )( void ) );
				return end_fn( );
			}

			static auto color( clr_t clr ) -> void {
				METHOD( color_fn, xrs("UnityEngine::GL.Color()"), 1, xrs(""), -1, void( * )( clr_t ) );
				return color_fn( clr );
			}

			static auto vertex( float x, float y, float z ) -> void {
				METHOD( vertex_fn, xrs("UnityEngine::GL.Vertex3()"), -1, xrs(""), -1, void( * )( float, float, float ) );
				return vertex_fn( x, y, z );
			}
		};

		inline auto gl_start( int mode ) -> void{
			if ( !draw_material )
				return;

			METHOD( set_pass_fn, xrs("UnityEngine::Material.SetPass()"), 1, xrs(""), -1, bool( * )( std::uintptr_t, int ) );

			set_pass_fn( draw_material, 0 );
			c_gl::push( );
			c_gl::begin( mode );
		}

		inline auto gl_end( ) -> void
		{
			c_gl::end( );
			c_gl::pop( );
		}

		inline auto line( math::vector_2d_t start, math::vector_2d_t end, clr_t col ) -> void{
			gl_start(Enums::Primitive_Mode::lines );

			c_gl::color( col );
			c_gl::vertex( start.x, start.y, 0 );
			c_gl::vertex( end.x, end.y, 0 );

			gl_end( );
		}

		inline auto box( math::vector_2d_t pos, math::vector_2d_t size, clr_t col ) -> void{
			gl_start( Enums::Primitive_Mode::line_strip );

			c_gl::color( col );
			c_gl::vertex( pos.x + 0.5f, pos.y + 0.5f, 0 );
			c_gl::vertex( pos.x + size.x + 0.5f, pos.y + 0.5f, 0 );
			c_gl::vertex( pos.x + size.x + 0.5f, pos.y + size.y + 0.5f, 0 );
			c_gl::vertex( pos.x + 0.5f, pos.y + size.y + 0.5f, 0 );
			c_gl::vertex( pos.x + 0.5f, pos.y + 0.5f, 0 );

			gl_end( );
		}

		inline auto filled_box(math::vector_2d_t pos, math::vector_2d_t size, clr_t col) -> void{
			gl_start(Enums::Primitive_Mode::quads);

			c_gl::color(col);
			c_gl::vertex(pos.x + 0.5f, pos.y + 0.5f, 0);
			c_gl::vertex(pos.x + size.x + 0.5f, pos.y + 0.5f, 0);
			c_gl::vertex(pos.x + size.x + 0.5f, pos.y + size.y + 0.5f, 0);
			c_gl::vertex(pos.x + 0.5f, pos.y + size.y + 0.5f, 0);

			gl_end();
		}
}