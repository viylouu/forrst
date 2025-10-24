# furry engine
furry engine is a game engine designed to be a game engine  
it is built using c99  

## design philosophy
furry engine is designed around fast compile times, (relatively) clean code, and not fucking deviating your septum. not fucking deviating from the rules i swear to god if you even TOUCH the rules i WILL rewrite your entire fucking MIND.  

rules i will not tolerate the breakage of:  
- language: no c++
- every module has a state struct
- no fucking implementations in the headers, i swear to god

paerperrperr (i forgot the word precedence):
- readability over performance (mostly in the headers, depends on just how bad it is in main source)
- minimal dependencies. do not fucking add anything.

## when designing a feature
when designing a feature, first define how you want the user to interact and interface with it. this makes it so you can have a clear way of how the user should use it, and if you are lazy, thats really good, please be lazy, because you want the user to not have to type 5 fucking paragraphs when drawing a rectangle.

## license
this project is licensed under the LGPLv3 copyleft,  
for more information, see [here](LICENSE.LGPL)

## todo
- reimplement render targets
