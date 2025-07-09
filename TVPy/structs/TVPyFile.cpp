#include "TVPyFile.hpp"
#include "TvPyFileInfo.hpp"
#include "TVPyClip.hpp"

static inline void init_file(PyTVPaintFile& file, std::string& path) {
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

	file.mmap = mio::ummap_source{ path };
	file.source = path;
	file.tvp_file = std::make_shared<File>(file.mmap);
	auto clips_amt = file.tvp_file->clips.size();
	for (std::size_t i{}; i < clips_amt; i++) {
		file.clips.push_back(std::make_shared<PyClip>(file.shared_from_this(), i));
	}
}

PyTVPaintFile::PyTVPaintFile(std::string path){
	init_file(*this, path);
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

	init_file(*this, strpath);
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
		.def(py::init<py::str>(), "path"_a)
		.def(py::init<py::object>(), "path"_a)
		.def_property("info", &PyTVPaintFile::info, EMPTY_FUNC)
		.def("__repr__", [](PyTVPaintFile& f) {
		return std::format("<TvpFile sourced from: {}>", f.source); }
		);
};