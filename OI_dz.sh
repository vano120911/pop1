#!/bin/bash

is_palindrome() {
    local word="$1"
    local reversed_word=$(echo "$word" | rev)


    if [[ "$word" == "$reversed_word" ]]; then
        return 0
    else
        return 1
    fi
}
if [ "$#" -eq 0 ]; then
    echo "Использование: $0 <слово1> [слово2] [слово3] ..."
    exit 1
fi

for word in "$@";
    do
   	 if is_palindrome "$word"; then
        	echo "$word — это палиндром."
    	else
        	echo "$word — это НЕ палиндром."
    fi
done
