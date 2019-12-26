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


if [ -e .git ] && [ -e .gitignore ]; then
    PROJECT_DIR=$(git rev-parse --show-toplevel)
    cmd="cd ${PROJECT_DIR} && git ls-files > $TMPDIR/tmp.txt; \
         rsync ${PWD%sh} --files-from=$TMPDIR/tmp.txt \"$r_user@$r_host:${r_path}\"  "
else
    PROJECT_DIR=${PWD%/sh}
    cmd="cd ${PROJECT_DIR} && rsync -avzu . \"$r_user@$r_host:${r_path}\""
fi
echo $cmd
eval $cmd
