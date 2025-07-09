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

PyTVPaintFile::PyTVPaintFile(py::object const& path) {
	// Import pathlib and get the Path class
	py::module pathlib = py::module::import("pathlib");
	py::object Path = pathlib.attr("Path");

	if (!py::isinstance(path, Path)) {
		throw std::invalid_argument("Expected a pathlib.Path object");
	}

	// Call str() on the object
	auto strpath = py::str(path).operator std::string();

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

	strpath = strpath_normalize(strpath);
#endif
	auto filepath = fs::path(strpath);
	if (!fs::exists(strpath)) {
		throw py::value_error("Given path does not exist.");
	}
	if (!fs::is_regular_file(filepath)) {
		throw py::value_error("Given path is not a file.");
	}
	if (filepath.extension() != ".tvpp") {
		throw py::value_error("Given path needs to point to a '*.tvpp' file.");
	}

	mmap = mio::ummap_source{ strpath };
	tvp_file = std::make_shared<File>(mmap);
}

PyTVPaintFile::~PyTVPaintFile() {
	this->deinit();
}

void PyTVPaintFile::deinit() {
	for (auto& c : tvp_file->clips) {
		for (auto& l : c->layers) {
			l->clear_layer_contents();
		}
	}
	mmap.unmap();
}

PyFileInfo PyTVPaintFile::info() {
	return PyFileInfo(shared_from_this());
};

void register_tvpyfile(py::module_& m) {
	py::class_<PyTVPaintFile, std::shared_ptr<PyTVPaintFile>>(m, "TvpFile")
		.def(py::init<py::str>(),"path"_a)
		.def(py::init<py::object>(), "path"_a)
		.def_property("info", &PyTVPaintFile::info, EMPTY_FUNC);
};