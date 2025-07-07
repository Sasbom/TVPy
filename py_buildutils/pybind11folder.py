import sys
from pathlib import Path

import pybind11

if __name__ == "__main__":
    print(str(Path(pybind11.get_include())))
    sys.exit(0)
