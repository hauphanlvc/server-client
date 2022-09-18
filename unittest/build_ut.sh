root_proj_dir=$(git rev-parse --show-toplevel)

# build
build_dir="$root_proj_dir/build"
cd $build_dir || (echo "cd build error" && exit)
cmake ../
make