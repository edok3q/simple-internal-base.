#pragma once
#include <SDK.hpp>

namespace unity
{
	inline std::uintptr_t asset_bundle, camera;

	class c_component {
	public:
		template < typename type >
		auto get_component(std::uintptr_t type_name) -> type {
			METHOD(get_component_fn, "UnityEngine::Component.GetComponent()", -1, "", -1, type(*)(void*, std::uintptr_t));
			return get_component_fn(this, type_name);
		}
	};

	class c_game_object : public c_component {
	public:
		template < typename type >
		auto get_component(std::uintptr_t type_name) -> type {
			METHOD(game_object_get_component_fn, "UnityEngine::GameObject.GetComponent()", 1, "", -1, std::uintptr_t(*)(void*, std::uintptr_t));
			return *reinterpret_cast<type*>(game_object_get_component_fn(this, type_name));
		}
	};

	class c_screen {
	public:
		static auto get_width() -> int {
			METHOD(get_screen_width_fn, "UnityEngine::Screen.get_width()", 0, "", -1, int (*)());
			return get_screen_width_fn();
		}

		static auto get_height() -> int {
			METHOD(get_screen_height_fn, "UnityEngine::Screen.get_height()", 0, "", -1, int (*)());
			return get_screen_height_fn();
		}
	};

	class c_time {
	public:
		static auto get_time() -> float {
			METHOD(get_time_fn, "UnityEngine::Time.get_time()", 0, "", -1, float(*)());
			return get_time_fn();
		}
	};

	struct rect_t
	{
		float x, y, w, h;
		rect_t(float _x, float _y, float _w, float _h) : x(_x), y(_y), w(_w), h(_h) { }
		rect_t() : x(0), y(0), w(0), h(0) { }

		auto contains(math::vector_2d_t point) -> bool
		{
			return point.x >= x && point.x < (x + w) && point.y >= y && point.y < (y + h);
		}
	};

	inline auto view_matrix() -> math::mat4x4_t
	{
		ICALL(get_main_camera_fn, "UnityEngine.Camera::get_main()", std::uintptr_t(*)());

		if (!camera) {
			camera = get_main_camera_fn();
		}

		auto camera_ = *reinterpret_cast<std::uintptr_t*>(camera + 0x10);
		if (!camera_) {
			return {};
		}

		auto matrix = *reinterpret_cast<math::mat4x4_t*>(camera_ + 0x2e4);
		if (!matrix.m) {
			return {};
		}

		return matrix;
	}

	inline auto screen_transform(math::vector_t wrld) -> math::vector_t
	{
		auto matrix = view_matrix();

		if (!matrix.m) {
			return { 0,0,0 };
		}

		math::vector_t out;
		const auto temp = matrix.transpose();

		auto trans = math::vector_t{ temp[3][0], temp[3][1], temp[3][2] };
		auto up = math::vector_t{ temp[1][0], temp[1][1], temp[1][2] };
		auto right = math::vector_t{ temp[0][0], temp[0][1], temp[0][2] };

		float w = trans.dot(wrld) + temp[3][3];

		if (w < 0.001f) {
			return math::vector_t(0, 0, 0);
		}

		float x = right.dot(wrld) + temp[0][3];
		float y = up.dot(wrld) + temp[1][3];

		out.x = (static_cast<float>(unity::c_screen::get_width()) / 2) * (1 + x / w);
		out.y = (static_cast<float>(unity::c_screen::get_height()) / 2) * (1 - y / w);
		out.z = 0.0f;

		return out;
	}

	inline auto calculate_fov(math::vector_t pos) -> float
	{
		auto screen_pos = screen_transform(pos);
		if (screen_pos.is_empty())
			return 10000;

		auto get_2d_dist = [&](const math::vector_2d_t& source, const math::vector_t& dest) {
			return math::vector_t::sqrtf(_powf(source.x - dest.x) + _powf(source.y - dest.y));
			};

		return get_2d_dist(math::vector_2d_t(unity::c_screen::get_width() / 2, unity::c_screen::get_height() / 2), screen_pos);
	}


	inline auto camera_pos() -> math::vector_t
	{
		ICALL(get_main_camera_fn, "UnityEngine.Camera::get_main()", std::uintptr_t(*)());

		if (!camera)
			camera = get_main_camera_fn();

		auto camera_ = *reinterpret_cast<std::uintptr_t*>(camera + 0x10);
		if (!camera_) {
			return {};
		}

		auto position = *reinterpret_cast<math::vector_t*>(camera_ + 0x42c);
		if (!position.x || !position.y) {
			return {};
		}

		return position;
	}
}