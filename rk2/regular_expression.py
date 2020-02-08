import re
from main import main


def test_method(line: str) -> bool:
    pattern = re.compile(r'(\".*\")*[^\"]*\.\w+\(')
    return bool(pattern.search(line))


def test_std(line: str) -> bool:
    pattern = re.compile(r'((\".*\")*.*\Wstd::)|(^std::)')
    return bool(pattern.search(line))


if __name__ == '__main__':
    main(test_method, test_std)
