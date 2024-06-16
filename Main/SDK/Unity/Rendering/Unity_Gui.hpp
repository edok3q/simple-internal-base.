#pragma once
#include "Unity_Gl.hpp"

namespace rendering
{
		inline std::uintptr_t label_style, skin, white_texture;

		inline auto init( ) -> void{
			METHOD( get_skin_fn, xrs("UnityEngine::GUI.get_skin()"), 0, xrs(""), -1, std::uintptr_t( * )( ) );
			METHOD( get_white_texture_fn, xrs("UnityEngine::Texture2D.get_whiteTexture()"), 0, xrs(""), -1, std::uintptr_t( * )( ) );

			if ( !skin || !label_style ){
				skin = get_skin_fn( );
				label_style = *reinterpret_cast< std::uintptr_t* >( skin + 0x38 );
			}

			white_texture = get_white_texture_fn( );

			METHOD( set_font_size_fn, xrs("UnityEngine::GUIStyle.set_fontSize()"), -1, xrs(""), -1, void( * )( std::uintptr_t, int ) );
			METHOD( set_color_fn, xrs("UnityEngine::GUI.set_color()"), -1, xrs(""), -1, void( * )( clr_t ) );
			METHOD( set_alignment_fn, xrs("UnityEngine::GUIStyle.set_alignment()"), -1, xrs(""), -1, void( * )( std::uintptr_t, std::uintptr_t ) );
			ICALL( load_asset_fn, xrs("UnityEngine.AssetBundle::LoadAsset_Internal(System.String,System.Type)"), std::uintptr_t( * )( std::uintptr_t, managed_system::string, std::uintptr_t ) );
			ICALL( load_from_file_fn, xrs("UnityEngine.AssetBundle::LoadFromFile_Internal(System.String,System.UInt32,System.UInt64)"), std::uintptr_t( * )( managed_system::string, std::uint32_t, std::uint64_t ) );

			if ( !unity::asset_bundle ) 
				unity::asset_bundle = load_from_file_fn(xrs(L"Assets.bundle"), 0, 0);

			const auto set_font = [ & ]( managed_system::string font_name, int size ) {
				static auto font = load_asset_fn( unity::asset_bundle, font_name, il2cpp_lib::type_object(xrs("UnityEngine"), xrs("Font" )));
				*reinterpret_cast< std::uintptr_t* >( skin + 0x18 ) = font; 
				set_font_size_fn( label_style, size );
			};

			//Here you can change your font
			set_font(xrs(L"tahoma.ttf"), 10 );

			//Material system
			if ( !gl_rendering::draw_material ){
				gl_rendering::draw_material = il2cpp_lib::object_new( il2cpp_lib::find_class(xrs("Material"), xrs("UnityEngine")));

				METHOD( create_with_shader_fn, xrs("UnityEngine::Material.CreateWithShader()"), 2, xrs(""), -1, void( * )( std::uintptr_t, std::uintptr_t ) );
				METHOD( set_int_fn, xrs("UnityEngine::Material.SetInt()"), -1, xrs(""), -1, void( * )( std::uintptr_t, managed_system::string, int ) );
				METHOD( find_shader_fn, xrs("UnityEngine::Shader.Find()"), -1, xrs(""), -1, std::uintptr_t( * )( managed_system::string ) );

				create_with_shader_fn( gl_rendering::draw_material, find_shader_fn(xrs(L"Hidden/Internal-Colored")) );

				set_int_fn( gl_rendering::draw_material, xrs(L"_SrcBlend"), 5 );
				set_int_fn( gl_rendering::draw_material, xrs(L"_DstBlend"), 10 );
				set_int_fn( gl_rendering::draw_material, xrs(L"_Cull"), 0 );
				set_int_fn( gl_rendering::draw_material, xrs(L"_ZWrite"), 0 );
			}

			set_alignment_fn( label_style, 0 );
			set_color_fn( { 1, 1, 1, 1 } );
		}

		inline auto draw_filled_rect( unity::rect_t pos, clr_t clr ) -> void
		{
			METHOD( set_color_fn, xrs("UnityEngine::GUI.set_color()"), -1, xrs(""), -1, void( * )( clr_t ) );
			METHOD( draw_texture_fn, xrs("UnityEngine::GUI.DrawTexture()"), 2, xrs(""), -1, void ( * )( unity::rect_t, std::uintptr_t ) );

			set_color_fn( clr );
			draw_texture_fn( pos, white_texture );
		}

		inline auto draw_string( unity::rect_t pos, managed_system::string text, clr_t clr, bool centered, bool drop_shadow, bool outline) -> void
		{
			if ( !label_style ) {
				return;
			}

			METHOD( gui_content_temp_fn, xrs("UnityEngine::GUIContent.Temp()"), 1, xrs("t"), 1, std::uintptr_t( * )( managed_system::string* ) );
			METHOD( set_color_fn, xrs("UnityEngine::GUI.set_color()"), -1, xrs(""), -1, void( * )( clr_t ) );
			METHOD( label_fn, xrs("UnityEngine::GUI.Label()"), 3, xrs("content"), 2, void( * )( unity::rect_t, std::uintptr_t, std::uintptr_t ) );
			METHOD( set_alignment_fn, xrs("UnityEngine::GUIStyle.set_alignment()"), -1, xrs(""), -1, void( * )( std::uintptr_t, std::uintptr_t ) );

			const auto content = gui_content_temp_fn( &text );

			if ( centered )
				set_alignment_fn( label_style, 0x4 );
			else
				set_alignment_fn( label_style, 0x0 );

			if ( outline ) 
			{
				set_color_fn( { 0, 0, 0, ( clr.a * 255 ) } );
				label_fn( { pos.x, pos.y + 1, pos.w, pos.h }, content, label_style );
				label_fn( { pos.x, pos.y - 1, pos.w, pos.h }, content, label_style );
				label_fn( { pos.x - 1, pos.y, pos.w, pos.h }, content, label_style );
				label_fn( { pos.x + 1, pos.y, pos.w, pos.h }, content, label_style );
			}

			if ( drop_shadow ) 
			{
				set_color_fn( { 0, 0, 0, ( clr.a * 255 ) } );
				label_fn( { pos.x + 1, pos.y + 1, pos.w, pos.h }, content, label_style );
			}

			set_color_fn( clr );
			label_fn( pos, content, label_style );
		}
}
