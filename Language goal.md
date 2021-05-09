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

# How would all of this work? Wouldn't that be a compiler nightmare?

Yes, and yet it's possible. It would be easier to start it off as some sort of BrainF\*ck style scripting language, so not too ambitious, and then later think of a way to make a compiler.

I couldn't wrap my head around how this would work, mainly because I was thinking of having a single stack with some sort of object inheritance.

In CS they talk about prefix and postfix (aka polish and reverse polish) and infix. Prefix looks like `* - 5 6 7`, postfix looks like `7 5 6 - *` and infix looks like `(5-6)*7`. 

The reason why reverse polish notation (postfix) is useful is because you can use a single stack for your variables as long as your operators have everything they need before they are called. If you see a number, just push it onto the stack, and if you see an operator, pull the nessesary amount of variables off of the stack. This makes RPN (postfix) the easiest notation to code.

So how would prefix be solved? It's a bit harder because the operators need to wait for the right amount of operands before they go away. Easiest thing to do is to just convert to postfix by flipping the order around. So `* - 5 6 7` becomes `7 6 5 - *`. That still isn't right because the minus isn't commutative, so you just need to define the minus operator with the operands reversed. That is just a hackish way of doing it which can't live eval because it has to wait until the entire line is typed for it to be reversed, then it can start evaluating. Live eval for an infix language is impossible because you would need an engine to do both postfix and prefix.

If you wanted to have a live eval for prefix, your operators would be held on the stack and your variables would be held in a queue. However, the weird bit is that when a operator has what it needs, it grabs those variables and replaces it with the return, placing the return variable at the front of the queue, breaking the queue.

The way javascript implements queues is with an array. Arrays have `push` and `pop` methods that implement the functionality of a stack. Push puts things on the top and pop pops off the top of the queue. The method they use to get data off the bottom is called `shift` aka dequeue or remove. So stacks use push and pop and queues use push and shift. If you want to push something to the front of the queue, you use the function `unshift` which takes an element. It basically does the opposite of what `shift` aka dequeue or remove does. So we need something like that.

Singly linked lists give the functionality of a stack, but for a queue, they need to know where the front of the queue is to remove stuff and the back of the queue to add stuff. Otherwise you have to find the front every time you remove something and find the back every time you add something, which does a loop through all the elements every single time(for one of those at least). Using a doubly linked list solves that, but at the same time those are a pain and take up more space than I'd like.

So in summary, my entire language problem can be summed down into making a doubly linked list, which isn't hard but just tedious.

But after I do that, basically I got a stack for my operators, and a doubly linked queue with an unshift for the operands. After I do that, I basically feed the operands into the operator on the top and it's done. Here's what would happen if I ran that sample prefix problem with my live eval prefix solver.

```
* - 5 6 7
Operator stack and variable queue:
1. '*'	["*"]				[] 
	"*" doesn't have what it needs

2. '-'	["*","-"]			[]
	"-" doesn't have what it needs

3. '5'	["*","-"]			[5]
	"-" doesn't have what it needs

4. '6'	["*","-"]			[5,6]
	"-" has what it needs, the 5 and the 6
	It takes those off the queue and uses operates
	It returns a number that gets unshifted back onto the stack
	["*"]			[-1]
	
5. '7'	["*"]			[-1,7]
	"*" has what it needs, a -1 and a 7
	It takes those off the queue and uses operates
	It returns a number that gets unshifted back onto the stack
	[]			[-7]
```

But here's the kicker, let's try running the postfix problem on my prefix solver.

```
7 5 6 - *
Operator stack and variable queue:
1. '7'	[]				[7] 
	There are no operators to operate with

2. '5'	[]			[7,5]
	There are no operators to operate with

3. '6'	[]			[7,5,6]
	There are no operators to operate with

4. '-'	["-"]			[7,5,6]
	"-" has what it needs, the 7 and the 5
```

Well darn, I really thought that was going to work. How about, if an operator is pushed to the stack and it has everything it needs, it pops the variables off of our ugly queue-stack. (I don't really do this in the program, just trying to prove a terrible point)

```
7 5 6 - *
Operator stack and variable queue:
1. '7'	[]				[7] 
	There are no operators to operate with

2. '5'	[]			[7,5]
	There are no operators to operate with

3. '6'	[]			[7,5,6]
	There are no operators to operate with

4. '-'	["-"]			[7,5,6]
	"-" has what it needs, the 5 and the 6
	It takes those off the queue and uses operates
	It returns a number that gets unshifted back onto the stack
	[]			[-1]
	
5. '7'	["*"]			[-1,7]
	"*" has what it needs, a -1 and a 7
	It takes those off the queue and uses operates
	It returns a number that gets unshifted back onto the stack
	[]			[-7]
```

Anyways, the reason I'm hammering on this is because I said that if there was an engine that could solve both prefix and postfix, infix would possible. My language is trying to have infix operators all over the place, so let's try it out on the solver.

```
5 - 6 * 7	//Screw your order of operations, use parentheses if you don't want this
Operator stack and variable queue:
1. '5'	[]				[5] 
	There are no operators to operate with

2. '-'	["-"]			[5]
	"-" doesn't have what it needs

3. '6'	["-"]			[5,6]
	"-" has what it needs, the 5 and the 6
	It takes those off the queue and uses operates
	It returns a number that gets unshifted back onto the stack
	[]			[-1]

4. '*'	["*"]			[-1]
	"*" doesn't have what it needs
	
5. '7'	["*"]			[-1,7]
	"*" has what it needs, a -1 and a 7
	It takes those off the queue and uses operates
	It returns a number that gets unshifted back onto the stack
	[]			[-7]
```

Luckily for me, infix doesn't have more than 1 variable behind an operator, so I don't need to do that weird thing with the postfix. I don't even know how doing that reverse thing with 3 variables would work, let alone 2 behind the operator and 1 in front. If it comes down to it, I can just store the index of the words when they are pushed so when an operator needs to order them it can reorder them in relation to its own index. I'm probably going to start a second repo for this, actually do this in js, then go back to c and do it with words. That way I'll know exacly how that popping of the front of the queue thing would work.
