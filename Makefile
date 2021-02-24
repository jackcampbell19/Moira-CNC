test:
	python3 tst/preparation/mi/mi_test.py

clean:
	rm tst/runtime/*
	rm main

build:
	gcc -o main src/machine/*/*.c src/machine/*.c

run:
	./main tst/expected/test_1_mi_file_expected.mi