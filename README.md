ICI
===

ICI is both a language targeting configuration files and its implementation in Qt, 
using the not well-known nor documented, yet fantastic, qlalr [http://qt.gitorious.org/qt/qlalr]

Aims
---
 * A minimalist (not Turing-complete) language to write simples and powerful configuration files
 * Use a syntax somehow similar to the INI format, hence the name
 * Can declare variables, list, maps
 * Boolean logic to tune the configuration based on a pre-existing context
 * Extensible through functions

Language specifications
-----------------------
    #numbers
    pi= 3.14
    univers= 42
    
    #strings
    mystring = 'hello'
    mystring = "a \"small\" string" #one can owerwrite variables and put quotes inside strings
    raw_string="""
    #include<iostream>
    int main()
    {
        std::cout << "Hello, new world!\n";
    }
    """
    
    #lists
    list = ["hello", 42, string]  #refer to other variables
    list += "foo" #list can be extended
    list -= "foo" #remove something from a list

    #maps
    map = {}
    map = {foo:"bar", bar:{"foo}}
    
    #that's a function. you can create your own using the c++ api
    test = contains(list, 42);
    
    #logical expressions.
    if equals(test, true){
        mystring = "let's put ${mystring} here !" #use variables inside strings
    }
    else {
       a.b.c = list # there we have created a map, containing a map, containing a list
       list += a.b.c # a list, containing a map, containing a map, containing a list
       a = null # that was silly right, never mind, we can destroy all that
       list = null
    }
    #complex expressions
    if !equals(foo, 42) or (equals(bar, 42) and equals(1,2,3))
       var = "look, no brackets !"

C++/Qt api
-----

	//load a file
	ICISettings settings(path);
	if(settings.hasError()){
		// handle parsing errors
		qDebug() << settings.errorString();
	}
	else {
		// you can prepare an initial context
		settings.setValue("foo", "bar");
		if(settings.evaluate()){
			 QVariant baz = settings.value("baz");
			 if(settings.contains("a.b.c"){ // fetch map value easily
				 QVariant map = settings.value("a.b.c");
			 }
		}
	}
Adding functions
----------------
	QVariant hello(ICISettingsContext* ctx) {
		if(ctx->args().size !=1 )
			ctx->setErrorMessage("hello takes exactly one argument");
		else
			return "hello " + ctx->args().at(1).toString();
		return QVariant();
	}

	ICISettings settings("foo = hello('foo')");
	settings.createFunction("hello", hello);
	settings.evaluate();
	//settings.value("foo"); == "hello foo"
