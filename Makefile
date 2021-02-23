test:
	python3 tst/preparation/ct/ct_test.py

clean:
	rm tst/runtime/*
	rm main

build:
	gcc -o main src/machine/*/*.c src/machine/*.c