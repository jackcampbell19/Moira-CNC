
class Verification:

    good_prefixes = ['c', 'w']
    upper_bound = 8000

    @staticmethod
    def verify(path):
        file = open(path)
        position = [0, 0, 0]
        for instruction in file.readlines():
            if instruction[0] not in Verification.good_prefixes:
                print(f"'{instruction}' contains bad prefix.")
                return False
            if instruction[0] == 'c':
                split_ins = instruction[2:-1].split(',')
                if len(split_ins) != 3:
                    print(f"'{instruction}' contains bad arguments.")
                    return False
                for x in range(3):
                    if split_ins[x] in ['-', '+']:
                        position[x] += int(split_ins[x])
                    else:
                        position[x] = int(split_ins[x])
                    if sum([1 if p < 0 or p > Verification.upper_bound else 0 for p in position]) > 0:
                        print(f"'{instruction}' caused out of bounds error.")
                        return False
            if instruction[0] == 'w':
                if int(instruction[2:]) < 0:
                    print(f"'{instruction}' contains bad arguments.")
                    return False
        return True
