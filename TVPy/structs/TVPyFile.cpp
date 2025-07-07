#include "TVPyFile.hpp"
#include "TvPyFileInfo.hpp"
#include "TVPyClip.hpp"

PyTVPaintFile::PyTVPaintFile(std::string path){
	namespace fs = std::filesystem;

#ifdef WIN32
	auto strpath_normalize = [](std::string const& str) -> std::string {
		std::string newpath{};
		for (auto it = str.begin(); it != str.end(); it += 1) {
			if (*it == '\\') {
				newpath += '/';
				if (*(it + 1) == '\\')
					it++;
				continue;
			}
			newpath += *it;
		}
		return newpath;
		};

	path = strpath_normalize(path);
#endif
	auto filepath = fs::path(path);
	if (!fs::exists(path)) {
		throw py::value_error("Given path does not exist.");
	}
	if (!fs::is_regular_file(filepath)) {
		throw py::value_error("Given path is not a file.");
	}
	if (filepath.extension() != ".tvpp") {
		throw py::value_error("Given path needs to point to a '*.tvpp' file.");
	}

	mmap = mio::ummap_source{ path };
	tvp_file = std::make_shared<File>(mmap);
};

PyTVPaintFile::~PyTVPaintFile() {
	this->deinit();
}

void PyTVPaintFile::deinit() {
	mmap.unmap();
	tvp_file.release();
}

PyFileInfo PyTVPaintFile::info() {
	return PyFileInfo(shared_from_this());
};