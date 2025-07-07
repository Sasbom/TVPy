import sys
from pathlib import Path

if __name__ == "__main__":
    print(str(Path(sys.base_prefix)))
    sys.exit(0)
