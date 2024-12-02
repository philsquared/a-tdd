```
Member class:
    Username
    Email address
    Status

    enroll()
    complete_flight( flight )
```

Can write individual test like this:

```
def test_member():
    member = Member("username", "user@test.com")
    assert member.status == Member.Status.Future
```

... or use fixture:

```
@pytest.fixture
def future_member() -> Member:
    return Member("username", "user@test.com")


def test_future_member(future_member):
    assert future_member.status == Member.Status.Future
```

Can now reuse fixture for testing:

* Red members (0-25k miles flown)
* Green (25k-50k)
* Blue (50-75k)
* Gold (75k+)