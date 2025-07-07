import importlib.util as imutil
import sys

if __name__ == "__main__":
    fail = False

    for module in sys.argv[1:]:
        if imutil.find_spec(module) is None:
            print(f"{module} not found...")
            fail = True

    sys.exit(fail)
