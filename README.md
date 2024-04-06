# Series of examples of apps in GTK and C

I am gonna use this repo to dump examples of stuff I learn while exploring the GTK interface library

**The command to install GTK on Debain**
` ~ sudo apt install libgtk-4-dev`

**This is the command from the source code**

```
gcc $( pkg-config --cflags gtk4 ) -o example-2 example-2.c $( pkg-config --libs gtk4 )
```

**This command also works to compile the app**

```
$ example-01 ( main) gcc -o example-0 example-0.c `pkg-config --cflags --libs gtk+-3.0`
```

**The tutorial from the doc**

`https://docs.gtk.org/gtk4/getting_started.html#building-applications`
