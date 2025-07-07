#include "TVPyClip.hpp"
#include <tvp_pp/structs/Clip.hpp>

#define EXPIRE_GUARD                                                        \
if (parent.expired()) {                                                     \
    throw py::value_error("Parent TVPaint File object not valid anymore."); \
}

PyClip::PyClip(std::shared_ptr<PyTVPaintFile> tvp_file, std::size_t index): parent(tvp_file), clip_idx(index) {};

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