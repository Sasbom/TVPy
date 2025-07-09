#pragma once
#include "../TVPy.hpp"

//declare things that need to be children of File object ahead of time.
struct PyFileInfo;
struct PyClip;

// Provide an interface that keeps track of mmap source so we can add a context manager.
struct PyTVPaintFile : public std::enable_shared_from_this<PyTVPaintFile> {
	PyTVPaintFile(std::string path);
	PyTVPaintFile(py::object const& path);
	~PyTVPaintFile();
	
	std::string source{};
	mio::ummap_source mmap;
	std::shared_ptr<File> tvp_file;

	std::vector<std::shared_ptr<PyClip>> clips{};

	PyFileInfo info();

	void deinit();
};

void register_tvpyfile(py::module_& m);