from enum import Enum
from string import ascii_letters, digits
from main import main


LEGAL_CHARS = ascii_letters + digits + '_'


class TestMethodState(Enum):
    USUAL = 0
    IN_STRING = 1
    IN_STRING_AFTER_BACKSLASH = 2
    AFTER_SLASH = 3
    IN_COMMENT = 4
    IN_COMMENT_AFTER_STAR = 5
    AFTER_DOT = 6
    FOUND = 7
    NOT_FOUND = 8


def test_method(line: str) -> bool:
    state = TestMethodState.USUAL
    for char in line:
        if state == TestMethodState.USUAL:
            if char == '"':
                state = TestMethodState.IN_STRING
            elif char == '/':
                state = TestMethodState.AFTER_SLASH
            elif char == '.':
                state = TestMethodState.AFTER_DOT
        elif state == TestMethodState.IN_STRING:
            if char == '\\':
                state = TestMethodState.IN_STRING_AFTER_BACKSLASH
            elif char == '"':
                state = TestMethodState.USUAL
        elif state == TestMethodState.IN_STRING_AFTER_BACKSLASH:
            state = TestMethodState.IN_STRING
        elif state == TestMethodState.AFTER_SLASH:
            if char == '/':  # Not found
                state = TestMethodState.NOT_FOUND
                return False
            elif char == '*':
                state = TestMethodState.IN_COMMENT
            elif char == '"':
                state = TestMethodState.IN_STRING
            else:
                state = TestMethodState.USUAL
        elif state == TestMethodState.IN_COMMENT:
            if char == '*':
                state = TestMethodState.IN_COMMENT_AFTER_STAR
        elif state == TestMethodState.IN_COMMENT_AFTER_STAR:
            if char == '/':
                state = TestMethodState.USUAL
            elif char != '*':
                state = TestMethodState.IN_COMMENT
        elif state == TestMethodState.AFTER_DOT:
            if char == '(':  # Found
                state = TestMethodState.FOUND
                return True
            elif char not in LEGAL_CHARS:
                state = TestMethodState.USUAL
    state = TestMethodState.NOT_FOUND
    return False


class TestStdState(Enum):
    USUAL = 0
    IN_STRING = 1
    IN_STRING_AFTER_BACKSLASH = 2
    AFTER_SLASH = 3
    IN_COMMENT = 4
    IN_COMMENT_AFTER_STAR = 5
    IN_NAME = 6
    AFTER_S = 7
    AFTER_ST = 8
    AFTER_STD = 9
    AFTER_STDc = 10
    FOUND = 11
    NOT_FOUND = 12


def test_std(line: str) -> bool:
    state = TestStdState.USUAL
    for char in line:
        if state == TestStdState.USUAL:
            if char == '"':
                state = TestStdState.IN_STRING
            elif char == '/':
                state = TestStdState.AFTER_SLASH
            elif char == 's':
                state = TestStdState.AFTER_S
            elif char in LEGAL_CHARS:
                state = TestStdState.IN_NAME
        elif state == TestStdState.IN_STRING:
            if char == '\\':
                state = TestStdState.IN_STRING_AFTER_BACKSLASH
            elif char == '"':
                state = TestStdState.USUAL
        elif state == TestStdState.IN_STRING_AFTER_BACKSLASH:
            state = TestStdState.IN_STRING
        elif state == TestStdState.AFTER_SLASH:
            if char == '/':  # Not found
                state = TestStdState.NOT_FOUND
                return False
            elif char == '*':
                state = TestStdState.IN_COMMENT
            elif char == '"':
                state = TestStdState.IN_STRING
            elif char == 's':
                state = TestStdState.AFTER_S
            elif char in LEGAL_CHARS:
                state = TestStdState.IN_NAME
            else:
                state = TestStdState.USUAL
        elif state == TestStdState.IN_COMMENT:
            if char == '*':
                state = TestStdState.IN_COMMENT_AFTER_STAR
        elif state == TestStdState.IN_COMMENT_AFTER_STAR:
            if char == '/':
                state = TestStdState.USUAL
            elif char != '*':
                state = TestStdState.IN_COMMENT
        elif state == TestStdState.IN_NAME:
            if char not in LEGAL_CHARS:
                state = TestStdState.USUAL
        elif state == TestStdState.AFTER_S:
            if char == 't':
                state = TestStdState.AFTER_ST
            elif char in LEGAL_CHARS:
                state = TestStdState.IN_NAME
            else:
                state = TestStdState.USUAL
        elif state == TestStdState.AFTER_ST:
            if char == 'd':
                state = TestStdState.AFTER_STD
            elif char in LEGAL_CHARS:
                state = TestStdState.IN_NAME
            else:
                state = TestStdState.USUAL
        elif state == TestStdState.AFTER_STD:
            if char == ':':
                state = TestStdState.AFTER_STDc
            elif char in LEGAL_CHARS:
                state = TestStdState.IN_NAME
            else:
                state = TestStdState.USUAL
        elif state == TestStdState.AFTER_STDc:
            if char == ':':  # Found
                state = TestStdState.FOUND
                return True
            elif char in LEGAL_CHARS:
                state = TestStdState.IN_NAME
            else:
                state = TestStdState.USUAL
    state = TestStdState.NOT_FOUND
    return False


if __name__ == '__main__':
    main(test_method, test_std)
