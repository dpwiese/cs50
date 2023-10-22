# CS50 Section 26-October-2014

* IP address is unique identifier
* Rules for computers and servers interacting:
  * TCP - transmission control protocal
  * IP
* These two cover how me and servers interact
* Protocol is the generally accepted thing to do when the computers and servers communicate together - the basic rules of how communication works
* Another thing TCP does: webpages are pretty big. how do you make sure it all gets to the other end? Thats what TCP does.
* HTTP is another protocal. used for actual webpages.
* other things on internet:
  * FTP
  * Telnet
* See study50 slides on HTTP
* hypertext is how websites are defined. A set of rules that tells web browser what is a link, header, entire layout of page etc. Basically the blueprints of the page that browser
can assemble into something we can
* Hyper Text:
  * Developer tools take the source and can slightly interpret it to provide indentations and stuff to make it easier to look at
  * tags are enclosed in angle brackets
* Transfer Protocal: consists of requests and responses.
  * curl - make web requests from command line without using a browser
  * EX: `curl www.google.com`
* `ls -l` (I think l stands for long)
* first thing is a d if its a directory, otherwise its not
* next set of three rwx
* r - read
* w - write
* x - executre
* groups:
  * user
  * users in your user group
  * everyone
* By default when we create a file: `-rw-------` only we can read it and write it, no one else can
* Need to make sure permissionas are correct
* Use change mode tool: chmod
* EX: make `index.html` viewable to everyone
* (each group of three is its own octal byte)
* Don't give things execute permission unless they actually are a program
  * rw- = 110 = 6
  * r-- = 100 = 4
  * r-- = 100 = 4
  * `chmod 644 index.html`
* Tags give more info about what is to be displayed
* HTML IS WHAT THINGS SHOULD LOOK LIKE
* CSS IS HOW THINGS SHOULD LOOK
* In CSS there are three parts?
* Tag with list of different rules

```css
tag {
    rule1
    rule2
}
```

* html ignores newlines
* Classes in html: way to identify certain things
* Comma separates in CSS
* space nests
* tbody tr
* th, td
* Class and ID can go with any tag
* Class and ID are things we just make up to identify it to ourselves
* Difference between ids and classes
* IDs need to be unique on the page, classes dont!
* `.` in front of tag in CSS thing says look for class. eg: `.best`
* Conflicts of rules with CSS?
  * It picks whichever one is most specific and uses that and overrides
* Pretty much everything: `644`
* PhP programs: `600`
* Directories: `711`
