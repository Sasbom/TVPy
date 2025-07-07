#pragma once
#include "../TVPy.hpp"
#include "TVPyFile.hpp"
#include <tvp_pp/structs/Layer.hpp>
// Layer wrapper

struct PyLayer : public std::enable_shared_from_this<PyLayer> {
	PyLayer(std::shared_ptr<PyTVPaintFile> tvp_file, std::size_t clip_index, std::size_t layer_index);
	std::weak_ptr<PyTVPaintFile> parent;
	std::size_t clip_idx{};
	std::size_t layer_idx{};

	std::string name();
	std::string name_ascii();

	std::size_t first_frame_num();
	long int frame_offset();
	std::size_t frames_amount();

	blendmode_t blend_mode();

	// Replace these repeat in/out w/ enum class type
	repeat_t repeat_in_type();
	repeat_t repeat_out_type();

	std::size_t group_id();

	double opacity();

	bool invisible();
	bool lighttable();
	bool stencil();
	bool locked();
	bool position_locked();
	bool preserve_trans();

	std::string format_info();

	void cache_layer_contents();
	void clear_layer_contents();

	// output as numpy compatible image
	cache_t& get_cache_at_frame(int long const& frame);
	
	py::object py_get_cache_at_frame(int long frame);
	
	
	std::string repeat_t_to_str(repeat_t const& rep);
	std::string blendmode_t_to_str(blendmode_t const& blend);
private:
	Layer * get_layer();
};

