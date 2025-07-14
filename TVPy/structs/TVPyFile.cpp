#include "TVPyFile.hpp"
#include "TvPyFileInfo.hpp"
#include "TVPyClip.hpp"

PyTVPaintFile::PyTVPaintFile(py::object const& path) {
	// Import pathlib and get the Path class
	py::module pathlib = py::module::import("pathlib");
	py::object Path = pathlib.attr("Path");

	if (!py::isinstance(path, Path) && !py::isinstance<py::str>(path)) {
		throw std::invalid_argument("Expected a pathlib.Path or str.");
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
	source = strpath;
	tvp_file = std::make_shared<File>(mmap);
}

void PyTVPaintFile::getfileclips() {
	if (init_clips)
		return;

	auto clips_amt = tvp_file->clips.size();
	for (std::size_t i{}; i < clips_amt; i++) {
		clips.push_back(std::make_shared<PyClip>(shared_from_this(), i));
	}
	init_clips = true;
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
		.def(py::init<py::object>(), "path"_a)
		.def_property("info", &PyTVPaintFile::info, EMPTY_FUNC)
		.def_property("clips", py::cpp_function([](PyTVPaintFile& f) {
		f.getfileclips();
		return f.clips;
			}, py::return_value_policy::reference_internal), EMPTY_FUNC)
		.def("__repr__", [](PyTVPaintFile& f) {
		return std::format("<TvpFile sourced from: {}>", f.source); }
		)
		.def("__getitem__", [](PyTVPaintFile& f, std::size_t index) {
		f.getfileclips();
		if (index >= 0 && index < f.clips.size())
			return f.clips[index];
		else
			throw py::index_error("Clip index out of range"); }
		)
		.def("close", [](PyTVPaintFile& f) {
			f.deinit();
		})
		.def("__enter__", [](PyTVPaintFile& f) {
			return f.shared_from_this();
		})
		.def("__exit__", [](PyTVPaintFile& f, py::args args) {
			f.deinit();
			return py::none();
		});
};