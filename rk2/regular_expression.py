import re
from main import main


def clean_line(line: str) -> str:
    def replacement(m):
        return '' if m.group(1) else m.group(0)
    pattern = re.compile(r'(/\*.*?\*/)')
    without_multiline_comments = pattern.sub(replacement, line)
    pattern = re.compile(r'([^"\\]*(\\.|"([^"\\]*\\.)*[^"\\]*"))*')
    without_strings_and_multiline_comments = pattern.sub(replacement, without_multiline_comments)
    pattern = re.compile(r'//.*$')
    return pattern.sub('', without_strings_and_multiline_comments)


def test_method(line: str) -> bool:
    pattern = re.compile(r'\.[\w_]+\(')
    return bool(pattern.search(clean_line(line)))


def test_std(line: str) -> bool:
    pattern = re.compile(r'\bstd::')
    return bool(pattern.search(clean_line(line)))


if __name__ == '__main__':
    main(test_method, test_std)
