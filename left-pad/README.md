# Left Pad

We've all heard of the notorious left-pad javascript library that was
pulled from NPM a few years ago.
We scoffed at how having a dependency on such a trivial library disrupted
so much of the internet.
But how trivial was it really? Let's implement it in C++!

The requirements are:

* Write a function that takes a string and a number and returns a string
* The number represents the "padded" size.
* The returned string should be the input string,
  padded with spaces on the left if shorter than the size argument.
* The pad character should be optionally specifiable via an extra, defaulted argument

