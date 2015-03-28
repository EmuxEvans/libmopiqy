# Base version number
VERSION = 0.0.0

# Need to call git with manually specified paths to repository
BASE_GIT_COMMAND = git --work-tree $$PWD

# Trying to get version from git tag / revision
GIT_VERSION = $$system($$BASE_GIT_COMMAND describe --always --tags)

# Check if we have a valid version
VERSION_FOUND = $$find(GIT_VERSION,\d+\.\d+\.\d+)
isEmpty(VERSION_FOUND) {
    GIT_COMMIT_COUNT = $$system($$BASE_GIT_COMMAND rev-list HEAD --count)
    GIT_VERSION = $$VERSION-$$GIT_COMMIT_COUNT
}

# Turns describe output like 0.1.5-42-g652c397 into "0.1.5.42-652c397"
GIT_VERSION ~= s/-/"."
GIT_VERSION ~= s/\.g/"-"

# Now we are ready to pass parsed version to Qt
VERSION = $$GIT_VERSION
win32 { # On windows version can only be numerical so remove commit hash
    VERSION ~= s/-[a-f0-9]{6,}//
}

# Adding C preprocessor #DEFINE so we can use it in C++ code
# also here we want full version on every system so using GIT_VERSION
DEFINES += GIT_VERSION=\\\"$$GIT_VERSION\\\"
