# Use clang++ when on Solus Linux, otherwise gcc
if command -v eopkg >/dev/null 2>&1; then
    clang++ $@
else
    gcc $@
fi
