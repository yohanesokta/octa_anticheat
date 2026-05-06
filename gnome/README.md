> GNOME is using gnome-shell, which is a graphical shell for the GNOME desktop environment. to acess the window title, we can use the `xprop` command to get the window properties, including the title. and cant use `xdotool` to get the active window title, because it may not work properly with gnome-shell. instead, we can use `xprop` to get the active window title by using the following command:

```bash
xprop -root | grep "_NET_ACTIVE_WINDOW(WINDOW)" | awk '{print $5}'
```
