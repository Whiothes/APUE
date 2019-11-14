#!/usr/bin/env bash
set -e

read -p "remote host [default 39.105.199.190]: " r_host
read -p "remote user [default root]: " r_user
read -p "remote path [default ~/APUE/]: " r_path

if [ -z $r_user ]; then
    r_user="root"
fi

if [ -z $r_path ]; then
    r_path="~/APUE/"
fi

if [ -z $r_host ]; then
    r_host="39.105.199.190"
fi

PROJECT_DIR=${PWD%/sh}

cd ${PROJECT_DIR}
if [ -e .git ] && [ -e .gitignore ]; then
    cmd="rsync -avzu . \"$r_user@$r_host:${r_path}\" --exclude-from=.gitignore --exclude=.git --exclude=Doxyfile --exclude=API.org --exclude=README.org --exclude=.*"
else
    cmd="rsync -avzu . \"$r_user@$r_host:${r_path}\""
fi
echo $cmd
eval $cmd
