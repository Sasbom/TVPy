#include "TVPyLayer.hpp"

#define EXPIRE_GUARD                                                        \
if (parent.expired()) {                                                     \
    throw py::value_error("Parent TVPaint File object not valid anymore."); \
}

PyLayer::PyLayer(std::shared_ptr<PyTVPaintFile> tvp_file, std::size_t clip_index, std::size_t layer_index) : parent(tvp_file), clip_idx(clip_index), layer_idx(layer_index) {};

std::string PyLayer::repeat_t_to_str(repeat_t const& rep) {
    switch (rep) {
    case repeat_t::NONE:
        return "NONE";
    case repeat_t::REPEAT:
        return "REPEAT";
    case repeat_t::PINGPONG:
        return "PINGPONG";
    case repeat_t::HOLD:
        return "HOLD";
    }
    return "NONE";
}

#ifdef DIFFERENCE // on msvc, difference is a macro in winuser.
#define RESTORE_DIFFERENCE
#undef DIFFERENCE
#endif

std::string PyLayer::blendmode_t_to_str(blendmode_t const& blend) {
    switch (blend) {
    case blendmode_t::COLOR:
        return "Color";
    case blendmode_t::BEHIND:
        return "Behind";
    case blendmode_t::ERASE:
        return "Erase";
    case blendmode_t::SHADE:
        return "Shade";
    case blendmode_t::LIGHT:
        return "Light";
    case blendmode_t::COLORIZE:
        return "Colorize";
    case blendmode_t::TINT:
        return "Tint";
    case blendmode_t::SATURATE2:
        return "Saturate2";
    case blendmode_t::VALUE:
        return "Value";
    case blendmode_t::ADD:
        return "Add";
    case blendmode_t::SUB:
        return "Sub";
    case blendmode_t::MULTIPLY:
        return "Multiply";
    case blendmode_t::SCREEN:
        return "Screen";
    case blendmode_t::REPLACE:
        return "Replace";
    case blendmode_t::SUBSTITUTE:
        return "Substitute";
    case blendmode_t::DIFFERENCE:
        return "Difference";
    case blendmode_t::DIVIDE:
        return "Divide";
    case blendmode_t::OVERLAY:
        return "Overlay";
    case blendmode_t::OVERLAY2:
        return "Overlay2";
    case blendmode_t::DODGE:
        return "Dodge";
    case blendmode_t::BURN:
        return "Burn";
    case blendmode_t::HARDLIGHT:
        return "Hard Light";
    case blendmode_t::SOFTLIGHT:
        return "Soft Light";
    case blendmode_t::GRAINEXTRACT:
        return "Grain Extract";
    case blendmode_t::GRAINMERGE:
        return "Grain Merge";
    case blendmode_t::SUBTRACT:
        return "Subtract";
    case blendmode_t::DARKENONLY:
        return "Darken Only";
    case blendmode_t::LIGHTENONLY:
        return "Lighten Only";
    case blendmode_t::ALPHADIFF:
        return "Alpha Diff";
    }
    return "COLOR";
}

#ifdef RESTORE_DIFFERENCE
#define DIFFERENCE 11
#undef RESTORE_DIFFERENCE
#endif

Layer* PyLayer::get_layer() {
	auto tvp_file = parent.lock()->tvp_file;
	Layer* layer{ nullptr };
	if (clip_idx < tvp_file->clips.size()) {
		auto clip = tvp_file->clips.at(clip_idx).get();
		if (layer_idx < clip->layers.size()) {
			layer = clip->layers.at(layer_idx).get();
		}
		else {
			throw py::index_error("Layer index is inaccessible / out of bounds.");
		}
	}
	else {
		throw py::index_error("Clip index is inaccessible / out of bounds.");
	}
	return layer;
}

std::string PyLayer::name() {
	EXPIRE_GUARD;
	return get_layer()->name;
};
std::string PyLayer::name_ascii() {
	EXPIRE_GUARD;
	return get_layer()->name_ascii;
};

std::size_t PyLayer::first_frame_num() {
	EXPIRE_GUARD;
	return get_layer()->first_frame_num;
};
long int PyLayer::frame_offset() {
	EXPIRE_GUARD;
	return get_layer()->frame_offset;
};
std::size_t PyLayer::frames_amount() {
	EXPIRE_GUARD;
	return get_layer()->frames_amount;
};

blendmode_t PyLayer::blend_mode() {
	EXPIRE_GUARD;
	return get_layer()->blend_mode;
};

repeat_t PyLayer::repeat_in_type() {
	EXPIRE_GUARD;
	return get_layer()->repeat_in_type;
};
repeat_t PyLayer::repeat_out_type() {
	EXPIRE_GUARD;
	return get_layer()->repeat_out_type;
};

std::size_t PyLayer::group_id() {
	EXPIRE_GUARD;
	return get_layer()->group_id;
};

double PyLayer::opacity() {
	EXPIRE_GUARD;
	return get_layer()->opacity;
};

bool PyLayer::invisible() {
	EXPIRE_GUARD;
	return get_layer()->invisible;
};
bool PyLayer::lighttable() {
	EXPIRE_GUARD;
	return get_layer()->lighttable;
};
bool PyLayer::stencil() {
	EXPIRE_GUARD;
	return get_layer()->stencil;
};
bool PyLayer::locked() {
	EXPIRE_GUARD;
	return get_layer()->locked;
};
bool PyLayer::position_locked() {
	EXPIRE_GUARD;
	return get_layer()->position_locked;
};
bool PyLayer::preserve_trans() {
	EXPIRE_GUARD;
	return get_layer()->preserve_trans;
};

std::string PyLayer::format_info() {
	auto s = std::format(R"(Layer:
Name: {}
Frame Offset: {}
Frames in Layer: {}
Repeat In / Repeat Out: {} / {}
Group: {}

Opacity: {}%
Blend Mode: {}

Layer Flags:
Invisible: {}
Lighttable: {}
Stencil Mode: {}
Locked: {}
Position Locked: {}
Preserve Transparency: {}
)",
name(), frame_offset(), frames_amount(),
repeat_t_to_str(repeat_in_type()), repeat_t_to_str(repeat_out_type()),
group_id(), opacity(), blendmode_t_to_str(blend_mode()),
invisible(), lighttable(), stencil(), locked(), position_locked(), preserve_trans()
);
    return s;
};

void PyLayer::cache_layer_contents() {
    EXPIRE_GUARD;
    return get_layer()->cache_layer_contents();
};
void PyLayer::clear_layer_contents() {
    EXPIRE_GUARD;
    return get_layer()->clear_layer_contents();
};

// TODO REFACTOR: output as numpy compatible image
cache_t& PyLayer::get_cache_at_frame(int long const& frame) {
    EXPIRE_GUARD;
    return get_layer()->get_cache_at_frame(frame);
};