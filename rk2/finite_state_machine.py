from enum import Enum
from string import ascii_letters, digits
from main import main


LEGAL_CHARS = ascii_letters + digits + '_'


class TestMethodState(Enum):
    USUAL = 0
    IN_STRING = 1
    AFTER_DOT = 2


def test_method(line: str) -> bool:
    state = TestMethodState.USUAL
    for char in line:
        if state == TestMethodState.USUAL:
            if char == '"':
                state = TestMethodState.IN_STRING
            elif char == '.':
                state = TestMethodState.AFTER_DOT
        elif state == TestMethodState.IN_STRING:
            if char == '"':
                state = TestMethodState.USUAL
        elif state == TestMethodState.AFTER_DOT:
            if char == '(':  # Found
                return True
            elif char not in LEGAL_CHARS:
                state = TestMethodState.USUAL
    return False


class TestStdState(Enum):
    USUAL = 0
    IN_STRING = 1
    IN_NAME = 2
    AFTER_S = 3
    AFTER_ST = 4
    AFTER_STD = 5
    AFTER_STDc = 6


def test_std(line: str) -> bool:
    state = TestStdState.USUAL
    for char in line:
        if state == TestStdState.USUAL:
            if char == '"':
                state = TestStdState.IN_STRING
            elif char == 's':
                state = TestStdState.AFTER_S
            elif char in LEGAL_CHARS:
                state = TestStdState.IN_NAME
        elif state == TestStdState.IN_STRING:
            if char == '"':
                state = TestStdState.USUAL
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
                return True
            elif char in LEGAL_CHARS:
                state = TestStdState.IN_NAME
            else:
                state = TestStdState.USUAL
    return False


if __name__ == '__main__':
    main(test_method, test_std)
