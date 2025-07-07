#pragma once
#include "TVPy.hpp"

//declare PyFileInfo ahead of time.
struct PyFileInfo;

// Provide an interface that keeps track of mmap source so we can add a context manager.
struct PyTVPaintFile : public std::enable_shared_from_this<PyTVPaintFile> {
	PyTVPaintFile(std::string path);
	~PyTVPaintFile();
	
	mio::ummap_source mmap;
	std::unique_ptr<File> tvp_file;

	PyFileInfo info();

	void deinit();
};

