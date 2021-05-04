The goal of L would be to piggy back off of english to make writing code and reading code easy.

## First objective: Eliminate the dot operator

`person.name` becomes `person name` Ik you're like, "Whaaaat? You can't do that!". Hold up, I'll explain

## Second objective: No more functions, only template sentence definitions

`function multiply(int a, int b){return a*b}` becomes `define multiply $1 * $2`

So, no more functions. That doesn't mean it's the same as a preprocessor define. Every time the sentence identifier is seen, it just replaces the identifier with the definition, then it replaces single character words with their respective argument. Theoretically this also enables you to pass sentences into other sentences without too much hassle. If you wanted to make a recursive function, you could do `define recursion recursion`(If I wanted to make a real recursive statement, I would need control flow which I haven't thought about yet).

## Third objective: Functions get called like operators

So `str.equals(phrase)` becomes `str equals phrase`

Already this is a huge improvement. Operator style readability is the main thing driving this language.

### Third objective part 2: Parentheses no longer call functions

So that makes parentheses mean what they literally mean in math: "Do this first".

Parentheses would be used solely to reorder precedence, because `str equals person name` would mean `str.equals(person).name`, when you really meant`str equals (person name)` which is `str.equals(person.name)`

You'd think that because I have to explain it in code it's more complicated, but if you go back over it without looking at the code, it makes sense. I don't have to get into how this functionless language works off of functional progamming theory and monads(which these things aren't really, but that still kind of furthers my point) or any other theory gargon to try to explain it. I can just show that the syntax works and let it speak for itself.

## Fourth objective: Wherever you'd use a semicolon, you can use a period

Yes, I'm bringing back the dots.

Just like how sentences end with periods, your lines of code could end with periods.

Note that I'm leaving the option to use semicolons. Sometimes it's gramatically correct to use a semicolon in some cases, especially if you want to put 2 statements on one line, like in for loops.

## Fifth objective and arguably the most complicated: No more assignment operator.

So
```java
String bruh = "";
```
becomes
```
String bruh "".
```
or probably more commonly,
```
String bruh ("").	//Almost looks like c++, yeah?
```

That's because later on, you might want to set a variable to something, so you would use
```
bruh (person name + " the third").
```

If you have two variables next to each other, then the left one gets set to the one on the right.

## Sixth and objectively easier than the last thing: Allow for the type to be removed if it is set to a typed value.

So `String bruh ""` becomes `bruh ""`

It makes it a lot harder to read, but some people don't like to think about types and footgun themselves. Good practice always has the type, but without it is the same as `auto`.

#How would all of this work? Wouldn't that be a compiler nightmare?

Yes, and yet it's possible. It would be easier to start it off as some sort of BrainF*ck style scripting language, so not too ambitious, and then later think of a way to make a compiler.

In all likelyhood, this thing is going to compile into c (or c--) and then that compiles into assembly, so it will take twice as long to compile, but that doesn't matter.

Words can only really be four things:
	1. Type names/Name spaces
	2. Variables
	3. Operators
	4. Not assigned yet

Typename rules		//Be aware, when I say "next to" I mean to the left of.

If a typename is next to a typename, crash.
If a typename is next to some variables, it constructs a variable from those variables.
If a typename is next to an operator, check if it is in the typename namespace. Find the definition, and treat the whole thing as an operator.
If a typename is next to something that isn't assigned yet, create a variable with that word as its identifier.

Variable rules

If a variable is next to a typename, crash.
If a variable is next to a variable, check to make sure that the thing on the right is the same type, then set the variable to the value of the thing on the right.
If a variable is next to an operator, check to see if the operator is in the namespace of the variable, or if it's global. Else, crash.
If a variable is next to something that isn't assigned yet, crash.

Operators rules

If an operator is next to a typename, crash.
If an operator is next to a variable, check to make sure that the thing on the right matches the operator signature, then do whatever operators do.
If an operator is next to an operator, check to see that the operator has an operator in the signature, then do whatever operators do.
If an operator is next to something that isn't assigned yet, crash.

Not assigned yet rules

If the thing to the right evaluates to a value, copy the type of that value and the value and make a new variable.
Else, Either crash, or skip it as a sort of comment or grammar word.

A bit of an internal thing, but

If a typename is next to a comma, make a tuple of typenames.
If a variable/operator is next to a comma, make a tuple of variables/operators.

Because of the whole auto thing and how I am doing functions initially (and quite ingeniously), I might not need function types which could save a lot of time coding.
