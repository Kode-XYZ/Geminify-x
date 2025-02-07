# gplaces - a simple terminal Gemini client

Because Gemini deserves a light client with a high power to weight ratio!

gplaces is named after Going Places, the 1965 album by Herb Alpert and The Tijuana Brass. The "o" is omitted from the executable name so it doesn't mess up tab completion for Gopher users and Go developers.

=> https://en.wikipedia.org/wiki/Going_Places_(Herb_Alpert_and_the_Tijuana_Brass_album) Going Places

The gplaces logo is an artist's impression of a Gemini VII capsule with the red accents of a Humes and Berg Stonelined straight trumpet mute. Sort of.

=> https://humesandberg.com Humes and Berg

gplaces is originally a Gemini port of the delve Gopher client by Sebastian Steinhauer.

=> https://github.com/kieselsteini/delve delve

## Features

* SSH-style TOFU with $XDG_DATA_HOME/gplaces_hosts or ~/.gplaces_hosts
* client certificates support via $XDG_DATA_HOME/gplaces_$host_$port_$path.{crt,key} or ~/.gplaces_$host_$port_$path.{crt,key}
* subscriptions
* permanent redirects with $XDG_DATA_HOME/gplaces_redirects or ~/.gplaces_redirects
* support for non-interactive operation
* single configuration file: $XDG_DATA_HOME/gplacesrc, ~/.gplacesrc or /etc/gplacesrc
* configurable MIME type handlers, with support for streaming to stdin
* "powerful" shell with tab completion, hints and aliases
* VT100 compatible with ANSI escape sequences and NO_COLOR support
* sh-style history with $XDG_DATA_HOME/gplaces_history or ~/.gplaces_history
* UTF-8 word wrapping
* configurable external pager
* optional Titan support
* optional Gopher support
* optional gophers:// (Gopher+TLS+TOFU) support
* optional Spartan support
* optional Finger support
* optional Guppy support
* small, hackable codebase
* no exotic external dependencies, no NIH: bestline, openssl or libressl, libcurl, libidn2 or libidn (optional) and libmagic (optional)
* ~100K executable when built with -O3 and -Wl,-s on x86_64

## How to install?

* Using Flatpak: `flatpak install com.github.dimkr.gplaces`
* compile yourself

=> https://flathub.org/apps/details/com.github.dimkr.gplaces gplaces on Flathub

## How to compile?

* clone this repo: `git clone --recursive https://github.com/dimkr/gplaces`
* type `cd gplaces`
* type `make PREFIX=/usr CONFDIR=/etc`, or `make WITH_TITAN=0 WITH_GOPHER=0 WITH_GOPHERS=0 WITH_SPARTAN=0 WITH_FINGER=0 WITH_GUPPY=0 WITH_LIBIDN2=0 WITH_LIBIDN=0 WITH_LIBMAGIC=0` to disable all optional dependencies and features
* type `make install` to install it on the system (defaults to /usr/local)

## How to use?

```
    > gemini.circumlunar.space
```

to show a Gemini page, type its URL, press `ENTER` and gplaces will stream the page contents to the terminal.

to abort the download, press `CTRL+c`.

when the download is finished, gplaces will display the downloaded page using less(1), the same tool man(1) uses to display man pages.

```
    `less -r` has exited with exit status 0
    gemini.circumlunar.space/> 
```

use the arrow keys to scroll, `/` to search and `q` to exit less and return to the gplaces prompt.

```
    (reverse-i-search `g') gemini.circumlunar.space
```

in addition, gplaces adds the page URL to the history: use the `Up` and `Down` keys to navigate through the history, or `CTRL+r` to search through it. these are only three examples of key bindings from shells like bash(1) which work in gplaces, too: see bestline/README.md for a list of navigation and editing shortcuts.

```
    cached 2023-04-29 19:41:44
    gemini.circumlunar.space/> 
```

if you visit the same page again, gplaces will return a cached copy and show the time the page was fetched. gplaces remembers up to `histsize` pages, so you can return to previously viewed pages immediately, without downloading them again. type `get` and press `ENTER` to force gplaces to fetch a cached page again.

```
    > gemini://konpeito.media/konpeito-09-a.mp3
```

gplaces displays only Gemtext, gophermaps or plain text files: it downloads other kinds of files (like images, audio and video) to temporary files and runs external "handler" programs (one for each file type) defined in the gplaces configuration file.

```
    > save gemini.circumlunar.space/docs/specification.gmi
    enter filename: /home/user/Downloads/specification.gmi
```

to download a file instead of displaying it or saving it to a temporary file, type `save`, followed by its URL, then press `ENTER`.

```
    > save gemini.circumlunar.space/docs/specification.gmi /tmp/spec.gmi
```

you can also specify the destination path and skip the prompt.

```
    > save gemini://konpeito.media/konpeito-09-a.mp3 -
```
 
alternatively, to stream a file into standard input of the handler program without saving to a file on disk and waiting for the download to complete, use `-` as the download destination. this is useful for audio or video streaming, and works only with some programs and some file formats.
 
```
    gemini.circumlunar.space/> 2 docs/
```

gplaces associates a number with each link in the last viewed page. type the number of a link to show its URL, then press `ENTER` to follow it.

to edit the URL of a link, type the link number, press `Tab`, edit the URL and press `ENTER`. for example, this is useful if a link leads to a post in another gemlog, but you want to see its homepage.

```
    gemini.circumlunar.space/> #gemini://gemini.circumlunar.space/docs/
    gemini.circumlunar.space/> 
```

the history can be used as a reading list: prefix a URL with `#` and press `ENTER` to add it to the history without opening it first. for example, to add the URL of link 2 to the history, type `2`, press `Tab` to edit the URL, press `CTRL+a` or `Home` to go to the beginning of the line, type `#` and press `ENTER`. to open this URL later, press the `Up` key, press `CTRL+a` or `Home`, press `Delete` to remove the leading `#`, then press `ENTER`.

```
    gemini.circumlunar.space/docs/> save 2
    enter filename (press ENTER for `/home/user/Downloads/specification.gmi`):
```

this number can be used to download the link, too.

```
    gemini.circumlunar.space/docs/> search
    Search query> gplaces
```

the gplaces configuration file allows you to define short aliases for URLs you visit often. for example, the default configuration file defines the `home` alias for the Gemini project homepage and the `search` alias for a Gemini search engine. type `search` and press `ENTER` to search geminispace.

```
    > geminispace.info/search gplaces
    > search gplaces
    > search "gemini client"
```

if a URL accepts input, you can specify the input in a second argument, to avoid another request to the same URL and skip the prompt. this works with aliases, too.

to show a feed of new posts, type `sub`, then press `ENTER`. the list of URLs gplaces is "subscribed" to is defined in the configuration file.

to exit gplaces, press `CTRL+d`.

additional documentation and more details are available in `man gplaces`. type `help` and press `ENTER` to see short descriptions of available commands.

## How to configure?

if installed through Flatpak, copy the read-only configuration file to your home directory so you can edit:

```
    ~$ flatpak run --command=sh com.github.dimkr.gplaces
    ~$ cp /app/etc/gplacesrc $XDG_CONFIG_HOME/
    ~$ exit
    ~$ xdg-open ~/.var/app/com.github.dimkr.gplaces/config
```

otherwise, you can edit /etc/gplacesrc directly or edit a copy under your home directory:

```
    ~$ cp /etc/gplacesrc $XDG_CONFIG_HOME/
    ~$ xdg-open $XDG_CONFIG_HOME/gplacesrc
```

## License

=> LICENSE GPLv3
