#include "TVPyClip.hpp"
#include <tvp_pp/structs/Clip.hpp>
#define EXPIRE_GUARD \
if (parent.expired()) {\
throw std::exception("Parent TVPaint File object not valid anymore.");\
}\

#define CLIP \
auto tvp_file = parent.lock()->tvp_file;\
Clip* clip{nullptr};\
if( clip_idx < tvp_file->clips.size() ){\
	clip = tvp_file->clips.at(clip_idx).get();\
}\
else {\
throw std::exception("Clip is inaccessible / out of bounds."); \
}\
clip\

PyClip::PyClip(std::shared_ptr<PyTVPaintFile> tvp_file, std::size_t index): parent(tvp_file), clip_idx(index) {};

std::string PyClip::name() {
	EXPIRE_GUARD;
	CLIP->name;
};
std::string PyClip::dialog() {
	EXPIRE_GUARD;
	CLIP->dialog;
};
std::string PyClip::action() {
	EXPIRE_GUARD;
	CLIP->action;
};
std::string PyClip::note() {
	EXPIRE_GUARD;
	CLIP->note;
};

bool PyClip::mark_in() {
	EXPIRE_GUARD;
	CLIP->mark_in;
};
long int PyClip::mark_in_pos() {
	EXPIRE_GUARD;
	CLIP->mark_in_pos;
};
bool PyClip::mark_out() {
	EXPIRE_GUARD;
	CLIP->mark_out;
};
long int PyClip::mark_out_pos() {
	EXPIRE_GUARD;
	CLIP->mark_out_pos;
};
bool PyClip::hidden() {
	EXPIRE_GUARD;
	CLIP->hidden;
};
std::size_t PyClip::color_idx() {
	EXPIRE_GUARD;
	CLIP->color_idx;
};