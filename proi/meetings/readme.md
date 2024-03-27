# WHAT IS THIS
This is an app to manage your meetings. You can add a meeting, change participants of a meeting, set its time and type.
# HOW TO USE
First you need to build this project using cmake.

Then you should enter the build folder and run a command:   

`
./meetings
`

The usage is:

`
./meetings [year] [month] [day] [hour] [minute] [participants...]
`

participants consist of name and surname, so we give two strings.

example:

`
./meetings 2024 3 12 10 0 Adam Lamar
`

the program shows in console currently added meeting. 