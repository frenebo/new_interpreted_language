# new_interpreted_language

instructions:

go into lang directory, create "build" directory, go into build, run "cmake .."
in shell, then run "cmake --build ."

Executable should now be in lang/build directory

todo: 'or' should only evaluate first statement

Example program in this language:
`
fizz = "Fizz";
buzz = "Buzz";

for (i = 0; i < 100; i += 1)
{
    if (i % 3 == 0 && i % 5 == 0)
    {
        print fizz+buzz;
    }
    else if (i % 3 == 0)
    {
        print fizz;
    }
    else if (i % 5 == 0)
    {
        print buzz;
    }
    else
    {
        print i;
    }
}
`
