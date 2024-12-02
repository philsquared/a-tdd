Airport codes should always be exactly three characters.
Raise an exception on construction of Flight, if not.

Syntax for testing that an exception is raised:

```
with pytest.raises(Exception):
    # statement that should throw
```

Stretch goal: include the airport code in the message and test for it.