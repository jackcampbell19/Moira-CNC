generate:
	python3 tst/file-gen.py

simulate:
	python3 tst/file-sim.py

test:
	python3 tst/tests/*.py

clean:
	rm tst/generated-files/*
