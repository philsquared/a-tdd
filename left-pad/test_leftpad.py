from hypothesis import given, assume
from hypothesis.strategies import text, integers


def leftpad(input_string: str, min_len: int) -> str:
    pad_len = max(0, min_len - len(input_string))
    return " " * pad_len + input_string

def test_string_length_matches_min_length():
    assert leftpad("", 0) == ""
    assert leftpad("abc", 3) == "abc" # confidence test

def test_string_length_greater_than_min_length():
    assert leftpad("abc", 0) == "abc"
    assert leftpad("abc", -1) == "abc" # confidence test

def test_string_length_less_than_min_length():
    assert leftpad("", 1) == " "
    assert leftpad("abc", 5) == "  abc"


@given(text(max_size=256), integers(min_value=-10, max_value=256))
def test_leftpad_properties(input_string: str, min_len: int):
    output_string = leftpad(input_string, min_len)
    assert len(output_string) >= len(input_string)
    assert len(output_string) >= min_len
    assert input_string in output_string
    assert len(output_string) == max(len(output_string), min_len)
    assert output_string in input_string.rjust(min_len)
    assert output_string.endswith(input_string)

@given(text(max_size=256))
def test_string_length_matches_min_length_property(input_string: str):
    assert leftpad(input_string, len(input_string)) == input_string

@given(text(max_size=256), integers(min_value=-10, max_value=256))
def test_string_length_greater_than_min_length_property(input_string: str, min_len: int):
    output_string = leftpad(input_string, min_len)
    if len(input_string) >= min_len:
        assert output_string == input_string
    else:
        assert output_string[0] == " "

