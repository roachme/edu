seq: 1-st writing<br/>
lvl: B1 or lower<br/>
date: Fri, Nov 13, 2020<br/><br/>


> some notes..

I decide to make my database (db) simple not because of its education purpose. If I cannot simply express my thoughts and ideas in C code 
then it means I've cheated, don't understand it all that's why just wanna finish.It's not good. Don't be too judgemental because it's just my first writing.<br/><br/>


> idea expl

I devide project into some layers, make each one complete and independent. (like browser plugins: you need it, plug it and that's it. and vice versa).
Inside of db you can find a lot of code what handles errors, queries, read and write data, etc. In order to make your code useable from others (and yourself of cource)
you have to represent code like collection of node (each one's responsible just for one conrete task) and organize it like tree data structure. That's the secret of
transferring ideas into code that  defenetly will make sense. 


![orogram srtucture](../.doc/prog_struct.jpg)


<br/><br/>

In the buttom of tree you can a lot of nodes that's far away from db idea in your head. And in top you see easy and lightwieght interface - how you wish
db should look like. It's how exactly I implemented it.

> tech part

The layers do in next order: <br/>

UI      <br/>
engine  <br/>
input   <br/>
query   <br/>
output  <br/>
dev     <br/><br/>


`UI` is user interface. There are two type: CLI and GUI (second is under development). This layer provides well-known commands like select, query, 
add and delete row, etc.
<br/>

`engine` is implmenetation of abow commands, hence the name
<br/>

`input` is for correct reading of user input, numbers, string, queries. without this layer our db will process wrong data which leads us program crash.
<br/>

`query` is layer for performing queries like MySQL. Currently can perform only `select`. Status - under development.
<br/>

`output` is same as input, but used to make output format more friendlty and costomeable.
<br/>

`dev` is layer for reading from and writing to .db file. we can change data during program execution and then save them into file using it
<br/>






