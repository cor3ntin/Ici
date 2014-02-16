Add the following in ~/.nanorc
    syntax "ici" "\.(ici|conf)$"
    color brightyellow "([0-9a-zA-Z_]+)\s*\("
    color brightyellow "\}"
    color brightcyan "\<(and|\!|or|if|else|include|unset|null|true|false)\>"
    color brightgreen "['][^']*[^\\][']" "[']{3}.*[^\\][']{3}"
    color brightgreen "["][^"]*[^\\]["]" "["]{3}.*[^\\]["]{3}"
    color yellow "\$\{.*\}"
    color brightgreen start=""""[^"]" end=""""" start="'''[^']" end="'''"
    color brightred "#.*$"
    #ici + pyratemp template engine
    color brightmagenta start="@\!" end="!@"
    color magenta "##!.*$"
