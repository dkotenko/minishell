
TAR_NAME="${PWD##*/}_$(date)"
TAR_NAME=${TAR_NAME//' '/_}
IS_DELETE=${1:-${TAR_NAME}}

find . -type f -name '*.c' | tar -cvf ${TAR_NAME}.tar -T -
if ($IS_DELETE = 'delete'); then
	find . -type f -print0 -name '*.c' -exec rm -rf {} \;
fi
