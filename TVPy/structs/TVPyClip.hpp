#pragma once
#include "../TVPy.hpp"
#include "TVPyFile.hpp"
// Clip wrapper

struct PyClip: public std::enable_shared_from_this<PyClip> {
	PyClip(std::shared_ptr<PyTVPaintFile> tvp_file, std::size_t index);
	std::weak_ptr<PyTVPaintFile> parent;
	std::size_t clip_idx;
	
	std::string name();
	std::string dialog();
	std::string action();
	std::string note();

	bool mark_in();
	long int mark_in_pos();
	bool mark_out();
	long int mark_out_pos();
	bool hidden();
	std::size_t color_idx();

private:
	Clip* get_clip();
};