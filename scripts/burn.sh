#!/bin/zsh
for file in $(pwd)/*.xml; do
	echo ${file}
	/Users/lucmarti/Documents/WIP/-RTAGAINSTTHESTRIKE/RT ${file} &
done;
