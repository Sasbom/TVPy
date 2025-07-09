#include "TVPyFileInfo.hpp"

PyFileInfo::PyFileInfo(std::shared_ptr<PyTVPaintFile> tvp_file): parent(tvp_file) {};

#define EXPIRE_GUARD                                                        \
if (parent.expired()) {                                                     \
    throw py::value_error("Parent TVPaint File object not valid anymore."); \
}

#define INFO parent.lock()->tvp_file->file_info

std::size_t PyFileInfo::width() {
	EXPIRE_GUARD;
	return INFO.width;
};
std::size_t PyFileInfo::height() {
	EXPIRE_GUARD;
	return INFO.height;
};
double PyFileInfo::fps() {
	EXPIRE_GUARD;
	return INFO.fps;
};
double PyFileInfo::pix_aspect_ratio() {
	EXPIRE_GUARD;
	return INFO.pix_aspect_ratio;
};
bool PyFileInfo::field_order() {
	EXPIRE_GUARD;
	return INFO.field_order;
};
std::size_t PyFileInfo::start_frame() {
	EXPIRE_GUARD;
	return INFO.start_frame;
};
std::string PyFileInfo::uid() {
	EXPIRE_GUARD;
	return INFO.uid;
};
std::size_t PyFileInfo::shots() {
	EXPIRE_GUARD;
	return INFO.shots;
};
std::size_t PyFileInfo::drawings() {
	EXPIRE_GUARD;
	return INFO.drawings;
};
std::string PyFileInfo::info() {
	EXPIRE_GUARD;
	return INFO.info;
};
std::vector<std::string> PyFileInfo::notes() {
	EXPIRE_GUARD;
	return INFO.notes;
};
std::string PyFileInfo::author() {
	EXPIRE_GUARD;
	return INFO.author;
};
std::string PyFileInfo::build() {
	EXPIRE_GUARD;
	return INFO.build;
}; // date of build
std::string PyFileInfo::host() {
	EXPIRE_GUARD;
	return INFO.host;
}; // software name
std::string PyFileInfo::os() {
	EXPIRE_GUARD;
	return INFO.os;
};
std::string PyFileInfo::date_creation() {
	EXPIRE_GUARD;
	return INFO.date_creation;
};
std::string PyFileInfo::date_lastchanged() {
	EXPIRE_GUARD;
	return INFO.date_lastchanged;
};

std::size_t PyFileInfo::camera_width() {
	EXPIRE_GUARD;
	return INFO.camera_width;
};
std::size_t PyFileInfo::camera_height() {
	EXPIRE_GUARD;
	return INFO.camera_height;
};
bool PyFileInfo::camera_field_order() {
	EXPIRE_GUARD;
	return INFO.camera_field_order;
};
double PyFileInfo::camera_fps() {
	EXPIRE_GUARD;
	return INFO.camera_fps;
};
double PyFileInfo::camera_pix_aspect_ratio() {
	EXPIRE_GUARD;
	return INFO.camera_pix_aspect_ratio;
};
bool PyFileInfo::camera_aa() {
	EXPIRE_GUARD;
	return INFO.camera_aa;
};
bool PyFileInfo::camera_show43_border() {
	EXPIRE_GUARD;
	return INFO.camera_show43_border;
};
bool PyFileInfo::camera_safearea() {
	EXPIRE_GUARD;
	return INFO.camera_safearea;
};
double PyFileInfo::camera_safearea_borderout() {
	EXPIRE_GUARD;
	return INFO.camera_safearea_borderout;
};
double PyFileInfo::camera_safearea_borderin() {
	EXPIRE_GUARD;
	return INFO.camera_safearea_borderin;
};

bool PyFileInfo::is_locked() {
	EXPIRE_GUARD;
	return INFO.is_locked;
};
bool PyFileInfo::is_protected() {
	EXPIRE_GUARD;
	return INFO.is_protected;
};
std::string PyFileInfo::password() {
	EXPIRE_GUARD;
	return INFO.password;
};

bool PyFileInfo::save_audio_deps() {
	EXPIRE_GUARD;
	return INFO.save_audio_deps;
};
bool PyFileInfo::save_video_deps() {
	EXPIRE_GUARD;
	return INFO.save_video_deps;
};
std::vector<std::string> PyFileInfo::save_history() {
	EXPIRE_GUARD;
	return INFO.save_history;
};
double PyFileInfo::user_workduration() {
	EXPIRE_GUARD;
	return INFO.user_workduration;
};
std::size_t PyFileInfo::user_workchange() {
	EXPIRE_GUARD;
	return INFO.user_workchange;
};
std::string PyFileInfo::format_info() {
	auto s = std::format(R"(File:
WxH: {} x {}
FPS: {}
Pixel Aspect Ratio: {}
Field Order: {}
Start Frame : {}
uuid: {}
Shots: {}
Drawings: {}
Info: {}
Notes: {}
Author: {}
Build: {} 
Host: {}
OS: {}
Created / Last Changed: {} / {}

Camera:
WxH: {} x {}
Field Order: {}
FPS: {}
Pixel Aspect Ratio: {}
Anti Aliasing: {}
Safe Area: {}
Border in/out: {} / {}

Meta:
Locked: {}
Protected: {}
Password: {}
Save Audio Dependencies: {}
Save Video dependencies: {}
History:
{}
Work Duration: {}
Work Change: {}
)",
width(), height(), fps(),
pix_aspect_ratio(),
field_order(),
start_frame(),
uid(),
shots(), drawings(),
info(), notes(), author(), build(), host(), os(),
date_creation(), date_lastchanged(),
camera_width(), camera_height(), camera_field_order(), camera_fps(),
camera_pix_aspect_ratio(), camera_aa(), camera_safearea(),
camera_safearea_borderin(), camera_safearea_borderout(),
is_locked(), is_protected(), password(), save_audio_deps(),
save_video_deps(), save_history(), user_workduration(), user_workchange()
);
	return s;
}

void register_tvpfileinfo(py::module_& m) {
	py::class_<PyFileInfo>(m, "TvpFileInfo")
		.def_property("width", &PyFileInfo::width, EMPTY_FUNC)
		.def_property("height", &PyFileInfo::height, EMPTY_FUNC)
		.def_property("fps", &PyFileInfo::fps, EMPTY_FUNC)
		.def_property("pix_aspect_ratio", &PyFileInfo::pix_aspect_ratio, EMPTY_FUNC)
		.def_property("field_order", &PyFileInfo::field_order, EMPTY_FUNC)
		.def_property("start_frame", &PyFileInfo::start_frame, EMPTY_FUNC)
		.def_property("uid", &PyFileInfo::uid, EMPTY_FUNC)
		.def_property("shots", &PyFileInfo::shots, EMPTY_FUNC)
		.def_property("drawings", &PyFileInfo::drawings, EMPTY_FUNC)
		.def_property("info", &PyFileInfo::info, EMPTY_FUNC)
		.def_property("notes", &PyFileInfo::notes, EMPTY_FUNC)
		.def_property("author", &PyFileInfo::author, EMPTY_FUNC)
		.def_property("build", &PyFileInfo::build, EMPTY_FUNC)
		.def_property("host", &PyFileInfo::host, EMPTY_FUNC)
		.def_property("os", &PyFileInfo::os, EMPTY_FUNC)
		.def_property("date_creation", &PyFileInfo::date_creation, EMPTY_FUNC)
		.def_property("date_lastchanged", &PyFileInfo::date_lastchanged, EMPTY_FUNC)
		.def_property("camera_width", &PyFileInfo::camera_width, EMPTY_FUNC)
		.def_property("camera_height", &PyFileInfo::camera_height, EMPTY_FUNC)
		.def_property("camera_field_order", &PyFileInfo::camera_field_order, EMPTY_FUNC)
		.def_property("camera_fps", &PyFileInfo::camera_fps, EMPTY_FUNC)
		.def_property("camera_pix_aspect_ratio", &PyFileInfo::camera_pix_aspect_ratio, EMPTY_FUNC)
		.def_property("camera_aa", &PyFileInfo::camera_aa, EMPTY_FUNC)
		.def_property("camera_show43_border", &PyFileInfo::camera_show43_border, EMPTY_FUNC)
		.def_property("camera_safearea", &PyFileInfo::camera_safearea, EMPTY_FUNC)
		.def_property("camera_safearea_borderout", &PyFileInfo::camera_safearea_borderout, EMPTY_FUNC)
		.def_property("camera_safearea_borderin", &PyFileInfo::camera_safearea_borderin, EMPTY_FUNC)
		.def_property("is_locked", &PyFileInfo::is_locked, EMPTY_FUNC)
		.def_property("is_protected", &PyFileInfo::is_protected, EMPTY_FUNC)
		.def_property("password", &PyFileInfo::password, EMPTY_FUNC)
		.def_property("save_audio_deps", &PyFileInfo::save_audio_deps, EMPTY_FUNC)
		.def_property("save_video_deps", &PyFileInfo::save_video_deps, EMPTY_FUNC)
		.def_property("save_history", &PyFileInfo::save_history, EMPTY_FUNC)
		.def_property("user_workduration", &PyFileInfo::user_workduration, EMPTY_FUNC)
		.def_property("user_workchange", &PyFileInfo::user_workchange, EMPTY_FUNC)
		.def("__str__",&PyFileInfo::format_info)
		.def("__repr__", [](PyFileInfo& f) {
		return std::format("<TvpFileInfo {}>", f.uid()); }
		);;
};