def main(test_method, test_std):
    for filepath in ('../rk1/sparse_matrix/sparse_matrix.hpp', 'test_input'):
        print(f'======== filepath: {filepath} ========')

        print('==== methods ====')
        with open(filepath, 'r') as file:
            for line in file:
                if test_method(line):
                    print(end=line)

        print('==== stds ====')
        with open(filepath, 'r') as file:
            for line in file:
                if test_std(line):
                    print(end=line)
