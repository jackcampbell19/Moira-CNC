class Test:

    name = ""

    def run_test(self, test, name):
        b = test()
        if not b:
            print(f"[{self.name}]: {name} failed.")
        return 1 if b else 0

    def run_tests(self):
        print(f"[{self.name}] Running...")
        eval(f"self.before")()
        tests = [self.run_test(eval(f"self.{name}"), name) for name in dir(self) if name.startswith('test')]
        print(f"[{self.name}] Completed: {sum(tests)}/{len(tests)} tests passed.")

    def compare_files(self, path_a, path_b):
        a_file = open(path_a, 'r')
        b_file = open(path_b, 'r')
        b = a_file.readlines() == b_file.readlines()
        a_file.close()
        b_file.close()
        return b
