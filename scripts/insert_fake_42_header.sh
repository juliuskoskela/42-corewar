#!/bin/bash

# A script that inserts the below fake 42 header into all C source and header files (*.c, *.h) in the current directory.
# Requires norminette to be installed.

# If you have not installed it, you can install it in a virtual environment with pip (requires python3):

# python3 -m venv venv
# source venv/bin/activate
# pip install norminette

header="\
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a header                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by marvin            #+#    #+#             */
/*   Updated: 1970/01/01 00:00:00 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */"

for file in $(find . -name "*.c" -or -name "*.h"); do
	norminette_missing_header=$(norminette $file | grep "Error: INVALID_HEADER")
	if [ -n "$norminette_missing_header" ]; then
		content=$(cat $file)
		echo "$header" > $file
		echo "" >> $file
		echo "$content" >> $file
		echo "Added header to $file"
	fi
done
