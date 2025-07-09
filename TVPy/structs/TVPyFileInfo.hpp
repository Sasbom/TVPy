#pragma once
#include "TVPyFile.hpp"

struct PyFileInfo {

	PyFileInfo( std::shared_ptr<PyTVPaintFile> tvp_file );

	std::weak_ptr<PyTVPaintFile> parent;

	std::size_t width();
	std::size_t height();
	double fps();
	double pix_aspect_ratio();
	bool field_order();
	std::size_t start_frame();
	std::string uid();
	std::size_t shots();
	std::size_t drawings();
	std::string info();
	std::vector<std::string> notes();
	std::string author();
	std::string build(); // date of build
	std::string host(); // software name
	std::string os();
	std::string date_creation();
	std::string date_lastchanged();

	std::size_t camera_width();
	std::size_t camera_height();
	bool camera_field_order();
	double camera_fps();
	double camera_pix_aspect_ratio();
	bool camera_aa();
	bool camera_show43_border();
	bool camera_safearea();
	double camera_safearea_borderout();
	double camera_safearea_borderin();

	bool is_locked();
	bool is_protected();
	std::string password();

	bool save_audio_deps();
	bool save_video_deps();
	std::vector<std::string> save_history();
	double user_workduration();
	std::size_t user_workchange();

	std::string format_info();
};

void register_tvpfileinfo(py::module_& m);