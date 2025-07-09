#include "TVPyClip.hpp"
#include "TVPyLayer.hpp"
#include <tvp_pp/structs/Clip.hpp>

#define EXPIRE_GUARD                                                        \
if (parent.expired()) {                                                     \
    throw py::value_error("Parent TVPaint File object not valid anymore."); \
}

PyClip::PyClip(std::shared_ptr<PyTVPaintFile> tvp_file, std::size_t index): parent(tvp_file), clip_idx(index) {
	this->init_layers();
};

Clip* PyClip::get_clip() {
	auto tvp_file = parent.lock()->tvp_file;
	Clip* clip{ nullptr };                                               
	if (clip_idx < tvp_file->clips.size()) {
		clip = tvp_file->clips.at(clip_idx).get();                     
	}                                                  
	else {
		throw py::index_error("Clip is inaccessible / out of bounds."); 
	}
	return clip;
}

std::vector<std::shared_ptr<PyLayer>> PyClip::init_layers() {
	EXPIRE_GUARD;
	auto list = std::vector<std::shared_ptr<PyLayer>>();
	for (std::size_t i{}; i < get_clip()->layers.size(); i++) {
		list.push_back(std::make_shared<PyLayer>(parent.lock(), clip_idx, i));
	}
	return list;
}

std::string PyClip::name() {
	EXPIRE_GUARD;
	return get_clip()->name;
};
std::string PyClip::dialog() {
	EXPIRE_GUARD;
	return get_clip()->dialog;
};
std::string PyClip::action() {
	EXPIRE_GUARD;
	return get_clip()->action;
};
std::string PyClip::note() {
	EXPIRE_GUARD;
	return get_clip()->note;
};

bool PyClip::mark_in() {
	EXPIRE_GUARD;
	return get_clip()->mark_in;
};
long int PyClip::mark_in_pos() {
	EXPIRE_GUARD;
	return get_clip()->mark_in_pos;
};
bool PyClip::mark_out() {
	EXPIRE_GUARD;
	return get_clip()->mark_out;
};
long int PyClip::mark_out_pos() {
	EXPIRE_GUARD;
	return get_clip()->mark_out_pos;
};
bool PyClip::hidden() {
	EXPIRE_GUARD;
	return get_clip()->hidden;
};
std::size_t PyClip::color_idx() {
	EXPIRE_GUARD;
	return get_clip()->color_idx;
};

std::string PyClip::format_info() {
	auto s = std::format(R"(Clip:
Name: {}
Dialog: {}
Action: {}
Note: {}
Dialog Size : {}
Action Size: {}
Note Size: {}
Mark In: {}
Mark In Position: {}
Mark Out: {}
Mark Out Position: {}
Hidden: {} 
Color Index: {}
)",
	get_clip()->name, get_clip()->dialog, get_clip()->action, get_clip()->note,
	get_clip()->dialog_size, get_clip()->action_size, get_clip()->note_size,
	get_clip()->mark_in, get_clip()->mark_in_pos, get_clip()->mark_out, get_clip()->mark_out_pos,
	get_clip()->hidden, get_clip()->color_idx
	);
	return s;
}


void register_tvpclip(py::module_& m) {
	py::class_<PyClip>(m, "TvpClip")
		.def_property("name", &PyClip::name, EMPTY_FUNC)
		.def_property("dialog", &PyClip::dialog, EMPTY_FUNC)
		.def_property("action", &PyClip::action, EMPTY_FUNC)
		.def_property("note", &PyClip::note, EMPTY_FUNC)
		.def_property("mark_in", &PyClip::mark_in, EMPTY_FUNC)
		.def_property("mark_in_pos", &PyClip::mark_in_pos, EMPTY_FUNC)
		.def_property("mark_out", &PyClip::mark_out, EMPTY_FUNC)
		.def_property("mark_out_pos", &PyClip::mark_out_pos, EMPTY_FUNC)
		.def_property("hidden", &PyClip::hidden, EMPTY_FUNC)
		.def_property("color_idx", &PyClip::color_idx, EMPTY_FUNC)
		.def("layers", [](PyClip& c) {return c.layers; }, py::return_value_policy::reference_internal)
		.def("__getitem__",                    // operator[] support
			[](PyClip& c, int const& idx) {
				if (idx >= 0 && idx < c.layers.size()) 
					return c.layers; 
				else 
					throw py::index_error("Requested layer out of range."); 
			}, 
			py::return_value_policy::reference_internal)
		.def("__str__", &PyClip::format_info)
		.def("__repr__", [](PyClip& c) {
		return std::format("<TvpClip '\"{}\" containing {} layers>", c.name(), c.layers.size()); }
		);
}