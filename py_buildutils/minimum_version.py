import sys

if __name__ == "__main__":
    major = sys.version_info.major
    minor = sys.version_info.minor
    micro = sys.version_info.micro
    current_version = [major, minor, micro]

    if len(sys.argv) != 2:
        print('Please provide a valid version, e.g. "3.8" or "3.8.1"')
        sys.exit(1)

    version_minimum = sys.argv[1]
    version_elements = [0, 0, 0]
    for i, v in enumerate(version_minimum.split(".")):
        try:
            version_elements[i] = int(v)
        except BaseException:
            print(f"Ill formatted version argument: {sys.argv[1]}")
            sys.exit(1)

    for goal, this in zip(version_elements, current_version):
        if this < goal:
            print(
                f"Expected version: '{'.'.join(str(x) for x in version_elements)}'"
                f" is newer than: '{'.'.join(str(x) for x in current_version)}'."
            )
            sys.exit(2)
    print(
        f"Expected version: '{'.'.join(str(x) for x in version_elements)}'"
        f" is compatible with: '{'.'.join(str(x) for x in current_version)}'."
    )
    sys.exit(0)
