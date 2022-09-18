#!/bin/bash

files=$(git show -m --name-only --format=format:)
root_project=$(git rev-parse --show-toplevel)
cpplint_container_name="cpplint_container_name"
shellcheck_container_name="shellcheck_container_name"
shellcheck_image="koalaman/shellcheck-alpine"
cpplint_image="sharaku/cpplint" 
list_files=""
for file in $files; do
    list_files+=" -v $root_project/$file:/home/$file "
done
echo $list_files
echo "docker run -d -it "$list_files --name=$cpplint_container_name $cpplint_image
docker run -d -it $list_files --name=$cpplint_container_name $cpplint_image

# $docker_run$list_files$cpplint_container_name$cpplint_image
echo "docker run -d -it "$list_files --name=$shellcheck_container_name$ shellcheck_image
docker run -d -it $list_files --name=$shellcheck_container_name $shellcheck_image

# $docker_run$list_files$shellcheck_container_name$shellcheck_image
for file in $files; do
    if [[ ${file##*.} == "cpp" ]]; then
        docker exec cpplint_container_name cpplint "/home/${file}"
    elif [[ ${file##*.} == "h" ]]; then
        docker exec cpplint_container_name cpplint "/home/${file}"
    elif [[ ${file##*.} == "sh" ]]; then
        docker exec shellcheck_container_name shellcheck "/home/${file}"
    else
        echo "$file passed!"
    fi
done


# Clean up 
docker rm -f $cpplint_container_name $shellcheck_container_name
